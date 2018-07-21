#pragma once
#include "singletonBase.h"
class soundManager : public singletonBase<soundManager>
{
public:
	//사운드매니져 초기화
	HRESULT init();
	//사운드매니져 해제
	void release();
	soundManager() {}
	~soundManager() {}
};