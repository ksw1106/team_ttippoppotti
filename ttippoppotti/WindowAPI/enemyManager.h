#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "enemy.h"

class playerManager;

class enemyManager : public gameNode
{
private:
	playerManager* _playerManager;
	enemy* _enemy;

public:
	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	enemyManager() {}
	~enemyManager() {}
};

