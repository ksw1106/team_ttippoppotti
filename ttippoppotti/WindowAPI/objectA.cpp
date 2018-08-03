#include "stdafx.h"
#include "objectA.h"
#include "skull.h"
#include "spike.h"

void objectA::update()
{
	switch (_state)
	{
	case OBJECT_IDLE:
		break;
	case OBJECT_MOVE:
		break;
	case OBJECT_DESTROY:
		break;
	}
}

void objectA::render()
{
	switch (_state)
	{
	case OBJECT_IDLE:
		break;
	case OBJECT_MOVE:
		break;
	case OBJECT_DESTROY:
		break;
	}
}

//void spike::init()
//{
//	_humanDeadImage = new image;
//	_humanDeadImage->init("human_dead.bmp", 1404, 125, 13, 1);
//	_spikeImage = new image;
//	_spikeImage->init("spike.bmp", 3795.f, 976.f, 15, 108, true, RGB(255, 0, 255));
//	//�ӽ� - ���߿� ��ȯ���� �� �� �������� �������� �� ��ȯ���� �����ؼ� ����� �ȴ�
//	_x = 3754.f;
//	_y = 995.f;
//



objectA * objectFactory::createObject(OBJECT_TYPE type)
{
	objectA* _object;

	switch (type)
	{
	case SKULL:
		_object = new skull;
		break;
	case SKULL_POLE:
		break;
	case SKULL_CONTAINER:
		break;
	case PRISONER:
		break;
	case WOODBOX:
		break;
	case BOTTLEGREEN:
		break;
	case BOTTLEGRAY:
		break;
	case BOTTLEBROWN:
		break;
	case TRUCK:
		break;
	case HUMAN_DEAD: //�̰Ŷ� ������ũ�� ��Ʈ�� �ٽ� ���°�?������
		break;
	case HELICOPTER:
		break;
	case BOX:
		break;
	case SPIKE:
		_object = new spike;
		break;
	case FLAG:
		break;
	default:
		//������ ��??
		break;
	}

	_object->init();

	return _object;
}
