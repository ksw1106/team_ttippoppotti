#pragma once
#include "gameNode.h"
class testScene_kmy : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	testScene_kmy() {}
	~testScene_kmy() {}
};