#pragma once
#include "singletonBase.h"
class cameraManager : public singletonBase<cameraManager>
{
	RECT _rcCamera;
public:
	RECT getCamera() { return _rcCamera; }
	void setCamera(RECT rc) { _rcCamera = rc; }
	//카메라매니져 초기화
	HRESULT init();
	//카메라매니져 해제
	void release();

	cameraManager() {}
	~cameraManager() {}
};

