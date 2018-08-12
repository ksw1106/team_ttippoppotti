#pragma once
#include "gameNode.h"
class missionFailed : public gameNode
{
	image* _missionFailed;
	image* _blackWindow;
	
	int _currentStage;
	int _alpha;
	int _x, _targetX;

	int _count;
public:
	void setCurrentStage(int currentStage) { _currentStage = currentStage; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	missionFailed() {}
	~missionFailed() {}
};

