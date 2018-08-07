#pragma once
#include "gameNode.h"

enum bossStatus
{
	LEFT_IDLE, MID_IDLE, RIGHT_IDLE,
	LEFT_FIRE_BULLET, RIGHT_FIRE_BULLET,
	LEFT_FIRE_ROCKET, RIGHT_FIRE_ROCKET

};

struct tagBossImage
{
	image* bodyImage;
	image* rotorImage;
	image* gunImage;
	int bodyIndex;
	int rotorIndex;
	int gunIndex;
};

struct tagBoss
{
	tagBossImage img;
	float x, y;
	float speed;
	float angle;
	int count;
	int hp;	
	
};

class boss : public gameNode
{
private:
	tagBoss _terrorKopter;

public:
	boss() {}
	~boss() {}
};

