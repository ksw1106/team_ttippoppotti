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

	//�ӽ� ���ľ���
	RECT CameraPosSetting(RECT rc);
	bool CameraIn(RECT rc);

	void CameraShakeOngoing();
	void CameraShake();
	//ī�޶�Ŵ��� �ʱ�ȭ
	HRESULT init();
	void update();
	//ī�޶�Ŵ��� ����
	void release();

	cameraManager() {}
	~cameraManager() {}
};