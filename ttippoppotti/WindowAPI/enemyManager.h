#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "soldier.h"

class playerManager;
class mapData;

class enemyManager : public gameNode
{
private:
	playerManager* _playerManager;
	mapData* _mapData;
	vector<enemy*> _vSoldier;
	eBullet* _eBullet;

public:
	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	void setMapData(mapData* mapData) { _mapData = mapData; }

	vector<enemy*> getVEnemy() { return _vSoldier; }
	eBullet* getVEBullet() { return _eBullet; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void collision();
	void setEnemy();
	
	enemyManager() {}
	~enemyManager() {}
};

