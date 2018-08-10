#pragma once
#include "gameNode.h"

enum bossStatus
{
	LEFT_IDLE, RIGHT_IDLE,
	LEFT_TO_RIGHT, RIGHT_TO_LEFT,
	LEFT_MOVE, RIGHT_MOVE,
	LEFT_FIRE_BULLET, RIGHT_FIRE_BULLET,
	LEFT_FIRE_ROCKET, RIGHT_FIRE_ROCKET
};

enum bossBodyStatus
{
	B_IDLE, B_TURN, B_DEATH
};

enum bossGunStatus
{
	BB_READY, BB_ROTATE, BB_FIRE
};

struct tagBossImage
{
	image* bodyImage[3];
	image* gunImage[3];
	image* propellerImage;
	image* rotorImage;
	image* bulletFireImage;
	int bodyIndex;
	int gunIndex;
	int propellerIndex;
	int rotorIndex;
	int frameCount;
	int frameSpeed;
	
};

struct tagBoss
{
	tagBossImage img;	
	RECT rcBody;
	RECT rcGun;
	RECT rcWing;
	float x, y;
	float startX, startY;
	float speed;
	float angle;
	float gravity;
	float distance;
		
	int count;
	int hp;
	bool isMove;
	bool isAlive;
	bool isLeft;
	bool isAttack;
	bool isTurning;
};

class boss : public gameNode
{
private:
	tagBoss _terrorKopter;

	bossStatus _status;
	bossBodyStatus _bodyStatus;
	bossGunStatus _gunStatus;

	int _count;
	int _stateNum;
	int _bulletEffectIndex;
	int _bulletEffectCount;
	int _bulletEffectSpeed;


public:
	tagBoss getTerrorKopter() { return _terrorKopter; }

	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);

	bossStatus getStatus() { return _status; }
	void setStatus(bossStatus bossStatus) { _status = bossStatus; }

	bossBodyStatus getBodyStatus() { return _bodyStatus; }
	bossGunStatus getGunStatus() { return _gunStatus; }

	bool getIsTurning() { return _terrorKopter.isTurning; }
	void setIsTurning(bool isTurning) { _terrorKopter.isTurning = isTurning; }
	bool getIsLeft() { return _terrorKopter.isLeft; }
	void setIsLeft(bool isLeft) { _terrorKopter.isLeft = isLeft; }
	bool getIsMoving() { return _terrorKopter.isMove;}
	void setIsMoving(bool isMove) { _terrorKopter.isMove = isMove; }

	// ���� ������ �ٲ�
	void terrorKopterMove();
	// ���̵� �����϶� ������
	void idleMovement();
	// ���ʿ��� ���������� �ִϸ��̼� ��ȭ
	void leftToRight();	
	// �����ʿ��� �������� �ִϸ��̼� ��ȭ
	void rightToLeft();
	// �Ѿ� �߻�
	void fireBullet();
	// ���� �߻�
	void rocketFire();
	// ������ ü����	
	void frameAnimate();
	
	// �����¿�� ������
	void verticalMove(float x, float y, float angle);
	void bombAttack(float x, float y, float angle);
	
	void move();
	
	boss() {}
	~boss() {}
};

