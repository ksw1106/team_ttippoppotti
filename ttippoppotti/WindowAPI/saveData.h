#pragma once
#include "singletonBase.h"
class saveData : public singletonBase<saveData>
{
	//프로그램 실행중 저장할 정보들을 여기에
	
public:
	//프로그램 실행중 저장할 정보들의 get set 여기에
	HRESULT init();
	void release();
	saveData() {}
	~saveData() {}
};