#include "stdafx.h"
#include "enemy.h"


HRESULT enemy::initSoldier(int x, int y, int hp, int randomNum)
{
	_x = x, _y = y;
	_hp = hp;
	
	_enemyImage.bodyImage[ENEMY_IDLE] = IMAGEMANAGER->findImage("군인평상시");
	_enemyImage.bodyImage[ENEMY_WALK] = IMAGEMANAGER->findImage("군인걸음");
	_enemyImage.bodyImage[ENEMY_DOUBT] = IMAGEMANAGER->findImage("군인의심");
	_enemyImage.bodyImage[ENEMY_FIRE] = IMAGEMANAGER->findImage("군인사격");
	_enemyImage.bodyImage[ENEMY_KNOCK_BACK] = IMAGEMANAGER->findImage("군인넉백");
	_enemyImage.bodyImage[ENEMY_FLY_AWAY] = IMAGEMANAGER->findImage("군인점프");
	_enemyImage.bodyImage[ENEMY_DEAD] = IMAGEMANAGER->findImage("군인시체");

	_enemyImage.armImage[GUN_IDLE] = IMAGEMANAGER->findImage("총평상시");
	_enemyImage.armImage[GUN_TARGETING] = IMAGEMANAGER->findImage("총조준");
	_enemyImage.armImage[GUN_READY] = IMAGEMANAGER->findImage("총발사대기");
	_enemyImage.armImage[GUN_FIRE] = IMAGEMANAGER->findImage("총발사");
	_enemyImage.armImage[GUN_RELOAD] = IMAGEMANAGER->findImage("총장전");

	_enemyImage.count = _enemyImage.index = 0;
	_enemyImage.speed = 10;
				
	_warnSign = IMAGEMANAGER->findImage("알람");
	_doubtSign = IMAGEMANAGER->findImage("의문");
		
	_frameSpeed = 0;
	_count = 0;

	_warnSign->setFrameY(0);
	_doubtSign->setFrameY(0);
		
	_angle = 270.f * 3.14f / 180;
	_speed = 2.f;
	_enemyStatus = ENEMY_IDLE;
	_gunStatus = GUN_IDLE;
	
	_gravity = 0.f;
	
	_randomNumber = randomNum;

	_kbSpeed = 20.f;
	_isAlive = true;
	_isLeft = true;
	_isOn = true;
	_isFire = false;
	_isUncovered = false;
	_isStrange = false;
	_rcEnemy = RectMake(_x, _y, _enemyImage.bodyImage[_enemyStatus]->getFrameWidth(), _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());

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
	// 밑에 없으면 떨어짐
	fall();
	
	// 살아있을때
	if (_isAlive)
	{
		// 적 시야 렉트 변화
		if (_isLeft)
		{
			_rcEnemySight = RectMake(_x - 800, _y, 800, _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());
		}
		else
		{
			_rcEnemySight = RectMake(_x + _enemyImage.bodyImage[_enemyStatus]->getFrameWidth(), _y, 800, _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());
		}

		if (_isUncovered)
		{
			// 플레이어 발견!
			this->discover();
		}

		if (_isStrange)
		{
			// 아군 시체 발견!
			this->doubt();
		}		
	}
	// 죽었을때
	else
	{
		

	}

	// 사격자세를 취한다	
	if (_enemyStatus == ENEMY_FIRE)
	{
		_gunStatus = GUN_TARGETING;
		this->fireMovement();
	}		

	this->move();
	this->frameAnimate();
		
	_rcEnemy = RectMake(_x, _y, _enemyImage.bodyImage[_enemyStatus]->getFrameWidth(), _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());	
}

