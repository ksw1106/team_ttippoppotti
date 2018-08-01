#include "stdafx.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "mapData.h"

HRESULT playerManager::init(void)
{
	_player = new player;
	_player->init();
	_pBullet = new pBullet;
	_pBullet->init(500.f);

	hit_left = hit_right = hit_top = hit_bottom = false;
	
	_fireCount = 0;
	_change = false;
	return S_OK;
}

void playerManager::release(void)
{
	SAFE_DELETE(_player);
	_pBullet->release();
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
	if (KEYMANAGER->isStayKeyDown('Z'))
	{
		if (_fireCount % 5 == 0)
		{
			if (_player->getIsLeft() == false)
			{
				_pBullet->fire(_player->getX() + 60, _player->getY() + 38, 20, _player->getIsLeft());
			}
			if (_player->getIsLeft() == true)
			{
				_pBullet->fire(_player->getX(), _player->getY() + 38, 20, _player->getIsLeft());
			}
			EFFECTMANAGER->cartridge(_player->getX(), _player->getY(), _player->getIsLeft());
		}

	}
	_pBullet->update();

	if (KEYMANAGER->isOnceKeyDown(VK_UP) && !_player->getIsJump())
	{
		_player->setState(JUMP);
		_player->setGravity(0.0f);
		_player->setJumpSpeed(20.f);
		_player->setIsJump(true);
		hit_left = false;
		hit_right = false;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
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

	rcPlayer = RectMake(tempX, tempY, _player->getImage(_player->getState())->getFrameWidth(), _player->getImage(_player->getState())->getFrameHeight());

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
	}

	if (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), _player->getGravity(), PLAYER_BOTTOM))		// 아래쪽 벽
	{
		_player->setGravity(0.f);
		_player->setJumpSpeed(0.f);
		_player->setIsJump(false);
		if (_player->getState() != RUN)
		{
			hit_left = false;
			hit_right = false;
			_player->setState(IDLE);
		}
	}
	//rcPlayer = RectMake(tempX, tempY, _player->getImage(_player->getState())->getFrameWidth(), _player->getImage(_player->getState())->getFrameHeight());

	if (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), _player->getGravity(), PLAYER_RIGHT))				// 오른쪽 벽
	{
		if (_player->getState() == HANG_FRONT_HOLD)
		{
			_player->setIsJump(false);
			_player->setGravity(0.f);
			_player->setJumpSpeed(0.f);
		}
		hit_left = true;
		_player->setIsLeft(false);
		_player->setIsCollision(!_player->getIsCollision());

		if (_player->getState() == JUMP)
		{
			_player->setState(HANG_FRONT_HOLD);
		}
	}

	//rcPlayer = RectMake(tempX, tempY, _player->getImage(_player->getState())->getFrameWidth(), _player->getImage(_player->getState())->getFrameHeight());

	if (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), _player->getGravity(), PLAYER_LEFT))				// 왼쪽벽
	{
		if (_player->getState() == HANG_FRONT_HOLD)
		{
			_player->setIsJump(false);
			_player->setGravity(0.f);
			_player->setJumpSpeed(0.f);
		}
		hit_right = true;
		_player->setIsLeft(true);
		if (_player->getState() != RUN)
		{
			_player->setState(HANG_FRONT_HOLD);
		}
	}
	
	
	_player->setX(tempX);
	_player->setY(tempY);
	
	/*
=======
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

	//if (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), 0, PLAYER_RIGHT))				// 왼쪽벽
	//{
	//	hit_left = true;
	//	_player->setIsJump(false);
	//	_player->setGravity(0.f);
	//	_player->setSpeed(0.f);
	//	if (_player->getState() != RUN)
	//	{
	//		_player->setState(HANG_FORNT_HOLD);
	//	}

	//}

	//if (COLLISIONMANAGER->pixelCollision(rcPlayer, tempX, tempY, _player->getSpeed(), 0, PLAYER_LEFT))				// 오른쪽벽
	//{
	//	hit_right = true;
	//	_player->setIsJump(false);
	//	_player->setIsLeft(true);
	//	_player->setGravity(0.f);
	//	_player->setSpeed(0.f);
	//	if (_player->getState() != RUN)
	//	{
	//		_player->setState(HANG_FORNT_HOLD);
	//	}
	//}

	_player->setX(tempX);
	_player->setY(tempY);
	
	
>>>>>>> 8e49a64b929487f1961c5ed9cb1bab871395c713
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

	char str[64];
	sprintf_s(str, "%d", _player->getIsLeft());
	TextOut(getMemDC(), 100, 100, str, strlen(str));

	RectangleMake(getMemDC(), rc.left, rc.top, rc.left + (rc.right-rc.left)/2, rc.top + (rc.bottom - rc.top) / 2);
}

void playerManager::collision()
{
	for (int i = 0; i < _enemyManager->getVEnemy().size(); i++)
	{
		//RECT rcEnemy = _enemyManager->getVEnemy()[i]->getEnemyArmImage()->boudingBoxWithFrame();
		//RECT rcTemp;
		//if (IntersectRect(&rcTemp, &rcEnemy, &_pBullet->getVPlayerBullet()[i].rc))
		//{
		//	getPBullet()->getVPlayerBullet()[i].bulletImage->release();
		//	SAFE_DELETE(getPBullet()->getVPlayerBullet()[i].bulletImage);
		//	getPBullet()->removeBullet(i);
		//}
		//else
		//{
		//	i++;
		//}
		//
		//RECT rcEnemy = _enemyManager->getVEnemy()[i]->getEnemyBodyImage(_enemyManager->getVEnemy()[i]->getBodyStatus())->boudingBoxWithFrame();
	}
}

playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}
