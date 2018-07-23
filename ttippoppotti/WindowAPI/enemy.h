#pragma once
#include "gameNode.h"

#define COOLTIME 10	// _frameIndex 바뀌는 속도

enum enemyStatus
{
	IDLE_LEFT, IDLE_RIGHT,
	WALK_LEFT, WALK_RIGHT,
	RUN_LEFT, RUN_RIGHT,
	FIRE_LEFT, FIRE_RIGHT,
	KNOCK_BACK_LEFT, KNOCK_BACK_RIGHT,
	HIT_LEFT, HIT_RIGHT,
};

//부모클래스 => 이놈을 상속받아서 보스, 일반몬스터등을 만든다
class enemy : public gameNode
{
private:
	enemyStatus _enemyStatus;
	image * _bodyImage;
	image * _armImage;
	image* _deadImage;
	
	RECT _enemyRC;
	RECT _enemySightRC;
	float _speed;
	float _gravity;
	int _x, _y;
	int _hp;
	bool _isLeft;

	int _frameCount, _frameIndex, _actionCount;
	
public:
	virtual HRESULT init(int x, int y, int hp);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual int getHP() { return _hp; }
	virtual int getX() { return _x; }
	virtual int getY() { return _y;	}
	virtual float getSpeed() { return _speed; }
	virtual float getGravity() { return _gravity; }
	virtual RECT getEnemyRC() { return _enemyRC; }
	virtual RECT getEnemySightRC() { return _enemySightRC; }
	virtual enemyStatus getEnemyStatus() { return _enemyStatus; }

	virtual void setHP(int hp) { _hp = hp; }
	virtual void setX(int x) { _x = x; }
	virtual void setY(int y) { _y = y; }
	virtual void setSpeed(float speed) { _speed = speed; }
	virtual void setGravity(float gravity) { _gravity = gravity; }
	virtual void setEnemyRC(RECT enemyRC) { _enemyRC = enemyRC; }
	virtual void setEnemySightRC(RECT enemySightRC) { _enemySightRC = enemySightRC; }
	virtual void setEnemyStatus(enemyStatus enemyStatus) { _enemyStatus = enemyStatus; }
	
	virtual void move();
	virtual void frameAnimate();
	
	enemy() {}
	virtual ~enemy() {}
};

