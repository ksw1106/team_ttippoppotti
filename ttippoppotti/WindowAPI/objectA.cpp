#include "stdafx.h"
#include "objectA.h"

void objectA::update()
{
	switch (_state)
	{
	case OBJECT_IDLE:
		idle();
		break;
	case OBJECT_MOVE:
		move();
		break;
	case OBJECT_DESTROY:
		break;
	}
	if(_isFrameImage)
		FRAMEMANAGER->frameChange(_image[_state], _count, _index, _animationSpeed, _isLeft);
}
void objectA::render(HDC hdc)
{
	switch (_state)
	{
	case OBJECT_IDLE:
		_image[OBJECT_IDLE]->frameRender(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
		break;
	case OBJECT_MOVE:
		_image[OBJECT_MOVE]->frameRender(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
		break;
	case OBJECT_DESTROY:
		break;
	}
}

void deadBody::init()
{
	for (int i = 0; i < 3; i++)
		_image[i] = IMAGEMANAGER->findImage("human_dead");
	_count = _index = 0;
	_animationSpeed = 3;
	_isFrameImage = true;
	_isLeft = false;
	_state = OBJECT_IDLE;
}

void deadBody::idle()
{
}

void deadBody::move()
{
}

void skull::init()
{
	for (int i = 0; i < 3; i++)
		_image[i] = IMAGEMANAGER->findImage("skull");
	_isFrameImage = false;
	_state = OBJECT_IDLE;
}

void skull::idle()
{
}

void skull::move()
{
}

void skullPole::init()
{
	for (int i = 0; i < 3; i++)
		_image[i] = IMAGEMANAGER->findImage("skullPole");
	_isFrameImage = false;
	_state = OBJECT_IDLE;
}

void skullPole::idle()
{
}

void skullPole::move()
{
}

void doubleSkullPole::init()
{
	for (int i = 0; i < 3; i++)
		_image[i] = IMAGEMANAGER->findImage("doubleSkullPole");
	_isFrameImage = false;
	_state = OBJECT_IDLE;
}

void doubleSkullPole::idle()
{
}

void doubleSkullPole::move()
{
}

void skullDrumRed::init()
{
	for (int i = 0; i < 3; i++)
		_image[i] = IMAGEMANAGER->findImage("skullDrumRed");
	_isFrameImage = false;
	_state = OBJECT_IDLE;
}

void skullDrumRed::idle()
{
}

void skullDrumRed::move()
{
}

void skullDrumGray::init()
{
	for (int i = 0; i < 3; i++)
		_image[i] = IMAGEMANAGER->findImage("skullDrumGray");
	_isFrameImage = false;
	_state = OBJECT_IDLE;
}

void skullDrumGray::idle()
{
}

void skullDrumGray::move()
{
}

void prisoner::init()
{
	for (int i = 0; i < 3; i++)
		_image[i] = IMAGEMANAGER->findImage("prisoner_inJail");
	_prisonerFreedImage = IMAGEMANAGER->findImage("prisoner_freed");
	_isFrameImage = false;
	_state = OBJECT_IDLE;
}

void prisoner::idle()
{
}

void prisoner::move()
{
}

void woodenBox::init()
{
	for (int i = 0; i < 3; i++)
		_image[i] = IMAGEMANAGER->findImage("woodenBox");
	_isFrameImage = false;
	_state = OBJECT_IDLE;
}

void woodenBox::idle()
{
}

void woodenBox::move()
{
}

void bottleGreen::init()
{
	for (int i = 0; i < 3; i++)
		_image[i] = IMAGEMANAGER->findImage("bottle_green");
	_isFrameImage = false;
	_state = OBJECT_IDLE;
}

void bottleGreen::idle()
{
}

void bottleGreen::move()
{
}

void bottleGray::init()
{
	for (int i = 0; i < 3; i++)
		_image[i] = IMAGEMANAGER->findImage("bottle_gray");
	_isFrameImage = false;
	_state = OBJECT_IDLE;
}

void bottleGray::idle()
{
}

void bottleGray::move()
{
}

void bottleBrown::init()
{
	for (int i = 0; i < 3; i++)
		_image[i] = IMAGEMANAGER->findImage("bottle_brown");
	_isFrameImage = false;
	_state = OBJECT_IDLE;
}

void bottleBrown::idle()
{
}

void bottleBrown::move()
{
}

void truck::init()
{
	for (int i = 0; i < 3; i++)
		_image[i] = IMAGEMANAGER->findImage("truck");
	_count = _index = 0;
	_animationSpeed = 3;
	_isFrameImage = true;
	_isLeft = false;
	_state = OBJECT_IDLE;
	_oldX = _x;
	_oldY = _y;
	_x = -_image[_state]->getFrameWidth();
}

void truck::idle()
{
	_isFrameImage = true;
	_x += 3.0f;
	if (_oldX <= _x)
		_x = _oldX;
}

void truck::move()
{
	//_isFrameImage = false;
	//_image[_state]->setFrameX(_image[_state]->getMaxFrameX());
}

void helicopter::init()
{
	for (int i = 0; i < 3; i++)
		_image[i] = IMAGEMANAGER->findImage("helicopter");
	_count = _index = 0;
	_animationSpeed = 3;
	_isFrameImage = true;
	_isLeft = false;
	_state = OBJECT_IDLE;
}

void helicopter::idle()
{
}

void helicopter::move()
{
}

void americanFlag::init()
{
	for (int i = 0; i < 3; i++)
		_image[i] = IMAGEMANAGER->findImage("saveFlag");
	_count = _index = 0;
	_animationSpeed = 3;
	_isFrameImage = true;
	_isLeft = false;
	_state = OBJECT_IDLE;
	_oldX = _x;
	_oldY = _y;
	//_y += _image[_state]->getFrameHeight();
}

void americanFlag::idle()
{
}

void americanFlag::move()
{
}

objectA * objectFactory::createObject(OBJECT_TYPE type)
{
	objectA* _object;
	switch (type)
	{
	case DEADBODY:
		_object = new deadBody;
		break;
	case SKULL:
		_object = new skull;
		break;
	case SKULL_POLE:
		_object = new skullPole;
		break;
	case DOUBLESKULL_POLE:
		_object = new doubleSkullPole;
		break;
	case BOTTLEGREEN:
		_object = new bottleGreen;
		break;
	case BOTTLEGRAY:
		_object = new bottleGray;
		break;
	case BOTTLEBROWN:
		_object = new bottleBrown;
		break;
	case PRISONER:
		_object = new prisoner;
		break;
	case WOODENBOX:
		_object = new woodenBox;
		break;
	case SKULL_DRUMRED:
		_object = new skullDrumRed;
		break;
	case SKULL_DRUMGRAY:
		_object = new skullDrumGray;
		break;
	case TRUCK:
		_object = new truck;
		break;
	case HELICOPTER:
		_object = new helicopter;
		break;
	case AMERICAN_FLAG:
		_object = new americanFlag;
		break;
	default:
		//´©±¸³Ä ³Í??
		break;
	}
	_object->init();

	return _object;
}
