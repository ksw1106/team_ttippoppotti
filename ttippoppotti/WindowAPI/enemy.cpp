#include "stdafx.h"
#include "enemy.h"


HRESULT enemy::init(int x, int y, int hp)
{
	_bodyImage = IMAGEMANAGER->addFrameImage("적몸통", "enemyImage/_enemy_with_head.bmp", 1600, 1600, 20, 20);
	_armImage = IMAGEMANAGER->addFrameImage("적팔", "enemyImage/_enemy_gun.bmp", 1600, 800, 19, 10);
	_enemyRC = RectMakeCenter(getX(), getY(), _bodyImage->getFrameWidth(), _bodyImage->getFrameHeight());
	setEnemyStatus(IDLE_LEFT);
	setSpeed(3.0f);
	setX(x), setY(y), setHP(hp);
			
	_isLeft = FALSE;
	_actionCount = _frameCount = _frameIndex = 0;

	return S_OK;
}

void enemy::release(void)
{
}

void enemy::update(void)
{
	this->move();
	this->frameAnimate();
	
	setEnemyRC(RectMakeCenter(getX(), getY(), _bodyImage->getFrameWidth(), _bodyImage->getFrameHeight()));
	_bodyImage->setX(getEnemyRC().left);
	_bodyImage->setY(getEnemyRC().top);
}

void enemy::render(void)
{
	IMAGEMANAGER->frameRender("적몸통", getMemDC(), _bodyImage->getX(), _bodyImage->getY(), _bodyImage->getFrameX(), _bodyImage->getFrameY());

	if (KEYMANAGER->isToggleKey(VK_F5))
	{
		Rectangle(getMemDC(), _bodyImage->getX(), _bodyImage->getY(), _bodyImage->getX() + _bodyImage->getFrameWidth(), _bodyImage->getY() + _bodyImage->getFrameHeight());
	}
}

void enemy::move()
{
	++_actionCount;
	// 일정시간 지나면 적 이동
	if (_actionCount > 0 && _actionCount < 100)
	{
		setEnemyStatus(WALK_LEFT);
	}
	else if (_actionCount > 100 && _actionCount < 200)
	{
		setEnemyStatus(WALK_RIGHT);
	}
	else if (_actionCount > 200 && _actionCount < 300)
	{
		if (_isLeft) setEnemyStatus(IDLE_LEFT);
		else		 setEnemyStatus(IDLE_RIGHT);
	}

	if (_actionCount % 200 == 0)
	{
		if (_isLeft) _isLeft = false;
		else         _isLeft = true;
	}

	if      (getEnemyStatus() == WALK_LEFT)	 setX(getX() - getSpeed());
	else if (getEnemyStatus() == WALK_RIGHT) setX(getX() + getSpeed());

	if (_actionCount > 1000) _actionCount = 0;
}

void enemy::frameAnimate()
{
	if (getEnemyStatus() == IDLE_LEFT)
	{
		_bodyImage->setFrameY(3);
		++_frameCount;
		if (_frameCount % COOLTIME == 0)
		{			
			//if (_frameIndex > 14) _frameIndex = 14;
			_frameIndex--;
			if (_frameIndex < 0) _frameIndex = 14;
		}
		_bodyImage->setFrameX(_frameIndex);
	}
	else if (getEnemyStatus() == IDLE_RIGHT)
	{
		_bodyImage->setFrameY(2);
		++_frameCount;
		if (_frameCount % COOLTIME == 0)
		{
			if (_frameIndex < 0) _frameIndex = 0;
			_frameIndex++;
			if (_frameIndex > 14) _frameIndex = 0;
		}
		_bodyImage->setFrameX(_frameIndex);
	}	
	else if (getEnemyStatus() == WALK_LEFT)
	{
		_bodyImage->setFrameY(1);
		++_frameCount;
		if (_frameCount % COOLTIME == 0)
		{
			if (_frameIndex > 7) _frameIndex = 7;
			_frameIndex--;
			if (_frameIndex < 0) _frameIndex = 7;
		}
		_bodyImage->setFrameX(_frameIndex);
	}
	else if (getEnemyStatus() == WALK_RIGHT)
	{
		_bodyImage->setFrameY(0);
		++_frameCount;
		if (_frameCount % COOLTIME == 0)
		{
			//if (_frameIndex < 0) _frameIndex = 0;
			++_frameIndex;
			if (_frameIndex > 7) _frameIndex = 0;
		}
		_bodyImage->setFrameX(_frameIndex);
	}

	if (_frameCount > 1000) _frameCount = 0;
}
