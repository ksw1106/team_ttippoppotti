#pragma once
#include "gameNode.h"

class mapdata;

//파편 구조체
struct tagParticle
{
	image* particleImg;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool fire;
	bool isActive;
	int count;
	int index;
};
//=============================================================
//	## effects ## (공용이펙트)
//=============================================================
class effects : public gameNode
{
private:
	//구조체를 담을 벡터, 반복자
	vector<tagParticle> _vParticle;

	mapdata* _mapdata;
	const char* _imageName;		//파편 이미지 이름(키값)
	int _particleMax;			//파편 최대갯수
	int _x, _y;				//이펙트 터트릴 위치좌표
	int _falseCount;
	int _count;
	int _explosionCount;
	int _index;
	int _animationSpeed;
	float _effectFPS;		//이펙트 속도
	bool _isRunning;		//이펙트 재생중이냐?
	bool _isParabola;
	bool _isExplosion;
	bool _isStaticAnim;
	bool _isLoopAnim;
	bool _isFlyingFlies;
	bool _isFrameImg;		//프레임이미지냐?

public:
	HRESULT init(const char* imageName, int particleMax, bool isFrameImg);
	void release(void);
	void update(void);
	void render(void);

	//탄피 설정
	void activateCartridge(float x, float y, bool isLeft);
	//중앙폭발
	void activateBallExplosion(float x, float y);

	//포물선 발사 설정 (피, 낙석, 나무파편)
	void activateParabola(float x, float y, float angle);
	//포물선 발사!
	void boomParabola();

	//파리날림
	void activateFlyingFlies(float x, float y);

	//폭발 설정
	void activateExplosion(float x, float y);
	//폭발 발사!
	void boomExplosion();

	//말풍선
	void activateLoopAnim(float x, float y);

	//총 발사시 이펙트
	void activateBulletPuff(float x, float y);
	void activateKnifePuff(float x, float y, bool isLeft);
	void boomStaticAnim();

	//충돌처리
	void collisionProcess();
	//애니메이션
	void frameChange();

	//이펙트가 재생중인지 상태값 가져오기
	bool getIsRunning() { return _isRunning; }

	//이펙트벡터 가져오기
	vector<tagParticle> getVParticle() { return _vParticle; }

	effects() : _isRunning(false), _x(0), _y(0) {}
	~effects() {}


};