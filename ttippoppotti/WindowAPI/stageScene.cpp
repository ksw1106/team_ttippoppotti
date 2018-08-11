#include "stdafx.h"
#include "stageScene.h"


HRESULT stageScene::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화를 한다

	soundName[0] = "3";
	soundName[1] = "2";
	soundName[2] = "1";
	soundName[3] = "go";
	
	soundCount = 0;

	_playerManager = new playerManager;
	_playerManager->init(1);

	_enemyManager = new enemyManager;
	_enemyManager->init(1);

	_mapData = new mapData;
	_mapData->init(1);

	_mapData->setObjectPixel("backGround_object");
	_mapData->setBackGroundMap("backGround_pixel");

	_test = new testScene_kmy;
	_test->init();

	_stageClear = new stageClear;
	_stageClear->init();
	_stageClear->setEnemyManager(_enemyManager);

	EFFECTMANAGER->init();
	_playerManager->setMapData(_mapData);
	_enemyManager->setMapData(_mapData);
	OBJECTMANAGER->setMapData(_mapData);
	OBJECTMANAGER->setPlayerManager(_playerManager);
	OBJECTMANAGER->init(1);				//오브젝트매니져 초기화
	_playerManager->setEnemyManager(_enemyManager);
	_enemyManager->setPlayerManager(_playerManager);

	COLLISIONMANAGER->setPixelMap(IMAGEMANAGER->findImage("backGround_pixel"), IMAGEMANAGER->findImage("ladder_pixel"));

	for (int i = 0; i < 3; i++)
	{
		ZeroMemory(&_backGround[i], sizeof(world));
		_backGround[i]._rc = RectMake(0, 2878 - WINSIZEY, 5755, WINSIZEY);
	}

	_backGround[0]._image = IMAGEMANAGER->findImage("backGround");
	/*_backGround[1]._image = IMAGEMANAGER->findImage("backGround_tree4");
	_backGround[2]._image = IMAGEMANAGER->findImage("backGround_tree3");
	_backGround[3]._image = IMAGEMANAGER->findImage("backGround_tree2");
	_backGround[4]._image = IMAGEMANAGER->findImage("backGround_tree1");*/
	_backGround[1]._image = IMAGEMANAGER->findImage("backGround_rock");
	_backGround[2]._image = IMAGEMANAGER->findImage("backGround_object");

	_camDebug = false;
	_rcCamera = RectMakeCenter(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), WINSIZEX, WINSIZEY);
	CAMERAMANAGER->setCamera(_rcCamera);

	_isClear = false;
	return S_OK;
}

void stageScene::release(void)
{
	//init함수에서 동적할당 new를 사용했다면 이곳에서 delete 사용한다
	//이미지매니져 사용시 safe_delete 할 필요 없다

	SAFE_DELETE(_playerManager);
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_mapData);
	SAFE_DELETE(_stageClear);
}

void stageScene::update(void)
{
	
	switch (soundCount)
	{
	case 0:
		if (!SOUNDMANAGER->isPlaySound(soundName[soundCount]))
		{
			SOUNDMANAGER->play(soundName[soundCount], 0.5f);
			soundCount++;
		}
		break;
	case 1:
		if (!SOUNDMANAGER->isPlaySound(soundName[soundCount-1]))
		{
			SOUNDMANAGER->play(soundName[soundCount], 0.5f);
			soundCount++;
		}
		break;
	case 2:
		if (!SOUNDMANAGER->isPlaySound(soundName[soundCount - 1]))
		{
			SOUNDMANAGER->play(soundName[soundCount], 0.5f);
			soundCount++;
		}
		break;
	case 3:
		if (!SOUNDMANAGER->isPlaySound(soundName[soundCount - 1]))
		{
			SOUNDMANAGER->play(soundName[soundCount], 0.5f);
			soundCount++;
		}
		break;
	case 4:
		if (SOUNDMANAGER->isPlaySound(soundName[soundCount - 1]))
		{
			SOUNDMANAGER->play("1stage", 0.5f);
			soundCount++;
		}
		break;
	}
	
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
	
	CAMERAMANAGER->setCamera(_rcCamera);

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		CAMERAMANAGER->CameraShake();
	}

	if (_isClear)
	{
		_stageClear->update();
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
		IMAGEMANAGER->findImage("backGround_pixel")->render(getMemDC(), 0, 0, _rcCamera.left, _rcCamera.top, WINSIZEX, WINSIZEY);
		IMAGEMANAGER->findImage("ladder_pixel")->render(getMemDC(), 0, 0, _rcCamera.left, _rcCamera.top, WINSIZEX, WINSIZEY);
	}
	_test->render();

	//테스트
	if (_isClear)
		_stageClear->render();
}