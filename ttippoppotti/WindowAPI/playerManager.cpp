#include "stdafx.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "mapData.h"

HRESULT playerManager::init(void)
{
	_broforce.x = 100;
	_broforce.y = 2085;
	_broforce.rc = RectMake(_broforce.x, _broforce.y, 60, 76);
	_broforce.gravity = 0.0f;
	_broforce.angle = 3.14f / 180 * 90.0f;
	_broforce.speed = S_NUM;

	//_isCollision[0] = RectMake(_broforce.x + 37, _broforce.y + 20, 5, 5);
	//_isCollision[1] = RectMake(_broforce.x - 2, _broforce.y + 20, 5, 5);

	for (int i = 0; i < MAX_POSE; i++)
	{
		_ramBro[i] = new image;
	}
	
	_ramBro[IDLE] = IMAGEMANAGER->addFrameImage("broforce_idle", "broforce_idle.bmp", 60, 152, 1, 2, true, RGB(255, 0, 255));
	_ramBro[RUN] = IMAGEMANAGER->addFrameImage("broforce_run (1)", "broforce_run (1).bmp", 512, 152, 8, 2, true, RGB(255, 0, 255));
	//_ramBro[FAST_RUN] = IMAGEMANAGER->addFrameImage("broforce_run (2)", "broforce_run (2).bmp", 448, 128, 8, 2, true, RGB(255, 0, 255));
	_ramBro[JUMP] = IMAGEMANAGER->addFrameImage("broforce_jump", "broforce_jump.bmp", 177, 152, 3, 2, true, RGB(255, 0, 255));
	//_ramBro[ROLL] = IMAGEMANAGER->addFrameImage("broforce_roll", "broforce_roll.bmp", 936, 136, 13, 2, true, RGB(255, 0, 255));

	_isLeftFall = false;
	_isRightFall = false;

	_index = _count = 0;
	_speed = 0;
	_isLeft = false;
	_state = RIGHT_IDLE;

	return S_OK;
}

void playerManager::release(void)
{
}

