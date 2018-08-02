#include "stdafx.h"
#include "objectA.h"

void objectA::update()
{
	if (nullptr == _targetIsActived)
	{

	}
	else
	{

	}
}

void spike::init()
{
	_humanDeadImage = new image;
	_humanDeadImage->init("human_dead.bmp", 1404, 125, 13, 1);
	_spikeImage = new image;
	_spikeImage->init("spike.bmp", 3795.f, 976.f, 15, 108, true, RGB(255, 0, 255));
	//임시 - 나중에 소환지점 싹 다 저장한후 랜덤으로 뭐 소환할지 선택해서 만들면 된다
	_x = 3754.f;
	_y = 995.f;

}

void spike::idle()
{
	

}

void spike::move()
{
}
