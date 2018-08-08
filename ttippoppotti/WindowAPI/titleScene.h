#pragma once
#include "gameNode.h"
class titleScene : public gameNode
{
	image* title[126];
	image* startButton[33];
	image* optionButton[33];
	float count, startCount, optionCount;
	bool isStart;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	titleScene(){}
	~titleScene() {}
};

