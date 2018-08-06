#include "stdafx.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "mapData.h"

HRESULT playerManager::init(void)
{
	_player = new player;
	_player->init();
	_pBullet = new pBullet;
	_pBullet->init(700.f);
	_pGrenade = new pGrenade;
	_pGrenade->init(500.f);

	hit_left = hit_right = hit_top = hit_bottom = false;
	
	_fireCount = 0;
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


	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_player->setIsLeft(true);
		if (JUMP != _player->getState()
			&& HANG_FRONT_HOLD != _player->getState())
		{
			_player->setState(RUN);
		}
		if (!hit_right)
		{
			_player->setX(_player->getX() - _player->getSpeed());
		}
		hit_left = false;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_player->setIsLeft(false);
		if (JUMP != _player->getState()
			&& HANG_FRONT_HOLD != _player->getState())
		{
			_player->setState(RUN);
		}
		if (!hit_left)
		{
			_player->setX(_player->getX() + _player->getSpeed());
		}
		hit_right = false;
	}
	_fireCount++;
	if (KEYMANAGER->isStayKeyDown('Z'))						// 기본 총알 발사
	{
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
			EFFECTMANAGER->cartridge(_player->getX(), _player->getY(), _player->getIsLeft());
		}
	}
	_pBullet->update();

	if (KEYMANAGER->isStayKeyDown('C'))							// 칼빵
	{
		if (_player->getIsLeft())
		{
			_player->setState(KNIFE);

		}
		else
		{
			_player->setState(KNIFE);
		}
	}

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
	_pGrenade->update();
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && !_player->getIsJump())
	{
		_player->setState(JUMP);
		_player->setGravity(0.0f);
		_player->setJumpSpeed(20.f);
		_player->setIsJump(true);
		hit_left = false;
		hit_right = false;
		if (_player->getState() == HANG_FRONT_HOLD || _player->getState() == HANG_BACK_HOLD)
		{
			_player->setJumpSpeed(10.f);
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT) || (KEYMANAGER->isOnceKeyUp('C')))
	{
		_player->setState(IDLE);
	}

	if (!hit_left && !hit_right)
	{
		_player->setY(_player->getY() + (-sin(_player->getAngle())*_player->getJumpSpeed() + _player->getGravity()));
	}

	if (hit_left || hit_right)
	{
		_player->setY(_player->getY() + 2.f);
	}

	RECT rcTemp;
	RECT rcPlayer;

	//image* _img = _player->getImage(_player->getState());

	float tempX = _player->getX();
	float tempY = _player->getY();

	rcPlayer = RectMake(tempX, tempY, 60, 80);

	if (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), _player->getGravity(), PLAYER_TOP))				// 위쪽 벽
	{
		_player->setGravity(0.f);
		_player->setJumpSpeed(0.f);
		_player->setIsJump(false);
		hit_left = false;
		hit_right = false;
		if (_player->getState() != JUMP)
		{
			_player->setState(IDLE);
		}

		hit_top = true;
	}
	else if (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), _player->getGravity(), PLAYER_BOTTOM))		// 아래쪽 벽
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

		//if (_player->getState())

		hit_bottom = true;
	}

	if (_player->getIsJump())
	{
		hit_bottom = false;
	}

	if (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), _player->getGravity(), PLAYER_RIGHT))				// 오른쪽 벽
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
	else if (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), _player->getGravity(), PLAYER_LEFT))				// 왼쪽벽
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
	else
	{
		hit_left = false;
		hit_right = false;

		if (_player->getState() == HANG_FRONT_HOLD)
			_player->setState(JUMP);
	}

	if (hit_left && !hit_right && !hit_bottom)
	{
		_player->setState(HANG_FRONT_HOLD);
	}
	else if (hit_right && !hit_left && !hit_bottom)
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
		if (COLLISIONMANAGER->pixelCollision(_pBullet->getVPlayerBullet()[i].rc,				// 왼쪽 벽에 충돌하면 벽 지워주기
			_pBullet->getVPlayerBullet()[i].x, _pBullet->getVPlayerBullet()[i].y, 
			_pBullet->getVPlayerBullet()[i].speed, _pBullet->getVPlayerBullet()[i].gravity,	PLAYER_LEFT))
		{
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (!_mapData->getObject()[j]._isActived)continue;
				if (IntersectRect(&temp, &_mapData->getObject()[j]._rc, &_pBullet->getVPlayerBullet()[i].rc))
				{
					_pBullet->getVPlayerBullet()[i].isActived = false;
					_mapData->deleteMap(j);
					break;
				}
			}
		}
		else if (COLLISIONMANAGER->pixelCollision(_pBullet->getVPlayerBullet()[i].rc,				// 오른쪽 벽에 충돌하면 벽 지워주기
			_pBullet->getVPlayerBullet()[i].x, _pBullet->getVPlayerBullet()[i].y,
			_pBullet->getVPlayerBullet()[i].speed, _pBullet->getVPlayerBullet()[i].gravity, PLAYER_RIGHT))
		{
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (!_mapData->getObject()[j]._isActived) continue;
				if (IntersectRect(&temp, &_pBullet->getVPlayerBullet()[i].rc, &_mapData->getObject()[j]._rc))
				{
					_pBullet->getVPlayerBullet()[i].isActived = false;
					_mapData->deleteMap(j);
					break;
				}
			}
		}
	}

	for (int i = 0; i < _pGrenade->getVPlayerGrenade().size(); i++)			// 수류탄이랑 벽이랑 충돌하면 벽 지워주기
	{
		if (!_pGrenade->getVPlayerGrenade()[i].isActived)continue;
		if (COLLISIONMANAGER->pixelCollision(_pGrenade->getVPlayerGrenade()[i].rc,			// 아래쪽 벽
			_pGrenade->getVPlayerGrenade()[i].x, _pGrenade->getVPlayerGrenade()[i].y, 
			_pGrenade->getVPlayerGrenade()[i].speed, _pGrenade->getVPlayerGrenade()[i].gravity, PLAYER_BOTTOM))
		{
			_pGrenade->getVPlayerGrenade()[i].gravity = 0;
			_pGrenade->getVPlayerGrenade()[i].angle = PI2 - _pGrenade->getVPlayerGrenade()[i].angle;
			_pGrenade->getVPlayerGrenade()[i].speed *= 0.5f;
		}
		else if (COLLISIONMANAGER->pixelCollision(_pGrenade->getVPlayerGrenade()[i].rc,		// 위쪽 벽
			_pGrenade->getVPlayerGrenade()[i].x, _pGrenade->getVPlayerGrenade()[i].y,
			_pGrenade->getVPlayerGrenade()[i].speed, _pGrenade->getVPlayerGrenade()[i].gravity, PLAYER_TOP))
		{
			_pGrenade->getVPlayerGrenade()[i].angle = PI2 - _pGrenade->getVPlayerGrenade()[i].angle;
			_pGrenade->getVPlayerGrenade()[i].speed *= 0.5f;
		}
		if (COLLISIONMANAGER->pixelCollision(_pGrenade->getVPlayerGrenade()[i].rc,			// 오른쪽 벽
			_pGrenade->getVPlayerGrenade()[i].x, _pGrenade->getVPlayerGrenade()[i].y,
			_pGrenade->getVPlayerGrenade()[i].speed, _pGrenade->getVPlayerGrenade()[i].gravity, PLAYER_RIGHT))
		{
			_pGrenade->getVPlayerGrenade()[i].angle = PI - _pGrenade->getVPlayerGrenade()[i].angle;
			_pGrenade->getVPlayerGrenade()[i].speed *= 0.5f;
			
		}
		else if (COLLISIONMANAGER->pixelCollision(_pGrenade->getVPlayerGrenade()[i].rc,		// 왼쪽 벽
			_pGrenade->getVPlayerGrenade()[i].x, _pGrenade->getVPlayerGrenade()[i].y,
			_pGrenade->getVPlayerGrenade()[i].speed, _pGrenade->getVPlayerGrenade()[i].gravity, PLAYER_LEFT))
		{
			_pGrenade->getVPlayerGrenade()[i].angle = PI - _pGrenade->getVPlayerGrenade()[i].angle;
			_pGrenade->getVPlayerGrenade()[i].speed *= 0.5f;
		}

		if (_pGrenade->getVPlayerGrenade()[i].count < 70) continue;

		for (int j = 0; j < _mapData->getObject().size(); j++)
		{
			if (!_mapData->getObject()[j]._isActived)continue;
			if (IntersectRect(&temp, &_mapData->getObject()[j]._rc, &_pGrenade->getVPlayerGrenade()[i].rc))
			{
				_mapData->deleteMap(j);
				_pGrenade->getVPlayerGrenade()[i].isActived = false;
				break;
			}			
		}
	}

	_player->setX(tempX);
	_player->setY(tempY);

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
}

void playerManager::render(void)
{
	RECT rc = RectMake(_player->getX(), _player->getY(), _player->getImage(_player->getState())->getFrameWidth(), _player->getImage(_player->getState())->getFrameHeight());
	_player->render();
	_pBullet->render();
	_pGrenade->render();

	char str[64];
	sprintf_s(str, "%d", hit_bottom);
	TextOut(getMemDC(), 100, 100, str, strlen(str));
	if (KEYMANAGER->isToggleKey(VK_F8))
	{
	}

	RectangleMake(getMemDC(), rc.left, rc.top, rc.left + (rc.right-rc.left)/2, rc.top + (rc.bottom - rc.top) / 2);
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
					break;
				}
			}
		}	
	}
}

playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}
