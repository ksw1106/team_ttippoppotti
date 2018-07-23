#pragma once
#include "gameNode.h"
#include "player.h"

class enemyManager;
#define J_NUM 5.0f;
#define G_NUM 0.05f;
#define S_NUM 3.0f;

enum playerState
{
	RIGHT_IDLE, LEFT_IDLE,
	RIGHT_RUN, LEFT_RUN,
	RIGHT_JUMP, LEFT_JUMP,
	RIGHT_HANG, LEFT_HANG,
	LADDER,
};
struct tagBroforce
{
	RECT rc;
	float x, y;
	float speed;
	float gravity;
	float jumpPower;
};


class playerManager : public gameNode
{

private:
	enemyManager * _enemyManager;
	player _player;


	playerState _state;
	tagBroforce _broforce;
	bool _iscollision;

public:
	void setEnemyManager(enemyManager* enemyManager) { _enemyManager = enemyManager; }
	
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	playerManager();
	~playerManager();
};

