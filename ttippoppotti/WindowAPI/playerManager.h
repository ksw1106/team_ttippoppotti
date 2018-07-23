#pragma once
#include "gameNode.h"
#include "player.h"

class enemyManager;

class playerManager : public gameNode
{
	enemyManager* _enemyManager;
	player _player;
public:
	void setEnemyManager(enemyManager* enemyManager) { _enemyManager = enemyManager; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	playerManager();
	~playerManager();
};

