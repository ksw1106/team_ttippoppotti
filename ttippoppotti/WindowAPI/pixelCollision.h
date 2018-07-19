#pragma once
#include "gameNode.h"

class pixelCollision : public gameNode
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	pixelCollision() {}
	~pixelCollision() {}
};

