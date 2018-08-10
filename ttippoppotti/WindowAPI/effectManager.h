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
	bool _isGrenadePuff;
	bool _isBigBang;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//탄피
	void cartridge(float x, float y, bool isLeft);
	//피
	void bloodSplash(float x, float y, bool isLeft);
	//낙석
	void rockFall(float x, float y, bool isLeft);
	//나무파편
	void woodDebris(float x, float y, bool isLeft);
	//스파크 튐
	void yellowSparks(float x, float y, bool isLeft);
	//재로 변하여 날아갑니다
	void ashes(float x, float y);
	//총알이펙트
	void bulletPuff(float x, float y);
	//수류탄 이펙트
	void grenadePuff(float x, float y);
	//수류탄 이펙트 초기화
	void grenadePuffStart(float x, float y);
	//칼 이펙트
	void knifePuff(float x, float y, bool isLeft);
	//파리날림
	void flyingFlies(float x, float y);
	//구하는 말풍선
	void saveBubble(float x, float y);
	//대폭발
	void bigBang(float x, float y);
	//대폭발 초기화
	void bigBangStart(float x, float y);
	//폭발
	void explosion(float x, float y);
	//폭발 초기화
	void explosionStart(float x, float y);
	
	//이펙트 추가(이펙트키값, 이미지키값, 1회당 출력갯수, 버퍼갯수, 애니메이션이냐?)
	void addEffect(string effectName, const char* imageName, int buffer, int count = 1, bool isFrameImg = false);
	//이펙트 플레이
	void playParabola(string effectName, float x, float y, bool isLeft);
	void playExplosion(string effectName, float x, float y);
	void playBallExplosion(string effectName, float x, float y);
	void playCartridge(string effectName, float x, float y, bool isLeft);
	void playEllipsePuff(string effectName, float x, float y);
	void playEllipsePuff(string effectName, float x, float y, bool isLeft);
	void playLoopAnim(string effectName, float x, float y);
	void playFlyingFlies(string effectName, float x, float y);
	void playAshes(string effectName, float x, float y);
	void playBigBang(string effectName, float x, float y);
	effectManager() {}
	~effectManager() {}
};

