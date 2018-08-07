#pragma once
#include "singletonBase.h"

#define DIRECT_LEFT 0
#define DIRECT_TOP 1
#define DIRECT_RIGHT 2
#define DIRECT_BOTTOM 3

class CollisionManager : public singletonBase<CollisionManager>
{
public:
	int pixelCollision(RECT rc, float& x, float& y, float speed, float gravity, int dir, bool isLadder = false);

	HRESULT init();
	void release();
	CollisionManager() {}
	~CollisionManager() {}
};