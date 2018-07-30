#pragma once
#include "singletonBase.h"
class CollisionManager : public singletonBase<CollisionManager>
{
public:
	bool pixelCollision(image* img, float& x, float& y, int dir);

	HRESULT init();
	void release();
	CollisionManager() {}
	~CollisionManager() {}
};