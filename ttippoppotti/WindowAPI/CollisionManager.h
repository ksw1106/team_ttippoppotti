#pragma once
#include "singletonBase.h"

#define DIRECT_LEFT 0
#define DIRECT_TOP 1
#define DIRECT_RIGHT 2
#define DIRECT_BOTTOM 3

class CollisionManager : public singletonBase<CollisionManager>
{
public:
	bool pixelCollision(image* img, float& x, float& y, float speed, float gravity, int dir);

	HRESULT init();
	void release();
	CollisionManager() {}
	~CollisionManager() {}
};