#include "stdafx.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "mapData.h"

HRESULT playerManager::init(int num)
{

		//_player = new player;
		_playerChange[0] = new player;
		_playerChange[0]->init(0);
		_playerChange[1] = new player;
		_playerChange[1]->init(1);

		_rambroChange = false;

		_player = _playerChange[_rambroChange];
		_player->setRcRambro(_player->getRcRambro());

		_pBullet = new pBullet;
		_pBullet->init(700.f);
		_pGrenade = new pGrenade;
		_pGrenade->init(500.f);
		_gBullet = new gBullet;
		_gBullet->init(400.f);
		_gMissile = new gMissile;
		_gMissile->init(2000.f);
		_xMissile = new xMissile;
		_xMissile->init(2000.f);

		_p1Bubble = IMAGEMANAGER->findImage("p1Bubble");
		_p1Bubble->setX(_player->getX() + _player->getImage(_player->getState())->getFrameWidth() / 2 - _p1Bubble->getFrameWidth() / 2);
		_p1Bubble->setY(_player->getY() - 100);

		_rcKnifeRight = RectMake(_player->getX() + 60, _player->getY() + 30, 30, 30);
		_rcKnifeLeft = RectMake(_player->getX() - 20, _player->getY() + 30, 30, 30);

		hit_left = hit_right = hit_top = hit_bottom = false;

		_index = _count = 0;
		_animationSpeed = 5;

		_fireCount = 0;
		_grenadeCount = 0;
		_missileCount = 0;

		_knifeCollision = false;
		_isLadder = false;
		_rambroFire = false;
		_rambroGrenade = false;
		_isGrenade = false;
		_xMissileCollision = false;
		_xMissileColl = false;
		_isMissile = false;
		_missile = false;
		_isGameover = false;

		_rc8 = RectMake(500.f, 2100.f, 60, 60);
		//_rcMissileRight = RectMake(100.f, 1000.f, 100, 10);
		//_rcMissileLeft = RectMake(1500.f, 1000.f, 100, 10);

		_player->setrcSkyRight(_player->getrcSkyRight());
		_player->setrcSkyLeft(_player->getrcSkyLeft());
	

	return S_OK;
}

void playerManager::release(void)
{
	SAFE_DELETE(_player);
	_pBullet->release();
	_pGrenade->release();
}

