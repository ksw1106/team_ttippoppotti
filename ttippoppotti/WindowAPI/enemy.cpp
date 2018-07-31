#include "stdafx.h"
#include "enemy.h"


HRESULT enemy::initSoldier(int x, int y, int hp, int randomNum)
{
	_x = x, _y = y;
	_hp = hp;
	
	_enemyImage.bodyImage[ENEMY_IDLE] = IMAGEMANAGER->findImage("��������");
	_enemyImage.bodyImage[ENEMY_WALK] = IMAGEMANAGER->findImage("���ΰ���");
	_enemyImage.bodyImage[ENEMY_DOUBT] = IMAGEMANAGER->findImage("�����ǽ�");
	_enemyImage.bodyImage[ENEMY_KNOCK_BACK] = IMAGEMANAGER->findImage("���γ˹�");
	_enemyImage.bodyImage[ENEMY_FLY_AWAY] = IMAGEMANAGER->findImage("��������");
	_enemyImage.bodyImage[ENEMY_DEAD] = IMAGEMANAGER->findImage("���ν�ü");

	_enemyImage.armImage[GUN_IDLE] = IMAGEMANAGER->findImage("������");
	_enemyImage.armImage[GUN_TARGETING] = IMAGEMANAGER->findImage("������");
	_enemyImage.armImage[GUN_READY] = IMAGEMANAGER->findImage("�ѹ߻���");
	_enemyImage.armImage[GUN_FIRE] = IMAGEMANAGER->findImage("�ѹ߻�");
	_enemyImage.armImage[GUN_RELOAD] = IMAGEMANAGER->findImage("������");

	_enemyImage.count = _enemyImage.index = 0;
	_enemyImage.speed = 5;
				
	_warnSign = IMAGEMANAGER->findImage("�˶�");
	_doubtSign = IMAGEMANAGER->findImage("�ǹ�");

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
	_isAlive = true;
	_isLeft = true;
	_isOn = true;
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
}

void enemy::update(void)
{	
	if (_isAlive)
	{
		//_gravity += _accel;
		if (_warnSign->getFrameX() >= _warnSign->getMaxFrameX())
		{
			//_warnSign.re
		}
		if (_doubtSign->getFrameX() >= _doubtSign->getMaxFrameX())
		{
			_isStrange = false;
		}

		if ((_enemyStatus <= 2 || _gunStatus == 0) && (_enemyStatus != ENEMY_KNOCK_BACK && _enemyStatus != ENEMY_DEAD))
		{
			this->controlAI(RND->getInt(200));
		}
		//if (_brovilStatus <= 2)
		//{
		//	this->controlAI(RND->getInt(200));
		//}
	}

	else
	{
		if (_enemyStatus == ENEMY_KNOCK_BACK)
		{
			if (_isLeft)
			{
				if (_enemyImage.bodyImage[ENEMY_KNOCK_BACK]->getFrameX() == 0 )
				{

				}
			}
			else
			{
				if (_enemyImage.bodyImage[ENEMY_KNOCK_BACK]->getFrameX() == _enemyImage.bodyImage[ENEMY_KNOCK_BACK]->getMaxFrameX())
				{

				}
			}
		}

	}
	
	this->move();
	this->frameAnimate();
	
	
	//if (_enemyStatus == ENEMY_KNOCK_BACK || _brovilStatus == BROVIL_KNOCK_BACK)
	//{
	//	this->knockBackMove();
	//}

	_enemyImage.bodyImage[getBodyStatus()]->setX(_x);
	_enemyImage.bodyImage[getBodyStatus()]->setY(_y);
	_enemyImage.armImage[getArmStatus()]->setX(_x);
	_enemyImage.armImage[getArmStatus()]->setY(_y);
	
	_rcEnemy = RectMake(_x, _y, _enemyImage.bodyImage[getBodyStatus()]->getFrameWidth(), _enemyImage.bodyImage[getBodyStatus()]->getFrameHeight());
	
}

