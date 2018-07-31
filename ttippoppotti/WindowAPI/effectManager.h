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

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	//피
	void bloodSplash();
	//탄피
	void cartridge(float x, float y, bool isLeft);
	//낙석
	void rockFall();
	
	//이펙트 추가(이펙트키값, 이미지키값, 1회당 출력갯수, 버퍼갯수)
	void addEffect(string effectName, const char* imageName, int count, int buffer, bool isFrameImg = false);
	//이펙트 플레이
	void playParabola(string effectName, int x, int y, float angle);

	void playCartridge(string effectName, int x, int y, bool isLeft);

	effectManager() {}
	~effectManager() {}
};

