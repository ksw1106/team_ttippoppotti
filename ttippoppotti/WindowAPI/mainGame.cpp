#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init(void)
//=============================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화를 한다
	
	_playerManager = new playerManager;
	_playerManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init();

	_backGround = IMAGEMANAGER->addImage("backGround", "background.bmp", 5755, 2878);
	_helicopter = IMAGEMANAGER->addFrameImage("helicopter", "helicopter.bmp", 1625, 182, 5, 1);
	IMAGEMANAGER->addImage("ladder", "ladder.bmp", 25, 237, true, RGB(255, 0, 255));

	_saveFlag = IMAGEMANAGER->addFrameImage("saveFlag", "saveFlag.bmp", 485, 110, 5, 1);

	_flagX = 3327.f;
	_flagY = 878.f;
	_isLeft = _isDown = false;
	_count = _index = _fcount = _findex = _speed = 0;
	_fspeed = 5;
	_x = 3400.f;
	_y = 500.f;
	_rcCamera = RectMake(0, 2878-1080, 5755, 1080);
	return S_OK;
}

//=============================================================
//	## 해제 ## release(void)
//=============================================================
void mainGame::release(void)
{
	gameNode::release();
	//init함수에서 동적할당 new를 사용했다면 이곳에서 delete 사용한다
	//이미지매니져 사용시 safe_delete 할 필요 없다

	SAFE_DELETE(_playerManager);
	SAFE_DELETE(_enemyManager);
}

//=============================================================
//	## 업데이트 ## update(void)
//=============================================================
void mainGame::update(void)
{
	gameNode::update();

	_playerManager->update();
	_enemyManager->update();

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
		if (_rcCamera.right >= _rcCamera.left + 10 + 1920)
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
		if (_rcCamera.bottom > _rcCamera.top + 10 + 1080)
		{
			_rcCamera.top += 10;
		}
	}

	if (_isDown)
	{
		_y+=0.5f;
		if (_y >= 500.f)
		{
			_isDown = false;
		}
	}
	else if (!_isDown)
	{
		_y-=0.5f;
		if (_y <= 495.f)
		{
			_isDown = true;
		}
	}

	FRAMEMANAGER->frameChange(_helicopter, _count, _index, _speed, _isLeft);
	FRAMEMANAGER->frameChange(_saveFlag, _fcount, _findex, _fspeed, _isLeft);
}

//=============================================================
//	## 렌더 ## render(void)
//=============================================================
void mainGame::render(void)
{
	//흰색 빈 비트맵(이것도 렌더에 그냥 둘것!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================

	_backGround->render(getMemDC(), 0, 0, _rcCamera.left, _rcCamera.top, WINSIZEX, WINSIZEY);
	_helicopter->frameRender(getMemDC(), _x - _rcCamera.left, _y - _rcCamera.top);
	IMAGEMANAGER->findImage("ladder")->render(getMemDC(), _x+169 - _rcCamera.left, _y+181 - _rcCamera.top);
	_saveFlag->frameRender(getMemDC(), _flagX - _rcCamera.left, _flagY - _rcCamera.top);
	_playerManager->render();
	_enemyManager->render();

//=============================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 둘것!!)
	this->getBackBuffer()->render(getHDC());
}
