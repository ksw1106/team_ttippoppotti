#include "stdafx.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "mapData.h"

HRESULT playerManager::init(void)
{
	_player = new player;
	_player->init();
	_playerChuck = new player;
	_pBullet = new pBullet;
	_pBullet->init(700.f);
	_pGrenade = new pGrenade;
	_pGrenade->init(500.f);

	_p1Bubble = IMAGEMANAGER->findImage("p1Bubble");
	_p1Bubble->setX(_player->getX() + _player->getImage(_player->getState())->getFrameWidth() / 2 - _p1Bubble->getFrameWidth() / 2);
	_p1Bubble->setY(_player->getY() - 100);

	_rcKnifeRight = RectMake(_player->getX() + 60, _player->getY() + 30, 30, 30);
	_rcKnifeLeft = RectMake(_player->getX() - 20, _player->getY() + 30, 30, 30);

	_player->setRcRambro(_player->getRcRambro());

	hit_left = hit_right = hit_top = hit_bottom = false;
	
	_index = _count = 0;
	_animationSpeed = 5;

	_fireCount = 0;

	_knifeCollision = false;
	_isLadder = false;
	_change = false;
	
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
	_player->setrcFlashRight(_player->getrcFlashRight());				// 총구 오른쪽 플래쉬 렉트
	_player->setrcFlashLeft(_player->getrcFlashLeft());					// 총구 왼쪽 플래쉬 렉트

	float knifeRightX = _player->getX() + 60;
	float knifeRightY = _player->getY() + 30;
	float knifeLeftX = _player->getX() - 20;
	float knifeLeftY = _player->getY() + 30;

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
				_player->setX(_player->getX() - _player->getSpeed());
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
			}
			hit_right = false;
		}
	}

	_fireCount++;
	if (KEYMANAGER->isStayKeyDown('Z'))							// 기본 총알 발사
	{
		if (_player->getIsLeft() == false)
		{
			_player->setIsFlash(true);
		}
		if (_player->getIsLeft() == true)
		{
			_player->setIsFlash(true);
		}

		if (_fireCount % 5 == 0)
		{
			if (_player->getIsLeft() == false)					// 오른쪽
			{
				_pBullet->fire(_player->getX() + 60, _player->getY() + 38, 20, _player->getIsLeft());
			}
			if (_player->getIsLeft() == true)					// 왼쪽
			{
				_pBullet->fire(_player->getX(), _player->getY() + 38, 20, _player->getIsLeft());
			}
			EFFECTMANAGER->cartridge(_player->getX(), _player->getY(), _player->getIsLeft());			// 총알 탄피
		}
	}
	if (KEYMANAGER->isOnceKeyUp('Z'))			// Z키에서 손때믄 총구앞 이미지 제거용
	{
		_player->setIsFlash(false);
	}
	_pBullet->update();											// 총알 업데이트 ( 무브 )

	if (_knifeCollision)
	{
		_rcKnifeRight = RectMake(knifeRightX, knifeRightY, 30, 30);			// 칼빵용 오른쪽 렉트
		_rcKnifeLeft = RectMake(knifeLeftX, knifeLeftY, 30, 30);			// 칼빵용 왼쪽 렉트
	}
	else
	{
		_knifeCollision = false;
	}

	if (KEYMANAGER->isStayKeyDown('C'))						// 칼빵
	{
		if (KNIFE != _player->getState())
		{
			_player->setState(KNIFE);
			_player->setIndex(0);
			_player->setCount(0);
			_knifeCollision = true;
		}
		//else if (KNIFE != _player->getState() && _player->getIsLeft() == true)
		//{
		//	_player->setState(KNIFE);
		//	_player->setIndex(0);
		//	_player->setCount(0);
		//}
	}
	
	if (KNIFE == _player->getState() && (_player->getIndex() >= _player->getImage(_player->getState())->getMaxFrameX()))
	{
		_player->setState(IDLE);
		_knifeCollision = false;
	}
	
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
		if (_player->getIsLeft() == false)						// 오른쪽
		{
			_pGrenade->fire(_player->getX() + 60, _player->getY() + 38, 20, _player->getIsLeft());
		}
		if (_player->getIsLeft() == true)						// 왼쪽
		{
			_pGrenade->fire(_player->getX(), _player->getY() + 38, 20, _player->getIsLeft());
		}
		
	}

	if (KEYMANAGER->isStayKeyDown('X'))
	{
		if (_player->getIsLeft())
		{
			_player->setState(FIRE);
		}
		else if (!_player->getIsLeft())
		{
			_player->setState(FIRE);
		}
	}
	_pGrenade->update();										// 수류탄 업데이트 ( 무브 )

	if (KEYMANAGER->isOnceKeyDown(VK_UP) && !_player->getIsJump())
	{
		if (!_isLadder)
		{
			_player->setState(JUMP);
			_player->setGravity(0.0f);
			_player->setJumpSpeed(20.f);
			_player->setIsJump(true);
			hit_left = false;
			hit_right = false;
			if (_player->getState() == HANG_FRONT_HOLD || _player->getState() == HANG_BACK_HOLD)
			{
				_player->setJumpSpeed(5.f);
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

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp('X') || KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_player->setState(IDLE);
	}

	if (!hit_left && !hit_right && !_isLadder)
	{
		_player->setY(_player->getY() + (-sin(_player->getAngle())*_player->getJumpSpeed() + _player->getGravity()));
	}

	if (hit_left || hit_right && !_isLadder)
	{
		_player->setY(_player->getY() + 2.f);
	}

	RECT rcTemp;
	RECT rcPlayer;

	//image* _img = _player->getImage(_player->getState());

	float tempX = _player->getX();
	float tempY = _player->getY();

	rcPlayer = RectMake(tempX, tempY, 60, 80);


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
			if (_player->getState() != JUMP && _player->getState() != HANG_FRONT_HOLD && _player->getState() != HANG_BACK_HOLD)
			{
				_player->setState(IDLE);
			}

			hit_top = true;
		}
		break;
	case RED:
		//_player->setState(LADDER);
		_isLadder = true;
		break;
	case BLUE:
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

			if (_player->getState() != RUN && _player->getState() != KNIFE && _player->getState() != HANG_FRONT_HOLD)
			{
				hit_left = false;
				hit_right = false;
				_player->setState(IDLE);
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
		break;
	default:
		break;
	}
	
	switch (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), _player->getGravity(), PLAYER_LEFT, _isLadder))
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

	
	for (int i = 0; i < _pBullet->getVPlayerBullet().size(); i++)  // 총알이랑 벽이랑 충돌하면 벽 지워주기
	{
		if (!_pBullet->getVPlayerBullet()[i].isActived)continue;
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

	for (int i = 0; i < _pGrenade->getVPlayerGrenade().size(); i++)			// 수류탄이랑 벽이랑 충돌하면 벽 지워주기
	{
		if (!_pGrenade->getVPlayerGrenade()[i].isActived)continue;
		if (COLLISIONMANAGER->pixelCollision(_pGrenade->getVPlayerGrenade()[i].rc,			// 아래쪽 벽
			_pGrenade->getVPlayerGrenade()[i].x, _pGrenade->getVPlayerGrenade()[i].y,
			_pGrenade->getVPlayerGrenade()[i].speed, _pGrenade->getVPlayerGrenade()[i].gravity, PLAYER_BOTTOM) == GREEN)
		{
			_pGrenade->getVPlayerGrenade()[i].gravity = 0;
			//_pGrenade->getVPlayerGrenade()[i].angle = PI2 - _pGrenade->getVPlayerGrenade()[i].angle;
			_pGrenade->getVPlayerGrenade()[i].speed *= 0.5f;
			
		}
		else if (COLLISIONMANAGER->pixelCollision(_pGrenade->getVPlayerGrenade()[i].rc,		// 위쪽 벽
			_pGrenade->getVPlayerGrenade()[i].x, _pGrenade->getVPlayerGrenade()[i].y,
			_pGrenade->getVPlayerGrenade()[i].speed, _pGrenade->getVPlayerGrenade()[i].gravity, PLAYER_TOP) == GREEN)
		{
			//_pGrenade->getVPlayerGrenade()[i].angle = PI2 - _pGrenade->getVPlayerGrenade()[i].angle;
			_pGrenade->getVPlayerGrenade()[i].speed *= 0.5f;
		}
		if (COLLISIONMANAGER->pixelCollision(_pGrenade->getVPlayerGrenade()[i].rc,			// 오른쪽 벽
			_pGrenade->getVPlayerGrenade()[i].x, _pGrenade->getVPlayerGrenade()[i].y,
			_pGrenade->getVPlayerGrenade()[i].speed, _pGrenade->getVPlayerGrenade()[i].gravity, PLAYER_RIGHT) == GREEN)
		{
			//_pGrenade->getVPlayerGrenade()[i].angle = PI - _pGrenade->getVPlayerGrenade()[i].angle;
			_pGrenade->getVPlayerGrenade()[i].speed *= 0.5f;
			
		}
		else if (COLLISIONMANAGER->pixelCollision(_pGrenade->getVPlayerGrenade()[i].rc,		// 왼쪽 벽
			_pGrenade->getVPlayerGrenade()[i].x, _pGrenade->getVPlayerGrenade()[i].y,
			_pGrenade->getVPlayerGrenade()[i].speed, _pGrenade->getVPlayerGrenade()[i].gravity, PLAYER_LEFT) == GREEN)
		{
			//_pGrenade->getVPlayerGrenade()[i].angle = PI - _pGrenade->getVPlayerGrenade()[i].angle;
			_pGrenade->getVPlayerGrenade()[i].speed *= 0.5f;
		}

		if (_pGrenade->getVPlayerGrenade()[i].count < 70) continue;

		for (int j = 0; j < _mapData->getObject().size(); j++)								// 수류탄 카운트 70보다 클때 맵 지워주기
		{
			if (!_mapData->getObject()[j]._isActived)continue;
			if (IntersectRect(&temp, &_mapData->getObject()[j]._rc, &_pGrenade->getVPlayerGrenade()[i].rc))
			{
				_mapData->deleteMapIndexByIndex(j, 1, 1);
				_pGrenade->getVPlayerGrenade()[i].isActived = false;
				break;
			}		
		}
	}

	//if (_knifeCollision)			// 칼빵 
	//{
	if (COLLISIONMANAGER->pixelCollision(_rcKnifeRight, knifeRightX, knifeRightY, _player->getSpeed(), _player->getGravity(), PLAYER_RIGHT) == GREEN)			// 칼빵 오른쪽 벽 뽀개기
		{
			for (int i = 0; i < _mapData->getObject().size(); i++)
			{
				if (IntersectRect(&temp, &_rcKnifeRight, &_mapData->getObject()[i]._rc))
				{
					_mapData->deleteMap(i);
					EFFECTMANAGER->knifePuff(_player->getX(), _player->getY(), _player->getIsLeft());
					break;
				}
			}
		}
		else if (COLLISIONMANAGER->pixelCollision(_rcKnifeLeft, knifeLeftX, knifeLeftY, _player->getSpeed(), _player->getGravity(), PLAYER_LEFT) == GREEN)		// 칼빵 왼쪽 벽 뽀개기
		{
			for (int i = 0; i < _mapData->getObject().size(); i++)
			{
				if (IntersectRect(&temp, &_rcKnifeLeft, &_mapData->getObject()[i]._rc))
				{
					_mapData->deleteMap(i);
					EFFECTMANAGER->knifePuff(_player->getX(), _player->getY(), _player->getIsLeft());
					break;
				}
			}
		}
	//}
	
	_player->setX(tempX);
	_player->setY(tempY);

	if (_isLadder)
	{
		_player->setGravity(0.f);
	}

	this->collision();
	this->rambroDie();
	
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
	RECT rc = RectMake(_player->getX(), _player->getY(), _player->getImage(_player->getState())->getFrameWidth(), _player->getImage(_player->getState())->getFrameHeight());
	_pBullet->render();
	_player->render();
	_pGrenade->render();
	_p1Bubble->frameRender(getMemDC(), _p1Bubble->getX() - CAMERAMANAGER->getCamera().left, _p1Bubble->getY() - CAMERAMANAGER->getCamera().top);

	char str[64];
	sprintf_s(str, "%d", _knifeCollision);
	TextOut(getMemDC(), 100, 100, str, strlen(str));
	if (KEYMANAGER->isToggleKey(VK_F8))
	{
		RectangleMake(getMemDC(), _player->getX() - CAMERAMANAGER->getCamera().left, _player->getY() - CAMERAMANAGER->getCamera().top, _player->getWidth(), _player->getHeight());
	}
	if (_knifeCollision)
	{
		if (_player->getIsLeft() == false)
		{
			RectangleMake(getMemDC(), _player->getX() + 60 - CAMERAMANAGER->getCamera().left, _player->getY() + 30 - CAMERAMANAGER->getCamera().top, 30, 30);
		}
		if (_player->getIsLeft() == true)
		{
			RectangleMake(getMemDC(), _player->getX() - 20 - CAMERAMANAGER->getCamera().left, _player->getY() + 30 - CAMERAMANAGER->getCamera().top, 30, 30);
		}
	}

	//RectangleMake(getMemDC(), _player->getX() + 50 - CAMERAMANAGER->getCamera().left, _player->getY() + 30 - CAMERAMANAGER->getCamera().top, 30, 30);
}

