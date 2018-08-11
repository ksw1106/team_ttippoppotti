#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::initSoldier(float x, float y)
{
	_x = x, _y = y;
	_hp = 10;
			
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
	_fireCount = 0;		// 사격애니메이션용 카운트
			
	this->corpseInit();	
	
	_angle = 0;
	_speed = 5.f;
	_enemyStatus = ENEMY_IDLE;
	_gunStatus = GUN_IDLE;
	
	_gravity = 0.f;
	
	_accel = 0.8f;
	_kbSpeed = 20.f;
	_kbIndex = 0;
	_isAlive = true;
	_isLeft = true;
	_isOn = true;
	_isFire = false;
	_isUncovered = false;
	_isStrange = false;
	_isApart = false;
	_rcEnemy = RectMake(_x, _y, _enemyImage.bodyImage[_enemyStatus]->getFrameWidth(), _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());
	
	return S_OK;
}

void enemy::release(void)
{
	_warnSign->release();
	SAFE_DELETE(_warnSign);
	_doubtSign->release();
	SAFE_DELETE(_doubtSign);
	for (int i = 0; i < 4; ++i)
	{
		_corpse[i].corpseImage->release();
		SAFE_DELETE(_corpse[i].corpseImage);
	}	
}

void enemy::update(void)
{			
	// 에너미 움직임 변화
	this->changeStatus();
	// 밑에 없으면 떨어짐
	this->fall();
	// 에이아이 움직임 랜덤조절
	this->controlAI();
	// 프레임 애니메이션
	this->frameAnimate();
	
	++_fireCount;
	if (_fireCount > 1000) _fireCount = 0;
		
	if (_isUncovered)
	{
		if (_enemyStatus != ENEMY_DOUBT && _enemyStatus != ENEMY_FIRE)
		_enemyStatus = ENEMY_DOUBT;
	}
	else if (_isStrange)
	{
		_enemyStatus = ENEMY_DOUBT;
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
			
	_rcEnemy = RectMake(_x, _y, _enemyImage.bodyImage[_enemyStatus]->getFrameWidth(), _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());
	
	// 시체상태가 아닐때, 렉트 움직임
	for (int i = 0; i < BODY_PART; ++i)
	{
		if (!_isApart)
		{
			_corpse[i].x = _x;
			_corpse[i].y = _y;
			_corpse[i].rcCorpse = RectMake(_corpse[i].x, _corpse[i].y, _corpse[i].corpseImage->getWidth(), _corpse[i].corpseImage->getHeight());
		}
	}
	
	//if (_isLeft) _angle = PI;
	//else _angle = 0.f;
		
}

void enemy::render(void)
{
	if (CAMERAMANAGER->CameraIn(getRcEnemy()))
	{		
		//몸통 이미지 렌더
		if (!_isApart)	// 분해되지 않았을때
		{
			_enemyImage.bodyImage[_enemyStatus]->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top,
				_enemyImage.bodyImage[_enemyStatus]->getFrameX(), _enemyImage.bodyImage[_enemyStatus]->getFrameY());
		}
		// 시체 렌더
		else
		{
			for (int i = 0; i < BODY_PART; ++i)
			{
				_corpse[i].corpseImage->rotateRender(getMemDC(), _corpse[i].x - CAMERAMANAGER->getCamera().left, _corpse[i].y - CAMERAMANAGER->getCamera().top, _corpse[i].angle);
			}
		}

		//팔 이미지 렌더
		if (_isAlive)
		{
			if (_isLeft)
			{
				_enemyImage.armImage[_gunStatus]->frameRender(getMemDC(), _x - (_enemyImage.armImage[_gunStatus]->getFrameWidth() - _enemyImage.bodyImage[_enemyStatus]->getFrameWidth()) - CAMERAMANAGER->getCamera().left,
					_y - CAMERAMANAGER->getCamera().top, _enemyImage.armImage[_gunStatus]->getFrameX(), _enemyImage.armImage[_gunStatus]->getFrameY());
			}
			else
			{
				_enemyImage.armImage[_gunStatus]->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top,
					_enemyImage.armImage[_gunStatus]->getFrameX(), _enemyImage.armImage[_gunStatus]->getFrameY());
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
			_x + _enemyImage.bodyImage[_enemyStatus]->getFrameWidth() - CAMERAMANAGER->getCamera().left, _y + _enemyImage.bodyImage[_enemyStatus]->getFrameHeight() - CAMERAMANAGER->getCamera().top);
	}

	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		// 적 시야 렉트 렌더
		RectangleMake(getMemDC(), _rcEnemySight.left - CAMERAMANAGER->getCamera().left, _rcEnemySight.top - CAMERAMANAGER->getCamera().top,
			800 + _enemyImage.bodyImage[_enemyStatus]->getFrameWidth(), _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());
	}	
}

