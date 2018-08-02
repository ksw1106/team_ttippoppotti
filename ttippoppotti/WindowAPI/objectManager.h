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
	//오브젝트매니져 초기화
	HRESULT init();
	//오브젝트매니져 해제
	void release();
	void update();
	void render(HDC hdc);
	objectManager() {}
	~objectManager() {}
};