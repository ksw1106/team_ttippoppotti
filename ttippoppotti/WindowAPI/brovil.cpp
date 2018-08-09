#include "stdafx.h"
#include "brovil.h"

HRESULT brovil::init(float x, float y)
{
	_x = x, _y = y;
	_hp = 10;

	_brovilImage.brovilImg[BROVIL_IDLE] = IMAGEMANAGER->findImage("브로빌평상시");
	_brovilImage.brovilImg[BROVIL_WALK] = IMAGEMANAGER->findImage("브로빌걸음");
	_brovilImage.brovilImg[BROVIL_KNOCK_BACK] = IMAGEMANAGER->findImage("브로빌넉백");
	_brovilImage.brovilImg[BROVIL_DEAD] = IMAGEMANAGER->findImage("브로빌죽음");
	_brovilImage.brovilImg[BROVIL_DISAPPEAR] = IMAGEMANAGER->findImage("브로빌승화");
	_brovilImage.brovilImg[BROVIL_FLY_AWAY] = IMAGEMANAGER->findImage("브로빌점프");

	_brovilImage.frameCount = _brovilImage.frameIndex = 0;
	_brovilImage.frameSpeed = 3;
	
	this->initSign();
	this->corpseInit();

	_brovilStatus = BROVIL_IDLE;
	_gravity = 0.f;

	_speed = 5.f;
	_angle = PI;
	
	_accel = 0.8f;
	_kbSpeed = 20.f;
	_kbIndex = 0;
	_isAlive = true;
	_isLeft = true;
	_isOn = true;	
	_isUncovered = false;
	_isStrange = false;
	_isApart = false;

	return S_OK;
}

void brovil::release(void)
{
	_warnSign->release();
	SAFE_DELETE(_warnSign);
	_doubtSign->release();
	SAFE_DELETE(_doubtSign);	
	for (int i = 0; i < BODY_PART; ++i)
	{
		_corpse[i].corpseImage->release();
		SAFE_DELETE(_corpse[i].corpseImage);
	}
}

void brovil::update(void)
{
	this->fall();
	this->changeStatus();

	_rcBrovil = RectMake(_x, _y, _brovilImage.brovilImg[_brovilStatus]->getFrameWidth(), _brovilImage.brovilImg[_brovilStatus]->getFrameHeight());

}

void brovil::render(void)
{
	if (CAMERAMANAGER->CameraIn(_rcBrovil))
	{
		//몸통 이미지 렌더
		if (!_isApart)	// 분해되지 않았을때
		{
			_brovilImage.brovilImg[_brovilStatus]->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top,
				_brovilImage.brovilImg[_brovilStatus]->getFrameX(), _brovilImage.brovilImg[_brovilStatus]->getFrameY());
		}

		// 시체 렌더
		else
		{
			for (int i = 0; i < BODY_PART; ++i)
			{
				_corpse[i].corpseImage->render(getMemDC(), _corpse[i].x - CAMERAMANAGER->getCamera().left, _corpse[i].y - CAMERAMANAGER->getCamera().top);
			}
		}
		

		// 플레이어 발견했을때, 느낌표 말풍선!
		if (_isUncovered && _warnFrameIndex < _warnSign->getMaxFrameX())
		{
			_warnSign->frameRender(getMemDC(), _x + 10 - CAMERAMANAGER->getCamera().left, _y - 50 - CAMERAMANAGER->getCamera().top, _warnSign->getFrameX(), _warnSign->getFrameY());
		}

		// 적 (아군) 시체를 발견했을때 물음표 말풍선!
		if (_isStrange && _doubtFrameIndex < _doubtSign->getMaxFrameX())
		{
			_doubtSign->frameRender(getMemDC(), _x + 10 - CAMERAMANAGER->getCamera().left, _y - 50 - CAMERAMANAGER->getCamera().top, _doubtSign->getFrameX(), _doubtSign->getFrameY());
		}

	}

	if (KEYMANAGER->isToggleKey(VK_F4))
	{
		// 에너미 렉트 렌더
		Rectangle(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top,
			_x + _brovilImage.brovilImg[_brovilStatus]->getFrameWidth() - CAMERAMANAGER->getCamera().left, _y + _brovilImage.brovilImg[_brovilStatus]->getFrameHeight() - CAMERAMANAGER->getCamera().top);
	}

	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		// 적 시야 렉트 렌더
		RectangleMake(getMemDC(), _rcBrovilSight.left - CAMERAMANAGER->getCamera().left, _rcBrovilSight.top - CAMERAMANAGER->getCamera().top,
			800 + _brovilImage.brovilImg[_brovilStatus]->getFrameWidth(), _brovilImage.brovilImg[_brovilStatus]->getFrameHeight());
	}
}

