#include "stdafx.h"
#include "enemy.h"


HRESULT enemy::initSoldier(int x, int y)
{
	_x = x, _y = y;
		
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

	_enemyImage.count = 5;
	_enemyImage.speed = 5;
	_enemyImage.index = 0;
				
	//�˶� �̹��� �ʱ�ȭ
	//IMAGEMANAGER->addFrameImage("�˶�", "enemyImage/ExclamationMark.bmp", 1020, 60, 17, 1);
	////�ǹ� �̹��� �ʱ�ȭ
	//IMAGEMANAGER->addFrameImage("�ǹ�", "enemyImage/QuestionMark.bmp", 960, 60, 16, 1);
	
	//IMAGEMANAGER->findImage("�˶�");
	//_doubtSign = IMAGEMANAGER->findImage("�ǹ�");
	
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
	_speed = 2.f;
	_enemyStatus = ENEMY_IDLE;
	_gunStatus = GUN_IDLE;
	
	_gravity = 0.f;
	
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
//	_brovilImage.brovilImg[BROVIL_IDLE] = IMAGEMANAGER->findImage("��κ�����");
//	_brovilImage.brovilImg[BROVIL_WALK] = IMAGEMANAGER->findImage("��κ�����");
//	_brovilImage.brovilImg[BROVIL_KNOCK_BACK] = IMAGEMANAGER->findImage("��κ��˹�");
//	_brovilImage.brovilImg[BROVIL_DEAD] = IMAGEMANAGER->findImage("��κ���ü");
//	_brovilImage.brovilImg[BROVIL_DISAPPEAR] = IMAGEMANAGER->findImage("��κ���ȭ");
//
//	_brovilImage.count = _brovilImage.index = 0;
//	_brovilImage.speed = 5;
//
//	_warnSign = IMAGEMANAGER->findImage("�˶�");
//	_doubtSign = IMAGEMANAGER->findImage("�ǹ�");
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
	_warnSign->release();
	SAFE_DELETE(_warnSign);
	_doubtSign->release();
	SAFE_DELETE(_doubtSign);
}

void enemy::update(void)
{	
	// �ؿ� ������ ������
	fall();
	
	// ���������
	if (_isAlive)
	{
		// �� �þ� ��Ʈ ��ȭ
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
			// �÷��̾� �߰�!
			this->discover();
		}

		if (_isStrange)
		{
			// �Ʊ� ��ü �߰�!
			this->doubt();
		}

		if (_enemyImage.bodyImage[ENEMY_KNOCK_BACK]->getFrameX() == _enemyImage.bodyImage[ENEMY_KNOCK_BACK]->getMaxFrameX())
		{
			
		}

	}
	// �׾�����
	else
	{
		

	}

	// ����ڼ��� ���Ѵ�	
	if (_enemyStatus == ENEMY_FIRE)
	{		
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
		//���� �̹��� ����
		_enemyImage.bodyImage[_enemyStatus]->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top,
			_enemyImage.bodyImage[_enemyStatus]->getFrameX(), _enemyImage.bodyImage[_enemyStatus]->getFrameY());
		
		//�� �̹��� ����
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

//======================================================================================================================================
//======================================================================================================================================
//======================================================================================================================================

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
		//�¿� �̵�
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
	
	//���󰥶�
	if (_enemyStatus == ENEMY_FLY_AWAY)
	{
		flyAway();
	}	
}

// �� �ǽ� (�Ʊ� ��ü �߰�)
void enemy::doubt()
{
	//_enemyStatus = ENEMY_DOUBT;
	////�Ʊ�(��) ��ü �߰��ϰ� �ǽ��Ҷ�,
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

// �÷��̾� �߰�
void enemy::discover()
{
	_enemyStatus = ENEMY_DOUBT;

	if (!_isLeft)
	{
		if (_enemyImage.bodyImage[ENEMY_DOUBT]->getFrameX() >= _enemyImage.bodyImage[ENEMY_DOUBT]->getMaxFrameX())
		{
			// ��� ���
			_enemyStatus = ENEMY_FIRE;
		}
	}
	else
	{
		if (_enemyImage.bodyImage[ENEMY_DOUBT]->getFrameX() <= 0)
		{
			// ��� ���
			_enemyStatus = ENEMY_FIRE;
		}
	}
}

//���ư���
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
	_gunStatus = GUN_TARGETING;
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
	if (_enemyStatus == ENEMY_KNOCK_BACK && _enemyImage.bodyImage[_enemyStatus]->getFrameX() < _enemyImage.bodyImage[_enemyStatus]->getMaxFrameX())
	{
		FRAMEMANAGER->frameChange(_enemyImage.bodyImage[_enemyStatus], _enemyImage.count, _enemyImage.index, _enemyImage.speed, !_isLeft);
	}
	else
	{
		FRAMEMANAGER->frameChange(_enemyImage.bodyImage[_enemyStatus], _enemyImage.count, _enemyImage.index, _enemyImage.speed, _isLeft);
	}

	//FRAMEMANAGER->frameChange(_brovilImage.brovilImg[_brovilStatus], _brovilImage.count, _brovilImage.index, _brovilImage.speed, _isLeft);
	FRAMEMANAGER->frameChange(_enemyImage.armImage[_gunStatus], _enemyImage.count, _enemyImage.index, _enemyImage.speed, _isLeft);
	
	if (_isUncovered && _warnFrameIndex < _warnSign->getMaxFrameX())
	{
		FRAMEMANAGER->frameChange(_warnSign, _warnFrameCount, _warnFrameIndex, _frameSpeed, 0);
	}
	
	if (_isStrange && _doubtFrameIndex < _doubtSign->getMaxFrameX())
	{
		FRAMEMANAGER->frameChange(_doubtSign, _doubtFrameCount, _doubtFrameIndex, _frameSpeed, 0);
	}
}

void enemy::knockBackMove(float angle)
{
	// �˹������, �ڷ� ����
	
	float tempAngle = 2 * PI - angle;
	setX(getX() + cosf(tempAngle)*_kbSpeed);
	_kbSpeed -= 0.5f;
	
	//if (_kbSpeed < 0)
	//{
	//	_enemyStatus = ENEMY_DEAD;
	//	//_brovilStatus = BROVIL_DEAD;
	//}	
}

void enemy::dead()
{
	
}

