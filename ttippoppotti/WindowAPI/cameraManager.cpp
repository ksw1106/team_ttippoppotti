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

HRESULT cameraManager::init()
{
	return S_OK;
}

void cameraManager::release()
{
}
