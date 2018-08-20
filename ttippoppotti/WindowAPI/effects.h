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
	float oldX, oldY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool fire;
	bool isActive;
	bool isFrameImg;
	bool isAlphaImg;
	int alpha;
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
	int _alpha;
	int _count;
	int _explosionCount;
	int _bigBangCount;
	int _index;
	int _animationSpeed;
	float _range;
	float _effectFPS;		//이펙트 속도
	bool _isRunning;		//이펙트 재생중이냐?
	bool _isParabola;
	bool _isParabolaNoCollision;
	bool _isLeft;
	bool _isExplosion;
	bool _isStaticAnim;
	bool _isFlyingFlies;
	bool _isAshes;
	bool _isBigBang;
	bool _isMissileTrail;
	bool _isMissilePuff;
	bool _isFrameImg;		//프레임이미지냐?
	bool _isAlphaImg;		//알파이미지냐?


public:
	HRESULT init(const char* imageName, int particleMax = 0, bool isFrameImg = false);
	void release(void);
	void update(void);
	void render(void);

	//탄피 설정
	void activateCartridge(float x, float y, bool isLeft);
	//중앙폭발
	void activateBallExplosion(float x, float y);
	//포물선 발사 설정 (피, 낙석, 나무파편)
	void activateParabola(float x, float y, bool isLeft);
	void activateParabolaNoCollision(float x, float y, bool isLeft);
	void boomParabola();
	void boomParabolaNoCollision();
	//분수
	void activateFountain(float x, float y);
	void activateFountainNoCollision(float x, float y);

	void activateFall(float x, float y);
	//핏자국
	void activateBlotch(float x, float y);
	void boomBlotch();
	//파리날림
	void activateFlyingFlies(float x, float y);
	void boomFlyingFlies();
	//재가 되어 날아간당
	void activateAshes(float x, float y);
	void boomAshes();
	//폭발 설정
	void activateExplosion(float x, float y);
	void boomExplosion();
	//말풍선
	void activateLoopAnim(float x, float y);
	//동그라미 이펙트
	void activateEllipsePuff(float x, float y);
	void activateEllipsePuff(float x, float y, bool isLeft);
	//대폭발 설정
	void activateBigBang(float x, float y);
	void boomBigBang();

	//미사일
	void activateMissileTrail(float x, float y, bool isLeft);
	void boomMissileTrail();
	void activateMissilePuff(float x, float y, int speed, bool isLeft);
	void boomMissilePuff();

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