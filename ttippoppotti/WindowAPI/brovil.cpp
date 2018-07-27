#include "stdafx.h"
#include "brovil.h"

HRESULT brovil::init(int x, int y, int randomNum)
{
	_x = x, _y = y;
	_hp = 100;

	_bodyImage[BROVIL_IDLE] = IMAGEMANAGER->findImage("브로빌평상시");
	_bodyImage[BROVIL_WALK] = IMAGEMANAGER->findImage("브로빌걸음");
	_bodyImage[BROVIL_KNOCK_BACK] = IMAGEMANAGER->findImage("브로빌넉백");
	_bodyImage[BROVIL_DEAD] = IMAGEMANAGER->findImage("브로빌시체");
	_bodyImage[BROVIL_DISAPPEAR] = IMAGEMANAGER->findImage("브로빌승화");

	_warnSign = IMAGEMANAGER->findImage("알람");
	_doubtSign = IMAGEMANAGER->findImage("의문");

	_warnSign->setFrameY(0);
	_doubtSign->setFrameY(0);

	_angle = 270.f * 3.14f / 180;
	_speed = 2.f;
	_gravity = 0.f;
	_kbSpeed = 20.f;
	setStatus(BROVIL_IDLE);

	_randomNumber = randomNum;

	_frameCount = _frameIndex = _frameIndex2 = _frameIndex3 = _frameIndex4 = 0;
	_actionSpeed = 4;

	_isLeft = true;
	_isOn = false;
	_isAlarm = false;
	_isAlarm2 = false;
	_rc = RectMakeCenter(_x, _y, _bodyImage[getStatus()]->getFrameWidth(), _bodyImage[getStatus()]->getFrameHeight());	

	return S_OK;
}

void brovil::release(void)
{
}

void brovil::update(void)
{
	if (_warnSign->getFrameX() >= _warnSign->getMaxFrameX())
	{
		_isAlarm = false;
	}
	if (_doubtSign->getFrameX() >= _doubtSign->getMaxFrameX())
	{
		_isAlarm2 = false;
	}

	if (_status <= 2 || _status == 0)
	{
		this->controlAI(RND->getInt(20));
	}
	
	if (_status == BROVIL_KNOCK_BACK)
	{
		this->knockBackMove();
	}

	this->move();
	this->frameAnimate();
	
	_bodyImage[getStatus()]->setX(_rc.left);
	_bodyImage[getStatus()]->setY(_rc.top);
	
	_rc = RectMakeCenter(_x, _y, _bodyImage[getStatus()]->getFrameWidth(), _bodyImage[getStatus()]->getFrameHeight());
}

void brovil::render(void)
{
	if (CAMERAMANAGER->CameraIn(getRC()))
	{
		_bodyImage[getStatus()]->frameRender(getMemDC(), _rc.left - CAMERAMANAGER->getCamera().left, _rc.top - CAMERAMANAGER->getCamera().top,
			_bodyImage[getStatus()]->getFrameX(), _bodyImage[getStatus()]->getFrameY());
		
		// 플레이어 발견했을때, 느낌표 말풍선!
		if (_isAlarm)
		{
			IMAGEMANAGER->frameRender("알람", getMemDC(), _rc.left + 10 - CAMERAMANAGER->getCamera().left, _rc.top - 50 - CAMERAMANAGER->getCamera().top, _warnSign->getFrameX(), _warnSign->getFrameY());
		}

		if (_isAlarm2)
		{
			IMAGEMANAGER->frameRender("의문", getMemDC(), _rc.left + 10 - CAMERAMANAGER->getCamera().left, _rc.top - 50 - CAMERAMANAGER->getCamera().top, _doubtSign->getFrameX(), _doubtSign->getFrameY());
		}
	}

	if (KEYMANAGER->isToggleKey(VK_F4))
	{
		// 에너미 렉트 렌더
		Rectangle(getMemDC(), getX() - getBodyImage()->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, getY() - getBodyImage()->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top,
			getX() + getBodyImage()->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, getY() + getBodyImage()->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top);
	}
	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		// 적 시야 렉트 렌더
		RectangleMake(getMemDC(), _rcSight.left - CAMERAMANAGER->getCamera().left, _rcSight.top - CAMERAMANAGER->getCamera().top, 500, getBodyImage()->getFrameHeight());
	}
}

void brovil::move()
{
	if (!_isOn)
	{
		if (_gravity < 3.0f) _gravity = 3.0f;
		_y += -sinf(_angle) * _speed + _gravity;
		_gravity += 0.5f;
	}
	else
	{
		_gravity = 0;
	}

	//좌우 이동
	if (getStatus() == BROVIL_WALK)
	{
		if (_isLeft)
		{
			setX(getX() - getSpeed());
		}
		else
		{
			setX(getX() + getSpeed());
		}
	}	

	// 적 시야 렉트 변화
	if (_isLeft)
	{
		_rcSight = RectMake(getX() - 500, getY() - _bodyImage[getStatus()]->getFrameHeight() / 2,
			500 + _bodyImage[getStatus()]->getFrameWidth() / 2, _bodyImage[getStatus()]->getFrameHeight());
	}
	else
	{
		_rcSight = RectMake(getX(), getY() - _bodyImage[getStatus()]->getFrameHeight() / 2,
			500 + _bodyImage[getStatus()]->getFrameWidth() / 2, _bodyImage[getStatus()]->getFrameHeight());
	}
}

void brovil::flyAway()
{
	if (_isLeft)
	{
		_angle = PI / 4 * 3;
		_x += cosf(_angle)*15.0f;
		_y += -sinf(_angle)*15.0f + _gravity;
		_gravity += _accel;
	}
	else
	{
		_angle = PI / 4;
		_x += cosf(_angle)*15.0f;
		_y += -sinf(_angle)*15.0f + _gravity;
		_gravity += _accel;
	}
}

void brovil::controlAI(int randomNum)
{
	if (getStatus() != BROVIL_DEAD)
	{
		if (randomNum == 1)
		{
			setStatus(BROVIL_WALK);			
		}
		else if (randomNum == 0)
		{
			setStatus(BROVIL_IDLE);			
		}
		else if (randomNum == 2)
		{
			if (getDirection()) setDirection(false);
			else setDirection(true);
		}
	}
}

void brovil::frameAnimate()
{
	FRAMEMANAGER->frameChange(_bodyImage[getStatus()], _frameCount, _frameIndex, _actionSpeed, _isLeft);
	FRAMEMANAGER->frameChange(_warnSign, _frameCount, _frameIndex2, _actionSpeed, 0);
	FRAMEMANAGER->frameChange(_doubtSign, _frameCount, _frameIndex3, _actionSpeed, 0);
}

void brovil::knockBackMove()
{
	// 넉백됐을때, 뒤로 날라감

	if (_isLeft)
	{
		setX(getX() - _kbSpeed);
		_kbSpeed -= 0.5f;
		if (_kbSpeed < 0)
		{
			_status = BROVIL_DEAD;
		}
	}
	else
	{
		setX(getX() + _kbSpeed);
		_kbSpeed -= 0.5f;
		if (_kbSpeed < 0)
		{
			_status = BROVIL_DEAD;
		}
	}
}
