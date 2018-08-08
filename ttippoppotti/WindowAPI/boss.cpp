#include "stdafx.h"
#include "boss.h"

HRESULT boss::init(float x, float y)
{
	ZeroMemory(&_terrorKopter, sizeof(tagBoss));
	ZeroMemory(&_terrorKopter.img, sizeof(tagBossImage));
		
	_terrorKopter.img.bodyImage[B_IDLE] = IMAGEMANAGER->findImage("Å×·¯ÄßÅÍ ¾ÆÀÌµé");
	_terrorKopter.img.bodyImage[B_TURN] = IMAGEMANAGER->findImage("Å×·¯ÄßÅÍ È¸Àü");
	_terrorKopter.img.bodyImage[B_DEATH] = IMAGEMANAGER->findImage("Å×·¯ÄßÅÍ Á×À½");
	
	_terrorKopter.img.gunImage[BB_READY] = IMAGEMANAGER->findImage("Å×·¯ÄßÅÍ ±â°üÃÑ ¿¹¿­");
	_terrorKopter.img.gunImage[BB_ROTATE] = IMAGEMANAGER->findImage("Å×·¯ÄßÅÍ ±â°üÃÑ È¸Àü");
	_terrorKopter.img.gunImage[BB_FIRE] = IMAGEMANAGER->findImage("Å×·¯ÄßÅÍ ±â°üÃÑ ¹ß»ç");	

	_terrorKopter.img.propellerImage = IMAGEMANAGER->findImage("Å×·¯ÄßÅÍ ÇÁ·ÎÆç·¯");

	_terrorKopter.angle = 0.f;
	_terrorKopter.speed = 5.f;
	_terrorKopter.x = x;
	_terrorKopter.y = y;

	_terrorKopter.img.bodyIndex = _terrorKopter.img.gunIndex = _terrorKopter.img.propellerIndex = _terrorKopter.img.rotorIndex = 0;
	_terrorKopter.img.frameCount = 1;
	_terrorKopter.img.frameSpeed = 5;

	_status = LEFT_IDLE;
	_bodyStatus = B_IDLE;
	_gunStatus = BB_ROTATE;
	
	_count = 0;
	
	return S_OK;
}

void boss::release(void)
{

}

void boss::update(void)
{	
	this->controlAI();
	this->terrorKopterMove();
	this->frameAnimate();

	// ±â°üÃÑ ·ºÆ®
	_terrorKopter.rcGun = RectMake(_terrorKopter.x + 100, _terrorKopter.y + 210, _terrorKopter.img.gunImage[_gunStatus]->getFrameWidth(), _terrorKopter.img.gunImage[_gunStatus]->getFrameHeight());
}

void boss::render(void)
{
	// Å×·¯ÄßÅÍ º»Ã¼
	_terrorKopter.img.bodyImage[_bodyStatus]->frameRender(getMemDC(), _terrorKopter.x - CAMERAMANAGER->getCamera().left, _terrorKopter.y - CAMERAMANAGER->getCamera().top,
		_terrorKopter.img.bodyImage[_bodyStatus]->getFrameX(), _terrorKopter.img.bodyImage[_bodyStatus]->getFrameY());
	
	// ÇÁ·ÎÆç·¯
	if (_bodyStatus != B_TURN)
	{
		_terrorKopter.img.propellerImage->frameRender(getMemDC(), _terrorKopter.x + 50 - CAMERAMANAGER->getCamera().left, _terrorKopter.y + 20 - CAMERAMANAGER->getCamera().top,
			_terrorKopter.img.propellerImage->getFrameX(), _terrorKopter.img.propellerImage->getFrameY());
	}

	// ±â°üÃÑ
	_terrorKopter.img.gunImage[_gunStatus]->frameRender(getMemDC(), _terrorKopter.x + 100 - CAMERAMANAGER->getCamera().left, _terrorKopter.y + 205 - CAMERAMANAGER->getCamera().top,
		_terrorKopter.img.gunImage[_gunStatus]->getFrameX(), _terrorKopter.img.gunImage[_gunStatus]->getFrameY());

	if (KEYMANAGER->isToggleKey(VK_F10))
	{
		RectangleMake(getMemDC(), _terrorKopter.rcGun.left - CAMERAMANAGER->getCamera().left, _terrorKopter.rcGun.top - CAMERAMANAGER->getCamera().top,
			_terrorKopter.img.gunImage[_gunStatus]->getFrameWidth(), _terrorKopter.img.gunImage[_gunStatus]->getFrameHeight());
	}
}

