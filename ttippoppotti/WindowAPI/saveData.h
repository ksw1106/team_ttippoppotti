#pragma once
#include "singletonBase.h"
class saveData : public singletonBase<saveData>
{
	//���α׷� ������ ������ �������� ���⿡
	
public:
	//���α׷� ������ ������ �������� get set ���⿡
	HRESULT init();
	void release();
	saveData() {}
	~saveData() {}
};