void playerManager::rambroDie()
{
	RECT _rcPlayer;
	_rcPlayer = RectMake(_player->getX(), _player->getY(), 60, 80);
	for (int i = 0; i < _enemyManager->getEBullet()->getVEnemybullet().size(); i++)
	{
		if (IntersectRect(&temp, &_rcPlayer, &_enemyManager->getEBullet()[i].getVEnemybullet()[i].rc))
		{
			_player->setY(_player->getY() + (-sin(_player->getAngle()) * _player->getJumpSpeed() + _player->getGravity()));
			_player->setState(DIE);
		}
	}	
}

void playerManager::collision()
{
	for (int i = 0; i < _enemyManager->getVEnemy().size();++i)
	{
		for (int j = 0; j < getPBullet()->getVPlayerBullet().size(); ++j)
		{
			RECT rcTemp;
			RECT rcEnemy = _enemyManager->getVEnemy()[i]->getRcEnemy();
			if (IntersectRect(&rcTemp, &rcEnemy, &_pBullet->getVPlayerBullet()[j].rc))
			{
				if (_pBullet->getVPlayerBullet()[j].isActived == true)
				{
					_pBullet->getVPlayerBullet()[j].isActived = false;
					if (_pBullet->getVPlayerBullet()[j].isActived == false)
						EFFECTMANAGER->bulletPuff(_pBullet->getVPlayerBullet()[j].x, _pBullet->getVPlayerBullet()[j].y);
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
