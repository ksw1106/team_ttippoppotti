#include "stdafx.h"
#include "enemy.h"


HRESULT enemy::initSoldier(int x, int y, int hp, int randomNum)
{
	_x = x, _y = y;
	_hp = hp;
	
	_enemyImage.bodyImage[ENEMY_IDLE] = IMAGEMANAGER->findImage("군인평상시");
	_enemyImage.bodyImage[ENEMY_WALK] = IMAGEMANAGER->findImage("군인걸음");
	_enemyImage.bodyImage[ENEMY_DOUBT] = IMAGEMANAGER->findImage("군인의심");
	_enemyImage.bodyImage[ENEMY_KNOCK_BACK] = IMAGEMANAGER->findImage("군인넉백");
	_enemyImage.bodyImage[ENEMY_FLY_AWAY] = IMAGEMANAGER->findImage("군인점프");
	_enemyImage.bodyImage[ENEMY_DEAD] = IMAGEMANAGER->findImage("군인시체");

	_enemyImage.armImage[GUN_IDLE] = IMAGEMANAGER->findImage("총평상시");
	_enemyImage.armImage[GUN_TARGETING] = IMAGEMANAGER->findImage("총조준");
	_enemyImage.armImage[GUN_READY] = IMAGEMANAGER->findImage("총발사대기");
	_enemyImage.armImage[GUN_FIRE] = IMAGEMANAGER->findImage("총발사");
	_enemyImage.armImage[GUN_RELOAD] = IMAGEMANAGER->findImage("총장전");

	_enemyImage.count = _enemyImage.index = 0;
	_enemyImage.speed = 5;
				
	_warnSign = IMAGEMANAGER->findImage("알람");
	_doubtSign = IMAGEMANAGER->findImage("의문");

	_warnFrameCount = _doubtFrameCount = 0;
	_warnFrameIndex = _doubtFrameCount = 0;
	_frameSpeed = 0;

	_warnSign->setFrameY(0);
	_doubtSign->setFrameY(0);
		
	_angle = 270.f * 3.14f / 180;
	_speed = 3.f;
	_enemyStatus = ENEMY_WALK;
	_gunStatus = GUN_IDLE;
	
	_gravity = 0.f;
	
	_randomNumber = randomNum;

	_kbSpeed = 20.f;
	_isLeft = true;
	_isOn = false;
	_isUncovered = false;
	_isStrange = false;
	_rcEnemy = RectMakeCenter(_x, _y, _enemyImage.bodyImage[_enemyStatus]->getFrameWidth(), _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());

	return S_OK;
}

//HRESULT enemy::initBrovil(int x, int y, int hp, int randomNum)
//{
//	_x = x, _y = y;
//	_hp = 100;
//
//	_brovilImage.brovilImg[BROVIL_IDLE] = IMAGEMANAGER->findImage("브로빌평상시");
//	_brovilImage.brovilImg[BROVIL_WALK] = IMAGEMANAGER->findImage("브로빌걸음");
//	_brovilImage.brovilImg[BROVIL_KNOCK_BACK] = IMAGEMANAGER->findImage("브로빌넉백");
//	_brovilImage.brovilImg[BROVIL_DEAD] = IMAGEMANAGER->findImage("브로빌시체");
//	_brovilImage.brovilImg[BROVIL_DISAPPEAR] = IMAGEMANAGER->findImage("브로빌승화");
//
//	_brovilImage.count = _brovilImage.index = 0;
//	_brovilImage.speed = 5;
//
//	_warnSign = IMAGEMANAGER->findImage("알람");
//	_doubtSign = IMAGEMANAGER->findImage("의문");
//
//	_warnFrameCount = _doubtFrameCount = 0;
//	_warnFrameIndex = _doubtFrameCount = 0;
//	_frameSpeed = 0;
//
//	_warnSign->setFrameY(0);
//	_doubtSign->setFrameY(0);
//
//	_angle = 270.f * 3.14f / 180;
//	_speed = 2.f;
//	_gravity = 0.f;
//	_kbSpeed = 20.f;
//	setBrovilStatus(BROVIL_IDLE);
//
//	_randomNumber = randomNum;
//	
//	_isLeft = true;
//	_isOn = false;
//	_isUncovered = false;
//	_isStrange = false;
//	_rcEnemy = RectMakeCenter(_x, _y, _brovilImage.brovilImg[getBrovilStatus()]->getFrameWidth(), _brovilImage.brovilImg[getBrovilStatus()]->getFrameHeight());
//		
//	return S_OK;
//}

