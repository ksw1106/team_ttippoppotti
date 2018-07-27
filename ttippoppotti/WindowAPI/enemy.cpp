#include "stdafx.h"
#include "enemy.h"


HRESULT enemy::init(int x, int y, int hp, int randomNum)
{
	_x = x, _y = y;
	_hp = hp;

	_bodyImage[E_IDLE] = IMAGEMANAGER->findImage("��������");
	_bodyImage[E_WALK] = IMAGEMANAGER->findImage("���ΰ���");
	_bodyImage[E_DOUBT] = IMAGEMANAGER->findImage("�����ǽ�");
	_bodyImage[E_KNOCK_BACK] = IMAGEMANAGER->findImage("���γ˹�");
	_bodyImage[E_FLY_AWAY] = IMAGEMANAGER->findImage("��������");
	_bodyImage[E_DEAD] = IMAGEMANAGER->findImage("���ν�ü");

	_armImage[G_IDLE] = IMAGEMANAGER->findImage("������");
	_armImage[G_TARGETING] = IMAGEMANAGER->findImage("������");
	_armImage[G_READY] = IMAGEMANAGER->findImage("�ѹ߻���");
	_armImage[G_FIRE] = IMAGEMANAGER->findImage("�ѹ߻�");
	_armImage[G_RELOAD] = IMAGEMANAGER->findImage("������");
				
	_warnSign = IMAGEMANAGER->findImage("�˶�");
	_doubtSign = IMAGEMANAGER->findImage("�ǹ�");

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
		//���� �̹��� ����
		_bodyImage[getBodyStatus()]->frameRender(getMemDC(), _enemyRC.left - CAMERAMANAGER->getCamera().left, _enemyRC.top - CAMERAMANAGER->getCamera().top,
			_bodyImage[getBodyStatus()]->getFrameX(), _bodyImage[getBodyStatus()]->getFrameY());
		
		//�� �̹��� ����
		if (getBodyStatus() != ( E_DEAD || E_KNOCK_BACK || E_FLY_AWAY ))
		_armImage[getArmStatus()]->frameRender(getMemDC(), _enemyRC.left - CAMERAMANAGER->getCamera().left, _enemyRC.top - CAMERAMANAGER->getCamera().top,
			_armImage[getArmStatus()]->getFrameX(), _armImage[getArmStatus()]->getFrameY());
		
		// �÷��̾� �߰�������, ����ǥ ��ǳ��!
		if (_isAlarm)
		{
			IMAGEMANAGER->frameRender("�˶�", getMemDC(), _enemyRC.left + 10 - CAMERAMANAGER->getCamera().left, _enemyRC.top - 50 - CAMERAMANAGER->getCamera().top, _warnSign->getFrameX(), _warnSign->getFrameY());
		}

		if (_isAlarm2)
		{
			IMAGEMANAGER->frameRender("�ǹ�", getMemDC(), _enemyRC.left + 10 - CAMERAMANAGER->getCamera().left, _enemyRC.top - 50 - CAMERAMANAGER->getCamera().top, _doubtSign->getFrameX(), _doubtSign->getFrameY());
		}		
	}
	
	if (KEYMANAGER->isToggleKey(VK_F4))
	{
		// ���ʹ� ��Ʈ ����
		Rectangle(getMemDC(), getX() - getBodyImage()->getFrameWidth() / 2 - CAMERAMANAGER->getCamera().left, getY() - getBodyImage()->getFrameHeight() / 2 - CAMERAMANAGER->getCamera().top,
			getX() + getBodyImage()->getFrameWidth()/2 - CAMERAMANAGER->getCamera().left, getY() + getBodyImage()->getFrameHeight()/2 - CAMERAMANAGER->getCamera().top);
	}
	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		// �� �þ� ��Ʈ ����
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
		
	//�¿� �̵�
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
	
	//���󰥶�
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

	// �� �þ� ��Ʈ ��ȭ
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
	// �˹������, �ڷ� ����
	
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
