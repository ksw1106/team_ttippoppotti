#pragma once
#include "gameNode.h"

#define BOSS_BULLET_MAX 20
#define BOSS_ROCKET_MAX 4

//�Ѿ� ����ü
struct tagBullet
{
	image* bulletImage;
	image* grenadeImage;
	image* missileImageRight;
	image* missileImageLeft;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool isActived;
	bool fire;
	bool isLeft;
	int count;
	int frameCount;
	int frameIndex;
	int frameSpeed;
	
};

//============================================================================================
//	## eBullet ## (�� �Ϲ��Ѿ�)
//============================================================================================
class eBullet : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vEBullet;

private:
	float _range;			//�Ѿ� ��Ÿ�
	int _bulletMax;			//�Ѿ� �ִ밹��

	int _bulletCount;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(int x, int y, int fireSpeed, bool isLeft);
	//�Ѿ˹���
	void move();
	//�ִϸ��̼�
	void animation(int i);

	//�Ѿ˺��� ��������
	vector<tagBullet> getVEnemybullet() { return _vEBullet; }

	eBullet() {}
	~eBullet() {}
};

//============================================================================================
//	## bossBullet ## (���� �Ѿ�)
//============================================================================================
class bossBullet : public gameNode
{
private:
	float _range;			//�Ѿ� ��Ÿ�
	int _bulletMax;			//�Ѿ� �ִ밹��

	int _bulletCount;
	int _interval;

	tagBullet _bossBullet[BOSS_BULLET_MAX];

public:
	HRESULT init();
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(int x, int y, bool isLeft);
	//�Ѿ˹���
	void move();
	
	//�Ѿ˱���ü ��������
	tagBullet* getBossBullet() { return _bossBullet; }

	bossBullet() {}
	~bossBullet() {}
};

//============================================================================================
//	## bossRocket ## (���� ����)
//============================================================================================
class bossRocket : public gameNode
{	
private:
	float _range;			//�Ѿ� ��Ÿ�
	int _bulletMax;			//�Ѿ� �ִ밹��

	int _bulletCount;
	int _interval;
	
	tagBullet _bossRocket[BOSS_ROCKET_MAX];

public:
	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(int x, int y, int fireSpeed, bool isLeft);
	//�Ѿ˹���
	void move();
	//�Ѿ˾ִϸ��̼�	
	void animation(int i);

	tagBullet* getBossRocket() { return _bossRocket; }
	
	bossRocket() {}
	~bossRocket() {}
};

//=============================================================
//	## pBullet ## (�÷��̾� �Ϲ��Ѿ�)
//=============================================================
class pBullet : public gameNode
{
private:
	// �Ѿ� ����ü�� ���� ����
	vector<tagBullet> _vBullet;

private:
	float _range;				// �Ѿ� ��Ÿ�
	int _bulletMax;				// �Ѿ� �ִ밹��

public:

	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);

	// �Ѿ� �߻�
	void fire(int x, int y, int fireSpeed, bool isLeft);
	// �Ѿ� ����
	void move();
	// �Ѿ�����
	void removeBullet(int index);
	// �Ѿ˺��� ��������
	vector<tagBullet>& getVPlayerBullet() { return _vBullet; }

	pBullet() {}
	~pBullet() {}
};
//=============================================================
//	## pGrenade  ## (�÷��̾� ����ź)
//=============================================================
class pGrenade : public gameNode
{
private:
	vector<tagBullet> _vBullet;

private:
	float _range;
	int _grenadeMax;
	int _count;

public:

	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(int x, int y, int fireSpeed, bool isLeft);

	void move();

	vector<tagBullet>& getVPlayerGrenade() { return _vBullet; }

	pGrenade() {}
	~pGrenade() {}
};
//=============================================================
//	## gBullet ## (�Ҿƹ��� �Ϲ��Ѿ�)
//=============================================================
class gBullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;

private:
	float _range;
	int _gBulletMax;
	int _count;
	
public:

	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(int x, int y, int fireSpeed, bool isLeft);

	void move();

	vector<tagBullet>& getVPlayergBullet() { return _vBullet; }
	gBullet() {}
	~gBullet() {}
};

//=============================================================
//	## gMissile ## (�Ҿƹ��� �̻���)
//=============================================================
class gMissile : public gameNode
{
private:
	vector<tagBullet> _vBullet;

private:
	float _range;
	int _gMissileMax;
	int _count;

public:

	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(int x, int y, int fireSpeed, bool isLeft);

	void move();

	vector<tagBullet>& getVPlayergMissile() { return _vBullet; }
	gMissile() {}
	~gMissile() {}
};

//=============================================================
//	## xMissile ## (�Ҿƹ��� �̻��� X )
//=============================================================
class xMissile : public gameNode
{
private:
	vector<tagBullet> _vBullet;

private:
	float _range;
	int _xMissileMax;
	int _count;

public:

	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(int x, int y, int fireSpeed, bool isLeft);

	void move();

	vector<tagBullet>& getVPlayerxMissile() { return _vBullet; }
	xMissile() {}
	~xMissile() {}
};