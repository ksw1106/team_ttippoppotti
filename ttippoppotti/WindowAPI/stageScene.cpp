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
	_playerManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init();

	_mapData = new mapData;
	_mapData->init(1);

	_test = new testScene_kmy;
	_test->init();

	_playerManager->setMapData(_mapData);
	_enemyManager->setMapData(_mapData);
	_playerManager->setEnemyManager(_enemyManager);
	_enemyManager->setPlayerManager(_playerManager);

	for (int i = 0; i < 3; i++)
	{
		ZeroMemory(&_backGround[i], sizeof(object));
		_backGround[i]._rc = RectMake(0, 2878 - WINSIZEY, 5755, WINSIZEY);
	}

	_backGround[0]._image = IMAGEMANAGER->findImage("backGround");
	_backGround[1]._image = IMAGEMANAGER->findImage("backGround_rock");
	_backGround[2]._image = IMAGEMANAGER->findImage("backGround_object");

	_helicopter = IMAGEMANAGER->findImage("helicopter");
	
	_saveFlag = IMAGEMANAGER->findImage("saveFlag");
	_humanDead = IMAGEMANAGER->findImage("humanDead");
	IMAGEMANAGER->findImage("spike");
	_humanDead->setX(3754.f);
	_humanDead->setY(995.f);

	_flag = IMAGEMANAGER->findImage("flag");

	_flagCount = _flagIndex = 0;
	_flagSpeed = 5;

	_flagX = 3326.f;
	_flagY = 870.f;
	_isLeft = _isDown = false;
	_count = _index = _fcount = _findex = _speed = _hcount = _hindex = 0;
	_fspeed = 1;
	_hspeed = 5;
	_x = 3400.f;
	_y = 500.f;
	_rcCamera = RectMake(0, 2878 - WINSIZEY, 5755, WINSIZEY);
	CAMERAMANAGER->setCamera(_rcCamera);
	return S_OK;
}

void stageScene::release(void)
{
	//init함수에서 동적할당 new를 사용했다면 이곳에서 delete 사용한다
	//이미지매니져 사용시 safe_delete 할 필요 없다

	SAFE_DELETE(_playerManager);
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_mapData);
}

void stageScene::update(void)
{
	
	/*switch (soundCount)
	{
	case 0:
		if (!SOUNDMANAGER->isPlaySound(soundName[soundCount]))
		{
			SOUNDMANAGER->play(soundName[soundCount]);
			soundCount++;
		}
		break;
	case 1:
		if (!SOUNDMANAGER->isPlaySound(soundName[soundCount-1]))
		{
			SOUNDMANAGER->play(soundName[soundCount]);
			soundCount++;
		}
		break;
	case 2:
		if (!SOUNDMANAGER->isPlaySound(soundName[soundCount - 1]))
		{
			SOUNDMANAGER->play(soundName[soundCount]);
			soundCount++;
		}
		break;
	case 3:
		if (!SOUNDMANAGER->isPlaySound(soundName[soundCount - 1]))
		{
			SOUNDMANAGER->play(soundName[soundCount]);
			soundCount++;
		}
		break;
	}*/
	
	
	
	_playerManager->update();

	_enemyManager->update();
	_test->update();
	//이곳에서 계산식, 키보드, 마우스등등 업데이트를 한다
	//간단하게 이곳에서 코딩한다고 생각하면 된다
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_rcCamera.left > 0)
		{
			_rcCamera.left -= 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_rcCamera.right >= _rcCamera.left + 10 + WINSIZEX)
		{
			_rcCamera.left += 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_rcCamera.top > 10)
		{
			_rcCamera.top -= 10;
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_rcCamera.bottom > _rcCamera.top + 10 + WINSIZEY)
		{
			_rcCamera.top += 10;
		}
	}

	if (_isDown)
	{
		_y += 0.5f;
		if (_y >= 500.f)
		{
			_isDown = false;
		}
	}
	else if (!_isDown)
	{
		_y -= 0.5f;
		if (_y <= 495.f)
		{
			_isDown = true;
		}
	}

	FRAMEMANAGER->frameChange(_helicopter, _count, _index, _speed, _isLeft);
	FRAMEMANAGER->frameChange(_saveFlag, _fcount, _findex, _fspeed, _isLeft);
	FRAMEMANAGER->frameChange(_humanDead, _hcount, _hindex, _hspeed, _isLeft);
	FRAMEMANAGER->frameChange(_flag, _flagCount, _flagIndex, _flagSpeed, _isLeft);

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		POINT ptTemp;
		ptTemp.x = _ptMouse.x + _rcCamera.left;
		ptTemp.y = _ptMouse.y + _rcCamera.top;
		//충돌체크
		for (int i = 0; i < _mapData->getObject().size(); i++)
		{
			if (!_mapData->getObject()[i]._isActived) continue;

			if (PtInRect(&_mapData->getObject()[i]._rc, ptTemp))
			{
				
				mapObject obj = _mapData->getObject()[i];

				SelectObject(IMAGEMANAGER->findImage("backGround_object")->getMemDC(), GetStockObject(DC_BRUSH));
				SetDCBrushColor(IMAGEMANAGER->findImage("backGround_object")->getMemDC(), RGB(255, 0, 255));
				SelectObject(IMAGEMANAGER->findImage("backGround_object")->getMemDC(), GetStockObject(DC_PEN));
				SetDCPenColor(IMAGEMANAGER->findImage("backGround_object")->getMemDC(), RGB(255, 0, 255));
				RectangleMake(IMAGEMANAGER->findImage("backGround_object")->getMemDC(), obj._rc.left, obj._rc.top, obj._width, obj._height);

				obj._isActived = false;
				_mapData->setObject(obj, i);
				break; //임시
			}
		}
	}

	CAMERAMANAGER->setCamera(_rcCamera);
	
}

