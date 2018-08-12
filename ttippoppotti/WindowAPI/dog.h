#pragma once
#include "gameNode.h"

#define BODY_PART 4

enum dogStatus
{
	D_IDLE, D_ATTACK, D_KNOCK_BACK, D_DEAD
};

struct dogCorpse
{
	image* corpseImage;
	RECT rcCorpse;
	float x, y;
	float angle;
	float speed;
	float gravity;
};

struct tagDog
{
	image* dogImage[4];	
	RECT rc;	
	RECT rcSight;
	RECT rcAttackRange;
	int index;	
	int count;
	int fspeed;
	float x, y;
	float speed;
	float angle;
	float gravity;	
	float kbSpeed;
	int hp;
	bool isMove;
	bool isAlive;
	bool isLeft;	
	bool isOn;
	bool isAttack;
	bool isApart;
	bool isNear;
};

class dog :	public gameNode
{
private:	
	dogStatus _dogStatus;	
	tagDog _dog;
	dogCorpse _corpse[BODY_PART];

	image * _warnSign;
	image * _doubtSign;
	int _warnFrameIndex, _doubtFrameIndex;
	int _warnFrameCount, _doubtFrameCount;
	int _frameSpeed;
	int _warnDelay;
	int _warnCount;
	bool _isUncovered;		// 플레이어 발견! 
	bool _isStrange;		// 아군(적) 의 시체 발견!

	
public:	
	HRESULT initDog(float x, float y, bool isLeft);
	void release(void);
	void update(void);
	void render(void);

	float getX() { return _dog.x; }
	void setX(float x) { _dog.x = x; }
	float getY() { return _dog.y; }
	void setY(float y) { _dog.y = y; }
	float getSpeed() { return _dog.speed; }
	void setSpeed(float speed) { _dog.speed = speed; }
	float getAngle() { return _dog.angle; }
	void setAngle(float angle) { _dog.angle = angle; }
	int getIndex() { return _dog.index; }
	void setIndex(int index) { _dog.index = index; }
	image* getImage(int num) { return _dog.dogImage[num]; }
	dogCorpse* getCorpse() { return _corpse; }
	
	RECT getRC() { return _dog.rc; }
	RECT getRCsight() { return _dog.rcSight; }
	RECT getRCattackRange() { return _dog.rcAttackRange; }
	float getGravity() { return _dog.gravity; }
	int getHP() { return _dog.hp; }
	void setHP(int hp) { _dog.hp = hp; }
	bool getIsLeft() { return _dog.isLeft; }
	void setIsLeft(bool isLeft) { _dog.isLeft = isLeft; }
	bool getIsAlive() { return _dog.isAlive; }
	void setIsAlive(bool isAlive) { _dog.isAlive = isAlive; }
	bool getIsOn() { return _dog.isOn; }
	void setIsOn(bool isOn) { _dog.isOn = isOn; }
	bool getIsApart() { return _dog.isApart; }
	void setIsApart(bool isApart) { _dog.isApart = isApart; }
	bool getIsAttack() { return _dog.isAttack; }
	void setIsAttack(bool isAttack) { _dog.isAttack = isAttack; }
	bool getIsUncovered() { return _isUncovered; }
	void setIsUncovered(bool isUncovered) { _isUncovered = isUncovered; }
	bool getIsNear() { return _dog.isNear; }
	void setIsNear(bool isNear) { _dog.isNear = isNear; }

	dogStatus getStatus() { return _dogStatus; }
	void setStatus(dogStatus dogStat) { _dogStatus = dogStat; }
	RECT getRcDog() { return _dog.rc; }
	void setRcDog(RECT rc) { _dog.rc = rc; }
	image* getDogImage(dogStatus dogStat) { return _dog.dogImage[dogStat]; }
	

	// 군견시체 초기화
	void corpseInit();
	// 군견액션 변화
	void dogActionChange();
	// 군견 AI
	void dogAI();
	// 군견 중력
	void dogFall();
	// 군견 죽음
	void dogDie();
	// 군견 공격
	void dogAttack(bool isleft);
	// 군견 넉백
	void knockBackMove(bool bulletLeft);
	// 군견 시체 날라감
	void partMove();
	// 군견 시체 움직임
	void deadMove();

	void frameAnimate();

	dog() {}
	~dog() {}
};

