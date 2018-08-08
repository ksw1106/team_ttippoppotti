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
	float speed;
	float angle;
	float gravity;
	int count;
	int hp;
	bool isAlive;
	bool isLeft;
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

public:
	tagBoss getTerrorKopter() { return _terrorKopter; }

	HRESULT init(float x, float y);
	void release(void);
	void update(void);
	void render(void);

	bossStatus getStatus() { return _status; }
	bossBodyStatus getBodyStatus() { return _bodyStatus; }
	bossGunStatus getGunStatus() { return _gunStatus; }

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
	// AI ����
	void controlAI();
	// �����¿�� ������
	void move();

	boss() {}
	~boss() {}
};

