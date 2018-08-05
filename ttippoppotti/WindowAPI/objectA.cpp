#include "stdafx.h"
#include "objectA.h"

void objectA::update()
{
	if (!_targetIsActived)
		_state = OBJECT_DESTROY;
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
		FRAMEMANAGER->frameChange(_image, _count, _index, _animationSpeed, _isLeft);
}
void objectA::render(HDC hdc)
{
	switch (_state)
	{
	case OBJECT_IDLE:
		if (_isFrameImage)
			_image->frameRender(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
		else
			_image->render(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
		break;
	case OBJECT_MOVE:
		if (_isFrameImage)
			_image->frameRender(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
		else
			_image->render(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
		break;
	case OBJECT_DESTROY:
		break;
	}
}

void deadBody::init()
{
	_image = IMAGEMANAGER->findImage("human_dead");
	_count = _index = 0;
	_animationSpeed = 5;
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
	_image = IMAGEMANAGER->findImage("skull");
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
	_image = IMAGEMANAGER->findImage("skullPole");
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
	_image = IMAGEMANAGER->findImage("doubleSkullPole");
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
	_image = IMAGEMANAGER->findImage("skullDrum_red");
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
	_image = IMAGEMANAGER->findImage("skullDrum_gray");
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
	_image = IMAGEMANAGER->findImage("prisoner_inJail");
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
	_image = IMAGEMANAGER->findImage("woodenBox");
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
	_image = IMAGEMANAGER->findImage("bottle_green");
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
	_image = IMAGEMANAGER->findImage("bottle_gray");
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
	_image = IMAGEMANAGER->findImage("bottle_brown");
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
	_image = IMAGEMANAGER->findImage("truck");
	_count = _index = 0;
	_animationSpeed = 5;
	_isFrameImage = false;
	_isLeft = false;
	_state = OBJECT_IDLE;
	_destX = _x;
	_destY = _y;
	_x = -_image->getFrameWidth();
}

void truck::idle()
{
	if (_destX <= _x)
		_x = _destX;
	else
		_x += 3.0f;
}

void truck::move()
{
	//_isFrameImage = false;
	//_image[_state]->setFrameX(_image[_state]->getMaxFrameX());
}

void helicopter::init()
{
	_image = IMAGEMANAGER->findImage("helicopter");
	_count = _index = 0;
	_animationSpeed = 5;
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
	_image = IMAGEMANAGER->findImage("saveFlag");
	_count = _index = 0;
	_animationSpeed = 5;
	_isFrameImage = true;
	_isActived = false;
	_isLeft = false;
	_state = OBJECT_IDLE;
	_destX = _x;
	_destY = _y;
	_rc = RectMake(_x - _image->getFrameWidth(), _y, _image->getFrameWidth() * 2, _image->getFrameHeight() * 2);
	_y += _image->getFrameHeight() * 2.5;
}

void americanFlag::idle()
{
	if (_isActived)
	{
		if (_y != _destY)
		{
			_y -= 3.0f;
			if (_y <= _destY)
				_y = _destY;
		}
	}
}

void americanFlag::move()
{
	_isActived = true;
}

void amFlagPole::init()
{
	_image = IMAGEMANAGER->findImage("saveFlag_pole");
	_isActived = true;
	_isFrameImage = false;
}

void amFlagPole::idle()
{
	_isActived = true;
}

void amFlagPole::move()
{
	_isActived = true;
}

void enemyFlag::init()
{
	_image = IMAGEMANAGER->findImage("flag");
	_count = _index = 0;
	_animationSpeed = 5;
	_isFrameImage = true;
	_isActived = true;
	_isLeft = false;
	_state = OBJECT_IDLE;
}

void enemyFlag::idle()
{
	_isActived = true;
}

void enemyFlag::move()
{
	_isActived = true;
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
	case AMFLAG_POLE:
		_object = new amFlagPole;
		break;
	case ENEMY_FLAG:
		_object = new enemyFlag;
		break;
	default:
		//´©±¸³Ä ³Í??
		break;
	}
	_object->init();

	return _object;
}

