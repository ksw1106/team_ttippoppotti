#pragma once
#include "singletonBase.h"
class cameraManager : public singletonBase<cameraManager>
{
	RECT _rcCamera;
public:
	RECT getCamera() { return _rcCamera; }
	void setCamera(RECT rc) { _rcCamera = rc; }
	//ī�޶�Ŵ��� �ʱ�ȭ
	HRESULT init();
	//ī�޶�Ŵ��� ����
	void release();

	cameraManager() {}
	~cameraManager() {}
};

