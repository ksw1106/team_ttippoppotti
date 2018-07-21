#pragma once
#include "gameNode.h"
class testScene : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	testScene() {}
	~testScene() {}
};

