#include "stdafx.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "mapData.h"

HRESULT playerManager::init(void)
{
	_player = new player;
	_player->init();

	_ground = 2158.f;
	hit_left = hit_right = false;
	return S_OK;
}

void playerManager::release(void)
{
	SAFE_DELETE(_player);
}

void playerManager::update(void)
{
	_player->update();
	_player->setOldX(_player->getX());
	_player->setOldY(_player->getY());

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_player->setIsLeft(true);
		if (JUMP != _player->getState())
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
		if (JUMP != _player->getState())
		{
			_player->setState(RUN);
		}
		if (!hit_left)
		{
			_player->setX(_player->getX() + 5.f);
		}
		hit_right = false;
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)&& !_player->getIsJump())
	{
		_player->setState(JUMP);
		_player->setGravity(0.0f);
		_player->setSpeed(20.f);
	}

	if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D'))
	{
		_player->setState(IDLE);
	}
	if (!hit_left && !hit_right)
	{
		_player->setY(_player->getY() + (-sin(_player->getAngle())*_player->getSpeed() + _player->getGravity()));
	}
	
	//if (hit_left || hit_right)
	//{
	//	_player->setY(_player->getY() + 2.f);
	//}

	if (_player->getY() >= _ground - _player->getImage(_player->getState())->getFrameHeight())
	{
		_player->setY(_ground - _player->getImage(_player->getState())->getFrameHeight());
		_player->setIsJump(false);
		_player->setGravity(0.0f);
		_player->setSpeed(0.0f);
		hit_left = false;
		hit_right = false;
	}

	for (int i = 0; i < MAX_STATE; i++)
	{
		_player->getImage(i)->setX(_player->getX());
		_player->getImage(i)->setY(_player->getY());
	}

	RECT rcTemp;
	RECT rcPlayer = _player->getImage(_player->getState())->boudingBoxWithFrame();
	image* _img = _player->getImage(_player->getState());

	for (int i = 0; i < _mapData->getObject().size(); i++)
	{
		if (!_mapData->getObject()[i]._isActived) continue;

		if (!CAMERAMANAGER->CameraIn(_mapData->getObject()[i]._rc)) continue;
		
		count++;
		if (IntersectRect(&rcTemp, &rcPlayer, &_mapData->getObject()[i]._rc)											
			&& _img->getY() > _mapData->getObject()[i]._rc.top && _img->getY() < _mapData->getObject()[i]._rc.bottom
			&& _img->getX() < _mapData->getObject()[i]._rc.left && (_player->getY() - _player->getOldY() > 0))
		{
			if (_player->getY() < _ground - _player->getImage(_player->getState())->getFrameHeight())
			{
				hit_left = true;
			}
			_player->setIsJump(false);
			_player->setGravity(0.f);
			_player->setSpeed(0.f);
			break;
		}
		else if (IntersectRect(&rcTemp, &rcPlayer, &_mapData->getObject()[i]._rc)
			&& _img->getY() > _mapData->getObject()[i]._rc.top && _img->getY() < _mapData->getObject()[i]._rc.bottom
			&& _img->getX() + _img->getFrameWidth() > _mapData->getObject()[i]._rc.left && (_player->getY() - _player->getOldY() > 0))
		{
			if (_player->getY() < _ground - _player->getImage(_player->getState())->getFrameHeight())
			{
				hit_right = true;
			}		
			_player->setIsJump(false);
			_player->setGravity(0.f);
			_player->setSpeed(0.f);
			break;
		}
		else
		{
			hit_left = false;
			hit_right = false;
		}
		if (IntersectRect(&rcTemp, &rcPlayer, &_mapData->getObject()[i]._rc))				// 람브로가 오른쪽벽을 몬지나갑니다
		{
			if (_img->getY() < _mapData->getObject()[i]._rc.top									
				&& _img->getY() <= _mapData->getObject()[i]._rc.bottom
				&& _img->getX() + _img->getFrameWidth() > _mapData->getObject()[i]._rc.left
				&& _img->getX() + _img->getFrameWidth() < _mapData->getObject()[i]._rc.right)
			{
				_player->setX(_mapData->getObject()[i]._rc.left - _img->getFrameWidth());
				break;
			}
		}
		if (IntersectRect(&rcTemp, &rcPlayer, &_mapData->getObject()[i]._rc))
		{
			if (_img->getY() < _mapData->getObject()[i]._rc.top
				&& _img->getY() <= _mapData->getObject()[i]._rc.bottom
				&& _img->getX() > _mapData->getObject()[i]._rc.left
				&& _img->getX() < _mapData->getObject()[i]._rc.right)
			{
				_player->setX(_mapData->getObject()[i]._rc.right);
				break;
			}
		}
		if (_img->getX() < CAMERAMANAGER->getCamera().left)									// 밖으로 탈주못함
		{
			_player->setX(CAMERAMANAGER->getCamera().left);
			break;
		}
		//if (IntersectRect(&rcTemp, &rcPlayer, &_mapData->getObject()[i]._rc))				// 땅에 충돌 했을때 땅위로 올려버리기~
		//{
		//	if (_img->getY() <= _mapData->getObject()[i]._rc.top 
		//		&& _img->getY() <= _mapData->getObject()[i]._rc.bottom 
		//		&& _img->getX() >= _mapData->getObject()[i]._rc.left 
		//		&& _img->getX() <= _mapData->getObject()[i]._rc.right)		
		//	{
		//		_player->setY(_mapData->getObject()[i]._rc.top - _img->getFrameHeight());
		//		_player->setGravity(0.f);
		//		_player->setSpeed(0.f);
		//		_player->setState(IDLE);
		//	}
		//}
	}

	for (int i = 0; i < MAX_STATE; i++)
	{
		_player->getImage(i)->setX(_player->getX());
		_player->getImage(i)->setY(_player->getY());
	}
	
}

void playerManager::render(void)
{
	_player->render();

	char str[64];
	sprintf_s(str, "%d", count);
	TextOut(getMemDC(), 100, 100, str, strlen(str));
	count = 0;
}

playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}
