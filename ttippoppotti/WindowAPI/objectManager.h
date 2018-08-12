#pragma once
#include "singletonBase.h"
#include "objectA.h"

class mapData;
class playerManager;

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
	playerManager* _playerManager;
	fPos _fPos[23];
	fPos _prisonerPos[2];
	fPos _boxPos[40];
	fPos _drumRedPos[6];
	fPos _drumGrayPos[3];
	fPos _truckPos[1];
	fPos _helicopterPos[1];
	fPos _amFlagPos[3];
	fPos _amFlagPolePos[2];
	fPos _enemyFlagPos[2];
	int drumRedTarget[6];
	int drumGrayTarget[3];
public:
	vector<objectA*> getVObject() { return _vObject; }
	void setMapData(mapData* mapData) { _mapData = mapData;	}
	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	void collisionProcess();
	//������Ʈ�Ŵ��� �ʱ�ȭ
	HRESULT init(int num);
	//������Ʈ�Ŵ��� ����
	void release();
	void update();
	void render(HDC hdc);
	objectManager() {}
	~objectManager() {}
};