void enemy::render(void)
{
	if (CAMERAMANAGER->CameraIn(getRcEnemy()))
	{
		//몸통 이미지 렌더
		_enemyImage.bodyImage[_enemyStatus]->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top,
			_enemyImage.bodyImage[_enemyStatus]->getFrameX(), _enemyImage.bodyImage[_enemyStatus]->getFrameY());
		
		//팔 이미지 렌더
		if (_isAlive)
		{
			if (_isLeft)
			{
				_enemyImage.armImage[_gunStatus]->frameRender(getMemDC(), _x - (_enemyImage.armImage[_gunStatus]->getFrameWidth() - _enemyImage.bodyImage[_enemyStatus]->getFrameWidth()) - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top,
					_enemyImage.armImage[_gunStatus]->getFrameX(), _enemyImage.armImage[_gunStatus]->getFrameY());
			}
			else
			{
				_enemyImage.armImage[_gunStatus]->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top,
					_enemyImage.armImage[_gunStatus]->getFrameX(), _enemyImage.armImage[_gunStatus]->getFrameY());
			}
		}

		//_brovilImage.brovilImg[_brovilStatus]->frameRender(getMemDC(), _rcEnemy.left - CAMERAMANAGER->getCamera().left, _rcEnemy.top - CAMERAMANAGER->getCamera().top,
		//	_brovilImage.brovilImg[_brovilStatus]->getFrameX(), _brovilImage.brovilImg[_brovilStatus]->getFrameY());		

		// 플레이어 발견했을때, 느낌표 말풍선!
		if (_isUncovered)
		{
			if (_warnSign->getFrameX() >= _warnSign->getMaxFrameX()) return;
			IMAGEMANAGER->frameRender("알람", getMemDC(), _x + 10 - CAMERAMANAGER->getCamera().left, _y - 50 - CAMERAMANAGER->getCamera().top, _warnSign->getFrameX(), _warnSign->getFrameY());
		}

		if (_isStrange)
		{
			if (_doubtSign->getFrameX() >= _doubtSign->getMaxFrameX()) return;
			IMAGEMANAGER->frameRender("의문", getMemDC(), _x + 10 - CAMERAMANAGER->getCamera().left, _y - 50 - CAMERAMANAGER->getCamera().top, _doubtSign->getFrameX(), _doubtSign->getFrameY());
		}		
	}
	
	if (KEYMANAGER->isToggleKey(VK_F4))
	{
		// 에너미 렉트 렌더
		Rectangle(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top,
			_x + _enemyImage.bodyImage[_enemyStatus]->getFrameWidth() - CAMERAMANAGER->getCamera().left, _y + _enemyImage.bodyImage[_enemyStatus]->getFrameHeight() - CAMERAMANAGER->getCamera().top);
	}

	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		// 적 시야 렉트 렌더
		RectangleMake(getMemDC(), _rcEnemySight.left - CAMERAMANAGER->getCamera().left, _rcEnemySight.top - CAMERAMANAGER->getCamera().top,
			800 + _enemyImage.bodyImage[_enemyStatus]->getFrameWidth(), _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());
	}
	
}

//======================================================================================================================================
//======================================================================================================================================
//======================================================================================================================================

void enemy::fall()
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

void enemy::idle()
{
	if (_enemyStatus == ENEMY_IDLE)
	{
		
	}

}

void enemy::move()
{
	if (_isAlive)
	{		
		//좌우 이동
		if (_enemyStatus == ENEMY_WALK)
		{
			if (_isLeft)
			{
				_x -= _speed;
			}
			else
			{
				_x += _speed;
			}
		}	
	}	
	
	//날라갈때
	if (_enemyStatus == ENEMY_FLY_AWAY)
	{
		flyAway();
	}	
}

// 적 의심 (아군 시체 발견)
void enemy::doubt()
{
	_enemyStatus = ENEMY_DOUBT;
	//아군(적) 시체 발견하고 의심할때,
	if (_enemyStatus == ENEMY_DOUBT)
	{
		_gunStatus = GUN_TARGETING;
		if (_isLeft)
		{
			if (_enemyImage.armImage[_gunStatus]->getFrameX() == 0)
			{
				_gunStatus = GUN_FIRE;
				_enemyStatus = ENEMY_FIRE;
				_enemyImage.bodyImage[_enemyStatus]->setFrameX(4);
			}
		}
		else
		{
			if (_enemyImage.armImage[_gunStatus]->getFrameX() == _enemyImage.armImage[_gunStatus]->getMaxFrameX())
			{
				_gunStatus = GUN_FIRE;
				_enemyStatus = ENEMY_FIRE;
				_enemyImage.bodyImage[_enemyStatus]->setFrameX(4);
			}
		}
	}
}

