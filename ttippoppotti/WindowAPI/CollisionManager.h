#pragma once
#include "singletonBase.h"

#define DIRECT_LEFT 0
#define DIRECT_TOP 1
#define DIRECT_RIGHT 2
#define DIRECT_BOTTOM 3

class CollisionManager : public singletonBase<CollisionManager>
{
	string objectPixel;
	string ladderPixel;

public:
	int pixelCollision(RECT rc, float& x, float& y, float speed, float gravity, int dir, bool isLadder = false);

	void setPixelMap(int num)
	{
		if (1 == num)
		{
			objectPixel = "backGround_pixel";
			ladderPixel = "ladder_pixel";
		}
		else if (2 == num)
		{
			objectPixel = "stage2_background_pixel";
			ladderPixel = "stage2_ladder_pixel";
		}
	}

	HRESULT init();
	void release();
	CollisionManager() {}
	~CollisionManager() {}
};