#pragma once
#include "gameNode.h"
#include "player.h"

class enemyManager;
class mapData;

class playerManager : public gameNode
{

private:
	enemyManager * _enemyManager;
	player* _player;
	mapData* _mapData;
	
	RECT temp;
	bool hit_left, hit_right;
	float _ground;

public:
	void setEnemyManager(enemyManager* enemyManager) { _enemyManager = enemyManager; }
	void setMapData(mapData* mapData) { _mapData = mapData; }
	player* getPlayer() { return _player; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	playerManager();
	~playerManager();
};

