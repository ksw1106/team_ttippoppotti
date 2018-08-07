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
	fPos _fPos[12];
	fPos _prisonerPos[2];
	fPos _boxPos[14];
	fPos _drumRedPos[1];
	fPos _drumGrayPos[1];
	fPos _truckPos[1];
	fPos _helicopterPos[1];
	fPos _amFlagPos[3];
	fPos _amFlagPolePos[2];
	fPos _enemyFlagPos[2];
public:
	vector<objectA*> getVObject() { return _vObject; }
	void setMapData(mapData* mapData) { _mapData = mapData;	}
	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	//오브젝트매니져 초기화
	HRESULT init();
	//오브젝트매니져 해제
	void release();
	void update();
	void render(HDC hdc);
	objectManager() {}
	~objectManager() {}
};