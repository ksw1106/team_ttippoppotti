#include "stdafx.h"
#include "dog.h"

HRESULT dog::initDog(float x, float y, bool isLeft)
{
	ZeroMemory(&_dog, sizeof(tagDog));	
	_dog.dogImage[D_IDLE] = IMAGEMANAGER->findImage("군견평상시");
	_dog.dogImage[D_ATTACK] = IMAGEMANAGER->findImage("군견공격");
	_dog.dogImage[D_KNOCK_BACK] = IMAGEMANAGER->findImage("군견넉백");
	_dog.dogImage[D_DEAD] = IMAGEMANAGER->findImage("군견시체");
	_dog.fspeed = 3;
	_dog.count = 1;
	_dog.isLeft = isLeft;
	
	this->corpseInit();

	if (isLeft)
		_dog.angle = PI;
	else
		_dog.angle = 0.f;

	_dog.speed = 8.f;
	_dog.kbSpeed = 20.f;
	_dog.x = x;
	_dog.y = y;	
	_dog.isAlive = true;
	_dog.hp = 10;
	_dogStatus = D_IDLE;	
	
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

	_warnFrameIndex = _doubtFrameIndex = 0;
	_warnFrameCount = _doubtFrameCount = 0;
	_warnDelay = 50;
	_warnCount = 0;

	_frameSpeed = 5;
	_isUncovered = false;
	_isStrange = false;

	return S_OK;
}

void dog::release(void)
{
	_warnSign->release();
	SAFE_DELETE(_warnSign);
	_doubtSign->release();
	SAFE_DELETE(_doubtSign);
}

void dog::update(void)
{
	this->dogFall();
	this->dogAI();

	if (_dog.isAlive)
	{
		dogActionChange();
	}
	else
	{
		this->dogDie();
	}

	if (_dog.hp <= 0)
	{
		_dog.isApart = true;
		if (_dog.isApart)
		{
			this->partMove();
		}
	}
	
	this->frameAnimate();
	
	// 몸통 렉트
	_dog.rc = RectMake(_dog.x, _dog.y, _dog.dogImage[_dogStatus]->getFrameWidth(), _dog.dogImage[_dogStatus]->getFrameHeight());
	// 시야 렉트
	if (_dog.isLeft)
		_dog.rcSight = RectMake(_dog.x - 500, _dog.y, 500, _dog.dogImage[_dogStatus]->getFrameHeight());
	else
		_dog.rcSight = RectMake(_dog.x + _dog.dogImage[_dogStatus]->getFrameWidth(), _dog.y, 500, _dog.dogImage[_dogStatus]->getFrameHeight());
	// 공격반경 렉트
	_dog.rcAttackRange = RectMake(_dog.x - 20, _dog.y - 20, _dog.x + _dog.dogImage[_dogStatus]->getFrameWidth() + 20, _dog.dogImage[_dogStatus]->getFrameHeight() + 20);

	// 시체상태가 아닐때, 렉트 움직임
	for (int i = 0; i < BODY_PART; ++i)
	{
		if (!_dog.isApart)
		{
			_corpse[i].x = _dog.x;
			_corpse[i].y = _dog.y;
			_corpse[i].rcCorpse = RectMake(_corpse[i].x, _corpse[i].y, _corpse[i].corpseImage->getWidth(), _corpse[i].corpseImage->getHeight());
		}
	}
}

void dog::render(void)
{	
	if (!_dog.isApart)
	{
		_dog.dogImage[_dogStatus]->frameRender(getMemDC(), _dog.x - CAMERAMANAGER->getCamera().left, _dog.y - CAMERAMANAGER->getCamera().top, _dog.dogImage[_dogStatus]->getFrameX(), _dog.dogImage[_dogStatus]->getFrameY());
	}
	else
	{
		for (int i = 0; i < BODY_PART; ++i)
		{
			_corpse[i].corpseImage->render(getMemDC(), _corpse[i].x - CAMERAMANAGER->getCamera().left, _corpse[i].y - CAMERAMANAGER->getCamera().top);
		}
	}

	// 플레이어 발견했을때, 느낌표 말풍선!
	if (_isUncovered && _warnFrameIndex < _warnSign->getMaxFrameX())
	{
		_warnSign->frameRender(getMemDC(), _dog.x + 10 - CAMERAMANAGER->getCamera().left, _dog.y - 50 - CAMERAMANAGER->getCamera().top, _warnSign->getFrameX(), _warnSign->getFrameY());
	}

	// 적 (아군) 시체를 발견했을때 물음표 말풍선!
	if (_isStrange && _doubtFrameIndex < _doubtSign->getMaxFrameX())
	{
		_doubtSign->frameRender(getMemDC(), _dog.x + 10 - CAMERAMANAGER->getCamera().left, _dog.y - 50 - CAMERAMANAGER->getCamera().top, _doubtSign->getFrameX(), _doubtSign->getFrameY());
	}
}

