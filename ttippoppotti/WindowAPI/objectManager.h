#pragma once
#include "singletonBase.h"
class objectManager : public singletonBase<objectManager>
{
public:
	//오브젝트매니져 초기화
	HRESULT init();
	//오브젝트매니져 해제
	void release();
	objectManager() {}
	~objectManager() {}
};

