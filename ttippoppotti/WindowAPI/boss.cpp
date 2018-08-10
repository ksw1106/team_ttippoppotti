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
	_terrorKopter.img.bulletFireImage = IMAGEMANAGER->findImage("Å×·¯ÄßÅÍ ÃÑ¾Ë È¿°ú");

	_terrorKopter.angle = 0.f;
	_terrorKopter.speed = 3.f;
	_terrorKopter.x = x;
	_terrorKopter.y = y;
	_terrorKopter.isAttack = false;
	_terrorKopter.isTurning = false;

	_terrorKopter.img.bodyIndex = _terrorKopter.img.gunIndex = _terrorKopter.img.propellerIndex = _terrorKopter.img.rotorIndex = 0;
	_terrorKopter.img.frameCount = 1;
	_terrorKopter.img.frameSpeed = 5;

	_status = LEFT_IDLE;
	_bodyStatus = B_IDLE;
	_gunStatus = BB_ROTATE;
	
	_count = 0;

	_bulletEffectIndex = 0;
	_bulletEffectCount = 0;
	_bulletEffectSpeed = 3;
		
	return S_OK;
}

void boss::release(void)
{

}

void boss::update(void)
{		
	
	this->terrorKopterMove();
	this->frameAnimate();

	// ¸öÅë ·ºÆ®
	_terrorKopter.rcBody = RectMake(_terrorKopter.x + _terrorKopter.img.bodyImage[_bodyStatus]->getFrameWidth() / 4, _terrorKopter.y + 40,
		_terrorKopter.img.bodyImage[_bodyStatus]->getFrameWidth() / 2, _terrorKopter.img.bodyImage[_bodyStatus]->getFrameHeight() / 5 * 3);
	// ±â°üÃÑ ·ºÆ®
	_terrorKopter.rcGun = RectMake(_terrorKopter.x + 100, _terrorKopter.y + 210, _terrorKopter.img.gunImage[_gunStatus]->getFrameWidth(), _terrorKopter.img.gunImage[_gunStatus]->getFrameHeight());
}

void boss::render(void)
{
	if (CAMERAMANAGER->CameraIn(_terrorKopter.rcBody))
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

		// ÃÑ¾Ë È¿°ú
		if (_gunStatus == BB_FIRE)
		{
			if (_terrorKopter.isLeft)
			{
				_terrorKopter.img.bulletFireImage->frameRender(getMemDC(), _terrorKopter.rcGun.left - 30 - CAMERAMANAGER->getCamera().left, _terrorKopter.rcGun.bottom - 30 - CAMERAMANAGER->getCamera().top,
					_terrorKopter.img.bulletFireImage->getFrameX(), _terrorKopter.img.bulletFireImage->getFrameY());
			}
			else
				_terrorKopter.img.bulletFireImage->frameRender(getMemDC(), _terrorKopter.rcGun.right - CAMERAMANAGER->getCamera().left, _terrorKopter.rcGun.bottom - 30 - CAMERAMANAGER->getCamera().top,
					_terrorKopter.img.bulletFireImage->getFrameX(), _terrorKopter.img.bulletFireImage->getFrameY());
		}

		// ·ºÆ® È®ÀÎ
		if (KEYMANAGER->isToggleKey(VK_F10))
		{
			RectangleMake(getMemDC(), _terrorKopter.rcBody.left - CAMERAMANAGER->getCamera().left, _terrorKopter.rcBody.top - CAMERAMANAGER->getCamera().top,
				_terrorKopter.rcBody.right - _terrorKopter.rcBody.left, _terrorKopter.rcBody.bottom - _terrorKopter.rcBody.top);
			RectangleMake(getMemDC(), _terrorKopter.rcGun.left - CAMERAMANAGER->getCamera().left, _terrorKopter.rcGun.top - CAMERAMANAGER->getCamera().top,
				_terrorKopter.img.gunImage[_gunStatus]->getFrameWidth(), _terrorKopter.img.gunImage[_gunStatus]->getFrameHeight());
		}
	}	
}

void boss::terrorKopterMove()
{
	switch (_status)
	{
		case LEFT_IDLE:
		{
			_terrorKopter.isLeft = true;			
			this->idleMovement();
			
			break;		
		}
		case RIGHT_IDLE:
		{
			_terrorKopter.isLeft = false;			
			this->idleMovement();
			
			break;
		}
		
		case LEFT_MOVE:
		{
			_terrorKopter.isLeft = true;
			this->move();

			break;
		}
		case RIGHT_MOVE:
		{
			_terrorKopter.isLeft = false;
			this->move();

			break;
		}
		case LEFT_FIRE_BULLET:
		{
			_terrorKopter.isLeft = true;			
			this->fireBullet();			

			break;
		}
		case RIGHT_FIRE_BULLET:
		{
			_terrorKopter.isLeft = false;			
			this->fireBullet();

			break;
		}
		case LEFT_FIRE_ROCKET:
		{
			_terrorKopter.isLeft = true;			
			this->rocketFire();

			break;
		}
		case RIGHT_FIRE_ROCKET:
		{
			_terrorKopter.isLeft = false;			
			this->rocketFire();

			break;
		}
		
	default:
		break;
	}


}

