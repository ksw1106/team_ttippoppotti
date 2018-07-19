#pragma once
#include "gameNode.h"
#include "bullet.h"


class enemyManager : public gameNode
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	enemyManager() {}
	~enemyManager() {}
};