void playerManager::update(void)
{
	_player->update();
	_player->setOldX(_player->getX());
	_player->setOldY(_player->getY());
	_player->setRcRambro(_player->getRcRambro());
	_player->setrcSkyRight(_player->getrcSkyRight());					// 오른쪽 하늘에 총알집
	_player->setrcSkyLeft(_player->getrcSkyLeft());						// 왼쪽 하늘에 총알집
	_player->setrcFlashRight(_player->getrcFlashRight());				// 총구 오른쪽 플래쉬 렉트
	_player->setrcFlashLeft(_player->getrcFlashLeft());					// 총구 왼쪽 플래쉬 렉트

	float knifeRightX = _player->getX() + 60;
	float knifeRightY = _player->getY() + 28;
	float knifeLeftX = _player->getX() - 30;
	float knifeLeftY = _player->getY() + 28;

	_rc8 = RectMake(20.f, 2100.f, 60, 60);
	//_rcMissileRight = RectMake(100.f, 1500.f, 100, 10);
	//_rcMissileLeft = RectMake(1500.f, 1500.f, 100, 10);

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_player->setIsLeft(true);

		if (_isLadder)
		{
			_player->setX(_player->getX() - _player->getSpeed());
		}
		else
		{
			if (JUMP != _player->getState()
				&& HANG_FRONT_HOLD != _player->getState()
				&& HANG_BACK_HOLD != _player->getState())
			{
				_player->setState(RUN);
			}
			if (!hit_right)
			{
				if (_player->getX() > 0)
				{
					_player->setX(_player->getX() - _player->getSpeed());
					_player->setSkyRightX(_player->getSkyRightX() - _player->getSpeed());
					_player->setSkyLeftX(_player->getSkyLeftX() - _player->getSpeed());
				}
			}
			hit_left = false;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player->setIsLeft(false);

		if (_isLadder)
		{
			_player->setX(_player->getX() + _player->getSpeed());
		}
		else
		{
			_player->setIsLeft(false);
			if (JUMP != _player->getState()
				&& HANG_FRONT_HOLD != _player->getState()
				&& HANG_BACK_HOLD != _player->getState())
			{
				_player->setState(RUN);
			}
			if (!hit_left)
			{
				_player->setX(_player->getX() + _player->getSpeed());
				_player->setSkyRightX(_player->getSkyRightX() + _player->getSpeed());
				_player->setSkyLeftX(_player->getSkyLeftX() + _player->getSpeed());
			}
			hit_right = false;
		}
	}

	_fireCount++;
	if (KEYMANAGER->isStayKeyDown('Z'))							// 기본 총알 발사
	{
		if (!_rambroFire)						// rambro 전용
		{
			if (_player->getIsLeft())
			{
				_player->setIsFlash(true);
				_player->setGun(RUN_GUN);
			}
			else
			{
				_player->setIsFlash(true);
				_player->setGun(RUN_GUN);
			}

			if (_fireCount % 5 == 0)
			{
				if (!_player->getIsLeft())					// 오른쪽
				{
					_pBullet->fire(_player->getX() + 60, _player->getY() + 38, 20, _player->getIsLeft());
				}
				else										// 왼쪽
				{
					_pBullet->fire(_player->getX(), _player->getY() + 38, 20, _player->getIsLeft());
				}
				EFFECTMANAGER->cartridge(_player->getX(), _player->getY(), _player->getIsLeft());			// 총알 탄피
			}
		}
		if (_rambroFire)								// chuck 전용
		{
			if (_player->getIsLeft())
			{
				_player->setIsFlash(true);
			}
			else
			{
				_player->setIsFlash(true);
			}

			if (_fireCount % 5 == 0)
			{
				if (!_player->getIsLeft() == false)					// 오른쪽
				{
					_gBullet->fire(_player->getX() + 60, _player->getY() + 38, 20, _player->getIsLeft());
				}
				else												// 왼쪽
				{
					_gBullet->fire(_player->getX(), _player->getY() + 38, 20, _player->getIsLeft());
				}
			}
		}
	}
	if (KEYMANAGER->isOnceKeyUp('Z'))									// Z키에서 손때믄 총구앞 이미지 제거용
	{
		_player->setIsFlash(false);
	}
	_pBullet->update();													// rambro 총알 업데이트 ( 무브 )
	_gBullet->update();													// chuck 총알 업데이트 ( 무브 )

	if (KEYMANAGER->isOnceKeyDown('C'))									// 칼빵
	{
		if (KNIFE != _player->getState())
		{
			if (!_player->getIsLeft())
			{
				_player->setState(KNIFE);
				_player->setIndex(0);
				_player->setCount(0);
				_knifeCollision = true;
			}
			else
			{
				_player->setState(KNIFE);
				_player->setIndex(_player->getImage(_player->getState())->getMaxFrameX());
				_player->setCount(0);
				_knifeCollision = true;
			}
		}
	}
	
	if (_knifeCollision)
	{
		_rcKnifeRight = RectMake(knifeRightX, knifeRightY, 30, 30);			// 칼빵용 오른쪽 렉트
		_rcKnifeLeft = RectMake(knifeLeftX, knifeLeftY, 30, 30);			// 칼빵용 왼쪽 렉트
	}
	else
	{

	}
	if (!_player->getIsLeft())
	{
		if (KNIFE == _player->getState() && (_player->getIndex() >= _player->getImage(_player->getState())->getMaxFrameX()))
		{
			_player->setState(IDLE);
			_knifeCollision = false;
		}
	}
	else
	{
		if (KNIFE == _player->getState() && (_player->getIndex() <= 0))
		{
			_player->setState(IDLE);
			_knifeCollision = false;
		}
	}
	//else if (KNIFE == _player->getState() && _player->getIndex())
	//{
	//	_player->setState(IDLE);
	//	_knifeCollision = false;

	//if (KNIFE == _player->getState())
	//{
	//	_player->setState(IDLE);
	//}
	//if (_startImg)
	//{
	//	_startCount++;
	//	if (_startCount % 30 == 0)
	//	{

	//		_player->getImage(5)->setFrameY(0);
	//		_player->getImage(5)->setFrameX(_startIndex);
	//		_startIndex++;

	//	}

	//	if (10 > _player->getImage(5)->getMaxFrameX())
	//	{
	//		_startIndex = 0;
	//		_startCount = 0;
	//		_startImg = false;
	//	}
	//}

	if (KEYMANAGER->isOnceKeyDown('X'))							// 수류탄
	{
		if (FIRE != _player->getState())
		{
			if (!_player->getIsLeft())
			{
				_player->setState(FIRE);
				_player->setIndex(0);
				_player->setCount(0);
			}
			else
			{
				_player->setState(FIRE);
				_player->setIndex(_player->getImage(_player->getState())->getMaxFrameX());
				_player->setCount(0);
			}
		}
		if (!_player->getIsLeft())								// 오른쪽
		{
			_pGrenade->fire(_player->getX() + 60, _player->getY() + 38, 20, _player->getIsLeft());
			_isGrenade = true;
		}
		else													// 왼쪽
		{
			_pGrenade->fire(_player->getX(), _player->getY() + 38, 20, _player->getIsLeft());
			_isGrenade = true;
		}
	}
	if (!_player->getIsLeft())
	{
		if (FIRE == _player->getState() && (_player->getIndex() >= _player->getImage(_player->getState())->getMaxFrameX()))
		{
			_player->setState(IDLE);
		}
	}
	else
	{
		if (FIRE == _player->getState() && (_player->getIndex() <= 0))
		{
			_player->setState(IDLE);
		}
	}

	if (_isGrenade)
	{
		_grenadeCount++;
	}
	if (_isMissile)
	{
		_missileCount++;
	}

	_pGrenade->update();										// 수류탄 업데이트 ( 무브 )
	_gMissile->update();										// chuck 핵간지 미사일 업데이트
	_xMissile->update();										// chuck 미사일 떨어지기전에 x미샬


	if (KEYMANAGER->isOnceKeyDown(VK_UP) && !_player->getIsJump())
	{
		if (!_isLadder)
		{
			//if (_player->getState() != HANG_FRONT_HOLD && _player->getState() != HANG_BACK_HOLD)
			//{
			_player->setState(JUMP);
			_player->setGravity(0.0f);
			_player->setJumpSpeed(20.f);
			_player->setIsJump(true);
			hit_left = false;
			hit_right = false;
			//}
			if (_player->getState() == HANG_FRONT_HOLD || _player->getState() == HANG_BACK_HOLD)
			{
				_player->setJumpSpeed(15.f);
				//_isLadder = false;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_isLadder)
		{
			_player->setY(_player->getY() - _player->getSpeed());
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_isLadder)
		{
			_player->setY(_player->getY() + _player->getSpeed());
		}
		else
		{

		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_player->setState(IDLE);
	}

	if (!hit_left && !hit_right && !_isLadder)
	{
		_player->setY(_player->getY() + (-sin(_player->getAngle())*_player->getJumpSpeed() + _player->getGravity()));
	}

	if (hit_left || hit_right && !_isLadder)
	{
		_player->setY(_player->getY() + 2);
	}

	RECT rcTemp;
	RECT rcPlayer;

	float tempX = _player->getX();
	float tempY = _player->getY();

	rcPlayer = RectMake(tempX, tempY, 65, 80);

	switch (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), _player->getGravity(), PLAYER_TOP, _isLadder))			// 위쪽 벽
	{
	case GREEN:
		if (_isLadder)
		{

		}
		else
		{
			_player->setGravity(0.f);
			_player->setJumpSpeed(0.f);
			_player->setIsJump(false);
			hit_left = false;
			hit_right = false;
			if (_player->getState() != JUMP && _player->getState() != HANG_FRONT_HOLD && _player->getState() != HANG_BACK_HOLD && _player->getState() == DIE)
			{
				_player->setState(IDLE);
			}
			if (_player->getState() != JUMP && _player->getState() != HANG_FRONT_HOLD && _player->getState() != HANG_BACK_HOLD && _player->getState() != IDLE && _player->getState() != RUN)
			{
				_player->setState(DIE);
			}
			hit_top = true;
		}
		break;
	case RED:
		//_player->setState(LADDER);
		_isLadder = true;
		break;
	case BLUE:
		if (_isLadder)
		{

		}
		else
		{
			_player->setGravity(0.f);
			_player->setJumpSpeed(0.f);
			_player->setIsJump(false);
			hit_left = false;
			hit_right = false;
			if (_player->getState() != JUMP && _player->getState() != HANG_FRONT_HOLD && _player->getState() != HANG_BACK_HOLD && _player->getState() == DIE)
			{
				_player->setState(IDLE);
			}

			hit_top = true;
		}
		break;
	default:
		_isLadder = false;
		break;
	}

	switch (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), _player->getGravity(), PLAYER_BOTTOM, _isLadder))		// 아래쪽 벽
	{
	case GREEN:
		if (_isLadder)
		{

		}
		else
		{
			_player->setGravity(0.f);
			_player->setJumpSpeed(0.f);
			_player->setIsJump(false);

			if (_player->getState() != RUN && _player->getState() != KNIFE && _player->getState() != HANG_FRONT_HOLD && _player->getState() != DIE)
			{
				hit_left = false;
				hit_right = false;
				_player->setState(IDLE);
			}
			if (_player->getState() != JUMP && _player->getState() != HANG_FRONT_HOLD && _player->getState() != HANG_BACK_HOLD && _player->getState() != IDLE && _player->getState() !=RUN)
			{
				_player->setState(DIE);
				_player->setY(_player->getY() + (-sin(_player->getAngle()) * _player->getJumpSpeed() + _player->getGravity()));
			}
			hit_bottom = true;
		}
		break;
	case RED:
		if (_player->getIsJump())
		{
			_isLadder = true;
		}
		//_player->setState(LADDER);
		//_isLadder = true;
		break;
	case BLUE:
		if (_isLadder)
		{

		}
		else
		{
			_player->setGravity(0.f);
			_player->setJumpSpeed(0.f);
			_player->setIsJump(false);

			if (_player->getState() != RUN && _player->getState() != KNIFE && _player->getState() != HANG_FRONT_HOLD)
			{
				hit_left = false;
				hit_right = false;
				_player->setState(IDLE);
			}
			if (_player->getState() != JUMP && _player->getState() != HANG_FRONT_HOLD && _player->getState() != HANG_BACK_HOLD && _player->getState() != IDLE)
			{
				_player->setState(DIE);
				_player->setY(_player->getY() + (-sin(_player->getAngle()) * _player->getJumpSpeed() + _player->getGravity()));
			}
			hit_bottom = true;
		}
		break;
	default:
		_isLadder = false;
		break;
	}

	if (_player->getIsJump())
	{
		hit_bottom = false;
	}

	switch (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), _player->getGravity(), PLAYER_RIGHT, _isLadder))			// 오른쪽 벽
	{
	case GREEN:
		if (_isLadder)
		{

		}
		else
		{
			if ((_player->getOldY() - tempY) < 0)
			{
				_player->setIsJump(false);
				_player->setGravity(0.f);
				_player->setJumpSpeed(0.f);
			}

			_player->setIsLeft(false);

			hit_right = true;
			hit_left = false;

			if (_player->getState() != JUMP && _player->getState() != HANG_FRONT_HOLD && _player->getState() != HANG_BACK_HOLD && _player->getState() != IDLE)
			{
				_player->setState(DIE);
				_player->setY(_player->getY() + (-sin(_player->getAngle()) * _player->getJumpSpeed() + _player->getGravity()));
			}
			//_player->setIsCollision(!_player->getIsCollision());

			//if (_player->getState() == JUMP)
			//{
			//	_player->setState(HANG_FRONT_HOLD);
			//}

			if (_player->getState() != HANG_FRONT_HOLD)
			{
				_player->setIsCollision(!_player->getIsCollision());
			}
		}
		break;
	case RED:
		if (_player->getIsJump())
		{
			_isLadder = true;
		}
		//_player->setState(LADDER);
		//_isLadder = true;
		break;
	case BLUE:
		if (_isLadder)
		{

		}
		else
		{
			if ((_player->getOldY() - tempY) < 0)
			{
				_player->setIsJump(false);
				_player->setGravity(0.f);
				_player->setJumpSpeed(0.f);
			}

			_player->setIsLeft(false);

			if (_player->getState() != JUMP && _player->getState() != HANG_FRONT_HOLD && _player->getState() != HANG_BACK_HOLD && _player->getState() != IDLE)
			{
				_player->setState(DIE);
				_player->setY(_player->getY() + (-sin(_player->getAngle()) * _player->getJumpSpeed() + _player->getGravity()));
			}

			hit_right = true;
			hit_left = false;

			//_player->setIsCollision(!_player->getIsCollision());

			//if (_player->getState() == JUMP)
			//{
			//	_player->setState(HANG_FRONT_HOLD);
			//}

			if (_player->getState() != HANG_FRONT_HOLD)
			{
				_player->setIsCollision(!_player->getIsCollision());
			}
		}
		break;
	default:
		break;
	}

	switch (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), _player->getGravity(), PLAYER_LEFT, _isLadder))			// 왼쪽벽
	{
	case GREEN:
		if (_isLadder)
		{

		}
		else
		{
			if ((_player->getOldY() - tempY) < 0)
			{
				_player->setIsJump(false);
				_player->setGravity(0.f);
				_player->setJumpSpeed(0.f);
			}
			_player->setIsLeft(true);

			if (_player->getState() != JUMP && _player->getState() != HANG_FRONT_HOLD && _player->getState() != HANG_BACK_HOLD && _player->getState() != IDLE)
			{
				_player->setState(DIE);
				_player->setY(_player->getY() + (-sin(_player->getAngle()) * _player->getJumpSpeed() + _player->getGravity()));
			}

			hit_left = true;
			hit_right = false;
			//if (_player->getState() == JUMP)
			//{
			//	_player->setState(HANG_FRONT_HOLD);
			//}

			/*if (_player->getState() != HANG_FRONT_HOLD)
			{
			_player->setIsCollision(!_player->getIsCollision());
			}*/
		}
		break;
	case RED:
		if (_player->getIsJump())
		{
			_isLadder = true;
		}
		//_player->setState(LADDER);

		break;
	case BLUE:
		if (_isLadder)
		{

		}
		else
		{
			if ((_player->getOldY() - tempY) < 0)
			{
				_player->setIsJump(false);
				_player->setGravity(0.f);
				_player->setJumpSpeed(0.f);
			}
			_player->setIsLeft(true);

			hit_left = true;
			hit_right = false;

			if (_player->getState() != JUMP && _player->getState() != HANG_FRONT_HOLD && _player->getState() != HANG_BACK_HOLD && _player->getState() != IDLE)
			{
				_player->setState(DIE);
				_player->setY(_player->getY() + (-sin(_player->getAngle()) * _player->getJumpSpeed() + _player->getGravity()));
			}
			//if (_player->getState() == JUMP)
			//{
			//	_player->setState(HANG_FRONT_HOLD);
			//}

			/*if (_player->getState() != HANG_FRONT_HOLD)
			{
			_player->setIsCollision(!_player->getIsCollision());
			}*/
		}
		break;
	default:
		break;
	}
	//if(true)
	//{
	//
	//}
	//else
	//{
	//	hit_left = false;
	//	hit_right = false;
	//
	//	if (_player->getState() == HANG_FRONT_HOLD)
	//		_player->setState(JUMP);
	//}
	if (hit_left && !hit_right && !hit_bottom && !_isLadder)
	{
		_player->setState(HANG_FRONT_HOLD);
	}
	else if (hit_right && !hit_left && !hit_bottom && !_isLadder)
	{
		_player->setState(HANG_FRONT_HOLD);
	}

	/*
	if (픽셀충돌) 총알 - 픽셀맵
	for (총알벡터)
	false 인 애들 continue
	for (맵벡터)
	if (렉트충돌) 총알 - 맵
	총알 isActived false로 바꾸고
	맵 deleteMap(i) 인가 써주고
	*/

	//플레이어와 오브젝트 충돌
	for (int k = 0; k < OBJECTMANAGER->getVObject().size(); k++)
	{
		if (OBJECT_DESTROY == OBJECTMANAGER->getVObject()[k]->getState()) continue;
		if (OBJECTMANAGER->getVObject()[k]->getType() == WOODENBOX || OBJECTMANAGER->getVObject()[k]->getType() == SKULL_DRUMGRAY || OBJECTMANAGER->getVObject()[k]->getType() == SKULL_DRUMRED ||
			OBJECTMANAGER->getVObject()[k]->getType() == PRISONER || OBJECTMANAGER->getVObject()[k]->getType() == AMERICAN_FLAG || OBJECTMANAGER->getVObject()[k]->getType() == HELICOPTER)
		{
			switch (OBJECTMANAGER->getVObject()[k]->getState())
			{
			case OBJECT_IDLE:
				//오브젝트와 플레이어가 충돌했을 때 (수류탄과의 충돌도 똑같이 해줘야 한다! +앵글 바꾸는것 더해줄것)
				if (IntersectRect(&temp, &_player->getRcRambro(), &OBJECTMANAGER->getVObject()[k]->getRect()) &&
					OBJECTMANAGER->getVObject()[k]->getType() != AMERICAN_FLAG && OBJECTMANAGER->getVObject()[k]->getType() != HELICOPTER)
				{
					int width = _player->getRcRambro().right - _player->getRcRambro().left;
					int height = _player->getRcRambro().bottom - _player->getRcRambro().top;

					if (_player->getRcRambro().left + width / 2 < temp.left)
						_player->setX(_player->getX() - (temp.right - temp.left)); //왼 쪽에서 부딪혔을 때
					else if (_player->getRcRambro().left + width / 2 > temp.right)
						_player->setX(_player->getX() + (temp.right - temp.left)); //오른쪽

					if (_player->getRcRambro().top + height / 2 < temp.top)
						_player->setY(_player->getY() - (temp.bottom - temp.top)); //위에서 눌러찍었을 때
					else if (_player->getRcRambro().top + height / 2 > temp.bottom)
						_player->setY(_player->getY() + (temp.bottom - temp.top));
				}
				if (IntersectRect(&temp, &_player->getRcRambro(), &OBJECTMANAGER->getVObject()[k]->getActivationRect()))
				{
					if (OBJECTMANAGER->getVObject()[k]->getType() == PRISONER)
						OBJECTMANAGER->getVObject()[k]->setIsActived(true);
					if (OBJECTMANAGER->getVObject()[k]->getType() == AMERICAN_FLAG || OBJECTMANAGER->getVObject()[k]->getType() == HELICOPTER)
					{
						OBJECTMANAGER->getVObject()[k]->setState(OBJECT_MOVE);
						//OBJECTMANAGER->getVObject()[k]->setFlagCount(OBJECTMANAGER->getVObject()[k]->getFlagCount() + 1);
					}
				}
				break;
			case OBJECT_MOVE:
				if (OBJECTMANAGER->getVObject()[k]->getType() == PRISONER)
				{
					if (IntersectRect(&temp, &_player->getRcRambro(), &OBJECTMANAGER->getVObject()[k]->getRect()))
					{
						//할아버지 등장 시점 
						_rambroChange = true;
						_playerChange[1]->init(1);
						_player = _playerChange[_rambroChange];
						_rambroFire = true;
						_rambroGrenade = true;
						OBJECTMANAGER->getVObject()[k]->setState(OBJECT_DESTROY);	
					}
					else
					{
						//OBJECTMANAGER->getVObject()[k]->setGravity(OBJECTMANAGER->getVObject()[k]->getGravity() + 0.55f);
						//OBJECTMANAGER->getVObject()[k]->setY(OBJECTMANAGER->getVObject()[k]->getY() + (-sinf(OBJECTMANAGER->getVObject()[k]->getAngle()) * OBJECTMANAGER->getVObject()[k]->getSpeed() + _vObject[i]->getGravity()));
						//OBJECTMANAGER->collisionProcess();
					}
				}
				if (OBJECTMANAGER->getVObject()[k]->getType() == AMERICAN_FLAG)
				{
					//부활 좌표 저장 시점
				}
				if (OBJECTMANAGER->getVObject()[k]->getType() == HELICOPTER)
				{
					//헬리콥터 사다리에 매달림
				}
				break;
			}
		}
	}

	// rambro bullet 
	for (int i = 0; i < _pBullet->getVPlayerBullet().size(); i++)  // 총알이랑 벽이랑 충돌하면 벽 지워주기
	{
		if (!_pBullet->getVPlayerBullet()[i].isActived)continue;
		for (int k = 0; k < OBJECTMANAGER->getVObject().size(); k++)
		{
			if (OBJECT_DESTROY == OBJECTMANAGER->getVObject()[k]->getState()) continue;
			if (OBJECTMANAGER->getVObject()[k]->getType() == WOODENBOX || OBJECTMANAGER->getVObject()[k]->getType() == SKULL_DRUMGRAY ||
				OBJECTMANAGER->getVObject()[k]->getType() == SKULL_DRUMRED || OBJECTMANAGER->getVObject()[k]->getType() == PRISONER)
			{
				switch (OBJECTMANAGER->getVObject()[k]->getState())
				{
				case OBJECT_IDLE:
					//총알과 박스/드럼통/감옥이 부딪혔을 때 (수류탄에도 똑같이 적용해 줄 것!)
					if (IntersectRect(&temp, &_pBullet->getVPlayerBullet()[i].rc, &OBJECTMANAGER->getVObject()[k]->getRect()))
					{
						if (OBJECTMANAGER->getVObject()[k]->getType() == WOODENBOX)
						{
							EFFECTMANAGER->woodDebris(OBJECTMANAGER->getVObject()[i]->getRect().left, OBJECTMANAGER->getVObject()[k]->getRect().top, _player->getIsLeft());
							OBJECTMANAGER->getVObject()[k]->setState(OBJECT_DESTROY);
						}
						else if (OBJECTMANAGER->getVObject()[k]->getType() == SKULL_DRUMGRAY || OBJECTMANAGER->getVObject()[k]->getType() == SKULL_DRUMRED)
						{
							EFFECTMANAGER->explosion(OBJECTMANAGER->getVObject()[k]->getRect().left, OBJECTMANAGER->getVObject()[k]->getRect().top);
							CAMERAMANAGER->CameraShake();
							OBJECTMANAGER->getVObject()[k]->setState(OBJECT_DESTROY);
						}
						else if (OBJECTMANAGER->getVObject()[k]->getType() == PRISONER)
						{
							EFFECTMANAGER->woodDebris(OBJECTMANAGER->getVObject()[k]->getRect().left, OBJECTMANAGER->getVObject()[k]->getRect().top, _player->getIsLeft());
							OBJECTMANAGER->getVObject()[k]->setState(OBJECT_MOVE);
						}
						EFFECTMANAGER->bulletPuff(_pBullet->getVPlayerBullet()[i].x, _pBullet->getVPlayerBullet()[i].y);
						_pBullet->getVPlayerBullet()[i].isActived = false;
					}
					break;
				case OBJECT_MOVE:
					break;
				}
			}
		}
		switch (COLLISIONMANAGER->pixelCollision(_pBullet->getVPlayerBullet()[i].rc,				// 왼쪽 벽에 충돌하면 벽 지워주기
			_pBullet->getVPlayerBullet()[i].x, _pBullet->getVPlayerBullet()[i].y,
			_pBullet->getVPlayerBullet()[i].speed, _pBullet->getVPlayerBullet()[i].gravity, PLAYER_LEFT))
		{
		case GREEN:
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (!_mapData->getObject()[j]._isActived)continue;
				if (IntersectRect(&temp, &_mapData->getObject()[j]._rc, &_pBullet->getVPlayerBullet()[i].rc))
				{
					_pBullet->getVPlayerBullet()[i].isActived = false;
					_mapData->deleteMap(j);
					if (_pBullet->getVPlayerBullet()[i].isActived == false)
					{
						EFFECTMANAGER->bulletPuff(_pBullet->getVPlayerBullet()[i].x, _pBullet->getVPlayerBullet()[i].y);
					}
					break;
				}
			}
			break;
		case RED:
			break;
		case BLUE:
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (!_mapData->getObject()[j]._isActived)continue;
				if (IntersectRect(&temp, &_mapData->getObject()[j]._rc, &_pBullet->getVPlayerBullet()[i].rc))
				{
					_pBullet->getVPlayerBullet()[i].isActived = false;
					_mapData->deleteMap(j);
					if (_pBullet->getVPlayerBullet()[i].isActived == false)
					{
						EFFECTMANAGER->bulletPuff(_pBullet->getVPlayerBullet()[i].x, _pBullet->getVPlayerBullet()[i].y);
					}
					break;
				}
			}
			break;
		default:
			break;
		}
		switch (COLLISIONMANAGER->pixelCollision(_pBullet->getVPlayerBullet()[i].rc,				// 오른쪽 벽에 충돌하면 벽 지워주기
			_pBullet->getVPlayerBullet()[i].x, _pBullet->getVPlayerBullet()[i].y,
			_pBullet->getVPlayerBullet()[i].speed, _pBullet->getVPlayerBullet()[i].gravity, PLAYER_RIGHT))
		{
		case GREEN:
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (!_mapData->getObject()[j]._isActived) continue;
				if (IntersectRect(&temp, &_pBullet->getVPlayerBullet()[i].rc, &_mapData->getObject()[j]._rc))
				{
					_pBullet->getVPlayerBullet()[i].isActived = false;
					_mapData->deleteMap(j);
					if (_pBullet->getVPlayerBullet()[i].isActived == false)
					{
						EFFECTMANAGER->bulletPuff(_pBullet->getVPlayerBullet()[i].x, _pBullet->getVPlayerBullet()[i].y);
					}
					break;
				}
			}
			break;
		case RED:
			break;
		case BLUE:
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (!_mapData->getObject()[j]._isActived)continue;
				if (IntersectRect(&temp, &_mapData->getObject()[j]._rc, &_pBullet->getVPlayerBullet()[i].rc))
				{
					_pBullet->getVPlayerBullet()[i].isActived = false;
					_mapData->deleteMap(j);
					if (_pBullet->getVPlayerBullet()[i].isActived == false)
					{
						EFFECTMANAGER->bulletPuff(_pBullet->getVPlayerBullet()[i].x, _pBullet->getVPlayerBullet()[i].y);
					}
					break;
				}
			}
			break;
		default:
			break;
		}
	}

	// chuck bullet 
	for (int i = 0; i < _gBullet->getVPlayergBullet().size(); i++)  // 총알이랑 벽이랑 충돌하면 벽 지워주기
	{
		if (!_gBullet->getVPlayergBullet()[i].isActived)continue;
		switch (COLLISIONMANAGER->pixelCollision(_gBullet->getVPlayergBullet()[i].rc,				// 왼쪽 벽에 충돌하면 벽 지워주기
			_gBullet->getVPlayergBullet()[i].x, _gBullet->getVPlayergBullet()[i].y,
			_gBullet->getVPlayergBullet()[i].speed, _gBullet->getVPlayergBullet()[i].gravity, PLAYER_LEFT))
		{
		case GREEN:
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (!_mapData->getObject()[j]._isActived)continue;
				if (IntersectRect(&temp, &_mapData->getObject()[j]._rc, &_gBullet->getVPlayergBullet()[i].rc))
				{
					_gBullet->getVPlayergBullet()[i].isActived = false;
					_mapData->deleteMap(j);
					if (_gBullet->getVPlayergBullet()[i].isActived == false)
					{
						EFFECTMANAGER->bulletPuff(_gBullet->getVPlayergBullet()[i].x, _gBullet->getVPlayergBullet()[i].y);
					}
					break;
				}
			}
			break;
		case RED:
			break;
		case BLUE:
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (!_mapData->getObject()[j]._isActived)continue;
				if (IntersectRect(&temp, &_mapData->getObject()[j]._rc, &_gBullet->getVPlayergBullet()[i].rc))
				{
					_gBullet->getVPlayergBullet()[i].isActived = false;
					_mapData->deleteMap(j);
					if (_gBullet->getVPlayergBullet()[i].isActived == false)
					{
						EFFECTMANAGER->bulletPuff(_gBullet->getVPlayergBullet()[i].x, _gBullet->getVPlayergBullet()[i].y);
					}
					break;
				}
			}
			break;
		default:
			break;
		}
		switch (COLLISIONMANAGER->pixelCollision(_gBullet->getVPlayergBullet()[i].rc,				// 오른쪽 벽에 충돌하면 벽 지워주기
			_gBullet->getVPlayergBullet()[i].x, _gBullet->getVPlayergBullet()[i].y,
			_gBullet->getVPlayergBullet()[i].speed, _gBullet->getVPlayergBullet()[i].gravity, PLAYER_RIGHT))
		{
		case GREEN:
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (!_mapData->getObject()[j]._isActived) continue;
				if (IntersectRect(&temp, &_gBullet->getVPlayergBullet()[i].rc, &_mapData->getObject()[j]._rc))
				{
					_gBullet->getVPlayergBullet()[i].isActived = false;
					_mapData->deleteMap(j);
					if (_gBullet->getVPlayergBullet()[i].isActived == false)
					{
						EFFECTMANAGER->bulletPuff(_gBullet->getVPlayergBullet()[i].x, _gBullet->getVPlayergBullet()[i].y);
					}
					break;
				}
			}
			break;
		case RED:
			break;
		case BLUE:
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (!_mapData->getObject()[j]._isActived)continue;
				if (IntersectRect(&temp, &_mapData->getObject()[j]._rc, &_gBullet->getVPlayergBullet()[i].rc))
				{
					_gBullet->getVPlayergBullet()[i].isActived = false;
					_mapData->deleteMap(j);
					if (_gBullet->getVPlayergBullet()[i].isActived == false)
					{
						EFFECTMANAGER->bulletPuff(_gBullet->getVPlayergBullet()[i].x, _gBullet->getVPlayergBullet()[i].y);
					}
					break;
				}
			}
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < _pGrenade->getVPlayerGrenade().size(); i++)			// 수류탄이랑 벽이랑 충돌하면 벽 지워주기
	{
		if (!_pGrenade->getVPlayerGrenade()[i].isActived)continue;

		if (COLLISIONMANAGER->pixelCollision(_pGrenade->getVPlayerGrenade()[i].rc,			// 아래쪽 벽
			_pGrenade->getVPlayerGrenade()[i].x, _pGrenade->getVPlayerGrenade()[i].y,
			20, _pGrenade->getVPlayerGrenade()[i].gravity, PLAYER_BOTTOM) == GREEN)
		{
			_pGrenade->getVPlayerGrenade()[i].gravity = 0;
			//_pGrenade->getVPlayerGrenade()[i].angle = PI2 - _pGrenade->getVPlayerGrenade()[i].angle;
			_pGrenade->getVPlayerGrenade()[i].speed *= 0.7f;

		}
		else if (COLLISIONMANAGER->pixelCollision(_pGrenade->getVPlayerGrenade()[i].rc,		// 위쪽 벽
			_pGrenade->getVPlayerGrenade()[i].x, _pGrenade->getVPlayerGrenade()[i].y,
			_pGrenade->getVPlayerGrenade()[i].speed, _pGrenade->getVPlayerGrenade()[i].gravity, PLAYER_TOP) == GREEN)
		{
			_pGrenade->getVPlayerGrenade()[i].angle = PI2 - _pGrenade->getVPlayerGrenade()[i].angle;
			_pGrenade->getVPlayerGrenade()[i].speed *= 0.6f;
		}
		if (COLLISIONMANAGER->pixelCollision(_pGrenade->getVPlayerGrenade()[i].rc,			// 오른쪽 벽
			_pGrenade->getVPlayerGrenade()[i].x, _pGrenade->getVPlayerGrenade()[i].y,
			_pGrenade->getVPlayerGrenade()[i].speed, _pGrenade->getVPlayerGrenade()[i].gravity, PLAYER_RIGHT) == GREEN)
		{
			_pGrenade->getVPlayerGrenade()[i].angle = PI - _pGrenade->getVPlayerGrenade()[i].angle;
			_pGrenade->getVPlayerGrenade()[i].speed *= 0.6f;

		}
		else if (COLLISIONMANAGER->pixelCollision(_pGrenade->getVPlayerGrenade()[i].rc,		// 왼쪽 벽
			_pGrenade->getVPlayerGrenade()[i].x, _pGrenade->getVPlayerGrenade()[i].y,
			_pGrenade->getVPlayerGrenade()[i].speed, _pGrenade->getVPlayerGrenade()[i].gravity, PLAYER_LEFT) == GREEN)
		{
			_pGrenade->getVPlayerGrenade()[i].angle = PI - _pGrenade->getVPlayerGrenade()[i].angle;
			_pGrenade->getVPlayerGrenade()[i].speed *= 0.6f;
		}

		if (_pGrenade->getVPlayerGrenade()[i].count < 90) continue;

		for (int j = 0; j < _mapData->getObject().size(); j++)								// 수류탄 카운트 70보다 클때 맵 지워주기
		{
			if (!_mapData->getObject()[j]._isActived)continue;
			if (IntersectRect(&temp, &_mapData->getObject()[j]._rc, &_pGrenade->getVPlayerGrenade()[i].rc))
			{
				if (!_rambroGrenade)
				{
					_mapData->deleteMapIndexByIndex(j, 2, 2);
					_pGrenade->getVPlayerGrenade()[i].isActived = false;
					EFFECTMANAGER->rambroGrenadeExplosion(_pGrenade->getVPlayerGrenade()[i].x, _pGrenade->getVPlayerGrenade()[i].y);
					CAMERAMANAGER->CameraShake();
				}
				if (_rambroGrenade)
				{
					_pGrenade->getVPlayerGrenade()[i].isActived = false;
					if (_pGrenade->getVPlayerGrenade()[i].isActived == false)
					{
						if (_grenadeCount >= 80)
						{
							if (!_player->getIsLeft())
							{
								_xMissile->fire(_player->getSkyRightX() + 50, _player->getSkyRightY() + 15, 10, _player->getIsLeft());
							}
							else
							{
								_xMissile->fire(_player->getSkyLeftX() + 50, _player->getSkyLeftY() + 15, 10, _player->getIsLeft());
							}
							_isMissile = true;
						}
					}
				}
				break;
			}
			//if(j >= _mapData->getObject().size()-1)
			//	_pGrenade->getVPlayerGrenade()[i].isActived = false;
		}
	}
	if (_missileCount >= 270)
	{
		for (int i = 0; i < _xMissile->getVPlayerxMissile().size(); i++)
		{
			_xMissile->getVPlayerxMissile()[i].isActived = false;
		}
		for (int i = 0; i < _gMissile->getVPlayergMissile().size(); i++)
		{
			if (!_player->getIsLeft())
			{
				_gMissile->fire(_player->getSkyRightX() + 50, _player->getSkyRightY() + 10, 20, _player->getIsLeft());
			}
			else
			{
				_gMissile->fire(_player->getSkyLeftX() + 50, _player->getSkyLeftY() + 10, 20, _player->getIsLeft());
			}
		}
		_missileCount = 0;
		_isMissile = false;
		_missile = true;
	}
	if (_missile)
	{
		int missileCount = 0;
		for (int i = 0; i < _gMissile->getVPlayergMissile().size(); i++)
		{
			if (COLLISIONMANAGER->pixelCollision(_gMissile->getVPlayergMissile()[i].rc, _gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y, _gMissile->getVPlayergMissile()[i].speed, _gMissile->getVPlayergMissile()[i].gravity, 3) == GREEN)				// 아래쪽 벽
			{
				for (int j = 0; j < _mapData->getObject().size(); j++)
				{
					if (IntersectRect(&temp, &_mapData->getObject()[j]._rc, &_gMissile->getVPlayergMissile()[i].rc))
					{
						_gMissile->getVPlayergMissile()[i].isActived = false;
						_mapData->deleteMapIndexByIndex(j, 2, 2);
						CAMERAMANAGER->CameraShake();
						//EFFECTMANAGER->rambroGrenadeExplosion(_gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y);
						missileCount++;
						break;
					}
				}
			}
			else if (COLLISIONMANAGER->pixelCollision(_gMissile->getVPlayergMissile()[i].rc, _gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y, _gMissile->getVPlayergMissile()[i].speed, _gMissile->getVPlayergMissile()[i].gravity, 1) == GREEN)			// 위쪽 벽
			{
				for (int j = 0; j < _mapData->getObject().size(); j++)
				{
					if (IntersectRect(&temp, &_mapData->getObject()[j]._rc, &_gMissile->getVPlayergMissile()[i].rc))
					{
						_gMissile->getVPlayergMissile()[i].isActived = false;
						_mapData->deleteMapIndexByIndex(j, 2, 2);
						CAMERAMANAGER->CameraShake();
						//EFFECTMANAGER->rambroGrenadeExplosion(_gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y);
						missileCount++;
						break;
					}
				}
			}
			if (COLLISIONMANAGER->pixelCollision(_gMissile->getVPlayergMissile()[i].rc, _gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y, _gMissile->getVPlayergMissile()[i].speed, _gMissile->getVPlayergMissile()[i].gravity, 2) == GREEN)				// 오른쪽 벽	
			{
				for (int j = 0; j < _mapData->getObject().size(); j++)
				{
					if (IntersectRect(&temp, &_mapData->getObject()[j]._rc, &_gMissile->getVPlayergMissile()[i].rc))
					{
						_gMissile->getVPlayergMissile()[i].isActived = false;
						_mapData->deleteMapIndexByIndex(j, 2, 2);
						CAMERAMANAGER->CameraShake();
						//EFFECTMANAGER->rambroGrenadeExplosion(_gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y);
						missileCount++;
						break;
					}
				}
			}
			else if (COLLISIONMANAGER->pixelCollision(_gMissile->getVPlayergMissile()[i].rc, _gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y, _gMissile->getVPlayergMissile()[i].speed, _gMissile->getVPlayergMissile()[i].gravity, 0) == GREEN)			// 왼쪽 벽	
			{
				for (int j = 0; j < _mapData->getObject().size(); j++)
				{
					if (IntersectRect(&temp, &_mapData->getObject()[j]._rc, &_gMissile->getVPlayergMissile()[i].rc))
					{
						_gMissile->getVPlayergMissile()[i].isActived = false;
						_mapData->deleteMapIndexByIndex(j, 2, 2);
						CAMERAMANAGER->CameraShake();
						//EFFECTMANAGER->rambroGrenadeExplosion(_gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y);
						missileCount++;
						break;
					}
				}
			}
		}
		if (missileCount == 5)
		{
			_missile = false;
		}
	}

	if (COLLISIONMANAGER->pixelCollision(_rcKnifeRight, knifeRightX, knifeRightY, _player->getSpeed(), _player->getGravity(), PLAYER_RIGHT) == GREEN)			// 칼빵 오른쪽 벽 뽀개기
	{
		for (int i = 0; i < _mapData->getObject().size(); i++)
		{
			if (IntersectRect(&temp, &_rcKnifeRight, &_mapData->getObject()[i]._rc))
			{
				_mapData->deleteMap(i);
				EFFECTMANAGER->knifePuff(_player->getX() - 30, _player->getY() - 25, _player->getIsLeft());
				break;
			}
		}
	}
	else if (COLLISIONMANAGER->pixelCollision(_rcKnifeLeft, knifeLeftX, knifeLeftY, _player->getSpeed(), _player->getGravity(), PLAYER_LEFT) == GREEN)			// 칼빵 왼쪽 벽 뽀개기
	{
		for (int i = 0; i < _mapData->getObject().size(); i++)
		{
			if (IntersectRect(&temp, &_rcKnifeLeft, &_mapData->getObject()[i]._rc))
			{
				_mapData->deleteMap(i);
				EFFECTMANAGER->knifePuff(_player->getX() - 34, _player->getY() - 25, _player->getIsLeft());
				break;
			}
		}
	}

	//if (IntersectRect(&temp, &_rc8, &_player->getRcRambro()))
	//{
	//}
	_player->setX(tempX);
	_player->setY(tempY);

	if (_isLadder)
	{
		_player->setGravity(0.f);
	}

	this->rambroCollision();
	this->rambroDie();
	this->chuckCollision();


	//else if (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), 0, PLAYER_RIGHT))				// 오른쪽벽
	//{
	//	hit_right = true;
	//	_player->setIsJump(false);
	//	_player->setGravity(0.f);
	//	_player->setSpeed(0.f);
	//	if (_player->getState() == JUMP)
	//	{
	//		_player->setState(HANG_FRONT_HOLD);
	//	}
	//}
	//else
	//{
	//	hit_left = false;
	//	hit_right = false;
	//}

	//if (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), _player->getGravity(), PLAYER_BOTTOM))		//바닥
	//{
	//	_player->setGravity(0.f);
	//	_player->setSpeed(0.f);
	//	_player->setIsJump(false);
	//	hit_left = false;
	//	hit_right = false;
	//	if (_player->getState() != RUN)
	//	{
	//		_player->setState(IDLE);
	//	}
	//}

	/*
	for (int i = 0; i < _mapData->getObject().size(); i++)
	{
	count++;
	if (!_mapData->getObject()[i]._isActived) continue;
	if (!CAMERAMANAGER->CameraIn(_mapData->getObject()[i]._rc)) continue;
	if (IntersectRect(&rcTemp, &rcPlayer, &_mapData->getObject()[i]._rc)					// 땅에 충돌 했을때 땅위로 올려버리기~
	&& _img->getY() + _img->getFrameHeight() >= _mapData->getObject()[i]._rc.top
	&& _img->getY() + _img->getFrameHeight() <= _mapData->getObject()[i]._rc.bottom
	&& _img->getX() >= _mapData->getObject()[i]._rc.left
	&& _img->getX() <= _mapData->getObject()[i]._rc.right)
	{
	_player->setY(_mapData->getObject()[i]._rc.top - _img->getFrameHeight());
	_player->setGravity(0.f);
	_player->setSpeed(0.f);
	_player->setIsJump(false);
	if (_player->getState() != RUN)
	{
	_player->setState(IDLE);
	}
	break;
	}

	if (IntersectRect(&rcTemp, &rcPlayer, &_mapData->getObject()[i]._rc)
	&& _img->getY() > _mapData->getObject()[i]._rc.top
	&& _img->getY() < _mapData->getObject()[i]._rc.bottom
	&& _img->getX() < _mapData->getObject()[i]._rc.left
	&& (_player->getY() - _player->getOldY() > 0))
	{
	hit_left = true;
	_player->setIsJump(false);
	_player->setGravity(0.f);
	_player->setSpeed(0.f);
	_player->setState(HANG_FORNT_HOLD);

	if (_img->getY() + _img->getFrameHeight() >= _mapData->getObject()[i]._rc.top
	&& _img->getY() + _img->getFrameHeight() <= _mapData->getObject()[i]._rc.bottom
	&& _img->getX() >= _mapData->getObject()[i]._rc.left
	&& _img->getX() <= _mapData->getObject()[i]._rc.right)
	{
	_player->setY(_mapData->getObject()[i]._rc.top - _img->getFrameHeight());
	_player->setGravity(0.f);
	_player->setSpeed(0.f);
	_player->setState(IDLE);
	//_player->setIsJump(false);
	hit_left = false;
	hit_right = false;
	break;
	}
	}
	else if (IntersectRect(&rcTemp, &rcPlayer, &_mapData->getObject()[i]._rc)
	&& _img->getY() > _mapData->getObject()[i]._rc.top
	&& _img->getY() < _mapData->getObject()[i]._rc.bottom
	&& _img->getX() + _img->getFrameWidth() > _mapData->getObject()[i]._rc.left
	&& (_player->getY() - _player->getOldY() > 0))
	{
	hit_right = true;
	_player->setIsJump(false);
	_player->setIsLeft(true);
	_player->setGravity(0.f);
	_player->setSpeed(0.f);
	_player->setState(HANG_FORNT_HOLD);

	if (_img->getY() + _img->getFrameHeight() >= _mapData->getObject()[i]._rc.top
	&& _img->getY() + _img->getFrameHeight() <= _mapData->getObject()[i]._rc.bottom
	&& _img->getX() >= _mapData->getObject()[i]._rc.left
	&& _img->getX() <= _mapData->getObject()[i]._rc.right)
	{
	_player->setY(_mapData->getObject()[i]._rc.top - _img->getFrameHeight());
	_player->setGravity(0.f);
	_player->setSpeed(0.f);
	_player->setState(IDLE);
	//_player->setIsJump(false);
	hit_left = false;
	hit_right = false;
	break;
	}
	}


	if (IntersectRect(&rcTemp, &rcPlayer, &_mapData->getObject()[i]._rc)				// 람브로가 오른쪽벽을 몬지나갑니다
	&& _img->getY() < _mapData->getObject()[i]._rc.top
	&& _img->getY() <= _mapData->getObject()[i]._rc.bottom
	&& _img->getX() + _img->getFrameWidth() > _mapData->getObject()[i]._rc.left
	&& _img->getX() + _img->getFrameWidth() < _mapData->getObject()[i]._rc.right)
	{
	_player->setX(_mapData->getObject()[i]._rc.left - _img->getFrameWidth());
	break;
	}
	if (IntersectRect(&rcTemp, &rcPlayer, &_mapData->getObject()[i]._rc)
	&& _img->getY() < _mapData->getObject()[i]._rc.top
	&& _img->getY() <= _mapData->getObject()[i]._rc.bottom
	&& _img->getX() > _mapData->getObject()[i]._rc.left
	&& _img->getX() < _mapData->getObject()[i]._rc.right)
	{
	_player->setX(_mapData->getObject()[i]._rc.right);
	break;
	}
	if (_img->getX() < CAMERAMANAGER->getCamera().left)									// 밖으로 탈주못함
	{
	_player->setX(CAMERAMANAGER->getCamera().left);
	break;
	}
	}
	*/
	p1Bubble();	
}

