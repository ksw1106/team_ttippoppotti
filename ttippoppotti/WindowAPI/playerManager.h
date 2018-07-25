#pragma once
#include "gameNode.h"
#include "player.h"

class enemyManager;
class mapData;

#define G_NUM 0.05f;
#define S_NUM 23.0f;
#define SPEED 7
#define MAX_POSE 5


enum pose
{
	IDLE, RUN, FAST_RUN, JUMP, ROLL
};

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
	float angle;
};


class playerManager : public gameNode
{

private:
	enemyManager * _enemyManager;
	player _player;
	mapData* _mapData;
	image * _ramBro[MAX_POSE];

	playerState _state;
	tagBroforce _broforce;
	pose _pose;
	RECT temp;

	RECT _isCollision[2];
	bool _isLeftFall;
	bool _isRightFall;

	int _index, _count;
	int _speed;
	bool _isLeft;

public:
	void setEnemyManager(enemyManager* enemyManager) { _enemyManager = enemyManager; }
	void setMap(mapData* mapData) { _mapData = mapData; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);



	playerManager();
	~playerManager();
};

