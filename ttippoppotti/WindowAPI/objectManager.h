#pragma once
#include "singletonBase.h"
class objectManager : public singletonBase<objectManager>
{
public:
	//������Ʈ�Ŵ��� �ʱ�ȭ
	HRESULT init();
	//������Ʈ�Ŵ��� ����
	void release();
	objectManager() {}
	~objectManager() {}
};

