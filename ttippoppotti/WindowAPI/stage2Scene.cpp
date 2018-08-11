#include "stdafx.h"
#include "stage2Scene.h"

HRESULT stage2Scene::init(void)
{
	_rcCamera = RectMake(0, 1694 - WINSIZEY, 5582, 1000+WINSIZEY);
	CAMERAMANAGER->setCamera(_rcCamera);

	_playerManager = new playerManager;
	_playerManager->init();
	_enemyManager = new enemyManager;
	_enemyManager->init();
	_mapData = new mapData;
	_mapData->init(2);
	_mapData->setObjectPixel("stage2_background_object");
	_mapData->setBackGroundMap("stage2_background_pixel");

	_backGround = IMAGEMANAGER->findImage("backGround");
	_backGroundObject = IMAGEMANAGER->findImage("stage2_background_object");
	_backGoundRock = IMAGEMANAGER->findImage("stage2_background_rock");
	_backGroundPixel = IMAGEMANAGER->findImage("stage2_background_pixel");
	_ladderPixel = IMAGEMANAGER->findImage("stage2_ladder_pixel");

	COLLISIONMANAGER->setPixelMap(2);

	EFFECTMANAGER->init();

	_camDebug = false;
	_rcCamera = RectMakeCenter(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), WINSIZEX, WINSIZEY);
	CAMERAMANAGER->setCamera(_rcCamera);

	return S_OK;
}

void stage2Scene::release(void)
{
}

void stage2Scene::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		POINT ptTemp;
		ptTemp.x = _ptMouse.x + CAMERAMANAGER->getCamera().left;
		ptTemp.y = _ptMouse.y + CAMERAMANAGER->getCamera().top;
		//충돌체크
		for (int i = 0; i < _mapData->getObject().size(); i++)
		{
			if (!_mapData->getObject()[i]._isActived) continue;

			if (PtInRect(&_mapData->getObject()[i]._rc, ptTemp))
			{
				_mapData->deleteMap(i);
				break; //임시
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F9))
		_camDebug = !_camDebug;

	if (!_camDebug)
		_rcCamera = RectMakeCenter(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), WINSIZEX, WINSIZEY);
	else
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{

			_rcCamera.left -= 10;
			_rcCamera.right -= 10;
		}
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_rcCamera.left += 10;
			_rcCamera.right += 10;
		}
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_rcCamera.top -= 10;
			_rcCamera.bottom -= 10;
		}

		if (KEYMANAGER->isStayKeyDown('S'))
		{
			_rcCamera.top += 10;
			_rcCamera.bottom += 10;
		}
	}
	if (!_camDebug)
	{
		if (_rcCamera.left <= 0)
		{
			_rcCamera.left = 0;
		}
		else if (_rcCamera.right >= 5582)
		{
			_rcCamera.left = 5582 - WINSIZEX;
		}
		if (_rcCamera.top <= 0)
		{
			_rcCamera.top = 0;
		}
		else if (_rcCamera.bottom >= 2694)
		{
			_rcCamera.top = 2694 - WINSIZEY;
		}
		_rcCamera = RectMake(_rcCamera.left, _rcCamera.top, WINSIZEX, WINSIZEY);
	}

	CAMERAMANAGER->setCamera(_rcCamera);

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		CAMERAMANAGER->CameraShake();
	}
}

void stage2Scene::render(void)
{
	_backGround->render(getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);
	_backGoundRock->render(getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);
	_backGroundObject->render(getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);

	if (KEYMANAGER->isToggleKey('8'))
	{
		_backGroundPixel->render(getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);
		_ladderPixel->render(getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);
	}
	
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		char str[64];
		sprintf_s(str, "%d", _ptMouse.x + CAMERAMANAGER->getCamera().left);
		TextOut(getMemDC(), 10, 100, str, strlen(str));
		sprintf_s(str, "%d", _ptMouse.y + CAMERAMANAGER->getCamera().top);
		TextOut(getMemDC(), 80, 100, str, strlen(str));
	}

	if (KEYMANAGER->isToggleKey(VK_F5))
	{
		char str[64];
		for (int i = 0; i < _mapData->getObject().size(); i++)
		{
			if (!_mapData->getObject()[i]._isActived) continue;

			if (!CAMERAMANAGER->CameraIn(_mapData->getObject()[i]._rc)) continue;

			RectangleMake(getMemDC(), _mapData->getObject()[i]._rc.left - CAMERAMANAGER->getCamera().left, _mapData->getObject()[i]._rc.top - CAMERAMANAGER->getCamera().top, _mapData->getObject()[i]._width, _mapData->getObject()[i]._height);
			sprintf(str, "%d", i);
			TextOut(getMemDC(), (_mapData->getObject()[i]._rc.left + (_mapData->getObject()[i]._rc.right - _mapData->getObject()[i]._rc.left) / 2) - CAMERAMANAGER->getCamera().left,
				(_mapData->getObject()[i]._rc.top + (_mapData->getObject()[i]._rc.bottom - _mapData->getObject()[i]._rc.top) / 2) - CAMERAMANAGER->getCamera().top, str, strlen(str));
		}
	}
}