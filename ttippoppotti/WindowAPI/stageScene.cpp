#include "stdafx.h"
#include "stageScene.h"


HRESULT stageScene::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ�� �Ѵ�

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

	EFFECTMANAGER->init();

	_playerManager->setMapData(_mapData);
	_enemyManager->setMapData(_mapData);
	OBJECTMANAGER->setMapData(_mapData);
	OBJECTMANAGER->setPlayerManager(_playerManager);
	OBJECTMANAGER->init();				//������Ʈ�Ŵ��� �ʱ�ȭ
	_playerManager->setEnemyManager(_enemyManager);
	_enemyManager->setPlayerManager(_playerManager);

	for (int i = 0; i < 7; i++)
	{
		ZeroMemory(&_backGround[i], sizeof(world));
		_backGround[i]._rc = RectMake(0, 2878 - WINSIZEY, 5755, WINSIZEY);
	}

	_backGround[0]._image = IMAGEMANAGER->findImage("backGround");
	//_backGround[1]._image = IMAGEMANAGER->findImage("backGround_tree4");
	//_backGround[2]._image = IMAGEMANAGER->findImage("backGround_tree3");
	//_backGround[3]._image = IMAGEMANAGER->findImage("backGround_tree2");
	//_backGround[4]._image = IMAGEMANAGER->findImage("backGround_tree1");
	_backGround[1]._image = IMAGEMANAGER->findImage("backGround_rock");
	_backGround[2]._image = IMAGEMANAGER->findImage("backGround_object");

	_helicopter = IMAGEMANAGER->findImage("helicopter");
	
	_saveFlag = IMAGEMANAGER->findImage("saveFlag");

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
	_camDebug = false;
	_rcCamera = RectMakeCenter(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), WINSIZEX, WINSIZEY);
	CAMERAMANAGER->setCamera(_rcCamera);
	return S_OK;
}

void stageScene::release(void)
{
	//init�Լ����� �����Ҵ� new�� ����ߴٸ� �̰����� delete ����Ѵ�
	//�̹����Ŵ��� ���� safe_delete �� �ʿ� ����

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
	OBJECTMANAGER->update();
	_test->update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	//�����ϰ� �̰����� �ڵ��Ѵٰ� �����ϸ� �ȴ�

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
	//FRAMEMANAGER->frameChange(_humanDead, _hcount, _hindex, _hspeed, _isLeft);
	FRAMEMANAGER->frameChange(_flag, _flagCount, _flagIndex, _flagSpeed, _isLeft);

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		POINT ptTemp;
		ptTemp.x = _ptMouse.x + CAMERAMANAGER->getCamera().left;
		ptTemp.y = _ptMouse.y + CAMERAMANAGER->getCamera().top;
		//�浹üũ
		for (int i = 0; i < _mapData->getObject().size(); i++)
		{
			if (!_mapData->getObject()[i]._isActived) continue;

			if (PtInRect(&_mapData->getObject()[i]._rc, ptTemp))
			{
				
				_mapData->deleteMap(i);
				break; //�ӽ�
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

	OBJECTMANAGER->update();
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
	char str[64];
	sprintf(str, "%d", _camDebug);
	TextOut(getMemDC(), 200, 200, str, strlen(str));

	_playerManager->render();
	_enemyManager->render();
	//IMAGEMANAGER->findImage("backGround_pixel")->render(getMemDC(), 0, 0, _rcCamera.left, _rcCamera.top, WINSIZEX, WINSIZEY);
	_test->render();
}