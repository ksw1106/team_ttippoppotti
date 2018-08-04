#pragma once
#include "objectA.h"

class spike : public objectA
{
private:
	image * _humanDeadImage;
	image* _spikeImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getHumanDeadImage() { return _humanDeadImage; }
	image* getSpikeImage() { return _spikeImage; }
};

