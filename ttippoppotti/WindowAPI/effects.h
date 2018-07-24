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
//	## effects ## (공용이펙트)
//=============================================================
class effects : public gameNode
{
private:
	//구조체를 담을 벡터, 반복자
	vector<tagParticle> _vParticle;

	const char* _imageName;		//파편 이미지 이름(키값)
	int _particleMax;			//파편 최대갯수
	float _range;

public:
	HRESULT init(const char* imageName, int particleMax);
	void release(void);
	void update(void);
	void render(void);

	//이펙트 발사 설정
	void activate(float x, float y, float angle, float speed, float gravity);
	//이펙트 발사!
	void boom();

	//이펙트벡터 가져오기
	vector<tagParticle> getVParticle() { return _vParticle; }


	////rambro 탄피 떨어지는 효과
	//void rambroCatridge();

	////벽 파편 떨어지는 효과
	//void rockParticleFall();

	////피터지는 효과
	//void bloodSplash();


	effects() {}
	~effects() {}
};
