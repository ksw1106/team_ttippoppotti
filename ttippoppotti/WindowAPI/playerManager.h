#pragma once
#include "gameNode.h"
#include "player.h"
#include "bullet.h"

class enemyManager;
class mapData;

class playerManager : public gameNode
{

private:
	enemyManager * _enemyManager;
	player* _player;
	mapData* _mapData;

	pBullet* _pBullet;
	
	RECT temp;
	bool hit_left, hit_right, hit_top, hit_bottom;

	float _ground;
	int count = 0;
	int _fireCount;
	bool _change;

	RECT _rcPlyaer;

public:

	void setEnemyManager(enemyManager* enemyManager) { _enemyManager = enemyManager; }
	void setMapData(mapData* mapData) { _mapData = mapData; }
	player* getPlayer() { return _player; }

	pBullet* getPBullet() { return _pBullet; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void collision();

	playerManager();
	~playerManager();
};