//===========================================================================================================================================================================================================
//===========================================================================================================================================================================================================
//===========================================================================================================================================================================================================

void enemy::walk()
{	
	if (_isLeft)
	{
		_x -= _speed/2;
	}
	else
	{
		_x += _speed/2;
	}
}

void enemy::controlAI()
{
	if (!_isAlive || _isUncovered || _isStrange || _isApart)
	{

	}
	else
	{
		++_count;
		if (_count % 30 == 0)
		{
			_phase = RND->getFromIntTo(0, 2);
			_direction = RND->getFromIntTo(0,1);
			if (_direction == 1)
			{
				_isLeft = true;
			}
			else
			{
				_isLeft = false;
			}
		}
		
		switch (_phase)
		{
			case 0:
			{
				_enemyStatus = ENEMY_IDLE;
				break;
			}
			case 1:
			{
				_enemyStatus = ENEMY_IDLE;
				break;
			}
			case 2:
			{
				_enemyStatus = ENEMY_WALK;
				break;
			}
		default:
			break;
		}
	}

	if (_count >= 500) _count = 0;	
}

// 에너미 움직임 변화
void enemy::changeStatus()
{
	switch (_enemyStatus)
	{
	case ENEMY_IDLE:
	{

		break;
	}
	case ENEMY_WALK:
	{
		if (_isAlive)
		{
			walk();
			break;
		}
		else
		{
			this->deadMove();
			break;
		}
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
		this->enemyExplode();
		break;
	}

	default:
		break;
	}
}

// 시체 초기화
void enemy::corpseInit()
{
	for (int i = 0; i < BODY_PART; ++i)
	{		
		if (_isLeft)
		{
			_corpse[i].angle = RND->getFromFloatTo(PI/2 + 0.2f, PI - 0.2f);
		}
		else
		{
			_corpse[i].angle = RND->getFromFloatTo(0.2f, PI / 2 - 0.2f);
		}
		_corpse[i].speed = RND->getFromFloatTo(6.f, 9.f);
		_corpse[i].gravity = 0.0f;
		_corpse[i].corpseImage = new image;
	}
	_corpse[0].corpseImage->init("enemyImage/soldier_part_head.bmp", 20, 28, true, RGB(255, 0, 255));
	_corpse[1].corpseImage->init("enemyImage/soldier_part_body.bmp", 40, 40, true, RGB(255, 0, 255));
	_corpse[2].corpseImage->init("enemyImage/soldier_part_arm.bmp", 12, 28, true, RGB(255, 0, 255));
	_corpse[3].corpseImage->init("enemyImage/soldier_part_leg.bmp", 16, 16, true, RGB(255, 0, 255));
}

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

void enemy::deadMove()
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

// 적 의심 (아군 시체 발견)
void enemy::doubt()
{
	
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
		_enemyStatus = ENEMY_DEAD;		
	}		
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
	else if (_enemyStatus == ENEMY_FLY_AWAY)
	{
		_enemyImage.speed = 3;
		FRAMEMANAGER->frameChange(_enemyImage.bodyImage[ENEMY_FLY_AWAY], _enemyImage.count, _enemyImage.bodyImageIndex, _enemyImage.speed, _isLeft);
	}
	else
	{
		_enemyImage.speed = 8;
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
			_angle = PI - 0.4f;
		}
		else
		{		
			_angle = 0.4f;
		}	
		_x += cosf(_angle)*_kbSpeed;
		_y += -sinf(_angle)*_kbSpeed;
		_kbSpeed -= 0.5f;
	}
}

// 피가 다 닳았을때 시체 분해됨 ㅋ
void enemy::enemyExplode()
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

void enemy::partMove()
{
	for (int i = 0; i < 4; ++i)
	{				
		_corpse[i].x += cosf(_corpse[i].angle) * _corpse[i].speed;
		_corpse[i].y += - sinf(_corpse[i].angle) * _corpse[i].speed + _corpse[i].gravity;
		_corpse[i].gravity += 0.4f;
		_corpse[i].speed -= 0.2f;	
		_corpse[i].rcCorpse = RectMake(_corpse[i].x, _corpse[i].y, _corpse[i].corpseImage->getWidth(), _corpse[i].corpseImage->getHeight());

		if (_corpse[i].speed <= 0.f) _corpse[i].speed = 0;
	}
}

