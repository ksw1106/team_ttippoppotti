#pragma once
#include "gameNode.h"
class titleScene : public gameNode
{
	image* title[126];
	float count;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	titleScene(){}
	~titleScene() {}
};

