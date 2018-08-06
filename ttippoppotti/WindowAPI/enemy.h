#pragma once
#include "gameNode.h"

#define COOLTIME 7	// _frameIndex 바뀌는 속도

enum enemyStatus
{
	ENEMY_IDLE = 0,
	ENEMY_WALK = 1,
	ENEMY_DOUBT = 2,
	ENEMY_FIRE = 3,
	ENEMY_KNOCK_BACK = 4,
	ENEMY_FLY_AWAY = 5,
	ENEMY_DEAD = 6,
};

enum gunStatus
{
	GUN_IDLE = 0,
	GUN_TARGETING = 1,
	GUN_READY = 2,
	GUN_FIRE = 3,
	GUN_RELOAD = 4,
};

enum brovilStatus
{
	BROVIL_IDLE,
	BROVIL_WALK,
	BROVIL_KNOCK_BACK,
	BROVIL_DEAD,
	BROVIL_DISAPPEAR,
};

enum {ENEMY_LEFT, ENEMY_TOP, ENEMY_RIGHT, ENEMY_BOTTOM};

struct enemyImage
{
	image* bodyImage[7];
	image* armImage[5];
	int bodyImageIndex;
	int armImageIndex;
	int count;
	int speed;	
};

struct brovilImage
{
	image* brovilImg[5];
	int count;
	int index;
	int speed;
};


//부모클래스 => 이놈을 상속받아서 보스, 일반몬스터등을 만든다
class enemy : public gameNode
{
private:	

	enemyStatus _enemyStatus;
	gunStatus _gunStatus;
	brovilStatus _brovilStatus;
	
	enemyImage _enemyImage;
	brovilImage _brovilImage;

	//image * _bodyImage[6];
	//image * _armImage[5];
	//image * _brovilImage[5];
	image * _warnSign;
	image * _doubtSign;
	
	RECT _rcEnemy;
	RECT _rcEnemySight;

	float _angle;
	float _speed;
	float _gravity;
	float _accel;
	float _kbSpeed;		// 맞았을 때 날아가는 속도
	
	float _x, _y;
	int _hp;
	
	bool _isAlive;
	bool _isLeft;
	bool _isFire;
	bool _isOn;
	bool _isUncovered;		// 플레이어 발견! 
	bool _isStrange;		// 아군(적) 의 시체 발견!
			
	int _count;				// 카운트
	int _randomNumber;
	int _kbIndex;
	int _warnFrameIndex, _doubtFrameIndex;
	int _warnFrameCount, _doubtFrameCount;
	int _frameSpeed;

public:
	HRESULT initSoldier(int x, int y);
	HRESULT initBrovil(int x, int y);

	void release(void);
	void update(void);
	void render(void);

	image* getEnemyBodyImage(enemyStatus enemyStat) { return _enemyImage.bodyImage[enemyStat]; }
	image* getEnemyArmImage(gunStatus armStat) { return _enemyImage.armImage[armStat]; }
	image* getBrovilImage() { return _brovilImage.brovilImg[_brovilStatus]; }
		
	RECT getRcEnemy() { return _rcEnemy; }
	RECT getRcEnemySight() { return _rcEnemySight; }
	float getSpeed() { return _speed; }
	float getGravity() { return _gravity; }
	float getX() { return _x; }
	float getY() { return _y; }
	int getHP() { return _hp; }
	bool getIsAlive() { return _isAlive; }
	bool getDirection() { return _isLeft; }
	bool getIsUncovered() { return _isUncovered; }
	bool getIsStrange() { return _isStrange; }
	bool getIsFire() { return _isFire; }
	enemyStatus getBodyStatus() { return _enemyStatus; }
	gunStatus getArmStatus() { return _gunStatus; }
	brovilStatus getBrovilStatus() { return _brovilStatus; }
	
	float getEnemyAngle() { return _angle; }
	int getRandomNum() { return _randomNumber; }
	float getAccel() { return _accel; }
	bool getIsOn() { return _isOn; }
			
	void setRcEnemy(RECT rcEnemy) { _rcEnemy = rcEnemy; }
	void setEnemySightRC(RECT rcEnemySight) { _rcEnemySight = rcEnemySight; }
	void setSpeed(float speed) { _speed = speed; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setHP(int hp) { _hp = hp; }
	void setIsAlive(bool isAlive) { _isAlive = isAlive; }
	void setDirection(bool isLeft) { _isLeft = isLeft; }
	void setIsUncovered(bool isUncovered) { _isUncovered = isUncovered; }
	void setIsStrange(bool isStrange) { _isStrange = isStrange; }
	void setIsFire(bool isFire) { _isFire = isFire; }
	void setBodyStatus(enemyStatus enemyStat) { _enemyStatus = enemyStat; }
	void setArmStatus(gunStatus gunStat) { _gunStatus = gunStat; }
	void setBrovilStatus(brovilStatus brovilStatus) { _brovilStatus = brovilStatus; }
	void setBodyImageIndex(int bodyImageIndex) { _enemyImage.bodyImageIndex = bodyImageIndex; }
	void setArmImageIndex(int armImageIndex) { _enemyImage.armImageIndex = armImageIndex; }
	
	void setEnemyAngle(float angle) { _angle = angle; }
	void setRandomNum(int randomNum) { _randomNumber = randomNum; }
	void setAccel(float accel) { _accel = accel; }
	void setIsOn(bool isOn) { _isOn = isOn; }

	//void controlAI(int randomNum);
	void fall();
	void idle();
	void move();
	void doubt();
	void discover();
	void fireMovement();
	void flyAway();
	void knockBackMove(bool isLeft);	// 총알맞았을때 뒤로 날아감
	void dead();
	void enemyExplode();				// 피가 다 닳았을때 토막남
	
	void frameAnimate();	
			
	enemy() {}
	virtual ~enemy() {}
};

//========================================================================================================

