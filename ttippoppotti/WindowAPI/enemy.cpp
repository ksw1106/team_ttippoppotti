#include "stdafx.h"
#include "enemy.h"


HRESULT enemy::init(int x, int y, int hp, int randomNum)
{
	_x = x, _y = y;
	_hp = hp;

	_bodyImage[E_IDLE] = IMAGEMANAGER->findImage("군인평상시");
	_bodyImage[E_WALK] = IMAGEMANAGER->findImage("군인걸음");
	_bodyImage[E_DOUBT] = IMAGEMANAGER->findImage("군인의심");
	_bodyImage[E_KNOCK_BACK] = IMAGEMANAGER->findImage("군인넉백");
	_bodyImage[E_FLY_AWAY] = IMAGEMANAGER->findImage("군인점프");
	_bodyImage[E_DEAD] = IMAGEMANAGER->findImage("군인시체");

	_armImage[G_IDLE] = IMAGEMANAGER->findImage("총평상시");
	_armImage[G_TARGETING] = IMAGEMANAGER->findImage("총조준");
	_armImage[G_READY] = IMAGEMANAGER->findImage("총발사대기");
	_armImage[G_FIRE] = IMAGEMANAGER->findImage("총발사");
	_armImage[G_RELOAD] = IMAGEMANAGER->findImage("총장전");
				
	_warnSign = IMAGEMANAGER->findImage("알람");
	_doubtSign = IMAGEMANAGER->findImage("의문");

	_warnSign->setFrameY(0);
	_doubtSign->setFrameY(0);
		
	_angle = 270.f * 3.14f / 180;
	_speed = 3.f;
	setBodyStatus(E_WALK);
	setArmStatus(G_IDLE);
	
	_gravity = 0.f;
	_frameCount = _frameIndex = _frameIndex2 = _frameIndex3 = _frameIndex4 = 0;
	_actionSpeed = 5;

	_randomNumber = randomNum;

	_kbSpeed = 20.f;
	_isLeft = true;
	_isOn = false;
	_isAlarm = false;
	_isAlarm2 = false;
	_enemyRC = RectMakeCenter(_x, _y, _bodyImage[getBodyStatus()]->getFrameWidth(), _bodyImage[getBodyStatus()]->getFrameHeight());

	return S_OK;
}

void enemy::release(void)
{
}

void enemy::update(void)
{	
	//_gravity += _accel;
	if (_warnSign->getFrameX() >= _warnSign->getMaxFrameX())
	{
		_isAlarm = false;
	}
	if (_doubtSign->getFrameX() >= _doubtSign->getMaxFrameX())
	{
		_isAlarm2 = false;
	}

	if (_enemyStatus <= 2 || _gunStatus == 0)
	{
		this->controlAI(RND->getInt(200));
	}
	
	this->move();
	this->frameAnimate();
	
	if (_enemyStatus == E_KNOCK_BACK)
	{
		this->knockBackMove();
	}

	_bodyImage[getBodyStatus()]->setX(getEnemyRC().left);
	_bodyImage[getBodyStatus()]->setY(getEnemyRC().top);
	_armImage[getArmStatus()]->setX(getEnemyRC().left);
	_armImage[getArmStatus()]->setY(getEnemyRC().top);
	
	setEnemyRC(RectMakeCenter(getX(), getY(), _bodyImage[getBodyStatus()]->getFrameWidth(), _bodyImage[getBodyStatus()]->getFrameHeight()));
}

