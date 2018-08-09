#pragma once
#include "gameNode.h"
#include "bullet.h"

#define COOLTIME 7	// _frameIndex 바뀌는 속도
#define BODY_PART 4

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

enum {ENEMY_LEFT, ENEMY_TOP, ENEMY_RIGHT, ENEMY_BOTTOM};

struct enemyImage
{
	image* bodyImage[7];
	image* armImage[5];	
;	int bodyImageIndex;
	int armImageIndex;
	int count;
	int speed;	
};

struct enemyCorpse
{
	image* corpseImage;
	RECT rcCorpse;
	float x, y;
	float angle;
	float speed;
	float gravity;
};


//부모클래스 => 이놈을 상속받아서 보스, 일반몬스터등을 만든다
class enemy : public gameNode
{
private:	

	enemyStatus _enemyStatus;	
	gunStatus _gunStatus;
	enemyImage _enemyImage;
	
	enemyCorpse _corpse[BODY_PART];
		
	image * _warnSign;
	image * _doubtSign;
	
	RECT _rcEnemy;
	RECT _rcEnemySight;	

	float _angle;	
	float _speed;
	float _gravity;
	float _accel;
	float _kbSpeed;			// 맞았을 때 날아가는 속도
	
	float _x, _y;
	int _hp;
		
	bool _isAlive;
	bool _isLeft;
	bool _isFire;
	bool _isOn;
	bool _isUncovered;		// 플레이어 발견! 
	bool _isStrange;		// 아군(적) 의 시체 발견!
	bool _isApart;			// 시체 토막!
			
	int _count;				// 카운트
	int _randomNumber;
	int _kbIndex;
	int _warnFrameIndex, _doubtFrameIndex;
	int _warnFrameCount, _doubtFrameCount;
	int _frameSpeed;

public:
	HRESULT initSoldier(float x, float y);	
	void release(void);
	void update(void);
	void render(void);

	image* getEnemyBodyImage(enemyStatus enemyStat) { return _enemyImage.bodyImage[enemyStat]; }
	image* getEnemyArmImage(gunStatus armStat) { return _enemyImage.armImage[armStat]; }
	
	enemyCorpse* getCorpse() { return _corpse; }

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
	bool getIsApart() { return _isApart; }
	enemyStatus getBodyStatus() { return _enemyStatus; }
	gunStatus getArmStatus() { return _gunStatus; }
	
	
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
	
	void setBodyImageIndex(int bodyImageIndex) { _enemyImage.bodyImageIndex = bodyImageIndex; }
	void setArmImageIndex(int armImageIndex) { _enemyImage.armImageIndex = armImageIndex; }
		
	void setEnemyAngle(float angle) { _angle = angle; }
	void setRandomNum(int randomNum) { _randomNumber = randomNum; }
	void setAccel(float accel) { _accel = accel; }
	void setIsOn(bool isOn) { _isOn = isOn; }
	void setIsApart(bool isApart) { _isApart = isApart; }
	
	void controlAI();
	// 에너미 움직임 변화
	void changeStatus();
	// 적 시체 초기화
	void corpseInit();		
	// 중력충돌
	void fall();	
	// 움직임
	void deadMove();	
	// 의심?
	void doubt();	
	// 발견!
	void discover();
	// 사격 애니 
	void fireMovement();
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
	// 시체조각 삭제
	bool removeCorpse();
			
	enemy() {}
	virtual ~enemy() {}
};


