#pragma once
#include "gameNode.h"
class stageClear : public gameNode
{
public:
	image* _clear[37];
	image* _clearBlank;
	image* _scoreBoard;
	image* _enemyBoard;

	int _clearCount;
	RECT _rc[2];
	float x;

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	stageClear() {}
	~stageClear() {}
};

