#include "stdafx.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "mapData.h"

HRESULT playerManager::init(void)
{
	_broforce.x = 100;
	_broforce.y = 2118;
	_broforce.rc = RectMake(_broforce.x, _broforce.y, 40, 40);
	_broforce.gravity = G_NUM;
	_broforce.speed = S_NUM;
	_broforce.jumpPower = J_NUM;

	_iscollision = false;

	_state = RIGHT_IDLE;

	return S_OK;
}

void playerManager::release(void)
{
}

void playerManager::update(void)
{
	_broforce.rc = RectMake(_broforce.x, _broforce.y, 40, 40);

	switch (_state)
	{
	case RIGHT_IDLE:
		_broforce.gravity = G_NUM;
		_broforce.jumpPower = J_NUM;
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_state = LEFT_RUN;
		}
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_state = RIGHT_RUN;
		}
		if (KEYMANAGER->isOnceKeyUp('A'))
		{
			_state = LEFT_IDLE;
		}
		if (KEYMANAGER->isOnceKeyUp('D'))
		{
			_state = RIGHT_IDLE;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_state = RIGHT_JUMP;
		}
		break;
	case LEFT_IDLE:
		_broforce.gravity = G_NUM;
		_broforce.jumpPower = J_NUM;
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_state = LEFT_RUN;
		}
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_state = RIGHT_RUN;
		}
		if (KEYMANAGER->isOnceKeyUp('A'))
		{
			_state = LEFT_IDLE;
		}
		if (KEYMANAGER->isOnceKeyUp('D'))
		{
			_state = RIGHT_IDLE;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_state = LEFT_JUMP;
		}
		break;
	case RIGHT_RUN:
		_broforce.gravity = G_NUM;
		_broforce.jumpPower = J_NUM;
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			if (_broforce.rc.right < 5000)
			{
				_broforce.x += _broforce.speed;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_state = RIGHT_JUMP;
		}
		if (KEYMANAGER->isOnceKeyUp('D'))
		{
			_state = RIGHT_IDLE;
		}
		if (KEYMANAGER->isOnceKeyUp('A'))
		{
			_state = LEFT_IDLE;
		}
		break;
	case LEFT_RUN:
		_broforce.gravity = G_NUM;
		_broforce.jumpPower = J_NUM;
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			if (_broforce.rc.left > 0)
			{
				_broforce.x -= _broforce.speed;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_state = LEFT_JUMP;
		}
		if (KEYMANAGER->isOnceKeyUp('D'))
		{
			_state = RIGHT_IDLE;
		}
		if (KEYMANAGER->isOnceKeyUp('A'))
		{
			_state = LEFT_IDLE;
		}
		break;
	case RIGHT_JUMP:
		_broforce.y -= _broforce.jumpPower;
		_broforce.jumpPower -= _broforce.gravity;
		for (int i = 0; i < map->getObject().size(); ++i)		// 
		{
			if (_broforce.y >= map->getObject()[i]._rc.top && _broforce.x >= map->getObject()[i]._rc.left && _broforce.x <= map->getObject()[i]._rc.right) 
			{
				_broforce.y = map->getObject()[i]._rc.top - 40;
				_broforce.gravity = 0.0f;
				_state = RIGHT_IDLE;
				break;
			}
		}
	
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			if (_broforce.rc.left > 0)
			{
				_broforce.x -= _broforce.speed;
			}
		}
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			if (_broforce.rc.right < 5000)
			{
				_broforce.x += _broforce.speed;
			}
		}
		break;
	case LEFT_JUMP:
		_broforce.y -= _broforce.jumpPower;
		_broforce.jumpPower -= _broforce.gravity;
		for (int i = 0; i < map->getObject().size(); ++i)		// 
		{
			if (_broforce.y >= map->getObject()[i]._rc.top && _broforce.x >= map->getObject()[i]._rc.left && _broforce.x <= map->getObject()[i]._rc.right)
			{
				_broforce.y = map->getObject()[i]._rc.top - 40;
				_broforce.gravity = 0.0f;
				_state = RIGHT_IDLE;
				break;
			}
		}
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			if (_broforce.rc.left > 0)
			{
				_broforce.x -= _broforce.speed;
			}
		}
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			if (_broforce.rc.right < 5000)
			{
				_broforce.x += _broforce.speed;
			}
		}
		break;
	case RIGHT_HANG:
		break;
	case LEFT_HANG:
		break;
	case LADDER:
		break;
	default:
		break;
	}
	for (int i = 0; i < map->getObject().size(); ++i)
	{
		if (IntersectRect(&temp, &_broforce.rc, &map->getObject()[i]._rc))
		{
			if (map->getObject()[i]._rc.left < _broforce.y + 40)
			{
				_broforce.y = map->getObject()[i]._rc.left - 40;
				_broforce.x = map->getObject()[i]._rc.top + 40;
			}
		}
	}
	
}

void playerManager::render(void)
{
	RectangleMake(getMemDC(), _broforce.rc.left - CAMERAMANAGER->getCamera().left,  _broforce.rc.top - CAMERAMANAGER->getCamera().top, 40, 40);
}

playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}