void playerManager::update(void)
{
	_broforce.rc = RectMake(_broforce.x, _broforce.y, 60, 76);
	//_isCollision[0] = RectMake(_broforce.x + 37, _broforce.y + 20, 5, 5);
	//_isCollision[1] = RectMake(_broforce.x - 2, _broforce.y + 20, 5, 5);

	_broforce.gravity += 0.98f;

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_isLeft = true;
		_pose = RUN;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_isLeft = false;
		_pose = RUN;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_pose = IDLE;
	}
	



	
	//switch (_state)
	//{
	//case RIGHT_IDLE:
	//	_pose = IDLE;
	//	_broforce.gravity = 0.0f;
	//	if (KEYMANAGER->isStayKeyDown('A'))
	//	{
	//		_state = LEFT_RUN;
	//	}
	//	if (KEYMANAGER->isStayKeyDown('D'))
	//	{
	//		_state = RIGHT_RUN;
	//	}
	//	if (KEYMANAGER->isOnceKeyUp('A'))
	//	{
	//		_state = LEFT_IDLE;
	//	}
	//	if (KEYMANAGER->isOnceKeyUp('D'))
	//	{
	//		_state = RIGHT_IDLE;
	//	}
	//	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//	{
	//		_state = RIGHT_JUMP;
	//		_broforce.gravity = 0.0f;
	//	}
	//	break;
	//case LEFT_IDLE:
	//	_pose = IDLE;
	//	_broforce.gravity = 0.0f;
	//	if (KEYMANAGER->isStayKeyDown('A'))
	//	{
	//		_state = LEFT_RUN;
	//	}
	//	if (KEYMANAGER->isStayKeyDown('D'))
	//	{
	//		_state = RIGHT_RUN;
	//	}
	//	if (KEYMANAGER->isOnceKeyUp('A'))
	//	{
	//		_state = LEFT_IDLE;
	//	}
	//	if (KEYMANAGER->isOnceKeyUp('D'))
	//	{
	//		_state = RIGHT_IDLE;
	//	}
	//	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//	{
	//		_state = LEFT_JUMP;
	//		_broforce.gravity = 0.0f;
	//	}
	//	break;
	//case RIGHT_RUN:
	//	_pose = RUN;
	//	_isLeft = false;
	//	_broforce.gravity = 0.0f;
	//	if (KEYMANAGER->isStayKeyDown('D'))
	//	{
	//		if (_broforce.rc.right < 5000)
	//		{
	//			_broforce.x += SPEED;
	//		}
	//	}
	//	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//	{
	//		_state = RIGHT_JUMP;
	//		_broforce.gravity = 0.0f;
	//	}
	//	if (KEYMANAGER->isOnceKeyUp('D'))
	//	{
	//		_state = RIGHT_IDLE;
	//	}
	//	if (KEYMANAGER->isOnceKeyUp('A'))
	//	{
	//		_state = LEFT_IDLE;
	//	}
	//	break;
	//case LEFT_RUN:
	//	_pose = RUN;
	//	_isLeft = true;
	//	_broforce.gravity = 0.0f;
	//	if (KEYMANAGER->isStayKeyDown('A'))
	//	{
	//		if (_broforce.rc.left > 0)
	//		{
	//			_broforce.x -= SPEED;
	//		}
	//	}
	//	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//	{
	//		_state = LEFT_JUMP;
	//		_broforce.gravity = 0.0f;
	//	}
	//	if (KEYMANAGER->isOnceKeyUp('D'))
	//	{
	//		_state = RIGHT_IDLE;
	//	}
	//	if (KEYMANAGER->isOnceKeyUp('A'))
	//	{
	//		_state = LEFT_IDLE;
	//	}
	//	break;
	//case RIGHT_JUMP:
	//	_pose = JUMP;
	//	_isLeft = false;
	//	_broforce.y += -sinf(_broforce.angle) * _broforce.speed + _broforce.gravity;
	//	for (int i = 0; i < map->getObject().size(); ++i)		 
	//	{
	//		if (_broforce.y >= map->getObject()[i]._rc.top && _broforce.x >= map->getObject()[i]._rc.left && _broforce.x <= map->getObject()[i]._rc.right) 
	//		{
	//			_broforce.y = map->getObject()[i]._rc.top - 76;
	//			_broforce.gravity = 0.0f;
	//			_state = RIGHT_IDLE;
	//			break;
	//		}
	//	}
	//
	//	if (KEYMANAGER->isStayKeyDown('A'))
	//	{
	//		if (_broforce.rc.left > 0)
	//		{
	//			_broforce.x -= SPEED;
	//		}
	//	}
	//	if (KEYMANAGER->isStayKeyDown('D'))
	//	{
	//		if (_broforce.rc.right < 5000)
	//		{
	//			_broforce.x += SPEED;
	//		}
	//	}
	//	break;
	//case LEFT_JUMP:
	//	_pose = JUMP;
	//	_isLeft = true;
	//	_broforce.y += -sinf(_broforce.angle) * _broforce.speed + _broforce.gravity;
	//	for (int i = 0; i < map->getObject().size(); ++i)		
	//	{
	//		if (_broforce.y >= map->getObject()[i]._rc.top && _broforce.x >= map->getObject()[i]._rc.left && _broforce.x <= map->getObject()[i]._rc.right)
	//		{
	//			_broforce.y = map->getObject()[i]._rc.top - 76;
	//			_broforce.gravity = 0.0f;
	//			_state = RIGHT_IDLE;
	//			break;
	//		}
	//
	//		if (i == map->getObject().size()-1)
	//		{
	//			this->_isLeftFall = true;
	//		}
	//	}
	//	if (KEYMANAGER->isStayKeyDown('A'))
	//	{
	//		if (_broforce.rc.left > 0)
	//		{
	//			_broforce.x -= SPEED;
	//		}
	//	}
	//	if (KEYMANAGER->isStayKeyDown('D'))
	//	{
	//		if (_broforce.rc.right < 5000)
	//		{
	//			_broforce.x += SPEED;
	//		}
	//	}
	//	break;
	//case RIGHT_HANG:
	//	break;
	//case LEFT_HANG:
	//	break;
	//case LADDER:
	//	break;
	//default:
	//	break;
	//}



	//FRAMEMANAGER->frameChange(_ramBro[_pose], _count, _index, _speed, _isLeft);
	//
	//for (int i = 0; i < map->getObject().size(); i++)
	//{
	//	if (_broforce.y >= map->getObject()[i]._rc.top && _broforce.x >= map->getObject()[i]._rc.left && _broforce.x <= map->getObject()[i]._rc.right)
	//	{
	//		_broforce.y = map->getObject()[i]._rc.top - 76;
	//		_broforce.gravity = 0.0f;
	//		//_state = RIGHT_IDLE;
	//		break;
	//	}
	//
	//	if (i == map->getObject().size() - 1)
	//	{
	//		this->_isLeftFall = true;
	//	}
	//
	//	
	//}

	
	//for (int i = 0; i < map->getObject().size(); ++i)
	//{
	//	//if (map->getObject()[i]._rc.left > _broforce.x + 40 && map->getObject()[i]._rc.right < _broforce.x + 40)
	//	//{
	//	//
	//	//}
	//	if (map->getObject()[i]._rc.top > _broforce.y)dd
	//	{
	//		_broforce.y += 1;
	//		_broforce.y = map->getObject()[i]._rc.top - 40;
	//	}
	//}
	

	//for (int i = 0; i < map->getObject().size(); ++i)
	//{
	//	if (map->getObject()[i]._rc.left < _broforce.rc.left
	//		&& map->getObject()[i]._rc.right > _broforce.rc.right)
	//	{
	//		_broforce.y = map->getObject()[i]._rc.left - 40;
	//		_broforce.x = map->getObject()[i]._rc.top + 40;
	//	}
	//	
	//}
	
}

