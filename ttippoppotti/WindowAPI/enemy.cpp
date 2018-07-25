#include "stdafx.h"
#include "enemy.h"


HRESULT enemy::init(const char* bodyImage, const char* armImage, int x, int y, int hp)
{
	_x = x, _y = y;
	_hp = hp;

	_bodyImage = IMAGEMANAGER->findImage(bodyImage);
	_armImage = IMAGEMANAGER->findImage(armImage);
	_warnSign = IMAGEMANAGER->findImage("알람");
	_warnSign->setFrameX(0);
	_enemyRC = RectMakeCenter(_x, _y, _bodyImage->getFrameWidth(), _bodyImage->getFrameHeight());
	
	setSpeed(3.0f);
	_enemyStatus = IDLE_LEFT;
	_kbSpeed = 20.f;

	_isLeft = FALSE;
	_isAlarm = FALSE;
	_actionCount = _frameCount = _frameIndex = _frameIndex2 = _frameIndex3 = 0;

	return S_OK;
}

void enemy::release(void)
{
}

void enemy::update(void)
{
	this->move(_enemyStatus);
	this->frameAnimate();
	this->knockBackMove();		
}

void enemy::render(void)
{
	IMAGEMANAGER->frameRender("적몸통", getMemDC(), _enemyRC.left - CAMERAMANAGER->getCamera().left, _enemyRC.top - CAMERAMANAGER->getCamera().top, _bodyImage->getFrameX(), _bodyImage->getFrameY());
	if (_enemyStatus < 12)
	{
		IMAGEMANAGER->frameRender("적팔", getMemDC(), _enemyRC.left - 5 - CAMERAMANAGER->getCamera().left, _enemyRC.top + 3 - CAMERAMANAGER->getCamera().top, _armImage->getFrameX(), _armImage->getFrameY());
	}

	if (_isAlarm && _warnSign->getFrameX() <= _warnSign->getMaxFrameX())	// 플레이어 발견했을때, 느낌표 말풍선!
	{
		IMAGEMANAGER->frameRender("알람", getMemDC(), _enemyRC.left + 10 - CAMERAMANAGER->getCamera().left, _enemyRC.top - 50 - CAMERAMANAGER->getCamera().top, _warnSign->getFrameX(), _warnSign->getFrameY());
		
	}
	if (KEYMANAGER->isToggleKey(VK_F5))
	{
		Rectangle(getMemDC(), getX() - _bodyImage->getFrameWidth()/2, getY() - _bodyImage->getFrameHeight()/2, getX() + _bodyImage->getFrameWidth()/2, getY() + _bodyImage->getFrameHeight()/2);
		RectangleMake(getMemDC(), _enemySightRC.left - CAMERAMANAGER->getCamera().left, _enemySightRC.top - CAMERAMANAGER->getCamera().top, 500, 100);
	}
}

