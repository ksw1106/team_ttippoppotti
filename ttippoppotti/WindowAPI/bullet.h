#pragma once
#include "gameNode.h"

#define BOSS_BULLET_MAX 20
#define BOSS_ROCKET_MAX 4

//총알 구조체
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
//	## eBullet ## (적 일반총알)
//============================================================================================
class eBullet : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vEBullet;

private:
	float _range;			//총알 사거리
	int _bulletMax;			//총알 최대갯수

	int _bulletCount;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//총알발사
	void fire(int x, int y, int fireSpeed, bool isLeft);
	//총알무브
	void move();
	//애니메이션
	void animation(int i);

	//총알벡터 가져오기
	vector<tagBullet> getVEnemybullet() { return _vEBullet; }

	eBullet() {}
	~eBullet() {}
};

//============================================================================================
//	## bossBullet ## (보스 총알)
//============================================================================================
class bossBullet : public gameNode
{
private:
	float _range;			//총알 사거리
	int _bulletMax;			//총알 최대갯수

	int _bulletCount;
	int _interval;

	tagBullet _bossBullet[BOSS_BULLET_MAX];

public:
	HRESULT init();
	void release(void);
	void update(void);
	void render(void);

	//총알발사
	void fire(int x, int y, bool isLeft);
	//총알무브
	void move();
	
	//총알구조체 가져오기
	tagBullet* getBossBullet() { return _bossBullet; }

	bossBullet() {}
	~bossBullet() {}
};

//============================================================================================
//	## bossRocket ## (보스 로켓)
//============================================================================================
class bossRocket : public gameNode
{	
private:
	float _range;			//총알 사거리
	int _bulletMax;			//총알 최대갯수

	int _bulletCount;
	int _interval;
	
	tagBullet _bossRocket[BOSS_ROCKET_MAX];

public:
	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);

	//총알발사
	void fire(int x, int y, int fireSpeed, bool isLeft);
	//총알무브
	void move();
	//총알애니메이션	
	void animation(int i);

	tagBullet* getBossRocket() { return _bossRocket; }
	
	bossRocket() {}
	~bossRocket() {}
};

//=============================================================
//	## pBullet ## (플레이어 일반총알)
//=============================================================
class pBullet : public gameNode
{
private:
	// 총알 구조체를 담을 벡터
	vector<tagBullet> _vBullet;

private:
	float _range;				// 총알 사거리
	int _bulletMax;				// 총알 최대갯수

public:

	HRESULT init(float range);
	void release(void);
	void update(void);
	void render(void);

	// 총알 발사
	void fire(int x, int y, int fireSpeed, bool isLeft);
	// 총알 무브
	void move();
	// 총알제거
	void removeBullet(int index);
	// 총알벡터 가져오기
	vector<tagBullet>& getVPlayerBullet() { return _vBullet; }

	pBullet() {}
	~pBullet() {}
};
//=============================================================
//	## pGrenade  ## (플레이어 수류탄)
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
//	## gBullet ## (할아버지 일반총알)
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
//	## gMissile ## (할아버지 미사일)
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
//	## xMissile ## (할아버지 미사일 X )
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