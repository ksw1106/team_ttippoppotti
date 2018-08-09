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
	float _kbSpeed;			// �¾��� �� ���ư��� �ӵ�

	float _x, _y;
	int _hp;

	bool _isAlive;
	bool _isLeft;	
	bool _isOn;
	bool _isUncovered;		// �÷��̾� �߰�! 
	bool _isStrange;		// �Ʊ�(��) �� ��ü �߰�!
	bool _isApart;			// ��ü �丷!

	int _frameCount;				// ī��Ʈ	
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

	// ���ʹ� ������ ��ȭ
	void changeStatus();
	// �� ��ü �ʱ�ȭ
	void corpseInit();
	// �߷��浹
	void fall();
	// ������
	void deadMove();
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
	// ��ǳ�� �ʱ�ȭ
	void initSign();

	brovil() {}
	~brovil() {}
};

