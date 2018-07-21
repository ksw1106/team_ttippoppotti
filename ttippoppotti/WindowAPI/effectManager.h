#pragma once
#include "singletonBase.h"
class effectManager : public singletonBase<effectManager>
{
public:
	//이펙트매니져 초기화
	HRESULT init();
	//이펙트매니져 해제
	void release();
	effectManager() {}
	~effectManager() {}
};