void dog::corpseInit()
{
	for (int i = 0; i < BODY_PART; ++i)
	{
		if (!_dog.isLeft)
		{
			_corpse[i].angle = RND->getFromFloatTo(PI / 2 + 0.2f, PI - 0.2f);
		}
		else
		{
			_corpse[i].angle = RND->getFromFloatTo(0.2f, PI / 2 - 0.2f);
		}
		_corpse[i].speed = RND->getFromFloatTo(6.f, 9.f);
		_corpse[i].gravity = 0.0f;
		_corpse[i].corpseImage = new image;
	}
	_corpse[0].corpseImage->init("enemyImage/dog_part_head.bmp", 32, 29, true, RGB(255, 0, 255));
	_corpse[1].corpseImage->init("enemyImage/dog_part_body.bmp", 40, 35, true, RGB(255, 0, 255));
	_corpse[2].corpseImage->init("enemyImage/dog_part_arm.bmp", 16, 32, true, RGB(255, 0, 255));
	_corpse[3].corpseImage->init("enemyImage/dog_part_leg.bmp", 28, 24, true, RGB(255, 0, 255));
}

void dog::dogActionChange()
{
	if (_dogStatus == D_IDLE)
	{
		
	}
	else if (_dogStatus == D_ATTACK)
	{
		dogAttack(_dog.isLeft);
	}
	else if (_dogStatus == D_KNOCK_BACK)
	{
		this->knockBackMove(_dog.isLeft);
	}
	else
	{
		this->deadMove();
	}
}

void dog::dogAI()
{
	if (_isUncovered)
	{
		++_warnCount;
		if (_warnCount > _warnDelay)
		{
			_dog.isAttack = true;
		}
	}

	if (_dog.isAttack)
	{
		_dogStatus = D_ATTACK;
	}
}

void dog::dogFall()
{
	// 떨어질때, 아닐떄
	if (!_dog.isOn)
	{
		if (_dog.gravity < 3.0f) _dog.gravity = 3.0f;
		_dog.y += -sinf(_dog.angle)*_dog.speed + _dog.gravity;
		_dog.gravity += 0.5f;
	}
	else
	{
		_dog.gravity = 0;
	}
}

void dog::dogDie()
{
	
}

void dog::dogAttack(bool isleft)
{
	if (_dog.isNear)
	{
		
	}
	else
	{
		if (isleft)
			_dog.x -= _dog.speed;
		else
			_dog.x += _dog.speed;
	}
	
}

void dog::knockBackMove(bool bulletLeft)
{
	if (_dog.kbSpeed > 0)
	{
		if (bulletLeft)
		{
			_dog.angle = PI - 0.4f;
		}
		else
		{
			_dog.angle = 0.4f;
		}
		_dog.x += cosf(_dog.angle)*_dog.kbSpeed;
		_dog.y += -sinf(_dog.angle)*_dog.kbSpeed;
		_dog.kbSpeed -= 0.5f;
	}
}

void dog::partMove()
{
	for (int i = 0; i < 4; ++i)
	{
		_corpse[i].x += cosf(_corpse[i].angle) * _corpse[i].speed;
		_corpse[i].y += -sinf(_corpse[i].angle) * _corpse[i].speed + _corpse[i].gravity;
		_corpse[i].gravity += 0.4f;
		_corpse[i].speed -= 0.2f;
		_corpse[i].rcCorpse = RectMake(_corpse[i].x, _corpse[i].y, _corpse[i].corpseImage->getWidth(), _corpse[i].corpseImage->getHeight());

		if (_corpse[i].speed <= 0.f) _corpse[i].speed = 0;
	}
}

void dog::deadMove()
{
	if (_dog.isLeft)
	{
		_dog.angle = PI;
	}
	else
	{
		_dog.angle = 0.f;
	}
	_dog.x += cosf(_dog.angle)* _dog.speed;
	_dog.y += -sinf(_dog.angle)* _dog.speed;

}

void dog::frameAnimate()
{
	if (_dogStatus == D_KNOCK_BACK)
	{
		_dog.fspeed = 2;

		if (_dog.isLeft)
		{
			if (_dog.index <= 0)
			{
				_dogStatus = D_DEAD;
			}
		}
		else
		{
			if (_dog.index >= _dog.dogImage[D_KNOCK_BACK]->getMaxFrameX())
			{
				_dogStatus = D_DEAD;
			}
		}

		FRAMEMANAGER->frameChange(_dog.dogImage[_dogStatus], _dog.count, _dog.index, _dog.fspeed, _dog.isLeft);
	}
	else
	{
		FRAMEMANAGER->frameChange(_dog.dogImage[_dogStatus], _dog.count, _dog.index, _dog.fspeed, _dog.isLeft);
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