void playerManager::render(void)
{
	//RECT rc = RectMake(_player->getX(), _player->getY(), _player->getImage(_player->getState())->getFrameWidth(), _player->getImage(_player->getState())->getFrameHeight());
	_player->render();
	_pBullet->render();
	_pGrenade->render();
	_gBullet->render();
	_gMissile->render();
	_p1Bubble->frameRender(getMemDC(), _p1Bubble->getX() - CAMERAMANAGER->getCamera().left, _p1Bubble->getY() - CAMERAMANAGER->getCamera().top);
	for (int i = 0; i < _xMissile->getVPlayerxMissile().size(); i++)
	{
		if (_xMissile->getVPlayerxMissile()[i].isCollision)
		{
			_xMissile->render();
		}
	}
	
	char str[64];
	sprintf_s(str, "%d", _missileCount);
	TextOut(getMemDC(), 100, 100, str, strlen(str));
	if (KEYMANAGER->isToggleKey(VK_F8))
	{
		//RECT rc = RectMake(_player->getX(), _player->getY(), 90, 110);
		RectangleMake(getMemDC(), _player->getX()-CAMERAMANAGER->getCamera().left, _player->getY()-CAMERAMANAGER->getCamera().top, 65, 80);
		//RectangleMake(getMemDC(), _player->getX() + 20 - CAMERAMANAGER->getCamera().left, _player->getY() + 25 - CAMERAMANAGER->getCamera().top, _player->getWidth() + 10, _player->getHeight() + 5);
	}
	if (_knifeCollision)
	{
		if (!_player->getIsLeft())
		{
			RectangleMake(getMemDC(), _player->getX() + 60 - CAMERAMANAGER->getCamera().left, _player->getY() + 28 - CAMERAMANAGER->getCamera().top, 30, 30);
		}
		else
		{
			RectangleMake(getMemDC(), _player->getX() - 30 - CAMERAMANAGER->getCamera().left, _player->getY() + 28 - CAMERAMANAGER->getCamera().top, 30, 30);
		}
	}
	RectangleMake(getMemDC(), 20.f - CAMERAMANAGER->getCamera().left, 2100.f - CAMERAMANAGER->getCamera().top, 60, 60);
	RectangleMake(getMemDC(), _player->getSkyRightX() - CAMERAMANAGER->getCamera().left, _player->getSkyRightY() - CAMERAMANAGER->getCamera().top, _player->getSkyLeftW(), _player->getSkyLeftH());
	RectangleMake(getMemDC(), _player->getSkyLeftX() - CAMERAMANAGER->getCamera().left, _player->getSkyLeftY() - CAMERAMANAGER->getCamera().top, _player->getSkyLeftW(), _player->getSkyLeftH());
	
}