void enemy::render(void)
{
	if (CAMERAMANAGER->CameraIn(getRcEnemy()))
	{
		//���� �̹��� ����
		_enemyImage.bodyImage[getBodyStatus()]->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top,
			_enemyImage.bodyImage[getBodyStatus()]->getFrameX(), _enemyImage.bodyImage[getBodyStatus()]->getFrameY());
		
		//�� �̹��� ����
		if (_isAlive)
		{
			_enemyImage.armImage[getArmStatus()]->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top,
				_enemyImage.armImage[getArmStatus()]->getFrameX(), _enemyImage.armImage[getArmStatus()]->getFrameY());
		}

		//_brovilImage.brovilImg[_brovilStatus]->frameRender(getMemDC(), _rcEnemy.left - CAMERAMANAGER->getCamera().left, _rcEnemy.top - CAMERAMANAGER->getCamera().top,
		//	_brovilImage.brovilImg[_brovilStatus]->getFrameX(), _brovilImage.brovilImg[_brovilStatus]->getFrameY());		

		// �÷��̾� �߰�������, ����ǥ ��ǳ��!
		if (_isUncovered)
		{
			IMAGEMANAGER->frameRender("�˶�", getMemDC(), _x + 10 - CAMERAMANAGER->getCamera().left, _y - 50 - CAMERAMANAGER->getCamera().top, _warnSign->getFrameX(), _warnSign->getFrameY());
		}

		if (_isStrange)
		{
			IMAGEMANAGER->frameRender("�ǹ�", getMemDC(), _x + 10 - CAMERAMANAGER->getCamera().left, _y - 50 - CAMERAMANAGER->getCamera().top, _doubtSign->getFrameX(), _doubtSign->getFrameY());
		}		
	}
	
	if (KEYMANAGER->isToggleKey(VK_F4))
	{
		// ���ʹ� ��Ʈ ����
		Rectangle(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top,
			_x + _enemyImage.bodyImage[getBodyStatus()]->getFrameWidth() - CAMERAMANAGER->getCamera().left, _y + _enemyImage.bodyImage[getBodyStatus()]->getFrameHeight() - CAMERAMANAGER->getCamera().top);
	}

	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		// �� �þ� ��Ʈ ����
		RectangleMake(getMemDC(), _rcEnemySight.left - CAMERAMANAGER->getCamera().left, _rcEnemySight.top - CAMERAMANAGER->getCamera().top,
			800 + _enemyImage.bodyImage[getBodyStatus()]->getFrameWidth(), _enemyImage.bodyImage[getBodyStatus()]->getFrameHeight());
	}
	
}

//======================================================================================================================================
//======================================================================================================================================
//======================================================================================================================================

void enemy::move()
{
	if (_isAlive)
	{		
		//�Ʊ�(��) ��ü �߰��ϰ� �ǽ��Ҷ�,
		if (_enemyStatus == ENEMY_DOUBT)
		{
			_gunStatus = GUN_TARGETING;
			if (_isLeft)
			{
				if (_enemyImage.armImage[_enemyStatus]->getFrameX() == 0)
				{
					_gunStatus = GUN_FIRE;
					_enemyStatus = ENEMY_IDLE;
					_enemyImage.bodyImage[_enemyStatus]->setFrameX(4);
				}
			}
			else
			{
				if (_enemyImage.armImage[_enemyStatus]->getFrameX() == _enemyImage.armImage[getArmStatus()]->getMaxFrameX())
				{
					_gunStatus = GUN_FIRE;
					_enemyStatus = ENEMY_IDLE;
					_enemyImage.bodyImage[_enemyStatus]->setFrameX(4);
				}
			}

		}

		// �� �þ� ��Ʈ ��ȭ
		if (_isLeft)
		{
			_rcEnemySight = RectMake(getX() - 800, getY(), 800 + _enemyImage.bodyImage[_enemyStatus]->getFrameWidth(), _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());
		}
		else
		{
			_rcEnemySight = RectMake(getX(), getY(), 800 + _enemyImage.bodyImage[_enemyStatus]->getFrameWidth(), _enemyImage.bodyImage[_enemyStatus]->getFrameHeight());
		}

	}	
	
	//���󰥶�
	if (_enemyStatus == ENEMY_FLY_AWAY)
	{
		flyAway();
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

void enemy::knockBackMove(float angle)
{
	// �˹������, �ڷ� ����
	
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