void enemy::render(void)
{
	if (CAMERAMANAGER->CameraIn(getEnemyRC()))
	{
		//몸통 이미지 렌더
		_bodyImage[getBodyStatus()]->frameRender(getMemDC(), _enemyRC.left - CAMERAMANAGER->getCamera().left, _enemyRC.top - CAMERAMANAGER->getCamera().top,
			_bodyImage[getBodyStatus()]->getFrameX(), _bodyImage[getBodyStatus()]->getFrameY());
		
		//팔 이미지 렌더
		if (getBodyStatus() != ( E_DEAD || E_KNOCK_BACK || E_FLY_AWAY ))
		_armImage[getArmStatus()]->frameRender(getMemDC(), _enemyRC.left - CAMERAMANAGER->getCamera().left, _enemyRC.top - CAMERAMANAGER->getCamera().top,
			_armImage[getArmStatus()]->getFrameX(), _armImage[getArmStatus()]->getFrameY());
		
		// 플레이어 발견했을때, 느낌표 말풍선!
		if (_isAlarm)
		{
			IMAGEMANAGER->frameRender("알람", getMemDC(), _enemyRC.left + 10 - CAMERAMANAGER->getCamera().left, _enemyRC.top - 50 - CAMERAMANAGER->getCamera().top, _warnSign->getFrameX(), _warnSign->getFrameY());
		}

		if (_isAlarm2)
		{
			IMAGEMANAGER->frameRender("의문", getMemDC(), _enemyRC.left + 10 - CAMERAMANAGER->getCamera().left, _enemyRC.top - 50 - CAMERAMANAGER->getCamera().top, _doubtSign->getFrameX(), _doubtSign->getFrameY());
		}		
	}
	
	if (KEYMANAGER->isToggleKey(VK_F4))
	{
		// 에너미 렉트 렌더
		Rectangle(getMemDC(), getX() - getBodyImage()->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, getY() - getBodyImage()->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top,
			getX() + getBodyImage()->getFrameWidth()/2 - CAMERAMANAGER->getCamera().left, getY() + getBodyImage()->getFrameHeight()/2 - CAMERAMANAGER->getCamera().top);
	}
	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		// 적 시야 렉트 렌더
		RectangleMake(getMemDC(), _enemySightRC.left - CAMERAMANAGER->getCamera().left, _enemySightRC.top - CAMERAMANAGER->getCamera().top, 500, getBodyImage()->getFrameHeight());
	}
	
}

//======================================================================================================================================
//======================================================================================================================================
//======================================================================================================================================

void enemy::move()
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
	if (getBodyStatus() == E_WALK)
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
	
	//날라갈때
	if (getBodyStatus() == E_FLY_AWAY)
	{
		flyAway();
	}

	if (getBodyStatus() == E_DOUBT)
	{
		_gunStatus = G_TARGETING;
		if (_isLeft)
		{
			if (_armImage[_gunStatus]->getFrameX() == 0)
			{
				_gunStatus = G_FIRE;
				_enemyStatus = E_IDLE;
				_bodyImage[_enemyStatus]->setFrameX(4);
			}
		}
		else
		{
			if (_armImage[_gunStatus]->getFrameX() == _armImage[_gunStatus]->getMaxFrameX())
			{
				_gunStatus = G_FIRE;
				_enemyStatus = E_IDLE;
				_bodyImage[_enemyStatus]->setFrameX(4);
			}
		}	
		
	}

	// 적 시야 렉트 변화
	if (_isLeft)
	{
		_enemySightRC = RectMake(getX() - 500, getY() - _bodyImage[getBodyStatus()]->getFrameHeight() / 2,
			500 + _bodyImage[getBodyStatus()]->getFrameWidth() / 2, _bodyImage[getBodyStatus()]->getFrameHeight());
	}
	else
	{
		_enemySightRC = RectMake(getX(), getY() - _bodyImage[getBodyStatus()]->getFrameHeight() / 2,
			500 + _bodyImage[getBodyStatus()]->getFrameWidth() / 2, _bodyImage[getBodyStatus()]->getFrameHeight());
	}	
}

//날아갈때
void enemy::flyAway()
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

	//_gravity += 0.05f;
}

void enemy::controlAI(int randomNum)
{	
	if (getBodyStatus() != E_DEAD)
	{
		if (randomNum % 7 == 1)
		{
			setBodyStatus(E_WALK);
			setArmStatus(G_IDLE);
		}
		else if (randomNum % 7 == 0)
		{
			setBodyStatus(E_IDLE);
			setArmStatus(G_IDLE);
		}
		else if (randomNum % 7 == 2)
		{
			if (getDirection()) setDirection(false);
			else setDirection(true);
		}
	}	
}

void enemy::frameAnimate()
{
	if (_gunStatus != G_FIRE)
	FRAMEMANAGER->frameChange(_bodyImage[getBodyStatus()], _frameCount, _frameIndex, _actionSpeed, getDirection());
	
	FRAMEMANAGER->frameChange(_armImage[getArmStatus()], _frameCount, _frameIndex2, _actionSpeed, getDirection());
	FRAMEMANAGER->frameChange(_warnSign, _frameCount, _frameIndex3, _actionSpeed, 0);
	FRAMEMANAGER->frameChange(_doubtSign, _frameCount, _frameIndex4, _actionSpeed, 0);
}

void enemy::knockBackMove()
{
	// 넉백됐을때, 뒤로 날라감
	
	if (_isLeft)
	{
		setX(getX() - _kbSpeed);
		_kbSpeed -= 0.5f;
		if (_kbSpeed < 0)
		{
			_enemyStatus = E_DEAD;
		}
	}
	else
	{
		setX(getX() + _kbSpeed);
		_kbSpeed -= 0.5f;
		if (_kbSpeed < 0)
		{
			_enemyStatus = E_DEAD;
		}
	}		
}
