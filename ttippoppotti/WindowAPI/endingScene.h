#pragma once
#include "gameNode.h"
class endingScene : public gameNode
{
	image* thankyou;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	endingScene() {}
	~endingScene() {}
};