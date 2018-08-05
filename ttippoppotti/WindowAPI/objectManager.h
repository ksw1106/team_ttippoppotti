#pragma once
#include "singletonBase.h"
#include "objectA.h"

class mapData;

struct fPos
{
	float x;
	float y;
};
class objectManager : public singletonBase<objectManager>
{
	mapData* _mapData;
	vector<objectA*> _vObject;
	objectFactory* _factory;
	fPos _fPos[6];
	fPos _prisonerPos[2];
	fPos _boxPos[14];
	fPos _drumRedPos[1];
	fPos _drumGrayPos[1];
	fPos _truckPos[1];
	fPos _helicopterPos[1];
	fPos _amFlagPos[2];
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