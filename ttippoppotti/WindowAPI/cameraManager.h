#pragma once
#include "singletonBase.h"
class cameraManager : public singletonBase<cameraManager>
{
	RECT _rcCamera;
	RECT _rcTemp;
public:
	RECT getCamera() { return _rcCamera; }
	void setCamera(RECT rc) { _rcCamera = rc; }

	//�ӽ� ���ľ���
	RECT CameraPosSetting(RECT rc);
	bool CameraIn(RECT rc);
	//ī�޶�Ŵ��� �ʱ�ȭ
	HRESULT init();
	//ī�޶�Ŵ��� ����
	void release();

	cameraManager() {}
	~cameraManager() {}
};