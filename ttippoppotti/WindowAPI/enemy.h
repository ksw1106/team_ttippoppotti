#pragma once
#include "gameNode.h"

#define COOLTIME 7	// _frameIndex �ٲ�� �ӵ�

enum enemyStatus
{
	E_IDLE = 0,
	E_WALK = 1,
	E_DOUBT = 2,
	E_KNOCK_BACK = 3,	
	E_FLY_AWAY = 4,
	E_DEAD = 5,
};

enum gunStatus
{
	G_IDLE = 0,
	G_TARGETING = 1,
	G_READY = 2,
	G_FIRE = 3,
	G_RELOAD = 4,
};

//�θ�Ŭ���� => �̳��� ��ӹ޾Ƽ� ����, �Ϲݸ��͵��� �����
class enemy : public gameNode
{
private:
	enemyStatus _enemyStatus;
	gunStatus _gunStatus;
	image * _bodyImage[6];
	image * _armImage[5];
	image * _warnSign;
	image * _doubtSign;
	image* _deadImage;

	RECT _enemyRC;
	RECT _enemySightRC;

	float _angle;
	float _speed;
	float _gravity;
	float _kbSpeed;		// �¾��� �� ���ư��� �ӵ�
	int _x, _y;
	int _hp;
	bool _isLeft;
	bool _isAlarm;

	int _frameCount, _frameIndex, _frameIndex2, _frameIndex3, _frameIndex4;
	int	_actionSpeed;		// �ൿ �ٲ� ����
		
	int _randomNumber;

public:
	virtual HRESULT init(int x, int y, int hp, int randomNum);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//virtual image* getBodyImage() { return _bodyImage[_enemyStatus]; }
	//virtual image* getArmImage() { return _armImage[_gunStatus]; }
	virtual RECT getEnemyRC() { return _enemyRC; }
	virtual RECT getEnemySightRC() { return _enemySightRC; }
	virtual float getSpeed() { return _speed; }
	virtual float getGravity() { return _gravity; }
	virtual int getX() { return _x; }
	virtual int getY() { return _y; }
	virtual int getHP() { return _hp; }
	virtual bool getDirection() { return _isLeft; }
	virtual bool getAlarm() { return _isAlarm; }
	virtual enemyStatus getBodyStatus() { return _enemyStatus; }
	virtual gunStatus getArmStatus() { return _gunStatus; }
	virtual int getFrameIndex() { return _frameIndex; }
	virtual int getFrameIndex2() { return _frameIndex2; }
	virtual float getEnemyAngle() { return _angle; }

	virtual void setBodyImage(image* bodyImage) { _bodyImage[_enemyStatus] = bodyImage; }
	virtual void setArmImage(image* armImage) { _armImage[_gunStatus] = armImage; }
	virtual void setEnemyRC(RECT enemyRC) { _enemyRC = enemyRC; }
	virtual void setEnemySightRC(RECT enemySightRC) { _enemySightRC = enemySightRC; }
	virtual void setSpeed(float speed) { _speed = speed; }
	virtual void setGravity(float gravity) { _gravity = gravity; }
	virtual void setX(int x) { _x = x; }
	virtual void setY(int y) { _y = y; }
	virtual void setHP(int hp) { _hp = hp; }
	virtual void setAlarm(bool isAlarm) { _isAlarm = isAlarm; }
	virtual void setBodyStatus(enemyStatus enemyStat) { _enemyStatus = enemyStat; }
	virtual void setArmStatus(gunStatus gunStat) { _gunStatus = gunStat; }
	virtual void setDirection(bool isLeft) { _isLeft = isLeft; }
	virtual void setEnemyAngle(float angle) { _angle = angle; }

	virtual void move();
	virtual void flyAway();
	virtual void controlAI(int randomNum);
	
	virtual void frameAnimate();	
	virtual void knockBackMove();	// �Ѿ˸¾����� �ڷ� ���ư�
			
	enemy() {}
	virtual ~enemy() {}
};