void boss::idleMovement()
{	
	_bodyStatus = B_IDLE;
	_gunStatus = BB_READY;

	if (_terrorKopter.angle >= 2 * PI) _terrorKopter.angle = 0.f;	 
	_terrorKopter.angle += 0.05f;
	_terrorKopter.y += -sinf(_terrorKopter.angle) * _terrorKopter.speed;		
}

void boss::leftToRight()
{
	_bodyStatus = B_TURN;
	_gunStatus = BB_ROTATE;
	if (_terrorKopter.img.bodyIndex >= _terrorKopter.img.bodyImage[_bodyStatus]->getMaxFrameX()) _terrorKopter.img.bodyIndex = _terrorKopter.img.bodyImage[_bodyStatus]->getMaxFrameX();
	if (_terrorKopter.img.gunIndex >= _terrorKopter.img.gunImage[_gunStatus]->getMaxFrameX()) _terrorKopter.img.gunIndex = _terrorKopter.img.gunImage[_gunStatus]->getMaxFrameX();
	if (_terrorKopter.img.gunIndex == _terrorKopter.img.gunImage[_gunStatus]->getMaxFrameX() &&
		_terrorKopter.img.bodyIndex == _terrorKopter.img.bodyImage[_bodyStatus]->getMaxFrameX())
	{		
		_status = RIGHT_IDLE;
	}
}

void boss::rightToLeft()
{
	_bodyStatus = B_TURN;
	_gunStatus = BB_ROTATE;
	if (_terrorKopter.img.bodyIndex <= 0) _terrorKopter.img.bodyIndex = 0;
	if (_terrorKopter.img.gunIndex <= 0) _terrorKopter.img.gunIndex = 0;
	if (_terrorKopter.img.bodyIndex == 0 && _terrorKopter.img.gunIndex == 0)
	{		
		_status = LEFT_IDLE;
	}
}

void boss::fireBullet()
{
	_bodyStatus = B_IDLE;
	_gunStatus = BB_FIRE;	
}

void boss::rocketFire()
{
	_bodyStatus = B_IDLE;
	_gunStatus = BB_READY;
}

void boss::frameAnimate()
{
	// º»Ã¼
	if (_status != B_TURN)
	{
		FRAMEMANAGER->frameChange(_terrorKopter.img.bodyImage[_bodyStatus], _terrorKopter.img.frameCount, _terrorKopter.img.bodyIndex, _terrorKopter.img.frameSpeed, _terrorKopter.isLeft);
	}
	// º»Ã¼°¡ ÅÏÇÒ¶§,
	else if (_status == B_TURN)
	{
		FRAMEMANAGER->frameChange(_terrorKopter.img.bodyImage[B_TURN], _terrorKopter.img.frameCount, _terrorKopter.img.bodyIndex, _terrorKopter.img.frameSpeed, _terrorKopter.isLeft);		
	}
	// ÇÁ·ÎÆç·¯
	FRAMEMANAGER->frameChange(_terrorKopter.img.propellerImage, _terrorKopter.img.frameCount, _terrorKopter.img.propellerIndex, _terrorKopter.img.frameSpeed, _terrorKopter.isLeft);
	// ±â°üÃÑ
	FRAMEMANAGER->frameChange(_terrorKopter.img.gunImage[_gunStatus], _terrorKopter.img.frameCount, _terrorKopter.img.gunIndex, _terrorKopter.img.frameSpeed, _terrorKopter.isLeft);
	// ÃÑ¾ËÈ¿°ú
	FRAMEMANAGER->frameChange(_terrorKopter.img.bulletFireImage, _bulletEffectCount, _bulletEffectIndex, _bulletEffectSpeed, _terrorKopter.isLeft);
	
}

void boss::verticalMove(float x, float y, float angle)
{
	_terrorKopter.y += -sinf(getAngle(x, y, _terrorKopter.x, _terrorKopter.y))* _terrorKopter.speed;
}

void boss::bombAttack(float x, float y, float angle)
{	
	_terrorKopter.x += cosf(getAngle(x, y - 500, _terrorKopter.x, _terrorKopter.y))* _terrorKopter.speed * 1.5f;
}

void boss::move()
{		
	_bodyStatus = B_IDLE;
	_gunStatus = BB_READY;

	if (_status == LEFT_MOVE)
	{
		_terrorKopter.angle = PI;
	}
	else if (_status == RIGHT_MOVE)
	{
		_terrorKopter.angle = 0.f;
	}
	_terrorKopter.x += cosf(_terrorKopter.angle) * _terrorKopter.speed;

	float distance = getDistance(_terrorKopter.startX, _terrorKopter.startY, _terrorKopter.x, _terrorKopter.y);
	if (distance > 200.f)
	{
		_terrorKopter.isMove = false;
	}
}


