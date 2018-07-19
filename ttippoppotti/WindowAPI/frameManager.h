#pragma once
#include "singletonBase.h"
class frameManager : public singletonBase<frameManager>
{
	
public:
	void frameChange(image* img, int& count, int& index, int &speed, bool isLeft);
	
	//프레임매니져 초기화
	HRESULT init();
	//프레임매니져 해제
	void release();

	frameManager() {}
	~frameManager() {}
};