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
	player* _playerChange[2];
	mapData* _mapData;

	pBullet * _pBullet;
	pGrenade * _pGrenade;
	image * _p1Bubble;
	
	RECT temp;			
	bool hit_left, hit_right, hit_top, hit_bottom;

	int _count, _index, _animationSpeed;

	int _fireCount;

	RECT _rcKnifeRight;
	RECT _rcKnifeLeft;
	bool _knifeCollision;

	bool _isLadder;

	bool _rambroChange;

	RECT _rc8;

public:

	void setEnemyManager(enemyManager* enemyManager) { _enemyManager = enemyManager; }
	void setMapData(mapData* mapData) { _mapData = mapData; }
	player* getPlayer() { return _player; }

	pBullet* getPBullet() { return _pBullet; }
	pGrenade* getPGrenade() { return _pGrenade; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void rambroDie();
	void collision();
	void p1Bubble();

	playerManager();
	~playerManager();
};

