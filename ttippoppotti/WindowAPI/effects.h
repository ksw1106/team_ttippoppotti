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
};
//=============================================================
//	## fragments ## (공용이펙트)
//=============================================================
class fragments : public gameNode
{
private:
	//구조체를 담을 벡터, 반복자
	vector<tagParticle> _vFragment;

	mapdata* _mapdata;
	const char* _imageName;		//파편 이미지 이름(키값)
	int _particleMax;			//파편 최대갯수
	float _randGravity;
	int _x, _y;				//이펙트 터트릴 위치좌표
	float _effectFPS;		//이펙트 속도
	bool _isRunning;		//이펙트 재생중이냐?

public:
	HRESULT init(const char* imageName, int particleMax);
	void release(void);
	void update(void);
	void render(void);


	//이펙트 발사 설정
	void activate(float x, float y, float angle);
	//이펙트 발사!
	void boom();

	//이펙트 멈추기
	void stopEffect();

	void collisionProcess();

	//이펙트가 재생중인지 상태값 가져오기
	bool getIsRunning() { return _isRunning; }

	//이펙트벡터 가져오기
	vector<tagParticle> getVFragment() { return _vFragment; }

	fragments() : _isRunning(false), _x(0), _y(0) {}
	~fragments() {}


};