//==============================================================================================
//==============================================================================================
//==============================================================================================
//==============================================================================================
//==============================================================================================

void brovil::changeStatus()
{
	switch (_brovilStatus)
	{
	case BROVIL_IDLE:
	{

		break;
	}
	case BROVIL_WALK:
	{
		this->deadMove();
		break;
	}
	case BROVIL_KNOCK_BACK:
	{
		_isAlive = false;
		this->knockBackMove(_isLeft);
		
		// 플레이어 발견!
		this->discover();

		// 아군 시체 발견
		this->doubt();

		break;
	}
	case BROVIL_DEAD:
	{	
		this->enemyExplode();
		break;
	}
	case BROVIL_DISAPPEAR:
	{
		
		break;
	}
	
	default:
		break;
	}
}

void brovil::corpseInit()
{
	for (int i = 0; i < BODY_PART; ++i)
	{
		_corpse[i].angle = RND->getFromFloatTo(PI / 8, PI / 8 * 7);
		_corpse[i].speed = RND->getFromFloatTo(6.f, 9.f);
		_corpse[i].gravity = 0.0f;
		_corpse[i].corpseImage = new image;
	}
	_corpse[0].corpseImage->init("enemyImage/brovil_part_head.bmp", 18, 32, true, RGB(255, 0, 255));
	_corpse[1].corpseImage->init("enemyImage/brovil_part_body.bmp", 40, 44, true, RGB(255, 0, 255));
	_corpse[2].corpseImage->init("enemyImage/brovil_part_arm.bmp", 12, 28, true, RGB(255, 0, 255));
	_corpse[3].corpseImage->init("enemyImage/brovil_part_leg.bmp", 16, 16, true, RGB(255, 0, 255));
}

void brovil::fall()
{
	// 떨어질때, 아닐떄
	if (!_isOn)
	{
		if (_gravity < 3.0f) _gravity = 3.0f;
		_y += -sinf(_angle)*_speed + _gravity;
		_gravity += 0.5f;
	}
	else
	{
		_gravity = 0;
	}
}

void brovil::deadMove()
{
	if (_isLeft)
	{
		_angle = PI;
	}
	else
	{
		_angle = 0.f;
	}
	_x += cosf(_angle)* _speed;
	_y += -sinf(_angle)* _speed;
}

void brovil::doubt()
{

}

void brovil::discover()
{

}

void brovil::flyAway()
{
	if (_kbSpeed > 0)
	{
		if (_isLeft)
		{
			_angle = PI / 4 * 3;
		}
		else
		{
			_angle = PI / 4;
		}
		_x += cosf(_angle) * _kbSpeed;
		_y += -sinf(_angle) * _kbSpeed;
		_kbSpeed -= 0.3f;
	}

	if (_kbSpeed <= 0.f)
	{
		_brovilStatus = BROVIL_DEAD;
	}
}

void brovil::knockBackMove(bool isLeft)
{
	// 넉백됐을때, 뒤로 날라감
	if (_kbSpeed > 0)
	{
		if (isLeft)
		{
			_angle = PI / 5 * 4;
		}
		else
		{
			_angle = PI / 5;
		}
		_x += cosf(_angle)*_kbSpeed;
		_y += -sinf(_angle)*_kbSpeed;
		_kbSpeed -= 0.5f;
	}
}