void enemy::release(void)
{
}

void enemy::update(void)
{	
	//_gravity += _accel;
	if (_warnSign->getFrameX() >= _warnSign->getMaxFrameX())
	{
		_isUncovered = false;
	}
	if (_doubtSign->getFrameX() >= _doubtSign->getMaxFrameX())
	{
		_isStrange = false;
	}

	if (_enemyStatus <= 2 || _gunStatus == 0)
	{
		this->controlAI(RND->getInt(200));
	}
	//if (_brovilStatus <= 2)
	//{
	//	this->controlAI(RND->getInt(200));
	//}
	
	this->move();
	this->frameAnimate();
	
	if (_enemyStatus == ENEMY_KNOCK_BACK || _brovilStatus == BROVIL_KNOCK_BACK)
	{
		this->knockBackMove();
	}

	_enemyImage.bodyImage[getBodyStatus()]->setX(getRcEnemy().left);
	_enemyImage.bodyImage[getBodyStatus()]->setY(getRcEnemy().top);
	_enemyImage.armImage[getArmStatus()]->setX(getRcEnemy().left);
	_enemyImage.armImage[getArmStatus()]->setY(getRcEnemy().top);
	
	setRcEnemy(RectMakeCenter(getX(), getY(), _enemyImage.bodyImage[getBodyStatus()]->getFrameWidth(), _enemyImage.bodyImage[getBodyStatus()]->getFrameHeight()));
}

