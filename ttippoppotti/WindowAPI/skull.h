#pragma once
#include "objectA.h"
class skull : public objectA
{
public:
	void init();
	void idle();
	void move();

	skull() {}
	~skull() {}
};

