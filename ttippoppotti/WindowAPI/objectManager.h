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
	//오브젝트매니져 초기화
	HRESULT init();
	//오브젝트매니져 해제
	void release();
	void update();
	void render();
	objectManager() {}
	~objectManager() {}
};