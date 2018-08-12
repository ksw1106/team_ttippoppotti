#include "stdafx.h"
#include "stageScene.h"


HRESULT stageScene::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화를 한다

	for (int i = 0; i < 3; i++)
	{
		ZeroMemory(&_backGround[i], sizeof(world));
		_backGround[i]._rc = RectMake(0, 2878 - WINSIZEY, 5755, WINSIZEY);

		_backGround[i]._image = new image;
	}

	_backGroundPixel = new image;
	_backGroundPixel->init("background_pixel.bmp", 5755, 2878, true, RGB(255, 0, 255));
	_ladderPixel = new image;
	_ladderPixel->init("ladder_pixel.bmp", 5755, 2878, true, RGB(255, 0, 255));
	_backGround[0]._image->init("background.bmp", 5755, 2878, true, RGB(255, 0, 255));
	/*_backGround[1]._image = IMAGEMANAGER->findImage("backGround_tree4");
	_backGround[2]._image = IMAGEMANAGER->findImage("backGround_tree3");
	_backGround[3]._image = IMAGEMANAGER->findImage("backGround_tree2");
	_backGround[4]._image = IMAGEMANAGER->findImage("backGround_tree1");*/
	_backGround[1]._image->init("background_rock.bmp", 5755, 2878, true, RGB(255, 0, 255));
	_backGround[2]._image->init("background_object.bmp", 5755, 2878, true, RGB(255, 0, 255));

	_playerManager = new playerManager;
	_playerManager->init(1);

	_enemyManager = new enemyManager;
	_enemyManager->init(1);

	_mapData = new mapData;
	_mapData->init(1);
	_mapData->setObjectPixel(_backGround[2]._image);
	_mapData->setBackGroundMap(_backGroundPixel);

	_test = new testScene_kmy;
	_test->init();

	_stageClear = new stageClear;
	_stageClear->init();
	_stageClear->setEnemyManager(_enemyManager);
	_stageClear->setCurrentStage(1);
	_stageStart = new stageStart;
	_stageStart->init();

	_missionFailed = new missionFailed;
	_missionFailed->init();

	EFFECTMANAGER->init();
	_playerManager->setMapData(_mapData);
	_enemyManager->setMapData(_mapData);
	OBJECTMANAGER->setMapData(_mapData);
	OBJECTMANAGER->setPlayerManager(_playerManager);
	OBJECTMANAGER->init(1);				//오브젝트매니져 초기화
	_playerManager->setEnemyManager(_enemyManager);
	_enemyManager->setPlayerManager(_playerManager);

	COLLISIONMANAGER->setPixelMap(_backGroundPixel, _ladderPixel);

	_camDebug = false;
	_rcCamera = RectMakeCenter(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), WINSIZEX, WINSIZEY);
	CAMERAMANAGER->setCamera(_rcCamera);

	_isClear = _isOver = false;
	return S_OK;
}

void stageScene::release(void)
{
	//init함수에서 동적할당 new를 사용했다면 이곳에서 delete 사용한다
	//이미지매니져 사용시 safe_delete 할 필요 없다

	for (int i = 0; i < 3; i++)
	{
		SAFE_DELETE(_backGround[i]._image);
	}
	SAFE_DELETE(_backGroundPixel);
	SAFE_DELETE(_ladderPixel);
	//_playerManager->release();
	//_enemyManager->release();
	_mapData->release();
	_stageClear->release();
	_stageStart->release();
	_missionFailed->release();
	_test->release();
	OBJECTMANAGER->release();

	SAFE_DELETE(_playerManager);
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_mapData);
	SAFE_DELETE(_stageClear);
	SAFE_DELETE(_stageStart);
	SAFE_DELETE(_missionFailed);
	SAFE_DELETE(_test);
}

void stageScene::update(void)
{
	_stageStart->update();
	
	_playerManager->update();
	_enemyManager->update();
	OBJECTMANAGER->update();
	_test->update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	//간단하게 이곳에서 코딩한다고 생각하면 된다

	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		_isClear = true;
		_stageClear->setClearTime(TIMEMANAGER->getWorldTime());
		SOUNDMANAGER->stop("1stage");
		SOUNDMANAGER->play("clear", 0.8f);
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
		_rcCamera = RectMake( _rcCamera.left, _rcCamera.top, WINSIZEX, WINSIZEY);
	}

	OBJECTMANAGER->setIsDead(_enemyManager->isClear());
	_isOver = _playerManager->getIsGameover();
	if (OBJECTMANAGER->getVObject()[30]->getState() == OBJECT_MOVE)
	{
		_rcCamera = RectMake(OBJECTMANAGER->getVObject()[30]->getX() - 170, OBJECTMANAGER->getVObject()[30]->getY() - 290, WINSIZEX, WINSIZEY);
		//CAMERAMANAGER->CameraShake();
	}
	if (OBJECTMANAGER->getVObject()[30]->getisArrived() && !_isClear)
	{
		
		_isClear = true;
	}

	if (_isClear)
	{
		if (!_isOnce)
		{
			_isOnce = true;
			_stageClear->setClearTime(TIMEMANAGER->getWorldTime());
			SOUNDMANAGER->stop("1stage");
			SOUNDMANAGER->play("clear", 0.8f);
		}
		
		
		_stageClear->update();
	}

	if (_isOver)
	{
		_missionFailed->update();
	}

	CAMERAMANAGER->setCamera(_rcCamera);

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		CAMERAMANAGER->CameraShake();
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_isOver = true;
	}
}

void stageScene::render(void)
{
	for (int i = 0; i < 2; i++)
	{
		_backGround[i]._image->render(getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);
	}
	
	OBJECTMANAGER->render(getMemDC());
	
	_backGround[2]._image->render(getMemDC(), 0, 0, CAMERAMANAGER->getCamera().left, CAMERAMANAGER->getCamera().top, WINSIZEX, WINSIZEY);
	
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		char str[64];
		sprintf_s(str, "%d", _ptMouse.x + CAMERAMANAGER->getCamera().left);
		TextOut(getMemDC(), 10, 100, str, strlen(str));
		sprintf_s(str, "%d", _ptMouse.y + CAMERAMANAGER->getCamera().top);
		TextOut(getMemDC(), 80, 100, str, strlen(str));
	}
	
	SelectObject(getMemDC(), GetStockObject(DC_BRUSH));
	SetDCBrushColor(getMemDC(), RGB(255, 255, 255));
	SelectObject(getMemDC(), GetStockObject(DC_PEN));
	SetDCPenColor(getMemDC(), RGB(0, 0, 0));
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

	_playerManager->render();
	_enemyManager->render();
	if (KEYMANAGER->isToggleKey('8'))
	{
		_backGroundPixel->render(getMemDC(), 0, 0, _rcCamera.left, _rcCamera.top, WINSIZEX, WINSIZEY);
		_ladderPixel->render(getMemDC(), 0, 0, _rcCamera.left, _rcCamera.top, WINSIZEX, WINSIZEY);
	}
	_test->render();


	//테스트
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