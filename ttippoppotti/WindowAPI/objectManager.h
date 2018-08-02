#pragma once
#include "singletonBase.h"
#include "objectA.h"

class mapData;

class objectManager : public singletonBase<objectManager>
{
	mapData* _mapData;
	vector<objectA> _vObject;
public:
	void setMapData(mapData* mapData) { _mapData = mapData;	}
	//������Ʈ�Ŵ��� �ʱ�ȭ
	HRESULT init();
	//������Ʈ�Ŵ��� ����
	void release();
	void update();
	void render(HDC hdc);
	objectManager() {}
	~objectManager() {}
};