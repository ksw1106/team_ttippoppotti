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

	//_rcPlyaer = RectMake(_player->getX(),_player->getY(),,)
	hit_left = hit_right = false;
	_isCollision = false;
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

	

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_player->setIsLeft(true);
		if (JUMP != _player->getState() 
			&& HANG_FORNT_HOLD != _player->getState())
		{
			_player->setState(RUN);
		}
		if (!hit_right)
		{
			_player->setX(_player->getX() - 5.f);	
		}
		hit_left = false;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_player->setIsLeft(false);
		if (JUMP != _player->getState()
			&& HANG_FORNT_HOLD != _player->getState())
		{
			_player->setState(RUN);
		}
		if (!hit_left)
		{
			_player->setX(_player->getX() + 5.f);
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
		}
	}
	_pBullet->update();
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)&& !_player->getIsJump())
	{
		_player->setState(JUMP);
		_player->setGravity(0.0f);
		_player->setSpeed(20.f);
		_player->setIsJump(true);
		hit_left = false;
		hit_right = false;
	}

	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
	{
		_player->setState(IDLE);
	}
	if (!hit_left && !hit_right)
	{
		_player->setY(_player->getY() + (-sin(_player->getAngle())*_player->getSpeed() + _player->getGravity()));
	}
	
	if (hit_left || hit_right)
	{
		_player->setY(_player->getY() + 2.f);
	}

	for (int i = 0; i < MAX_STATE; i++)
	{
		_player->getImage(i)->setX(_player->getX());
		_player->getImage(i)->setY(_player->getY());
	}

	RECT rcTemp;
	RECT rcPlayer = _player->getImage(_player->getState())->boudingBoxWithFrame();
	image* _img = _player->getImage(_player->getState());

	float tempX = _player->getX();
	float tempY = _player->getY();

	if (COLLISIONMANAGER->pixelCollision(_img, tempX, tempY, PLAYER_BOTTOM))
	{
		_player->setGravity(0.f);
	}


	if (COLLISIONMANAGER->pixelCollision(_img, tempX, tempY, PLAYER_RIGHT))
	{
		hit_left = true;
		_player->setIsJump(false);
		_player->setGravity(0.f);
		_player->setSpeed(0.f);
		_player->setState(HANG_FORNT_HOLD);
	}
	_player->setX(tempX);
	_player->setY(tempY);
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
	for (int i = 0; i < MAX_STATE; i++)
	{
		_player->getImage(i)->setX(_player->getX());
		_player->getImage(i)->setY(_player->getY());
	}
	
}

void playerManager::render(void)
{
	_player->render();
	_pBullet->render();

	char str[64];
	sprintf_s(str, "%d", _player->getIsJump());
	TextOut(getMemDC(), 100, 100, str, strlen(str));
	count = 0;
}

playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}