void playerManager::rambroDie()
{
	RECT _rcPlayer;
	_rcPlayer = RectMake(_player->getX() - 30, _player->getY() + 25, 60, 80);
	for (int i = 0; i < _enemyManager->getEBullet()->getVEnemybullet().size(); i++)
	{
		if (IntersectRect(&temp, &_rcPlayer, &_enemyManager->getEBullet()[i].getVEnemybullet()[i].rc))
		{
			_player->setY(_player->getY() + (-sin(_player->getAngle()) * _player->getJumpSpeed() + _player->getGravity()));
			if (_player->getIsLeft())
			{
				_player->setState(DIE);
				_isGameover = true;
			}
			else
			{
				_player->setState(DIE);
				_isGameover = true;
			}
		}
	}	
}

void playerManager::rambroCollision()
{
	for (int i = 0; i < _enemyManager->getVEnemy().size();++i)
	{
		for (int j = 0; j < getPBullet()->getVPlayerBullet().size(); ++j)
		{
			RECT rcTemp;
			RECT rcEnemy = _enemyManager->getVEnemy()[i]->getRcEnemy();
			if (!_pBullet->getVPlayerBullet()[j].isActived)continue;
			if (IntersectRect(&rcTemp, &rcEnemy, &_pBullet->getVPlayerBullet()[j].rc))
			{
				if (_enemyManager->getVEnemy()[i]->getIsApart()) continue;
				if (_pBullet->getVPlayerBullet()[j].isActived)
				{
					_pBullet->getVPlayerBullet()[j].isActived = false;
					if (!_pBullet->getVPlayerBullet()[j].isActived)
					{
						EFFECTMANAGER->bulletPuff(_pBullet->getVPlayerBullet()[j].x, _pBullet->getVPlayerBullet()[j].y);
					}
					break;
				}
			}
		}	
	}
}

