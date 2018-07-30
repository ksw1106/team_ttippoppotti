#pragma once
#include "singletonBase.h"
class CollisionManager : public singletonBase<CollisionManager>
{
public:
	void pixelCollision(RECT rc, int& x, int& y, int dir);
	CollisionManager() {}
	~CollisionManager() {}
};