void enemy::move(enemyStatus enemyStat)
{
	++_actionCount;
	// 적 방향에 따른 왼쪽, 오른쪽 불변수 변화
	if (enemyStat % 2 == 0) // 짝수면은 왼쪽
		_isLeft = true;
	else if (enemyStat % 2 == 1) // 홀수면은 오른쪽
		_isLeft = false;
	
	if (enemyStat == WALK_LEFT)	 setX(getX() - getSpeed());
	else if (enemyStat == WALK_RIGHT) setX(getX() + getSpeed());
	if (enemyStat == RUN_LEFT) setX(getX() - getSpeed() * 2);
	else if (enemyStat == RUN_RIGHT) setX(getX() + getSpeed() * 2);
	
	// 플레이어 발견시 움직임
	if (_isAlarm)
	{
		if (_isLeft) _enemyStatus = WARNING_LEFT;
		else _enemyStatus = WARNING_RIGHT;

		if (enemyStat == WARNING_LEFT)
		{
			if (_frameIndex2 > 6)
			{
				_frameIndex2 = 0;
				_enemyStatus = FIRE_LEFT;
			}
		}
		else if (enemyStat == WARNING_RIGHT)
		{
			if (_frameIndex2 < 0)
			{
				_frameIndex2 = 0;
				_enemyStatus = FIRE_RIGHT;
			}
		}
	}	

	setEnemyRC(RectMakeCenter(getX(), getY(), _bodyImage->getFrameWidth(), _bodyImage->getFrameHeight()));

	// 적 시야 렉트 변화
	if (_isLeft)
	{
		_enemySightRC = RectMake(getX() - 500, getY() - _bodyImage->getFrameHeight() / 2, 500 + _bodyImage->getFrameWidth() / 2, _bodyImage->getFrameHeight());
	}
	else
	{
		_enemySightRC = RectMake(getX() - _bodyImage->getFrameWidth() / 2, getY() - _bodyImage->getFrameHeight() / 2, 500 + _bodyImage->getFrameWidth() / 2, _bodyImage->getFrameHeight());
	}

	_bodyImage->setX(getEnemyRC().left);
	_bodyImage->setY(getEnemyRC().top);
	_armImage->setX(getEnemyRC().left);
	_armImage->setY(getEnemyRC().top);

	if (_actionCount > 2800) _actionCount = 0;
	// 일정시간 지나면 적 이동
	//if (_actionCount < 200)
	//{
	//	_enemyStatus = WALK_LEFT;
	//	_isLeft = true;
	//}
	//else if (_actionCount > 200 && _actionCount < 400)
	//{
	//	_enemyStatus = WALK_RIGHT;
	//	_isLeft = false;
	//}
	//else if (_actionCount > 400 && _actionCount < 600)
	//{
	//	_enemyStatus = IDLE_LEFT;
	//	_isLeft = true;
	//}
	//else if (_actionCount > 600 && _actionCount < 800)
	//{
	//	_enemyStatus = IDLE_RIGHT;
	//	_isLeft = false;
	//}
	//else if (_actionCount > 800 && _actionCount < 1000)
	//{
	//	_enemyStatus = WARNING_LEFT;
	//	_isLeft = true;
	//}
	//else if (_actionCount > 1000 && _actionCount < 1200)
	//{
	//	_enemyStatus = WARNING_RIGHT;
	//	_isLeft = false;
	//}
	//else if (_actionCount > 1200 && _actionCount < 1400)
	//{
	//	_enemyStatus = FIRE_LEFT;
	//	_isLeft = true;
	//}
	//else if (_actionCount > 1400 && _actionCount < 1600)
	//{
	//	_enemyStatus = FIRE_RIGHT;
	//	_isLeft = false;
	//}
	//else if (_actionCount > 1600 && _actionCount < 1800)
	//{
	//	_enemyStatus = KNOCK_BACK_LEFT;
	//	_isLeft = true;
	//}
	//else if (_actionCount > 1800 && _actionCount < 2000)
	//{
	//	_enemyStatus = KNOCK_BACK_RIGHT;
	//	_isLeft = false;				
	//}
	//else if (_actionCount > 2000 && _actionCount < 2200)
	//{
	//	_enemyStatus = DEAD_LEFT;
	//	_isLeft = true;		
	//}
	//else if (_actionCount > 2200 && _actionCount < 2400)
	//{
	//	_enemyStatus = DEAD_RIGHT;
	//	_isLeft = false;
	//}
	
	
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
			if (_frameIndex2 < 0) _frameIndex2 = 0;
		}
		_bodyImage->setFrameX(6);
		_armImage->setFrameX(_frameIndex2);
	}
	else if (_enemyStatus == WARNING_RIGHT)
	{
		_bodyImage->setFrameY(2);
		_armImage->setFrameY(8);
		++_frameCount;
		if (_frameCount % COOLTIME == 0)
		{
			if (_frameIndex2 < 0) _frameIndex2 = 0;
			_frameIndex2++;
			if (_frameIndex2 > 6) _frameIndex2 = 6;
		}
		_bodyImage->setFrameX(10);
		_armImage->setFrameX(_frameIndex2);
	}
	else if (_enemyStatus == FIRE_LEFT)
	{
		_bodyImage->setFrameY(3);
		_armImage->setFrameY(1);
		++_frameCount;
		if (_frameCount % COOLTIME == 0)
		{
			if (_frameIndex2 > 3) _frameIndex2 = 3;
			_frameIndex2--;
			if (_frameIndex2 < 0) _frameIndex2 = 3;
		}
		_bodyImage->setFrameX(6);
		_armImage->setFrameX(_frameIndex2);
	}
	else if (_enemyStatus == FIRE_RIGHT)
	{
		_bodyImage->setFrameY(2);
		_armImage->setFrameY(0);
		++_frameCount;
		if (_frameCount % COOLTIME == 0)
		{
			if (_frameIndex2 < 0) _frameIndex2 = 0;
			_frameIndex2++;
			if (_frameIndex2 > 3) _frameIndex2 = 0;
		}
		_bodyImage->setFrameX(10);
		_armImage->setFrameX(_frameIndex2);
	}
	else if (_enemyStatus == KNOCK_BACK_RIGHT)
	{
		_bodyImage->setFrameY(5);
		//_armImage->setFrameY(0);
		++_frameCount;
		if (_frameCount % COOLTIME == 0)
		{
			if (_frameIndex < 0) _frameIndex = 0;
			_frameIndex++;
			if (_frameIndex > 9)
			{					
				_frameIndex = 0;
			};
		}
		_bodyImage->setFrameX(_frameIndex);
		//_armImage->setFrameX(_frameIndex2);
	}
	else if (_enemyStatus == KNOCK_BACK_LEFT)
	{
		_bodyImage->setFrameY(4);
		//_armImage->setFrameY(1);
		++_frameCount;
		if (_frameCount % COOLTIME == 0)
		{
			if (_frameIndex > 9) _frameIndex = 9;
			_frameIndex--;
			if (_frameIndex < 0)
			{						
				_frameIndex = 9;
			};
		}
		_bodyImage->setFrameX(_frameIndex);
		//_armImage->setFrameX(_frameIndex2);
	}
	else if (_enemyStatus == DEAD_RIGHT)
	{
		_bodyImage->setFrameY(12);
		_bodyImage->setFrameX(1);
		
	}
	else if (_enemyStatus == DEAD_LEFT)
	{
		_bodyImage->setFrameY(13);
		_bodyImage->setFrameX(1);		
	}

	if (_frameCount > 100) _frameCount = 0;	

	//===================================================================================================================================================

	// 느낌표 말풍선 애니메이션
	if (_isAlarm)
	{
		_warnSign->setFrameY(0);
		++_frameCount;
		if (_frameCount % 5 == 0)
		{
			++_frameIndex3;
			if (_frameIndex3 > 16) _frameIndex3 = 0;
			//_isAlarm = false;
		}
		_warnSign->setFrameX(_frameIndex3);
	}
}

void enemy::fireToPlayer()
{
}

void enemy::knockBackMove()
{
	// 넉백됐을때, 뒤로 날라감
	if (_enemyStatus == KNOCK_BACK_LEFT)
	{
		setX(getX() - _kbSpeed);
		_kbSpeed -= 0.5f;
		if (_kbSpeed < 0) _kbSpeed = 0;
	}	
	if (_enemyStatus == KNOCK_BACK_RIGHT)
	{
		setX(getX() + _kbSpeed);
		_kbSpeed -= 0.5f;
		if (_kbSpeed < 0) _kbSpeed = 0;
	}	
}
