#include "stdafx.h"
#include "objectA.h"
#include "mapData.h"

void objectA::update()
{
	if (_type <= 9 && !*_targetIsActived)
	{
		if (_state == OBJECT_IDLE)
		{
			if (_type == 7)
				EFFECTMANAGER->woodDebris(_x, _y, RND->getInt(2));
			else if (_type == 8 || _type == 9)
			{
				for (int k = 0; k < _mapData->getObject().size(); k++)
				{
					POINT pt;
					pt.x = (_rc.left + (_rc.right - _rc.left) / 2);
					pt.y = (_rc.top + (_rc.bottom - _rc.top) / 2) + 68;

					if (PtInRect(&_mapData->getObject()[k]._rc, pt))
					{
						_mapData->deleteMapIndexByIndex(k, 5, 5);
						break;
					}
				}
				EFFECTMANAGER->explosion(_x, _y);
				CAMERAMANAGER->CameraShake();
			}
		}
		_state = OBJECT_DESTROY;
	}
	
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
	if (_isFrameImage)
		FRAMEMANAGER->frameChange(_image, _count, _index, _animationSpeed, _isLeft);
}
void objectA::render(HDC hdc)
{
	if (_isStart)
	{
		switch (_state)
		{
		case OBJECT_IDLE:
			if (_isFrameImage)
				_image->frameRender(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
			else
				_image->render(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
			for (int i = 0; i < _vElement.size(); i++)
			{
				if (_vElement[i].isFrameImg)
					_vElement[i].elementImg->frameRender(hdc, _vElement[i].x - CAMERAMANAGER->getCamera().left, _vElement[i].y - CAMERAMANAGER->getCamera().top);
				else
					_vElement[i].elementImg->render(hdc, _vElement[i].x - CAMERAMANAGER->getCamera().left, _vElement[i].y - CAMERAMANAGER->getCamera().top);
			}
			break;
		case OBJECT_MOVE:
			if (_isFrameImage)
				_image->frameRender(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
			else
				_image->render(hdc, _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
			for (int i = 0; i < _vElement.size(); i++)
			{
				if (_vElement[i].isFrameImg)
					_vElement[i].elementImg->frameRender(hdc, _vElement[i].x - CAMERAMANAGER->getCamera().left, _vElement[i].y - CAMERAMANAGER->getCamera().top);
				else
					_vElement[i].elementImg->render(hdc, _vElement[i].x - CAMERAMANAGER->getCamera().left, _vElement[i].y - CAMERAMANAGER->getCamera().top);
			}
			break;
		case OBJECT_DESTROY:
			break;
		}
	}
}

void deadBody::init()
{
	_image = IMAGEMANAGER->findImage("human_dead");
	_count = _index = 0;
	_animationSpeed = 5;
	_isFrameImage = true;
	_isLeft = false;
	_isStart = false;
}

void deadBody::idle()
{
	if (!_isStart)
	{
		for (int i = 0; i < 5; i++)
		{
			tagElement element;
			ZeroMemory(&element, sizeof(tagElement));
			element.elementImg = IMAGEMANAGER->findImage("blackPixelDot");
			element.angle = RND->getFloat(PI2);
			element.x = _x + _image->getFrameWidth() / 2 + RND->getFromFloatTo(5.0f, 10.0f);
			element.y = _y + _image->getFrameHeight() / 2 + RND->getFromFloatTo(2.0f, 5.0f) - 5.0f;
			element.speed = RND->getFromFloatTo(0.5f, 1.5f);

			_vElement.push_back(element);
		}
		_isStart = true;
	}
	else
	{
		for (int i = 0; i < _vElement.size(); ++i)
		{
			_vElement[i].x += cosf(_vElement[i].angle + RND->getFloat(1.1f)) * _vElement[i].speed;
			_vElement[i].y += -sinf(_vElement[i].angle + RND->getFloat(1.1f)) * _vElement[i].speed;
			_vElement[i].count++;
			if (_vElement[i].count % 5 == 0)
				_vElement[i].angle = (i < _vElement.size() / 2) ? _vElement[i].angle + RND->getFloat(PI_4) : _vElement[i].angle - RND->getFloat(PI_4);
		}
	}
}

void deadBody::move()
{
}

void skull::init()
{
	_image = IMAGEMANAGER->findImage("skull");
	_isStart = true;
	_isFrameImage = false;
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
	_isStart = true;
	_isFrameImage = false;
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
	_isStart = true;
	_isFrameImage = false;
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
	_speed = 8.0f;
	_gravity = 0.0f;
	_angle = PI + PI_2;
	_isStart = true;
	_isFrameImage = false;
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
	_speed = 8.0f;
	_gravity = 0.0f;
	_angle = PI + PI_2;
	_isStart = true;
	_isFrameImage = false;
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
	_speed = 8.0f;
	_gravity = 0.0f;
	_angle = PI + PI_2;
	_count = _index = 0;
	_animationSpeed = 3;
	_isLeft = false;
	_isFrameImage = false;
	_activationRc = RectMake(_x - _image->getWidth() * 3, _y - _image->getHeight() * 3, _image->getWidth() * 6, _image->getHeight() * 6);
	_isActived = false;
	_isStart = false;
}

void prisoner::idle()
{
	//EFFECTMANAGER->saveBubble(_x + 68, _y - 5);
	if (!_isStart)
	{
		for (int i = 0; i < 1; i++)
		{
			tagElement element;
			ZeroMemory(&element, sizeof(tagElement));
			element.elementImg = IMAGEMANAGER->findImage("saveBubble2");
			element.isFrameImg = true;
			element.x = _x - 14;
			element.y = _y - 65;

			_vElement.push_back(element);
		}
		_isStart = true;
	}
	else
		if (_isActived)
			for (int i = 0; i < _vElement.size(); i++)
				FRAMEMANAGER->frameChange(_vElement[i].elementImg, _count, _index, _animationSpeed, _isLeft);
}

void prisoner::move()
{
	_image = _prisonerFreedImage;
	_animationSpeed = 2;
	if (_isActived)
	{
		for (int i = 0; i < _vElement.size(); i++)
			FRAMEMANAGER->frameChange(_vElement[i].elementImg, _count, _index, _animationSpeed, _isLeft);
	}
}

void woodenBox::init()
{
	_image = IMAGEMANAGER->findImage("woodenBox");
	_speed = 8.0f;
	_gravity = 0.0f;
	_angle = PI + PI_2;
	_isStart = true;
	_isFrameImage = false;
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
	_isStart = true;
	_isFrameImage = false;
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
	_isStart = true;
	_isFrameImage = false;
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
	_isStart = true;
	_isFrameImage = false;
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
	_isFrameImage = false;
	_isStart = true;
	_isLeft = false;
	_speed = 8.0f;
	_gravity = 0.0f;
	_angle = PI + PI_2;
	_destX = _x;
	_destY = _y;
	_x -= _image->getWidth();
}

void truck::idle()
{
	if (_destX <= _x)
		_x = _destX;
	else
		_x += 5.0f;
}

void truck::move()
{
}

void helicopter::init()
{
	_image = IMAGEMANAGER->findImage("helicopter");
	_count = _index = 0;
	_animationSpeed = 0;
	_isStart = false;
	_isFrameImage = true;
	_isLeft = false;
	_destX = _x;
	_destY = _y;
	_x -= _image->getFrameWidth() * 2;
	_y -= _image->getFrameHeight() * 2;
}

void helicopter::idle()
{
	if (!_isStart)
	{
		for (int i = 0; i < 1; i++)
		{
			tagElement element;
			ZeroMemory(&element, sizeof(tagElement));
			element.elementImg = IMAGEMANAGER->findImage("ladder");
			element.isFrameImg = true;
			element.x = _x - 169;
			element.y = _y - 182;

			_vElement.push_back(element);
		}
		_isStart = true;
	}
	else
	{

		if (_destX >= _x)
			_x = _destX;
		else
			_x += 2.0f;

		if (_destY >= _y)
			_y = _destY;
		else
			_y += 2.0f;
		
		for (int i = 0; i < _vElement.size(); i++)
			_activationRc = RectMake(_vElement[i].x, _vElement[i].y, _vElement[i].elementImg->getWidth(), _vElement[i].elementImg->getHeight());
	}
}

void helicopter::move()
{
	for (int i = 0; i < _vElement.size(); i++)
		_activationRc = RectMake(_vElement[i].x, _vElement[i].y, _vElement[i].elementImg->getWidth(), _vElement[i].elementImg->getHeight());
}

void americanFlag::init()
{
	_image = IMAGEMANAGER->findImage("saveFlag");
	_count = _index = 0;
	_animationSpeed = 5;
	_isFrameImage = true;
	_isStart = false;
	_isActived = false;
	_isLeft = false;
	_destX = _x;
	_destY = _y;
	_activationRc = RectMake(_x - _image->getFrameWidth(), _y, _image->getFrameWidth() * 2, _image->getFrameHeight() * 2);
	_y += _image->getFrameHeight() * 2.5;
}

void americanFlag::idle()
{
}

void americanFlag::move()
{
	if (_y <= _destY)
		_y = _destY;
	else
	{
		_y -= 3.0f;
		if (_y <= _destY + _image->getFrameHeight() * 1.5)
			_isStart = true;
	}
}

void amFlagPole::init()
{
	_image = IMAGEMANAGER->findImage("saveFlag_pole");
	_isStart = true;
	_isFrameImage = false;
}

void amFlagPole::idle()
{
}

void amFlagPole::move()
{
}

void enemyFlag::init()
{
	_image = IMAGEMANAGER->findImage("flag");
	_count = _index = 0;
	_animationSpeed = 7;
	_isFrameImage = true;
	_isActived = true;
	_isLeft = false;
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
	_object->setType(type);

	return _object;
}
