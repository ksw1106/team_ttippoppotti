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

	_warnSign->setFrameX(0);
	_doubtSign->setFrameY(0);
		
	setEnemyAngle(0);
	setSpeed(3.0f);
	setGravity(0.05f);
	setBodyStatus(E_IDLE);
	setArmStatus(G_IDLE);
	_frameCount = _frameIndex = _frameIndex2 = _frameIndex3 = _frameIndex4 = 0;
	_actionSpeed = 5;

	_randomNumber = randomNum;

	_kbSpeed = 20.f;
	_isLeft = true;
	_isAlarm = false;
	_enemyRC = RectMakeCenter(_x, _y, _bodyImage[getBodyStatus()]->getFrameWidth(), _bodyImage[getBodyStatus()]->getFrameHeight());

	return S_OK;
}

void enemy::release(void)
{
}

void enemy::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		setBodyStatus(E_FLY_AWAY);		
	}

	this->controlAI(_randomNumber);
	this->move();
	this->frameAnimate();
	this->knockBackMove();		

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
		_armImage[getArmStatus()]->frameRender(getMemDC(), _enemyRC.left - CAMERAMANAGER->getCamera().left, _enemyRC.top - CAMERAMANAGER->getCamera().top,
			_armImage[getArmStatus()]->getFrameX(), _armImage[getArmStatus()]->getFrameY());
		
		// 플레이어 발견했을때, 느낌표 말풍선!
		if (_isAlarm && _warnSign->getFrameX() <= _warnSign->getMaxFrameX())
		{
			IMAGEMANAGER->frameRender("알람", getMemDC(), _enemyRC.left + 10 - CAMERAMANAGER->getCamera().left, _enemyRC.top - 50 - CAMERAMANAGER->getCamera().top, _warnSign->getFrameX(), _warnSign->getFrameY());
		}
		//if ()
	}
	
	if (KEYMANAGER->isToggleKey(VK_F4))
	{
		Rectangle(getMemDC(), getX() - 30 - CAMERAMANAGER->getCamera().left, getY() - 30 - CAMERAMANAGER->getCamera().top, getX() + 30 - CAMERAMANAGER->getCamera().left, getY() + 30 - CAMERAMANAGER->getCamera().top);

		// 적 시야 렉트 렌더
		RectangleMake(getMemDC(), _enemySightRC.left - CAMERAMANAGER->getCamera().left, _enemySightRC.top - CAMERAMANAGER->getCamera().top, 500, 100);
	}
}

void enemy::move()
{
	//좌우 이동
	if (getBodyStatus() == E_WALK)
	{
		if (_isLeft)
		{
			setX(getX() - getSpeed());
			setY(getY() + _gravity);
		}
		else
		{
			setX(getX() + getSpeed());
			setY(getY() + _gravity);
		}
	}

	//날라갈때
	if (getBodyStatus() == E_FLY_AWAY)
	{
		flyAway();
	}

	// 적 시야 렉트 변화
	if (_isLeft)
	{
		_enemySightRC = RectMake(getX() - 500, getY() - _bodyImage[getBodyStatus()]->getFrameHeight() / 2,
			500 + _bodyImage[getBodyStatus()]->getFrameWidth() / 2, _bodyImage[getBodyStatus()]->getFrameHeight());
	}
	else
	{
		_enemySightRC = RectMake(getX() - _bodyImage[getBodyStatus()]->getFrameWidth() / 2, getY() - _bodyImage[getBodyStatus()]->getFrameHeight() / 2,
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
		_gravity += 1.1f;
	}
	else
	{
		_angle = PI / 4;
		_x += cosf(_angle)*15.0f;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
		_y += -sinf(_angle)*15.0f + _gravity;
		_gravity += 1.1f;
	}
	//_gravity += 0.05f;
}

void enemy::controlAI(int randomNum)
{
	if (randomNum % 2 == 1)
	{
		setBodyStatus(E_WALK);
		setArmStatus(G_TARGETING);
		//setDirection(false);
	}
	else if (randomNum % 2 == 0)
	{
		setBodyStatus(E_IDLE);
		setArmStatus(G_READY);
	}
}

void enemy::frameAnimate()
{
	FRAMEMANAGER->frameChange(_bodyImage[getBodyStatus()], _frameCount, _frameIndex, _actionSpeed, getDirection());
	FRAMEMANAGER->frameChange(_armImage[getArmStatus()], _frameCount, _frameIndex2, _actionSpeed, getDirection());
	FRAMEMANAGER->frameChange(_warnSign, _frameCount, _frameIndex3, _actionSpeed, getDirection());
	FRAMEMANAGER->frameChange(_doubtSign, _frameCount, _frameIndex4, _actionSpeed, getDirection());
}

void enemy::knockBackMove()
{
	// 넉백됐을때, 뒤로 날라감
	if (_enemyStatus == E_KNOCK_BACK)
	{
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
}