void stageScene::render(void)
{
	for (int i = 0; i < 3; i++)
	{
		_backGround[i]._image->render(getMemDC(), 0, 0, _rcCamera.left, _rcCamera.top, WINSIZEX, WINSIZEY);
	}
	
	//헬기 등 오브젝트
	if(CAMERAMANAGER->CameraIn(RectMake(_x, _y, _helicopter->getWidth(), _helicopter->getHeight())))
		_helicopter->frameRender(getMemDC(), _x - _rcCamera.left, _y - _rcCamera.top);
	if (CAMERAMANAGER->CameraIn(RectMake(_x+169, _y+181, IMAGEMANAGER->findImage("ladder")->getWidth(), IMAGEMANAGER->findImage("ladder")->getHeight())))
		IMAGEMANAGER->findImage("ladder")->render(getMemDC(), _x + 169 - _rcCamera.left, _y + 181 - _rcCamera.top);
	if (CAMERAMANAGER->CameraIn(RectMake(_flagX, _flagY, _saveFlag->getWidth(), _saveFlag->getHeight())))
		_saveFlag->frameRender(getMemDC(), _flagX - _rcCamera.left, _flagY - _rcCamera.top);
	if (CAMERAMANAGER->CameraIn(RectMake(IMAGEMANAGER->findImage("spike")->getX(), IMAGEMANAGER->findImage("spike")->getY(), IMAGEMANAGER->findImage("spike")->getWidth(), IMAGEMANAGER->findImage("spike")->getHeight())))
		IMAGEMANAGER->findImage("spike")->render(getMemDC(), IMAGEMANAGER->findImage("spike")->getX() - _rcCamera.left, IMAGEMANAGER->findImage("spike")->getY() - _rcCamera.top);
	if (CAMERAMANAGER->CameraIn(RectMake(_humanDead->getX(), _humanDead->getY(), _humanDead->getWidth(), _humanDead->getHeight())))
		_humanDead->frameRender(getMemDC(), _humanDead->getX() - _rcCamera.left, _humanDead->getY() - _rcCamera.top);
	if (CAMERAMANAGER->CameraIn(RectMake(_flag->getX(), _flag->getY(), _flag->getWidth(), _flag->getHeight())))
		_flag->frameRender(getMemDC(), _flag->getX() - _rcCamera.left, _flag->getY() - _rcCamera.top);
	
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		char str[64];
		sprintf_s(str, "%d", _ptMouse.x + _rcCamera.left);
		TextOut(getMemDC(), 10, 100, str, strlen(str));
		sprintf_s(str, "%d", _ptMouse.y + _rcCamera.top);
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
			
			RectangleMake(getMemDC(), _mapData->getObject()[i]._rc.left-_rcCamera.left, _mapData->getObject()[i]._rc.top-_rcCamera.top, _mapData->getObject()[i]._width, _mapData->getObject()[i]._height);
			sprintf(str, "%d", i);
			TextOut(getMemDC(), (_mapData->getObject()[i]._rc.left + (_mapData->getObject()[i]._rc.right - _mapData->getObject()[i]._rc.left) / 2) - _rcCamera.left,
				(_mapData->getObject()[i]._rc.top + (_mapData->getObject()[i]._rc.bottom - _mapData->getObject()[i]._rc.top) / 2) - _rcCamera.top, str, strlen(str));
		}
	}

	_playerManager->render();
	_enemyManager->render();
	_test->render();
}