void brovil::enemyExplode()
{
	if (_hp <= 0)
	{
		_isApart = true;
	}

	if (_isApart)
	{
		this->partMove();
	}
}

void brovil::partMove()
{
	for (int i = 0; i < 4; ++i)
	{
		_corpse[i].x += cosf(_corpse[i].angle) * _corpse[i].speed;
		_corpse[i].y += -sinf(_corpse[i].angle) * _corpse[i].speed + _corpse[i].gravity;
		_corpse[i].gravity += 0.4f;
		_corpse[i].speed -= 0.2f;
		_corpse[i].rcCorpse = RectMake(_corpse[i].x, _corpse[i].y, _corpse[i].corpseImage->getWidth(), _corpse[i].corpseImage->getHeight());

		if (_corpse[i].speed <= 0.f) _corpse[i].speed = 0;
	}
}

void brovil::frameAnimate()
{
	if (_brovilStatus == BROVIL_KNOCK_BACK)
	{
		_brovilImage.frameSpeed = 2;

		if (_isLeft)
		{
			if (_brovilImage.frameIndex <= 0)
			{
				_brovilStatus = BROVIL_DEAD;
			}
		}
		else
		{
			if (_brovilImage.frameIndex >= _brovilImage.brovilImg[_brovilStatus]->getMaxFrameX())
			{
				_brovilStatus = BROVIL_DEAD;
			}

		}

		FRAMEMANAGER->frameChange(_brovilImage.brovilImg[_brovilStatus], _brovilImage.frameCount, _brovilImage.frameIndex, _brovilImage.frameSpeed, _isLeft);
	}
	else if (_brovilStatus == BROVIL_DEAD)
	{
		FRAMEMANAGER->frameChange(_brovilImage.brovilImg[BROVIL_DEAD], _brovilImage.frameCount, _brovilImage.frameIndex, _brovilImage.frameSpeed, _isLeft);
	}	
	else if (_brovilStatus == BROVIL_DISAPPEAR)
	{
		FRAMEMANAGER->frameChange(_brovilImage.brovilImg[BROVIL_DISAPPEAR], _brovilImage.frameCount, _brovilImage.frameIndex, _brovilImage.frameSpeed, _isLeft);
	}
	else
	{
		_brovilImage.frameSpeed = 10;
		FRAMEMANAGER->frameChange(_brovilImage.brovilImg[_brovilStatus], _brovilImage.frameCount, _brovilImage.frameIndex, _brovilImage.frameSpeed, _isLeft);		
	}

	// 플레이어 만났을 때 '!' 프레임 한번만 돌게
	if (_isUncovered && _warnFrameIndex < _warnSign->getMaxFrameX())
	{
		FRAMEMANAGER->frameChange(_warnSign, _warnFrameCount, _warnFrameIndex, _frameSpeed, 0);
	}

	// 에너미 아군 시체 만났을때, '?' 프레임 한번만 돌게
	if (_isStrange && _doubtFrameIndex < _doubtSign->getMaxFrameX())
	{
		FRAMEMANAGER->frameChange(_doubtSign, _doubtFrameCount, _doubtFrameIndex, _frameSpeed, 0);
	}
}

void brovil::initSign()
{
	_warnSign = new image;
	_warnSign->init("enemyImage/ExclamationMark.bmp", 1020, 60, 17, 1);
	_warnFrameCount = 5;
	_warnFrameIndex = 0;
	_warnSign->setFrameY(0);

	_doubtSign = new image;
	_doubtSign->init("enemyImage/QuestionMark.bmp", 960, 60, 16, 1);
	_doubtFrameCount = 5;
	_doubtFrameIndex = 0;
	_doubtSign->setFrameY(0);
}
