#pragma once
#include "singletonBase.h"
//이펙트 클래스 전방선언(뻥남 방지용)
class effects;

class effectManager : public singletonBase <effectManager>
{
private:
	//이펙트 클래스를 담을 벡터 및 반복자
	typedef vector<effects*> vEffect;
	typedef vector<effects*>::iterator viEffect;
	//이펙트를 담아놓은 벡터를 담을 맵
	typedef map<string, vEffect> mEffect;
	typedef map<string, vEffect>::iterator miEffect;

private:
	mEffect _mEffect;		//이펙트벡터가 담겨있는 맵
	int _count;
	float _x, _y;
	bool _isExplosion;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//탄피
	void cartridge(float x, float y, bool isLeft);
	//피
	void bloodSplash(float x, float y, float angle);
	//낙석
	void rockFall(float x, float y, float angle);
	//나무파편
	void woodDebris(float x, float y, float angle);

	//폭발
	void explosion(float x, float y);
	//폭발 초기화
	void explosionStart(float x, float y);
	
	//이펙트 추가(이펙트키값, 이미지키값, 1회당 출력갯수, 버퍼갯수, 애니메이션이냐?)
	void addEffect(string effectName, const char* imageName, int buffer, int count = 1, bool isFrameImg = false);
	//이펙트 플레이
	void playParabola(string effectName, float x, float y, float angle);
	void playExplosion(string effectName, float x, float y);
	void playBallExplosion(string effectName, float x, float y);

	void playCartridge(string effectName, float x, float y, bool isLeft);

	effectManager() {}
	~effectManager() {}
};

