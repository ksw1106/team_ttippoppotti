#pragma once
#include "gameNode.h"

#define BODY_PART 4

enum brovilStatus
{
	BROVIL_IDLE,
	BROVIL_WALK,
	BROVIL_KNOCK_BACK,
	BROVIL_DEAD,
	BROVIL_DISAPPEAR,
	BROVIL_FLY_AWAY
};

struct brovilImage
{
	image* brovilImg[6];
	int frameCount;
	int frameIndex;
	int frameSpeed;
};

struct brovilCorpse
{
	image* corpseImage;
	RECT rcCorpse;
	float x, y;
	float angle;
	float speed;
	float gravity;
};


class brovil : public gameNode
{
private:
	brovilStatus _brovilStatus;
	brovilImage _brovilImage;

	brovilCorpse _brovilCorpse[BODY_PART];

	image * _warnSign;
	image * _doubtSign;

	RECT _rcBrovil;
	RECT _rcBrovilSight;	

	float _angle;
	float _speed;
	float _gravity;
	float _accel;
	float _kbSpeed;			// 맞았을 때 날아가는 속도

	float _x, _y;
	int _hp;

	bool _isAlive;
	bool _isLeft;	
	bool _isOn;
	bool _isUncovered;		// 플레이어 발견! 
	bool _isStrange;		// 아군(적) 의 시체 발견!
	bool _isApart;			// 시체 토막!

	int _frameCount;				// 카운트	
	int _kbIndex;
	int _warnFrameIndex, _doubtFrameIndex;
	int _warnFrameCount, _doubtFrameCount;
	int _frameSpeed;

public:
	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);

	image* getBrovilImage(brovilStatus brovilStatus) { return _brovilImage.brovilImg[brovilStatus]; }
	brovilStatus getBrovilStatus() { return _brovilStatus; }
	
	brovilCorpse* getCorpse() { return _brovilCorpse; }

	int getBrovilImageIndex() { return _brovilImage.frameIndex; }
	RECT getRcBrovil() { return _rcBrovil; }
	float getSpeed() { return _speed; }
	float getGravity() { return _gravity; }
	float getX() { return _x; }
	float getY() { return _y; }
	int getHP() { return _hp; }
	bool getIsAlive() { return _isAlive; }
	bool getDirection() { return _isLeft; }
	bool getIsUncovered() { return _isUncovered; }
	bool getIsStrange() { return _isStrange; }
	float getEnemyAngle() { return _angle; }	
	float getAccel() { return _accel; }
	bool getIsOn() { return _isOn; }
	bool getIsApart() { return _isApart; }

	void setBrovilImageIndex(int index) { _brovilImage.frameIndex = index; }
	void setBrovilStatus(brovilStatus brovilStatus) { _brovilStatus = brovilStatus; }
	void setRcBrovil(RECT rcBrovil) { _rcBrovil = rcBrovil; }
	void setRcBrovilSight(RECT rcBrovilSight) { _rcBrovilSight = rcBrovilSight; }
	void setSpeed(float speed) { _speed = speed; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setHP(int hp) { _hp = hp; }
	void setIsAlive(bool isAlive) { _isAlive = isAlive; }
	void setDirection(bool isLeft) { _isLeft = isLeft; }
	void setIsUncovered(bool isUncovered) { _isUncovered = isUncovered; }
	void setIsStrange(bool isStrange) { _isStrange = isStrange; }		
	void setEnemyAngle(float angle) { _angle = angle; }	
	void setAccel(float accel) { _accel = accel; }
	void setIsOn(bool isOn) { _isOn = isOn; }
	void setIsApart(bool isApart) { _isApart = isApart; }

	// 에너미 움직임 변화
	void changeStatus();
	// 적 시체 초기화
	void corpseInit();
	// 중력충돌
	void fall();
	// 움직임
	void deadMove();
	// 폭발되었을때 날라감
	void flyAway();
	// 총알맞았을때 뒤로 날아감
	void knockBackMove(bool isLeft);
	// 피가 다 닳았을때 토막남
	void enemyExplode();
	// 시체 움직임
	void partMove();
	// 프레임 애니메이션
	void frameAnimate();
	// 말풍선 초기화
	void initSign();

	brovil() {}
	~brovil() {}
};

