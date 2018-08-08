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
	player* _playerChuck;
	mapData* _mapData;

	pBullet * _pBullet;
	pGrenade * _pGrenade;
	image * _p1Bubble;
	
	RECT temp;			
	bool hit_left, hit_right, hit_top, hit_bottom;

	float _ground;
	int _count, _index, _animationSpeed;
	int count = 0;
	int _fireCount;
	bool _change;
	bool _isLadder;

	RECT _rcKnifeRight;
	RECT _rcKnifeLeft;
	int _knifeCount;
	bool _knifeCollision;

	bool _startImg;
	int _startCount;
	int _startIndex;

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