void playerManager::chuckCollision()
{
	for (int i = 0; i < _enemyManager->getVEnemy().size(); i++)
	{
		for (int j = 0; j < _gBullet->getVPlayergBullet().size(); j++)
		{
			RECT rcTemp;
			RECT rcEnemy = _enemyManager->getVEnemy()[i]->getRcEnemy();
			if (!_gBullet->getVPlayergBullet()[j].isActived)continue;
			if (IntersectRect(&rcTemp, &rcEnemy, &_gBullet->getVPlayergBullet()[j].rc))
			{
				if (_enemyManager->getVEnemy()[i]->getIsApart())continue;
				if (_gBullet->getVPlayergBullet()[j].isActived)
				{
					_gBullet->getVPlayergBullet()[j].isActived = false;
					break;
				}
			}
		}
	}
}

void playerManager::p1Bubble()
{
	_p1Bubble->setX(_player->getX() + _player->getImage(_player->getState())->getFrameWidth() / 2 - _p1Bubble->getFrameWidth() / 2);
	_p1Bubble->setY(_player->getY() - _p1Bubble->getFrameHeight() - 5);
	if (_index >= _p1Bubble->getMaxFrameX())
	{
		_p1Bubble->setFrameX(_p1Bubble->getMaxFrameX());
	}
	else
	{
		FRAMEMANAGER->frameChange(_p1Bubble, _count, _index, _animationSpeed, false);
	}
}

playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}
