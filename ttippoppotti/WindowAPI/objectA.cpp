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
//	//임시 - 나중에 소환지점 싹 다 저장한후 랜덤으로 뭐 소환할지 선택해서 만들면 된다
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
	case HUMAN_DEAD: //이거랑 스파이크는 세트로 다시 따는게?ㅎㅎㅎ
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
		//누구냐 넌??
		break;
	}

	_object->init();

	return _object;
}
