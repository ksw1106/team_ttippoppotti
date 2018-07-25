#pragma once
#include "singletonBase.h"
#include "effects.h"

class effectManager : public singletonBase<effectManager>
{
private:
	fragments * _fragments[5];
	bool _isExplosion;

public:
	//이펙트매니져 초기화
	HRESULT init();
	//이펙트매니져 해제
	void release();
	void update(void);
	void render(HDC hdc);

	//벽 폭파시 파편 떨어지는 효과
	void rockExplosion(float x, float y, float angle);
	
	//rambro 탄피 떨어지는 효과
	//void rambroCatridge();

	////피터지는 효과
	//void bloodSplash();

	effectManager() {}
	~effectManager() {}
};