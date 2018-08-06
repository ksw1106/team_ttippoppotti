#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::initSoldier(int x, int y)
{
	_x = x, _y = y;
			
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

	_enemyImage.bodyImageIndex = 0;
	_enemyImage.armImageIndex = 0;
	
	_enemyImage.count = 3;
	_enemyImage.speed = 10;
	
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
		
	_frameSpeed = 5;
	_count = 0;

	_warnSign->setFrameY(0);
	_doubtSign->setFrameY(0);
		
	_angle = 270.f * 3.14f / 180;
	_speed = 3.f;
	_enemyStatus = ENEMY_IDLE;
	_gunStatus = GUN_IDLE;
	
	_gravity = 0.f;
	
	_kbSpeed = 20.f;
	_kbIndex = 0;
	_isAlive = true;
	_isLeft = true;
	_isOn = true;
	_isFire = false;
	_isUncovered = false;
	_isStrange = false;
	_rcEnemy = RectMake(_x, _y, _enemyImage.bodyImage[_enemyStatus]->getFrameWidth(), _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());

	return S_OK;
}

void enemy::release(void)
{
	_warnSign->release();
	SAFE_DELETE(_warnSign);
	_doubtSign->release();
	SAFE_DELETE(_doubtSign);
	
}

void enemy::update(void)
{	
		
	// 밑에 없으면 떨어짐
	fall();	

	if (_isUncovered)
	{
		if (_enemyStatus != ENEMY_DOUBT && _enemyStatus != ENEMY_FIRE)
		_enemyStatus = ENEMY_DOUBT;
	}
	else if (_isStrange)
	{
		_enemyStatus = ENEMY_DOUBT;
	}

	switch (_enemyStatus)
	{
		case ENEMY_IDLE:
		{

			break;
		}
		case ENEMY_WALK:
		{
			this->move();
			break;
		}
		case ENEMY_DOUBT:
		{
			// 플레이어 발견!
			this->discover();
				
			// 아군 시체 발견
			this->doubt();
			
			break;
		}
		case ENEMY_FIRE:
		{
			//if (_isFire) break;
			this->fireMovement();
			break;
		}
		case ENEMY_KNOCK_BACK:
		{
			_isAlive = false;
			this->knockBackMove(_isLeft);
			break;
		}
		case ENEMY_FLY_AWAY:
		{
			_isAlive = false;
			this->flyAway();
			break;
		}
		case ENEMY_DEAD:
		{
			_isAlive = false;
			break;
		}

		default:
			break;
	}

	// 적 시야 렉트 변화
	if (_isLeft)
	{
		_rcEnemySight = RectMake(_x - 800, _y, 800, _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());
	}
	else
	{
		_rcEnemySight = RectMake(_x + _enemyImage.bodyImage[_enemyStatus]->getFrameWidth(), _y, 800, _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());
	}
			
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
	
}

void enemy::move()
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

// 적 의심 (아군 시체 발견)
void enemy::doubt()
{
	//_enemyStatus = ENEMY_DOUBT;
	////아군(적) 시체 발견하고 의심할때,
	//if (_enemyStatus == ENEMY_DOUBT)
	//{
	//	_gunStatus = GUN_TARGETING;
	//	if (_isLeft)
	//	{
	//		if (_enemyImage.armImage[_gunStatus]->getFrameX() == 0)
	//		{
	//			_gunStatus = GUN_FIRE;
	//			_enemyStatus = ENEMY_FIRE;
	//			_enemyImage.bodyImage[_enemyStatus]->setFrameX(4);
	//		}
	//	}
	//	else
	//	{
	//		if (_enemyImage.armImage[_gunStatus]->getFrameX() == _enemyImage.armImage[_gunStatus]->getMaxFrameX())
	//		{
	//			_gunStatus = GUN_FIRE;
	//			_enemyStatus = ENEMY_FIRE;
	//			_enemyImage.bodyImage[_enemyStatus]->setFrameX(4);
	//		}
	//	}
	//}
}

