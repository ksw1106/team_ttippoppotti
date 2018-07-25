#pragma once
#include "gameNode.h"

#define COOLTIME 7	// _frameIndex 바뀌는 속도

enum enemyStatus
{
	IDLE_LEFT, IDLE_RIGHT,
	WALK_LEFT, WALK_RIGHT,
	RUN_LEFT, RUN_RIGHT,
	WARNING_LEFT, WARNING_RIGHT,
	FIRE_LEFT, FIRE_RIGHT,
	FIRE_IDLE_LEFT, FIRE_IDLE_RIGHT,
	KNOCK_BACK_LEFT, KNOCK_BACK_RIGHT,
	DEAD_LEFT, DEAD_RIGHT,
};

//부모클래스 => 이놈을 상속받아서 보스, 일반몬스터등을 만든다
class enemy : public gameNode
{
private:
	enemyStatus _enemyStatus;
	image * _bodyImage;
	image * _armImage;
	image * _warnSign;
	image* _deadImage;
	RECT _enemyRC;
	RECT _enemySightRC;
	float _speed;
	float _gravity;
	float _kbSpeed;		// 맞았을 때 날아가는 속도
	int _x, _y;
	int _hp;
	bool _isLeft;
	bool _isAlarm;

	int _frameCount, _frameIndex, _frameIndex2, _frameIndex3;
	int	_actionCount;
	
public:
	virtual HRESULT init(const char* bodyImage, const char* armImage, int x, int y, int hp);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual RECT getEnemyRC() { return _enemyRC; }
	virtual RECT getEnemySightRC() { return _enemySightRC; }
	virtual float getSpeed() { return _speed; }
	virtual float getGravity() { return _gravity; }
	virtual int getX() { return _x; }
	virtual int getY() { return _y; }
	virtual int getHP() { return _hp; }
	virtual bool getDirection() { return _isLeft; }
	virtual bool getAlarm() { return _isAlarm; }
	virtual enemyStatus getStatus() { return _enemyStatus; }
	virtual int getFrameIndex() { return _frameIndex; }
	virtual int getFrameIndex2() { return _frameIndex2; }

	virtual void setEnemyRC(RECT enemyRC) { _enemyRC = enemyRC; }
	virtual void setEnemySightRC(RECT enemySightRC) { _enemySightRC = enemySightRC; }
	virtual void setSpeed(float speed) { _speed = speed; }
	virtual void sestGravity(float gravity) { _gravity = gravity; }
	virtual void setX(int x) { _x = x; }
	virtual void setY(int y) { _y = y; }
	virtual void setHP(int hp) { _hp = hp; }

	virtual void move();
	virtual void frameAnimate();
	virtual void warning();
	
	enemy() {}
	virtual ~enemy() {}
};

