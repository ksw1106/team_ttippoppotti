#include "stdafx.h"
#include "playerManager.h"
#include "enemyManager.h"

HRESULT playerManager::init(void)
{
	_broforce.x = 0;
	_broforce.y = 2158;
	_broforce.rc = RectMakeCenter(_broforce.x, _broforce.y, 20, 20);
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
	_broforce.rc = RectMakeCenter(_broforce.x, _broforce.y, 20, 20);

	switch (_state)
	{
	case RIGHT_IDLE:
		_broforce.gravity = G_NUM;
		_broforce.jumpPower = J_NUM;
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_state = LEFT_RUN;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_state = RIGHT_RUN;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_state = LEFT_IDLE;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
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
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_state = LEFT_RUN;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_state = RIGHT_RUN;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_state = LEFT_IDLE;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
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
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
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
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_state = RIGHT_IDLE;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_state = LEFT_IDLE;
		}
		break;
	case LEFT_RUN:
		_broforce.gravity = G_NUM;
		_broforce.jumpPower = J_NUM;
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
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
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_state = RIGHT_IDLE;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_state = LEFT_IDLE;
		}
		break;
	case RIGHT_JUMP:
		_broforce.y -= _broforce.jumpPower;
		_broforce.jumpPower -= _broforce.gravity;

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (_broforce.rc.left > 0)
			{
				_broforce.x -= _broforce.speed;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
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
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (_broforce.rc.left > 0)
			{
				_broforce.x -= _broforce.speed;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
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
}

void playerManager::render(void)
{
	RectangleMake(getMemDC(), _broforce.rc.left - _broforce.rc.top);
}

playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}
