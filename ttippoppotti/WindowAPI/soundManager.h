#pragma once
#include "singletonBase.h"
class soundManager : public singletonBase<soundManager>
{
public:
	//����Ŵ��� �ʱ�ȭ
	HRESULT init();
	//����Ŵ��� ����
	void release();
	soundManager() {}
	~soundManager() {}
};