#pragma once
#include "gameNode.h"
#include "bullet.h"

#define COOLTIME 7	// _frameIndex �ٲ�� �ӵ�
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


//�θ�Ŭ���� => �̳��� ��ӹ޾Ƽ� ����, �Ϲݸ��͵��� �����
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
	float _kbSpeed;			// �¾��� �� ���ư��� �ӵ�
	
	float _x, _y;
	int _hp;
		
	bool _isAlive;
	bool _isLeft;
	bool _isFire;
	bool _isOn;
	bool _isUncovered;		// �÷��̾� �߰�! 
	bool _isStrange;		// �Ʊ�(��) �� ��ü �߰�!
	bool _isApart;			// ��ü �丷!
			
	int _count;				// ī��Ʈ
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
	// ���ʹ� ������ ��ȭ
	void changeStatus();
	// �� ��ü �ʱ�ȭ
	void corpseInit();		
	// �߷��浹
	void fall();	
	// ������
	void deadMove();	
	// �ǽ�?
	void doubt();	
	// �߰�!
	void discover();
	// ��� �ִ� 
	void fireMovement();
	// ���ߵǾ����� ����
	void flyAway();			
	// �Ѿ˸¾����� �ڷ� ���ư�
	void knockBackMove(bool isLeft);	
	// �ǰ� �� ������� �丷��
	void enemyExplode();	
	// ��ü ������
	void partMove();		
	// ������ �ִϸ��̼�
	void frameAnimate();	
	// ��ü���� ����
	bool removeCorpse();
			
	enemy() {}
	virtual ~enemy() {}
};