void boss::terrorKopterMove()
{
	switch (_status)
	{
		case LEFT_IDLE:
		{
			_terrorKopter.isLeft = true;
			_bodyStatus = B_IDLE;
			_gunStatus = BB_READY;
			this->idleMovement();
			
			break;		
		}
		case RIGHT_IDLE:
		{
			_terrorKopter.isLeft = false;
			_bodyStatus = B_IDLE;
			_gunStatus = BB_READY;
			this->idleMovement();
			
			break;
		}
		case LEFT_TO_RIGHT:
		{
			_terrorKopter.isLeft = false;
			_bodyStatus = B_TURN;
			_gunStatus = BB_ROTATE;
			this->leftToRight();
			
			break;
		}
		case RIGHT_TO_LEFT:
		{
			_terrorKopter.isLeft = true;
			_bodyStatus = B_TURN;
			_gunStatus = BB_ROTATE;
			this->rightToLeft();

			break;
		}
		case LEFT_MOVE:
		{
			_terrorKopter.isLeft = true;
			_bodyStatus = B_IDLE;
			_gunStatus = BB_READY;

			this->move();
			break;
		}
		case RIGHT_MOVE:
		{
			_terrorKopter.isLeft = false;
			_bodyStatus = B_IDLE;
			_gunStatus = BB_READY;

			this->move();
			break;
		}
		case LEFT_FIRE_BULLET:
		{
			_terrorKopter.isLeft = true;
			_bodyStatus = B_IDLE;
			_gunStatus = BB_FIRE;
			this->fireBullet();

			break;
		}
		case RIGHT_FIRE_BULLET:
		{
			_terrorKopter.isLeft = false;
			_bodyStatus = B_IDLE;
			_gunStatus = BB_FIRE;
			this->fireBullet();

			break;
		}
		case LEFT_FIRE_ROCKET:
		{
			_terrorKopter.isLeft = true;
			_bodyStatus = B_IDLE;
			_gunStatus = BB_READY;
			this->rocketFire();

			break;
		}
		case RIGHT_FIRE_ROCKET:
		{
			_terrorKopter.isLeft = false;
			_bodyStatus = B_IDLE;
			_gunStatus = BB_READY;
			this->rocketFire();

			break;
		}
		
	default:
		break;
	}


}

void boss::idleMovement()
{	
	if (_terrorKopter.angle >= 2 * PI) _terrorKopter.angle = 0.f;	 
	_terrorKopter.angle += 0.05f;
	_terrorKopter.y += -sinf(_terrorKopter.angle) * _terrorKopter.speed;		
}

void boss::leftToRight()
{

}

void boss::rightToLeft()
{

}

void boss::fireBullet()
{

}

void boss::rocketFire()
{

}

void boss::frameAnimate()
{
	// º»Ã¼
	FRAMEMANAGER->frameChange(_terrorKopter.img.bodyImage[_bodyStatus], _terrorKopter.img.frameCount, _terrorKopter.img.bodyIndex, _terrorKopter.img.frameSpeed, _terrorKopter.isLeft);
	// ÇÁ·ÎÆç·¯
	FRAMEMANAGER->frameChange(_terrorKopter.img.propellerImage, _terrorKopter.img.frameCount, _terrorKopter.img.propellerIndex, _terrorKopter.img.frameSpeed, _terrorKopter.isLeft);
	// ±â°üÃÑ
	FRAMEMANAGER->frameChange(_terrorKopter.img.gunImage[_gunStatus], _terrorKopter.img.frameCount, _terrorKopter.img.gunIndex, _terrorKopter.img.frameSpeed, _terrorKopter.isLeft);
}

void boss::controlAI()
{
	++_count;
	if (_count == 150)
	{
		_stateNum = RND->getFromIntTo(0,9);
	}
	if (_count > 150) _count = 0;

	switch (_stateNum)
	{
	case 0:
	{
		_status = LEFT_IDLE;
		break;
	}
	case 1:
	{
		_status = RIGHT_IDLE;
		break;
	}
	case 2:
	{
		_status = LEFT_TO_RIGHT;
		break;
	}
	case 3:
	{
		_status = RIGHT_TO_LEFT;
		break;
	}
	case 4:
	{
		_status = LEFT_FIRE_BULLET;
		break;
	}
	case 5:
	{
		_status = RIGHT_FIRE_BULLET;
		break;
	}
	case 6:
	{
		_status = LEFT_FIRE_ROCKET;
		break;
	}
	case 7:
	{
		_status = RIGHT_FIRE_ROCKET;
		break;
	}	
	case 8:
	{
		_status = LEFT_MOVE;
		break;
	}
	case 9:
	{
		_status = RIGHT_MOVE;
		break;
	}

	default:
		break;
	}
}

void boss::move()
{
	if (_status == LEFT_MOVE)
	{
		_terrorKopter.angle = PI;
	}
	else if (_status == RIGHT_MOVE)
	{
		_terrorKopter.angle = 0.f;
	}
	_terrorKopter.x += cosf(_terrorKopter.angle) * _terrorKopter.speed;
}
