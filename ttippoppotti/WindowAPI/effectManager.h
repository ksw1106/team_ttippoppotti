#pragma once
#include "singletonBase.h"

class effectManager : public singletonBase<effectManager>
{
public:
	//이펙트매니져 초기화
	HRESULT init();
	//이펙트매니져 해제
	void release();
	
	//rambro 탄피 떨어지는 효과
	//void rambroCatridge();

	////피터지는 효과
	//void bloodSplash();

	effectManager() {}
	~effectManager() {}
};