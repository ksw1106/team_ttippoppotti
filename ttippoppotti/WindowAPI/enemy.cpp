#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::initSoldier(float x, float y)
{
	_x = x, _y = y;
	_hp = 10;
			
	_enemyImage.bodyImage[ENEMY_IDLE] = IMAGEMANAGER->findImage("��������");
	_enemyImage.bodyImage[ENEMY_WALK] = IMAGEMANAGER->findImage("���ΰ���");
	_enemyImage.bodyImage[ENEMY_DOUBT] = IMAGEMANAGER->findImage("�����ǽ�");
	_enemyImage.bodyImage[ENEMY_FIRE] = IMAGEMANAGER->findImage("���λ��");
	_enemyImage.bodyImage[ENEMY_KNOCK_BACK] = IMAGEMANAGER->findImage("���γ˹�");
	_enemyImage.bodyImage[ENEMY_FLY_AWAY] = IMAGEMANAGER->findImage("��������");
	_enemyImage.bodyImage[ENEMY_DEAD] = IMAGEMANAGER->findImage("���ν�ü");

	_enemyImage.armImage[GUN_IDLE] = IMAGEMANAGER->findImage("������");
	_enemyImage.armImage[GUN_TARGETING] = IMAGEMANAGER->findImage("������");
	_enemyImage.armImage[GUN_READY] = IMAGEMANAGER->findImage("�ѹ߻���");
	_enemyImage.armImage[GUN_FIRE] = IMAGEMANAGER->findImage("�ѹ߻�");
	_enemyImage.armImage[GUN_RELOAD] = IMAGEMANAGER->findImage("������");
		
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
	_fireCount = 0;		// ��ݾִϸ��̼ǿ� ī��Ʈ
			
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
	// ���ʹ� ������ ��ȭ
	this->changeStatus();
	// �ؿ� ������ ������
	this->fall();
	// ���̾��� ������ ��������
	this->controlAI();
	// ������ �ִϸ��̼�
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

	// �� �þ� ��Ʈ ��ȭ
	if (_isLeft)
	{
		_rcEnemySight = RectMake(_x - 800, _y, 800, _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());
	}
	else
	{
		_rcEnemySight = RectMake(_x + _enemyImage.bodyImage[_enemyStatus]->getFrameWidth(), _y, 800, _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());
	}			
			
	_rcEnemy = RectMake(_x, _y, _enemyImage.bodyImage[_enemyStatus]->getFrameWidth(), _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());
	
	// ��ü���°� �ƴҶ�, ��Ʈ ������
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
		//���� �̹��� ����
		if (!_isApart)	// ���ص��� �ʾ�����
		{
			_enemyImage.bodyImage[_enemyStatus]->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top,
				_enemyImage.bodyImage[_enemyStatus]->getFrameX(), _enemyImage.bodyImage[_enemyStatus]->getFrameY());
		}
		// ��ü ����
		else
		{
			for (int i = 0; i < BODY_PART; ++i)
			{
				_corpse[i].corpseImage->rotateRender(getMemDC(), _corpse[i].x - CAMERAMANAGER->getCamera().left, _corpse[i].y - CAMERAMANAGER->getCamera().top, _corpse[i].angle);
			}
		}

		//�� �̹��� ����
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
		
		// �÷��̾� �߰�������, ����ǥ ��ǳ��!
		if (_isUncovered && _warnFrameIndex < _warnSign->getMaxFrameX())
		{
			_warnSign->frameRender(getMemDC(), _x + 10 - CAMERAMANAGER->getCamera().left, _y - 50 - CAMERAMANAGER->getCamera().top, _warnSign->getFrameX(), _warnSign->getFrameY());
		}

		// �� (�Ʊ�) ��ü�� �߰������� ����ǥ ��ǳ��!
		if (_isStrange && _doubtFrameIndex < _doubtSign->getMaxFrameX())
		{
			_doubtSign->frameRender(getMemDC(), _x + 10 - CAMERAMANAGER->getCamera().left, _y - 50 - CAMERAMANAGER->getCamera().top, _doubtSign->getFrameX(), _doubtSign->getFrameY());
		}		
	}

	if (KEYMANAGER->isToggleKey(VK_F4))
	{
		// ���ʹ� ��Ʈ ����
		Rectangle(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top,
			_x + _enemyImage.bodyImage[_enemyStatus]->getFrameWidth() - CAMERAMANAGER->getCamera().left, _y + _enemyImage.bodyImage[_enemyStatus]->getFrameHeight() - CAMERAMANAGER->getCamera().top);
	}

	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		// �� �þ� ��Ʈ ����
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

// ���ʹ� ������ ��ȭ
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
		// �÷��̾� �߰�!
		this->discover();

		// �Ʊ� ��ü �߰�
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

// ��ü �ʱ�ȭ
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
	// ��������, �ƴҋ�
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

// �� �ǽ� (�Ʊ� ��ü �߰�)
void enemy::doubt()
{
	
}

// �÷��̾� �߰�
void enemy::discover()
{
	//_enemyStatus = ENEMY_DOUBT;

	if (_isLeft)
	{		
		if (_enemyImage.bodyImageIndex <= 0)
		{
			// ��� ���
			_enemyStatus = ENEMY_FIRE;
		}
	}
	else
	{		
		if (_enemyImage.bodyImageIndex >= _enemyImage.bodyImage[ENEMY_DOUBT]->getMaxFrameX())
		{
			// ��� ���
			_enemyStatus = ENEMY_FIRE;
		}
	}
}

//���ư���
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

// �߻�� ���ʹ� ������ ������
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

// ������ �ִϸ��̼�
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
		
	// �÷��̾� ������ �� '!' ������ �ѹ��� ����
	if (_isUncovered && _warnFrameIndex < _warnSign->getMaxFrameX())
	{
		FRAMEMANAGER->frameChange(_warnSign, _warnFrameCount, _warnFrameIndex, _frameSpeed, 0);
	}
	
	// ���ʹ� �Ʊ� ��ü ��������, '?' ������ �ѹ��� ����
	if (_isStrange && _doubtFrameIndex < _doubtSign->getMaxFrameX())
	{
		FRAMEMANAGER->frameChange(_doubtSign, _doubtFrameCount, _doubtFrameIndex, _frameSpeed, 0);
	}
}

void enemy::knockBackMove(bool isLeft)
{
	// �˹������, �ڷ� ����
	
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

// �ǰ� �� ������� ��ü ���ص� ��
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

