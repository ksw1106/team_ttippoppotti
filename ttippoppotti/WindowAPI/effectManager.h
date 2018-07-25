#pragma once
#include "singletonBase.h"
#include "effects.h"

class effectManager : public singletonBase<effectManager>
{
private:
	fragments * _fragments[5];
	bool _isExplosion;

public:
	//����Ʈ�Ŵ��� �ʱ�ȭ
	HRESULT init();
	//����Ʈ�Ŵ��� ����
	void release();
	void update(void);
	void render(HDC hdc);

	//�� ���Ľ� ���� �������� ȿ��
	void rockExplosion(float x, float y, float angle);
	
	//rambro ź�� �������� ȿ��
	//void rambroCatridge();

	////�������� ȿ��
	//void bloodSplash();

	effectManager() {}
	~effectManager() {}
};