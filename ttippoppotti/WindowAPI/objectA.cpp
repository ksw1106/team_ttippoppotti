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
	//�ӽ� - ���߿� ��ȯ���� �� �� �������� �������� �� ��ȯ���� �����ؼ� ����� �ȴ�
	_x = 3754.f;
	_y = 995.f;

}

void spike::idle()
{
	

}

void spike::move()
{
}
