#include "stdafx.h"
#include "cameraManager.h"

RECT cameraManager::CameraPosSetting(RECT rc)
{
	return RectMake(rc.left-_rcCamera.left, rc.top-_rcCamera.top, rc.right, rc.bottom);
}

bool cameraManager::CameraIn(RECT rc)
{
	if (IntersectRect(&_rcTemp, &RectMake(_rcCamera.left, _rcCamera.top, WINSIZEX, WINSIZEY), &rc))
		return true;
	else
		return false;
}

void cameraManager::CameraShakeOngoing()
{
	if (_shakeStart)
	{
		_rcCamera = RectMake(_rcCamera.left + RND->getInt(50), _rcCamera.top + RND->getInt(50), WINSIZEX, WINSIZEY);
		_shakeCount++;
	}

	if (_shakeCount > 15)
	{
		_shakeStart = false;
		_shakeCount = 0;
	}		
}

void cameraManager::CameraShake()
{
	_shakeStart = true;
}

HRESULT cameraManager::init()
{
	_shakeStart = false;
	_shakeCount = 0;
	return S_OK;
}

void cameraManager::update()
{
	CameraShakeOngoing();
}

void cameraManager::release()
{
}
