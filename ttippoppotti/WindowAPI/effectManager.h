#pragma once
#include "singletonBase.h"
class effectManager : public singletonBase<effectManager>
{
private:

public:
	//����Ʈ�Ŵ��� �ʱ�ȭ
	HRESULT init();
	//����Ʈ�Ŵ��� ����
	void release();

	effectManager() {}
	~effectManager() {}
};