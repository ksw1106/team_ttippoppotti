#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "enemy.h"

class playerManager;
class mapData;

class enemyManager : public gameNode
{
private:
	playerManager* _playerManager;
	mapData* _mapData;
	enemy* _enemy;

public:
	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	void setMapData(mapData* mapData) { _mapData = mapData; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	enemyManager() {}
	~enemyManager() {}
};