void enemy::render(void)
{
	if (CAMERAMANAGER->CameraIn(getRcEnemy()))
	{
		//몸통 이미지 렌더
		_enemyImage.bodyImage[getBodyStatus()]->frameRender(getMemDC(), _rcEnemy.left - CAMERAMANAGER->getCamera().left, _rcEnemy.top - CAMERAMANAGER->getCamera().top,
			_enemyImage.bodyImage[getBodyStatus()]->getFrameX(), _enemyImage.bodyImage[getBodyStatus()]->getFrameY());
		
		//팔 이미지 렌더
		if (getBodyStatus() != ( ENEMY_DEAD || ENEMY_KNOCK_BACK || ENEMY_FLY_AWAY ))
		_enemyImage.armImage[getArmStatus()]->frameRender(getMemDC(), _rcEnemy.left - CAMERAMANAGER->getCamera().left, _rcEnemy.top - CAMERAMANAGER->getCamera().top,
			_enemyImage.armImage[getArmStatus()]->getFrameX(), _enemyImage.armImage[getArmStatus()]->getFrameY());

		//_brovilImage.brovilImg[_brovilStatus]->frameRender(getMemDC(), _rcEnemy.left - CAMERAMANAGER->getCamera().left, _rcEnemy.top - CAMERAMANAGER->getCamera().top,
		//	_brovilImage.brovilImg[_brovilStatus]->getFrameX(), _brovilImage.brovilImg[_brovilStatus]->getFrameY());
		
		// 플레이어 발견했을때, 느낌표 말풍선!
		if (_isUncovered)
		{
			IMAGEMANAGER->frameRender("알람", getMemDC(), _rcEnemy.left + 10 - CAMERAMANAGER->getCamera().left, _rcEnemy.top - 50 - CAMERAMANAGER->getCamera().top, _warnSign->getFrameX(), _warnSign->getFrameY());
		}

		if (_isStrange)
		{
			IMAGEMANAGER->frameRender("의문", getMemDC(), _rcEnemy.left + 10 - CAMERAMANAGER->getCamera().left, _rcEnemy.top - 50 - CAMERAMANAGER->getCamera().top, _doubtSign->getFrameX(), _doubtSign->getFrameY());
		}		
	}
	
	if (KEYMANAGER->isToggleKey(VK_F4))
	{
		// 에너미 렉트 렌더
		Rectangle(getMemDC(), getX() - _enemyImage.bodyImage[getBodyStatus()]->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, getY() - _enemyImage.bodyImage[getBodyStatus()]->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top,
			getX() + _enemyImage.bodyImage[getBodyStatus()]->getFrameWidth()/2 - CAMERAMANAGER->getCamera().left, getY() + _enemyImage.bodyImage[getBodyStatus()]->getFrameHeight()/2 - CAMERAMANAGER->getCamera().top);
	}

	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		// 적 시야 렉트 렌더
		RectangleMake(getMemDC(), _rcEnemySight.left - CAMERAMANAGER->getCamera().left, _rcEnemySight.top - CAMERAMANAGER->getCamera().top, 500, _enemyImage.bodyImage[getBodyStatus()]->getFrameHeight());
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
	if (getBodyStatus() == ENEMY_WALK)
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
	if (getBodyStatus() == ENEMY_FLY_AWAY)
	{
		flyAway();
	}

	if (getBodyStatus() == ENEMY_DOUBT)
	{
		_gunStatus = GUN_TARGETING;
		if (_isLeft)
		{
			if (_enemyImage.armImage[getArmStatus()]->getFrameX() == 0)
			{
				_gunStatus = GUN_FIRE;
				_enemyStatus = ENEMY_IDLE;
				_enemyImage.bodyImage[getArmStatus()]->setFrameX(4);
			}
		}
		else
		{
			if (_enemyImage.armImage[getArmStatus()]->getFrameX() == _enemyImage.armImage[getArmStatus()]->getMaxFrameX())
			{
				_gunStatus = GUN_FIRE;
				_enemyStatus = ENEMY_IDLE;
				_enemyImage.bodyImage[getBodyStatus()]->setFrameX(4);
			}
		}	
		
	}

	// 적 시야 렉트 변화
	if (_isLeft)
	{
		_rcEnemySight = RectMake(getX() - 500, getY() - _enemyImage.bodyImage[getBodyStatus()]->getFrameHeight() / 2,
			500 + _enemyImage.bodyImage[getBodyStatus()]->getFrameWidth() / 2, _enemyImage.bodyImage[getBodyStatus()]->getFrameHeight());
	}
	else
	{
		_rcEnemySight = RectMake(getX(), getY() - _enemyImage.bodyImage[getBodyStatus()]->getFrameHeight() / 2,
			500 + _enemyImage.bodyImage[getBodyStatus()]->getFrameWidth() / 2, _enemyImage.bodyImage[getBodyStatus()]->getFrameHeight());
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
	if (getBodyStatus() != ENEMY_DEAD)
	{
		if (randomNum % 7 == 1)
		{
			setBodyStatus(ENEMY_WALK);
			setArmStatus(GUN_IDLE);
		}
		else if (randomNum % 7 == 0)
		{
			setBodyStatus(ENEMY_IDLE);
			setArmStatus(GUN_IDLE);
		}
		else if (randomNum % 7 == 2)
		{
			if (getDirection()) setDirection(false);
			else setDirection(true);
		}
	}

	//if (getBrovilStatus() != BROVIL_DEAD)
	//{
	//	if (randomNum % 7 == 1)
	//	{
	//		setBrovilStatus(BROVIL_WALK);			
	//	}
	//	else if (randomNum % 7 == 0)
	//	{
	//		setBrovilStatus(BROVIL_IDLE);			
	//	}
	//	else if (randomNum % 7 == 2)
	//	{
	//		if (_isLeft) _isLeft = false;
	//		else _isLeft = true;
	//	}
	//}
}

void enemy::frameAnimate()
{
	if (_gunStatus != GUN_FIRE)
	{
		FRAMEMANAGER->frameChange(_enemyImage.bodyImage[getBodyStatus()], _enemyImage.count, _enemyImage.index, _enemyImage.speed, _isLeft);
	}	
	//FRAMEMANAGER->frameChange(_brovilImage.brovilImg[_brovilStatus], _brovilImage.count, _brovilImage.index, _brovilImage.speed, _isLeft);
	FRAMEMANAGER->frameChange(_enemyImage.armImage[getArmStatus()], _enemyImage.count, _enemyImage.index, _enemyImage.speed, _isLeft);
	FRAMEMANAGER->frameChange(_warnSign, _warnFrameCount, _warnFrameIndex, _frameSpeed, 0);
	FRAMEMANAGER->frameChange(_doubtSign, _doubtFrameCount, _doubtFrameIndex, _frameSpeed, 0);
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
			_enemyStatus = ENEMY_DEAD;
			//_brovilStatus = BROVIL_DEAD;
		}
	}
	else
	{
		setX(getX() + _kbSpeed);
		_kbSpeed -= 0.5f;
		if (_kbSpeed < 0)
		{
			_enemyStatus = ENEMY_DEAD;
			//_brovilStatus = BROVIL_DEAD;
		}
	}		
}
