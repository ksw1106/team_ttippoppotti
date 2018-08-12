#pragma once
#include "gameNode.h"
class stageStart : public gameNode
{
	image* start[4];
	const char* soundName[4];
	int soundCount;
	int goCount;
	int startPosX;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	stageStart() {}
	~stageStart() {}
};

