#pragma once
#include "gameNode.h"


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

	const char* _imageName;		//파편 이미지 이름(키값)
	int _particleMax;			//파편 최대갯수
	float _randGravity;

public:
	HRESULT init(const char* imageName, int particleMax);
	void release(void);
	void update(void);
	void render(void);

	//이펙트 발사 설정
	void activate(float x, float y, float angle);
	//이펙트 발사!
	void boom(float gravity);

	void collisionProcess();

	//이펙트벡터 가져오기
	vector<tagParticle> getVFragment() { return _vFragment; }


	fragments() {}
	~fragments() {}
};
