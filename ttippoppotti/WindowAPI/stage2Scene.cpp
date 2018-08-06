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

				mapObject obj = _mapData->getObject()[i];

				SelectObject(IMAGEMANAGER->findImage("stage2_background_object")->getMemDC(), GetStockObject(DC_BRUSH));
				SetDCBrushColor(IMAGEMANAGER->findImage("stage2_background_object")->getMemDC(), RGB(255, 0, 255));
				SelectObject(IMAGEMANAGER->findImage("stage2_background_object")->getMemDC(), GetStockObject(DC_PEN));
				SetDCPenColor(IMAGEMANAGER->findImage("stage2_background_object")->getMemDC(), RGB(255, 0, 255));
				RectangleMake(IMAGEMANAGER->findImage("stage2_background_object")->getMemDC(), obj._rc.left, obj._rc.top, obj._width, obj._height);

				obj._isActived = false;
				_mapData->setObject(obj, i);
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
		else if (_rcCamera.right >= 5755)
		{
			_rcCamera.left = 5755 - WINSIZEX;
		}
		if (_rcCamera.top <= 0)
		{
			_rcCamera.top = 0;
		}
		else if (_rcCamera.bottom >= 2878)
		{
			_rcCamera.top = 2878 - WINSIZEY;
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
	IMAGEMANAGER->findImage("backGround")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("stage2_background_rock")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("stage2_background_object")->render(getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);

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