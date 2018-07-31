#pragma once
#include "singletonBase.h"
class cameraManager : public singletonBase<cameraManager>
{
	RECT _rcCamera;
	RECT _rcTemp;
	int _shakeCount;
	bool _shakeStart;
public:
	RECT getCamera() { return _rcCamera; }
	void setCamera(RECT rc) { _rcCamera = rc; }

	//임시 고쳐야함
	RECT CameraPosSetting(RECT rc);
	bool CameraIn(RECT rc);

	void CameraShakeOngoing();
	void CameraShake();
	//카메라매니져 초기화
	HRESULT init();
	void update();
	//카메라매니져 해제
	void release();

	cameraManager() {}
	~cameraManager() {}
};