// 플레이어 발견
void enemy::discover()
{
	_enemyStatus = ENEMY_DOUBT;
	if (!_isLeft)
	{
		if (_enemyImage.bodyImage[ENEMY_DOUBT]->getFrameX() >= _enemyImage.bodyImage[ENEMY_DOUBT]->getMaxFrameX())
		{
			// 사격 모션
			_enemyStatus = ENEMY_FIRE;
		}
	}
	else
	{
		if (_enemyImage.bodyImage[ENEMY_DOUBT]->getFrameX() <= 0)
		{
			// 사격 모션
			_enemyStatus = ENEMY_FIRE;
		}
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

void enemy::fireMovement()
{
	switch (_gunStatus)
	{
		case GUN_TARGETING:
		{
			if (!_isLeft)
			{
				if (_enemyImage.armImage[GUN_TARGETING]->getFrameX() >= _enemyImage.armImage[GUN_TARGETING]->getMaxFrameX())
				{
					_gunStatus = GUN_READY;
					
				}
			}
			else
			{
				if (_enemyImage.armImage[GUN_TARGETING]->getFrameX() == 0)
				{
					_gunStatus = GUN_READY;
					
				}
			}
		}
		case GUN_READY:
		{
			if (!_isLeft)
			{
				if (_enemyImage.armImage[GUN_READY]->getFrameX() >= _enemyImage.armImage[GUN_READY]->getMaxFrameX())
				{
					_gunStatus = GUN_FIRE;
					
				}
			}
			else
			{
				if (_enemyImage.armImage[GUN_READY]->getFrameX() == 0)
				{
					_gunStatus = GUN_FIRE;
					
				}
			}
		}
		case GUN_FIRE:
		{
			if (!_isLeft)
			{
				if (_enemyImage.armImage[GUN_FIRE]->getFrameX() >= _enemyImage.armImage[GUN_FIRE]->getMaxFrameX())
				{
					_isFire = true;
					
				}
			}
			else
			{
				if (_enemyImage.armImage[GUN_FIRE]->getFrameX() == 0)
				{
					_isFire = true;
					
				}
			}
		}

	default:
		break;
	}
}

void enemy::frameAnimate()
{		
	FRAMEMANAGER->frameChange(_enemyImage.bodyImage[_enemyStatus], _enemyImage.count, _enemyImage.index, _enemyImage.speed, _isLeft);

	//FRAMEMANAGER->frameChange(_brovilImage.brovilImg[_brovilStatus], _brovilImage.count, _brovilImage.index, _brovilImage.speed, _isLeft);
	FRAMEMANAGER->frameChange(_enemyImage.armImage[_gunStatus], _enemyImage.count, _enemyImage.index, _enemyImage.speed, _isLeft);
	
	if (_isUncovered)
	FRAMEMANAGER->frameChange(_warnSign, _warnFrameCount, _warnFrameIndex, _frameSpeed, 0);
	
	if (_isStrange)
	FRAMEMANAGER->frameChange(_doubtSign, _doubtFrameCount, _doubtFrameIndex, _frameSpeed, 0);
}

void enemy::knockBackMove(float angle)
{
	// 넉백됐을때, 뒤로 날라감
	
	float tempAngle = 2 * PI - angle;

	if (_isLeft)
	{
		setX(getX() + cosf(tempAngle)*_kbSpeed);
		_kbSpeed -= 0.5f;
		if (_kbSpeed < 0)
		{
			_enemyStatus = ENEMY_DEAD;
			//_brovilStatus = BROVIL_DEAD;
		}
	}
	else
	{
		setX(getX() + cosf(tempAngle)*_kbSpeed);
		_kbSpeed -= 0.5f;
		if (_kbSpeed < 0)
		{
			_enemyStatus = ENEMY_DEAD;
			//_brovilStatus = BROVIL_DEAD;
		}
	}		
}