// 플레이어 발견
void enemy::discover()
{
	//_enemyStatus = ENEMY_DOUBT;

	if (_isLeft)
	{		
		if (_enemyImage.bodyImageIndex <= 0)
		{
			// 사격 모션
			_enemyStatus = ENEMY_FIRE;
		}
	}
	else
	{		
		if (_enemyImage.bodyImageIndex >= _enemyImage.bodyImage[ENEMY_DOUBT]->getMaxFrameX())
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

// 발사시 에너미 프레임 움직임
void enemy::fireMovement()
{			

	if (_gunStatus != GUN_TARGETING && _gunStatus != GUN_READY && _gunStatus != GUN_FIRE)
	{
		_gunStatus = GUN_TARGETING;

		if (_isLeft)
			_enemyImage.armImageIndex = _enemyImage.armImage[GUN_TARGETING]->getMaxFrameX();
		else
			_enemyImage.armImageIndex = 0;
	}	
	
	if (_isLeft)
	{	

		if (_gunStatus == GUN_TARGETING && _enemyImage.armImageIndex <= 0)
		{
			_gunStatus = GUN_READY;
			_enemyImage.armImageIndex = _enemyImage.armImage[GUN_READY]->getMaxFrameX();			
		}
		else if (_gunStatus == GUN_READY && _enemyImage.armImageIndex <= 0) 
		{
			_gunStatus = GUN_FIRE;
			_enemyImage.armImageIndex = _enemyImage.armImage[GUN_FIRE]->getMaxFrameX();			
		}
		else if (_gunStatus == GUN_FIRE && _enemyImage.armImageIndex <= 0)
		{
			_isFire = true;
		}
		else _isFire = false;
	}

	else
	{		

		if (_gunStatus == GUN_TARGETING && _enemyImage.armImageIndex >= _enemyImage.armImage[GUN_TARGETING]->getMaxFrameX())
		{
			_gunStatus = GUN_READY;
			_enemyImage.armImageIndex = 0;			
		}
		else if (_gunStatus == GUN_READY && _enemyImage.armImageIndex >= _enemyImage.armImage[GUN_READY]->getMaxFrameX())
		{
			_gunStatus = GUN_FIRE;
			_enemyImage.armImageIndex = 0;			
		}
		else if (_gunStatus == GUN_FIRE && _enemyImage.armImageIndex >= _enemyImage.armImage[GUN_FIRE]->getMaxFrameX())
		{			
			_isFire = true;
		}
		else _isFire = false;
	}
	
}

// 프레임 애니메이션
void enemy::frameAnimate()
{		
	if (_enemyStatus == ENEMY_KNOCK_BACK )
	{		
		_enemyImage.speed = 2;

		if (_isLeft)
		{				
			if (_enemyImage.bodyImageIndex <= 0)
			{
				_enemyStatus = ENEMY_DEAD;
			}
		}
		else
		{			
			if (_enemyImage.bodyImageIndex >= _enemyImage.bodyImage[ENEMY_KNOCK_BACK]->getMaxFrameX())
			{
				_enemyStatus = ENEMY_DEAD;
			}

		}
		
		FRAMEMANAGER->frameChange(_enemyImage.bodyImage[_enemyStatus], _enemyImage.count, _enemyImage.bodyImageIndex, _enemyImage.speed, _isLeft);
	}
	else if (_enemyStatus == ENEMY_DEAD)
	{		
		FRAMEMANAGER->frameChange(_enemyImage.bodyImage[ENEMY_DEAD], _enemyImage.count, _enemyImage.bodyImageIndex, _enemyImage.speed, _isLeft);
	}	
	else
	{
		_enemyImage.speed = 10;
		FRAMEMANAGER->frameChange(_enemyImage.bodyImage[_enemyStatus], _enemyImage.count, _enemyImage.bodyImageIndex, _enemyImage.speed, _isLeft);
		FRAMEMANAGER->frameChange(_enemyImage.armImage[_gunStatus], _enemyImage.count, _enemyImage.armImageIndex, _enemyImage.speed, _isLeft);
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

void enemy::knockBackMove(bool isLeft)
{
	// 넉백됐을때, 뒤로 날라감
	
	if (_kbSpeed > 0)
	{
		if (isLeft)
		{		
			_x -= _kbSpeed;			
		}
		else
		{		
			_x += _kbSpeed;
		}	
		_kbSpeed -= 1.0f;
	}
}

void enemy::dead()
{	
	
}

