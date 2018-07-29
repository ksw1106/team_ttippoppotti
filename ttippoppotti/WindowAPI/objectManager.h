#pragma once
#include "singletonBase.h"

struct tagObject
{
	float _x, _y;
	int _count;
	int _index;
	int _animationSpeed;
	bool _isActived;
	bool _targetIsActived;
};

class objectManager : public singletonBase<objectManager>
{
	vector<tagObject> _vObjectList;
public:
	//������Ʈ�Ŵ��� �ʱ�ȭ
	HRESULT init();
	//������Ʈ�Ŵ��� ����
	void release();
	void update();
	void render();
	objectManager() {}
	~objectManager() {}
};