#include "stdafx.h"
#include "stage2Scene.h"

HRESULT stage2Scene::init(void)
{
	_rcCamera = RectMake(0, 1694 - WINSIZEY, 5582, 1000+WINSIZEY);
	CAMERAMANAGER->setCamera(_rcCamera);

	_backGroundPixel = new image;
	_backGroundPixel->init("stage2_background_pixel.bmp", 5582, 2694, true, RGB(255, 0, 255));
	_ladderPixel = new image;
	_ladderPixel->init("stage2_ladder_pixel.bmp", 5582, 2694, true, RGB(255, 0, 255));
	_backGround = new image;
	_backGround->init("background.bmp", 5755, 2878, true, RGB(255, 0, 255));
	_backGoundRock = new image;
	_backGoundRock->init("stage2_background_rock.bmp", 5582, 2694, true, RGB(255, 0, 255));
	_backGroundObject = new image;
	_backGroundObject->init("stage2_background_object.bmp", 5582, 2694, true, RGB(255, 0, 255));

	_playerManager = new playerManager;
	_playerManager->init(2);
	_enemyManager = new enemyManager;
	_enemyManager->init(2);
	_mapData = new mapData;
	_mapData->init(2);
	_mapData->setObjectPixel(_backGroundObject);
	_mapData->setBackGroundMap(_backGroundPixel);

	_stageClear = new stageClear;
	_stageClear->init();
	_stageClear->setEnemyManager(_enemyManager);
	_stageClear->setCurrentStage(2);

	_stageStart = new stageStart;
	_stageStart->init();

	_missionFailed = new missionFailed;
	_missionFailed->init();

	EFFECTMANAGER->init();
	_playerManager->setMapData(_mapData);
	_enemyManager->setMapData(_mapData);
	_playerManager->setEnemyManager(_enemyManager);
	_enemyManager->setPlayerManager(_playerManager);

	OBJECTMANAGER->setMapData(_mapData);
	OBJECTMANAGER->setPlayerManager(_playerManager);
	OBJECTMANAGER->init(2);

	COLLISIONMANAGER->setPixelMap(_backGroundPixel, _ladderPixel);
	EFFECTMANAGER->init();

	_camDebug = false;
	_rcCamera = RectMakeCenter(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), WINSIZEX, WINSIZEY);
	CAMERAMANAGER->setCamera(_rcCamera);

	_isClear = _isOver = false;

	return S_OK;
}

void stage2Scene::release(void)
{
	//_playerManager->release();
	//_enemyManager->release();
	_mapData->release();
	_stageClear->release();
	_stageStart->release();
	_missionFailed->release();
	OBJECTMANAGER->release();

	SAFE_DELETE(_backGroundPixel);
	SAFE_DELETE(_ladderPixel);
	SAFE_DELETE(_backGround);
	SAFE_DELETE(_backGoundRock);
	SAFE_DELETE(_backGroundObject);
	SAFE_DELETE(_playerManager);
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_mapData);
	SAFE_DELETE(_stageClear);
	SAFE_DELETE(_stageStart);
	SAFE_DELETE(_missionFailed);
}

void stage2Scene::update(void)
{
	_stageStart->update();

	_playerManager->update();
	_enemyManager->update();
	OBJECTMANAGER->update();

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

	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		_isClear = true;
		_stageClear->setClearTime(TIMEMANAGER->getWorldTime());
		SOUNDMANAGER->stop("1stage");
		SOUNDMANAGER->play("clear", 0.8f);
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_isOver = true;
	}

	if (_isClear)
	{
		_stageClear->update();
	}

	if (_isOver)
	{
		_missionFailed->update();
	}
}

void stage2Scene::render(void)
{
	_backGround->render(getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);
	_backGoundRock->render(getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);
	_backGroundObject->render(getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);

	OBJECTMANAGER->render(getMemDC());
	_playerManager->render();
	_enemyManager->render();

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

	if (_isClear)
	{
		_stageClear->render();
	}

	if (_isOver)
	{
		_missionFailed->render();
	}

	_stageStart->render();
}