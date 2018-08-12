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
	gBullet * _gBullet;
	gMissile * _gMissile;
	xMissile * _xMissile;
	image * _p1Bubble;
	
	RECT temp;			
	bool hit_left, hit_right, hit_top, hit_bottom;

	int _count, _index, _animationSpeed;

	int _fireCount;
	bool _rambroFire;

	RECT _rcKnifeRight;
	RECT _rcKnifeLeft;
	bool _knifeCollision;

	bool _isLadder;

	bool _rambroChange;

	int _missileCount;
	bool _isMissile;
	bool _missile;

	RECT _rc8;

	RECT _rcMissileRight;
	RECT _rcMissileLeft;
	bool _rambroGrenade;
	int _grenadeCount;
	bool _isGrenade;

	bool _xMissileCollision;
	bool _xMissileColl;

public:

	void setEnemyManager(enemyManager* enemyManager) { _enemyManager = enemyManager; }
	void setMapData(mapData* mapData) { _mapData = mapData; }
	player* getPlayer() { return _player; }

	pBullet* getPBullet() { return _pBullet; }
	pGrenade* getPGrenade() { return _pGrenade; }
	gBullet* getGBullet() { return _gBullet; }
	gMissile* getGMissile() { return _gMissile; }
	xMissile* getXMissile() { return _xMissile; }

	HRESULT init(int num);
	void release(void);
	void update(void);
	void render(void);

	void rambroDie();
	void rambroCollision();
	void chuckCollision();
	void p1Bubble();

	playerManager();
	~playerManager();
};

