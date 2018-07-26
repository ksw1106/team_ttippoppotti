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

	_warnSign->setFrameX(0);
	_doubtSign->setFrameY(0);
		
	setSpeed(3.0f);
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
	this->controlAI(_randomNumber);
	this->move();
	this->frameAnimate();
	this->knockBackMove();		

	_bodyImage[getBodyStatus()]->setX(getEnemyRC().left);
	_bodyImage[getBodyStatus()]->setY(getEnemyRC().top);
	_armImage[getArmStatus()]->setX(getEnemyRC().left);
	_armImage[getArmStatus()]->setY(getEnemyRC().top);
	
	setEnemyRC(RectMakeCenter(getX(), getY(), _bodyImage[_enemyStatus]->getFrameWidth(), _bodyImage[_enemyStatus]->getFrameHeight()));
}

void enemy::render(void)
{
	if (CAMERAMANAGER->CameraIn(getEnemyRC()))
	{
		//���� �̹��� ����
		_bodyImage[getBodyStatus()]->frameRender(getMemDC(), _enemyRC.left - CAMERAMANAGER->getCamera().left, _enemyRC.top - CAMERAMANAGER->getCamera().top,
			_bodyImage[getBodyStatus()]->getFrameX(), _bodyImage[getBodyStatus()]->getFrameY());
		//�� �̹��� ����
		_armImage[getArmStatus()]->frameRender(getMemDC(), _enemyRC.left - CAMERAMANAGER->getCamera().left, _enemyRC.top - CAMERAMANAGER->getCamera().top,
			_armImage[getArmStatus()]->getFrameX(), _armImage[getArmStatus()]->getFrameY());
		
		// �÷��̾� �߰�������, ����ǥ ��ǳ��!
		if (_isAlarm && _warnSign->getFrameX() <= _warnSign->getMaxFrameX())	
		{
			IMAGEMANAGER->frameRender("�˶�", getMemDC(), _enemyRC.left + 10 - CAMERAMANAGER->getCamera().left, _enemyRC.top - 50 - CAMERAMANAGER->getCamera().top, _warnSign->getFrameX(), _warnSign->getFrameY());
		}
		//if ()
	}
	
	if (KEYMANAGER->isToggleKey(VK_F4))
	{
		//Rectangle(getMemDC(), getX() - _bodyImage[getBodyStatus()]->getFrameWidth()/2, getY() - _bodyImage[getBodyStatus()]->getFrameHeight()/2,
		//	getX() + _bodyImage[getBodyStatus()]->getFrameWidth()/2, getY() + _bodyImage[getBodyStatus()]->getFrameHeight()/2);

		// �� �þ� ��Ʈ ����
		RectangleMake(getMemDC(), _enemySightRC.left - CAMERAMANAGER->getCamera().left, _enemySightRC.top - CAMERAMANAGER->getCamera().top, 500, 100);
	}
}

void enemy::move()
{
	// �¿� �̵�
	if (getBodyStatus() == E_WALK)
	{
		if (_isLeft)
			setX(getX() - getSpeed());
		else 
			setX(getX() + getSpeed());
	}	
	
	// �� �þ� ��Ʈ ��ȭ
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

void enemy::controlAI(int randomNum)
{
	if (randomNum % 2 == 1)
	{
		setBodyStatus(E_WALK);
		setArmStatus(G_FIRE);
		setDirection(false);
	}
	else if (randomNum % 2 == 0)
	{
		setBodyStatus(E_IDLE);
	}
}

void enemy::frameAnimate()
{
	FRAMEMANAGER->frameChange(_bodyImage[getBodyStatus()], _frameCount, _frameIndex, _actionSpeed, _isLeft);
	FRAMEMANAGER->frameChange(_armImage[getArmStatus()], _frameCount, _frameIndex2, _actionSpeed, _isLeft);
	FRAMEMANAGER->frameChange(_warnSign, _frameCount, _frameIndex3, _actionSpeed, _isLeft);
	FRAMEMANAGER->frameChange(_doubtSign, _frameCount, _frameIndex4, _actionSpeed, _isLeft);
		
}

void enemy::knockBackMove()
{
	// �˹������, �ڷ� ����
	if (_enemyStatus == E_KNOCK_BACK)
	{
		setX(getX() - _kbSpeed);
		_kbSpeed -= 0.5f;
		if (_kbSpeed < 0)
		{
			_enemyStatus = E_DEAD;
		}
	}	
	if (_enemyStatus == E_KNOCK_BACK)
	{
		setX(getX() + _kbSpeed);
		_kbSpeed -= 0.5f;
		if (_kbSpeed < 0)
		{			
			_enemyStatus = E_DEAD;
		}
	}	
}
