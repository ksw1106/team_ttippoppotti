#include "stdafx.h"
#include "objectA.h"

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

void deadBody::init()
{
	_deadBodyImage = IMAGEMANAGER->findImage("human_dead");
	/*_humanDeadImage = new image;
	_humanDeadImage->init("human_dead.bmp", 1404, 125, 13, 1);
	_spikeImage = new image;
	_spikeImage->init("spike.bmp", 3795.f, 976.f, 15, 108, true, RGB(255, 0, 255));*/
	//임시 - 나중에 소환지점 싹 다 저장한후 랜덤으로 뭐 소환할지 선택해서 만들면 된다
	_x = 3754.f;
	_y = 995.f;

}

void deadBody::idle()
{


}

void deadBody::move()
{
}

void skull::init()
{
	_skullImage = IMAGEMANAGER->findImage("skull");
	//_skullImage->setX();
	//_skullImage->setY();
}

void skull::idle()
{
}

void skull::move()
{
}

void skullPole::init()
{
	_skullPoleImage = IMAGEMANAGER->findImage("skullPole");
	//_skullPoleImage->setX();
	//_skullPoleImage->setY();
}

void skullPole::idle()
{
}

void skullPole::move()
{
}

void doubleSkullPole::init()
{
	_doubleSkullPoleImage = IMAGEMANAGER->findImage("doubleSkullPole");
	//_doubleSkullPoleImage->setX();
	//_doubleSkullPoleImage->setY();
}

void doubleSkullPole::idle()
{
}

void doubleSkullPole::move()
{
}

void skullDrumRed::init()
{
	_skullDrumRedImage = IMAGEMANAGER->findImage("skullDrumRed");
	//_skullDrumImage->setX();
	//_skullDrumImage->setY();
}

void skullDrumRed::idle()
{
}

void skullDrumRed::move()
{
}

void skullDrumGray::init()
{
	_skullDrumGrayImage = IMAGEMANAGER->findImage("skullDrumGray");
	//_skullDrumImage->setX();
	//_skullDrumImage->setY();
}

void skullDrumGray::idle()
{
}

void skullDrumGray::move()
{
}

void prisoner::init()
{
	_prisonerImage[OBJECT_IDLE] = IMAGEMANAGER->findImage("prisoner_inJail");
	_prisonerImage[OBJECT_MOVE] = IMAGEMANAGER->findImage("prisoner_freed");
	//_prisonerImage[OBJECT_IDLE]->setX();
	//_prisonerImage[OBJECT_IDLE]->setY();
	//_prisonerImage[OBJECT_MOVE]->setX();
	//_prisonerImage[OBJECT_MOVE]->setY();
}

void prisoner::idle()
{
}

void prisoner::move()
{
}

void woodenBox::init()
{
	_woodenBoxImage = IMAGEMANAGER->findImage("woodenBox");
	//_woodenBoxImage->setX();
	//_woodenBoxImage->setY();
}

void woodenBox::idle()
{
}

void woodenBox::move()
{
}

void bottleGreen::init()
{
	_bottleGreenImage = IMAGEMANAGER->findImage("bottle_green");
	//_bottleGreenImage->setX();
	//_bottleGreenImage->setY();
}

void bottleGreen::idle()
{
}

void bottleGreen::move()
{
}

void bottleGray::init()
{
	_bottleGrayImage = IMAGEMANAGER->findImage("bottle_gray");
	//_bottleGrayImage->setX();
	//_bottleGrayImage->setY();
}

void bottleGray::idle()
{
}

void bottleGray::move()
{
}

void bottleBrown::init()
{
	_bottleBrownImage = IMAGEMANAGER->findImage("bottle_brown");
	//_bottleBrownImage->setX();
	//_bottleBrownImage->setY();
}

void bottleBrown::idle()
{
}

void bottleBrown::move()
{
}

void truck::init()
{
	_truckImage = IMAGEMANAGER->findImage("truck");
	//_truckImage->setX();
	//_truckImage->setY();
}

void truck::idle()
{
}

void truck::move()
{
}

void helicopter::init()
{
	_helicopterImage = IMAGEMANAGER->findImage("helicopter");
	//_helicopterImage->setX();
	//_helicopterImage->setY();
}

void helicopter::idle()
{
}

void helicopter::move()
{
}

void americanFlag::init()
{
	_americanFlagImage = IMAGEMANAGER->findImage("saveFlag");
	//_americanFlagImage->setX();
	//_americanFlagImage->setY();
}

void americanFlag::idle()
{
}

void americanFlag::move()
{
}

objectA * objectFactory::createObject(OBJECT_TYPE type)
{
	objectA* _objectA;
	switch (type)
	{
	case DEADBODY:
		_objectA = new deadBody;
		break;
	case SKULL:
		_objectA = new skull;
		break;
	case SKULL_POLE:
		_objectA = new skullPole;
		break;
	case DOUBLESKULL_POLE:
		_objectA = new doubleSkullPole;
		break;
	case SKULL_DRUMRED:
		_objectA = new skullDrumRed;
		break;
	case SKULL_DRUMGRAY:
		_objectA = new skullDrumGray;
		break;
	case PRISONER:
		_objectA = new prisoner;
		break;
	case WOODENBOX:
		_objectA = new woodenBox;
		break;
	case BOTTLEGREEN:
		_objectA = new bottleGreen;
		break;
	case BOTTLEGRAY:
		_objectA = new bottleGray;
		break;
	case BOTTLEBROWN:
		_objectA = new bottleBrown;
		break;
	case TRUCK:
		_objectA = new truck;
		break;
	case HELICOPTER:
		_objectA = new helicopter;
		break;
	case AMERICAN_FLAG:
		_objectA = new americanFlag;
		break;
	default:
		//누구냐 넌??
		break;
	}
	_objectA->init();

	return _objectA;
}