void playerManager::render(void)
{
	switch (_state)
	{
	case RIGHT_IDLE:
		_ramBro[IDLE]->frameRender(getMemDC(), _broforce.rc.left - CAMERAMANAGER->getCamera().left, _broforce.rc.top - CAMERAMANAGER->getCamera().top);
		break;
	case LEFT_IDLE:
		_ramBro[IDLE]->frameRender(getMemDC(), _broforce.rc.left - CAMERAMANAGER->getCamera().left, _broforce.rc.top - CAMERAMANAGER->getCamera().top);
		break;
	case RIGHT_RUN:
		_ramBro[RUN]->frameRender(getMemDC(), _broforce.rc.left - CAMERAMANAGER->getCamera().left, _broforce.rc.top - CAMERAMANAGER->getCamera().top);
		break;
	case LEFT_RUN:
		_ramBro[RUN]->frameRender(getMemDC(), _broforce.rc.left - CAMERAMANAGER->getCamera().left, _broforce.rc.top - CAMERAMANAGER->getCamera().top);
		break;
	case RIGHT_JUMP:
		_ramBro[JUMP]->frameRender(getMemDC(), _broforce.rc.left - CAMERAMANAGER->getCamera().left, _broforce.rc.top - CAMERAMANAGER->getCamera().top);
		break;
	case LEFT_JUMP:
		_ramBro[JUMP]->frameRender(getMemDC(), _broforce.rc.left - CAMERAMANAGER->getCamera().left, _broforce.rc.top - CAMERAMANAGER->getCamera().top);
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
	

	
	if (KEYMANAGER->isToggleKey(VK_F8))
	{
		RectangleMake(getMemDC(), _broforce.rc.left - CAMERAMANAGER->getCamera().left, _broforce.rc.top - CAMERAMANAGER->getCamera().top, 60, 76);
		//RectangleMake(getMemDC(), _isCollision[0].left - CAMERAMANAGER->getCamera().left, _isCollision[0].top - CAMERAMANAGER->getCamera().top, 5, 5);
		//RectangleMake(getMemDC(), _isCollision[1].left - CAMERAMANAGER->getCamera().left, _isCollision[1].top - CAMERAMANAGER->getCamera().top, 5, 5);
	}
}

playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}
