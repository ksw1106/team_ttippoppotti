#pragma once
#include "gameNode.h"

enum brovilStatus
{
	BROVIL_IDLE,
	BROVIL_WALK,
	BROVIL_KNOCK_BACK,
	BROVIL_DEAD,
	BROVIL_DISAPPEAR,
};

class brovil : public gameNode
{
private:
	brovilStatus _status;
	image * _bodyImage[5];	
	image * _warnSign;
	image * _doubtSign;
	
	RECT _rc;
	RECT _rcSight;

	float _angle;
	float _speed;
	float _gravity;
	float _accel;
	float _kbSpeed;		// 맞았을 때 날아가는 속도
	int _x, _y;
	int _hp;
	bool _isLeft;
	bool _isOn;
	bool _isAlarm;
	bool _isAlarm2;

	int _frameCount, _frameIndex, _frameIndex2, _frameIndex3, _frameIndex4;
	int	_actionSpeed;		// 행동 바뀔 변수
	int _randomNumber;		

public:
	HRESULT init(int x, int y, int randomNum);
	void release(void);
	void update(void);
	void render(void);

	image* getBodyImage() { return _bodyImage[_status]; }
	RECT getRC() { return _rc; }
	RECT getRCsight() { return _rcSight; }
	float getSpeed() { return _speed; }
	float getGravity() { return _gravity; }
	int getX() { return _x; }
	int getY() { return _y; }
	int getHP() { return _hp; }
	bool getDirection() { return _isLeft; }
	bool getAlarm() { return _isAlarm; }
	bool getAlarm2() { return _isAlarm2; }
	brovilStatus getStatus() { return _status; }
	int getFrameIndex() { return _frameIndex; }
	int getFrameIndex2() { return _frameIndex2; }
	float getEnemyAngle() { return _angle; }
	
	float getAccel() { return _accel; }
	bool getIsOn() { return _isOn; }

	void setBodyImage(image* bodyImage) { _bodyImage[_status] = bodyImage; }
	void setRC(RECT rc) { _rc = rc; }
	void setRCsight(RECT rcSight) { _rcSight = rcSight; }
	void setSpeed(float speed) { _speed = speed; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	void setHP(int hp) { _hp = hp; }
	void setAlarm(bool isAlarm) { _isAlarm = isAlarm; }
	void setAlarm2(bool isAlarm2) { _isAlarm2 = isAlarm2; }
	void setStatus(brovilStatus status) { _status = status; }
	
	void setDirection(bool isLeft) { _isLeft = isLeft; }
	void setEnemyAngle(float angle) { _angle = angle; }
	
	void setAccel(float accel) { _accel = accel; }
	void setIsOn(bool isOn) { _isOn = isOn; }

	void move();
	void flyAway();
	void controlAI(int randomNum);

	void frameAnimate();
	void knockBackMove();	// 총알맞았을때 뒤로 날아감

	brovil() {}
	~brovil() {}
};

