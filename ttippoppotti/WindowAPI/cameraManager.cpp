#include "stdafx.h"
#include "cameraManager.h"

bool cameraManager::CameraIn(RECT rc)
{
	if (_rcCamera.left >= rc.right)
		return true;

	if (_rcCamera.left+WINSIZEY >= rc.left)
		return true;

	if (_rcCamera.top <= rc.bottom)
		return true;

	if (_rcCamera.top+WINSIZEY <= rc.top)
		return true;

	return false;
}

HRESULT cameraManager::init()
{
	return S_OK;
}

void cameraManager::release()
{
}
