#include "stdafx.h"
#include "enemy.h"


HRESULT enemy::init(const char* bodyImage, const char* armImage, int x, int y, int hp)
{
	_x = x, _y = y;
	_hp = hp;

	_bodyImage = IMAGEMANAGER->findImage(bodyImage);
	_armImage = IMAGEMANAGER->findImage(armImage);
	_enemyRC = RectMakeCenter(_x, _y, _bodyImage->getFrameWidth(), _bodyImage->getFrameHeight());

	setSpeed(3.0f);
	_enemyStatus = IDLE_LEFT;

	_isLeft = FALSE;
	_isAlarm = TRUE;
	_actionCount = _frameCount = _frameIndex = _frameIndex2 = RND->getFromIntTo(0, 5);

	return S_OK;
}

void enemy::release(void)
{
}

void enemy::update(void)
{
	this->move();
	this->frameAnimate();
		
}

void enemy::render(void)
{
	IMAGEMANAGER->frameRender("적몸통", getMemDC(), _enemyRC.left - CAMERAMANAGER->getCamera().left, _enemyRC.top - CAMERAMANAGER->getCamera().top, _bodyImage->getFrameX(), _bodyImage->getFrameY());
	IMAGEMANAGER->frameRender("적팔", getMemDC(), _enemyRC.left - CAMERAMANAGER->getCamera().left, _enemyRC.top - CAMERAMANAGER->getCamera().top, _armImage->getFrameX(), _armImage->getFrameY());

	if (KEYMANAGER->isToggleKey(VK_F5))
	{
		Rectangle(getMemDC(), _bodyImage->getX(), _bodyImage->getY(), _bodyImage->getX() + _bodyImage->getFrameWidth(), _bodyImage->getY() + _bodyImage->getFrameHeight());
	}
}

void enemy::move()
{
	++_actionCount;

	// 일정시간 지나면 적 이동
	if (_actionCount < RND->getInt(100))
	{
		_enemyStatus = WALK_LEFT;
		_isLeft = true;
	}
	else if (_actionCount > 200 && _actionCount < 400)
	{
		_enemyStatus = WALK_RIGHT;
		_isLeft = false;
	}
	else if (_actionCount > 400 && _actionCount < 600)
	{
		_enemyStatus = IDLE_LEFT;
		_isLeft = true;
	}
	else if (_actionCount > 600 && _actionCount < 800)
	{
		_enemyStatus = IDLE_RIGHT;
		_isLeft = false;
	}
	else if (_actionCount > 800 && _actionCount < 1000)
	{
		_enemyStatus = WARNING_LEFT;
		_isLeft = true;
	}
	else if (_actionCount > 1000 && _actionCount < 1200)
	{
		_enemyStatus = WARNING_RIGHT;
		_isLeft = false;
	}

	if (_enemyStatus == WALK_LEFT)	 setX(getX() - getSpeed());
	else if (_enemyStatus == WALK_RIGHT) setX(getX() + getSpeed());

	setEnemyRC(RectMakeCenter(getX(), getY(), _bodyImage->getFrameWidth(), _bodyImage->getFrameHeight()));
	_bodyImage->setX(getEnemyRC().left);
	_bodyImage->setY(getEnemyRC().top);
	_armImage->setX(getEnemyRC().left);
	_armImage->setY(getEnemyRC().top);

	if (_actionCount > 1200) _actionCount = 0;
}

void enemy::frameAnimate()
{
	if (_enemyStatus == IDLE_LEFT)
	{
		_bodyImage->setFrameY(3);
		_armImage->setFrameY(7);
		++_frameCount;
		if (_frameCount % COOLTIME == 0)
		{
			if (_frameIndex > 14) _frameIndex = 14;
			_frameIndex--;
			if (_frameIndex < 0) _frameIndex = 14;

			if (_frameIndex2 > 7) _frameIndex2 = 7;
			_frameIndex2--;
			if (_frameIndex2 < 0) _frameIndex2 = 7;
		}
		_bodyImage->setFrameX(_frameIndex);
		_armImage->setFrameX(_frameIndex2);
	}
	else if (_enemyStatus == IDLE_RIGHT)
	{
		_bodyImage->setFrameY(2);
		_armImage->setFrameY(6);
		++_frameCount;
		if (_frameCount % COOLTIME == 0)
		{
			if (_frameIndex < 0) _frameIndex = 0;
			_frameIndex++;
			if (_frameIndex > 14) _frameIndex = 0;

			if (_frameIndex2 < 0) _frameIndex2 = 0;
			_frameIndex2++;
			if (_frameIndex2 > 7) _frameIndex2 = 0;
		}
		_bodyImage->setFrameX(_frameIndex);
		_armImage->setFrameX(_frameIndex2);
	}
	else if (_enemyStatus == WALK_LEFT)
	{
		_bodyImage->setFrameY(1);
		_armImage->setFrameY(7);
		++_frameCount;
		if (_frameCount % COOLTIME == 0)
		{
			if (_frameIndex > 7) _frameIndex = 7;
			_frameIndex--;
			if (_frameIndex < 0) _frameIndex = 7;

			if (_frameIndex2 > 7) _frameIndex2 = 7;
			_frameIndex2--;
			if (_frameIndex2 < 0) _frameIndex2 = 7;

		}
		_bodyImage->setFrameX(_frameIndex);
		_armImage->setFrameX(_frameIndex2);
	}
	else if (_enemyStatus == WALK_RIGHT)
	{
		_bodyImage->setFrameY(0);
		_armImage->setFrameY(6);
		++_frameCount;
		if (_frameCount % COOLTIME == 0)
		{
			if (_frameIndex < 0) _frameIndex = 0;
			++_frameIndex;
			if (_frameIndex > 7) _frameIndex = 0;

			if (_frameIndex2 < 0) _frameIndex2 = 0;
			_frameIndex2++;
			if (_frameIndex2 > 7) _frameIndex2 = 0;
		}
		_bodyImage->setFrameX(_frameIndex);
		_armImage->setFrameX(_frameIndex2);
	}
	else if (_enemyStatus == WARNING_LEFT)
	{
		_bodyImage->setFrameY(3);
		_armImage->setFrameY(9);
		++_frameCount;
		if (_frameCount % COOLTIME == 0)
		{
			if (_frameIndex2 > 6) _frameIndex2 = 6;
			_frameIndex2--;
			if (_frameIndex2 < 0) _frameIndex2 = 6;
		}
		_bodyImage->setFrameX(6);
		_armImage->setFrameX(_frameIndex2);
	}
	else if (_enemyStatus == WARNING_RIGHT)
	{
		_bodyImage->setFrameY(2);
		_armImage->setFrameY(9);
		++_frameCount;
		if (_frameCount % COOLTIME == 0)
		{
			if (_frameIndex2 < 0) _frameIndex2 = 0;
			_frameIndex2++;
			if (_frameIndex2 > 6) _frameIndex2 = 0;
		}
		_bodyImage->setFrameX(6);
		_armImage->setFrameX(_frameIndex2);
	}

	if (_frameCount > 1000) _frameCount = 0;
}