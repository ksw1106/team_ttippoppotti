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
	int _flagCount;
	int _maxFlag;
	bool _isGameClear;
	bool _isDead;
public:
	vector<objectA*> getVObject() { return _vObject; }
	int getFlagCount() { return _flagCount; }
	bool getGameClear() { return _isGameClear; }

	void setFlagCount(int flagCount) { _flagCount = flagCount; }
	void setIsDead(bool isDead) { _isDead = isDead; }
	void setMapData(mapData* mapData) { _mapData = mapData;	}
	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	void collisionProcess();
	//오브젝트매니져 초기화
	HRESULT init(int num);
	//오브젝트매니져 해제
	void release();
	void update();
	void render(HDC hdc);
	objectManager() {}
	~objectManager() {}
};