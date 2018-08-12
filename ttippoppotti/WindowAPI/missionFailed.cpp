#include "stdafx.h"
#include "missionFailed.h"

HRESULT missionFailed::init(void)
{
	_missionFailed = IMAGEMANAGER->findImage("missionFailed");
	_blackWindow = new image;
	_blackWindow->init(WINSIZEX, WINSIZEY);
	
	_count = _renderCount = 0;
	_alpha = 0;
	_targetX = WINSIZEX / 2 - _missionFailed->getWidth() / 2;
	_x = WINSIZEX;
	return S_OK;
}

void missionFailed::release(void)
{
	SAFE_DELETE(_blackWindow);
}

void missionFailed::update(void)
{
	_x += cosf(180.f * 3.14f / 180) * 100;
	if (_x <= _targetX)
	{
		_x = _targetX;
	}

	_alpha += 25;
	if (_alpha >= 255)
	{
		_alpha = 255;
	}
	_renderCount++;
	if (_renderCount >= 50)
	{
		_count++;
		if (_count >= 100)
		{
			SCENEMANAGER->getCurrentScene()->release();
			SCENEMANAGER->getCurrentScene()->init();
		}
	}
}

void missionFailed::render(void)
{
	if (_renderCount >= 50)
	{
		_blackWindow->alphaRender(getMemDC(), _alpha);
		_missionFailed->render(getMemDC(), _x, WINSIZEY / 2 - _missionFailed->getHeight() / 2);
	}
}
