#pragma once
#include "singletonBase.h"

class effectManager : public singletonBase<effectManager>
{
public:
	//����Ʈ�Ŵ��� �ʱ�ȭ
	HRESULT init();
	//����Ʈ�Ŵ��� ����
	void release();
	
	//rambro ź�� �������� ȿ��
	//void rambroCatridge();

	////�������� ȿ��
	//void bloodSplash();

	effectManager() {}
	~effectManager() {}
};