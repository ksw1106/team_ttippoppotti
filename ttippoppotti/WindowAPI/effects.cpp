#include "stdafx.h"
#include "effects.h"
#include "mapData.h"

HRESULT effects::init(const char * imageName, int particleMax, bool isFrameImg)
{
	//이미지 초기화
	_imageName = imageName;
	//갯수 초기화
	_particleMax = particleMax;

	_isFrameImg = isFrameImg;

	_count = _index = 0;
	_animationSpeed = 3;
	_explosionCount = 0;
	_isParabola = false;
	_isExplosion = false;
	_isStaticAnim = false;

	for (int i = 0; i < _particleMax; i++)
	{
		tagParticle particle;
		ZeroMemory(&particle, sizeof(tagParticle));
		particle.particleImg = IMAGEMANAGER->findImage(_imageName);

		_vParticle.push_back(particle);
	}
	return S_OK;
}

void effects::release(void)
{
}

void effects::update(void)
{
	if (_isRunning)
	{
		this->boomExplosion();
		this->boomStaticAnim();
		this->boomParabola();
		this->collisionProcess();
		this->frameChange();
	}
	else
	{
		_explosionCount = 0;
	}
}

void effects::render(void)
{
	if (!_isRunning) return;
	//for (int i = 0; i < _vParticle.size(); ++i)
	for (int i = _vParticle.size() -1; i >= 0 ; --i)
	{
		if(!_vParticle[i].fire) continue;
		if (_isFrameImg)
			_vParticle[i].particleImg->frameRender(getMemDC(), _vParticle[i].rc.left - CAMERAMANAGER->getCamera().left, _vParticle[i].rc.top - CAMERAMANAGER->getCamera().top);
		else
			_vParticle[i].particleImg->render(getMemDC(), _vParticle[i].rc.left - CAMERAMANAGER->getCamera().left, _vParticle[i].rc.top - CAMERAMANAGER->getCamera().top);
	}
}

void effects::activateCartridge(float x, float y, bool isLeft)
{
	_isRunning = true;
	_isParabola = true;
	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		_vParticle[i].y = y + 32;
		_vParticle[i].x = x + 32;
		if (isLeft)
			_vParticle[i].angle = PI / 3;
		else //플레이어가 오른쪽을 바라보고 있을 때
			_vParticle[i].angle = PI - PI / 3;
		_vParticle[i].gravity = 0.0f;
		_vParticle[i].speed = RND->getFromFloatTo(8.0f, 13.0f);
		_vParticle[i].count = 0;
		if (_isFrameImg)
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
		else
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());

	}
}

void effects::activateExplosion(float x, float y)
{
	_isRunning = true;
	_isExplosion = true;
	
	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		_vParticle[i].angle = PI / _particleMax * (i + 1);
		_vParticle[i].gravity = 0.0f;
		_vParticle[i].x = x;
		_vParticle[i].y = y;
		_vParticle[i].speed = 9.0f;
		_vParticle[i].count = 0;
		if (_isFrameImg)
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
		else
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());

	}
}
void effects::boomExplosion()
{
	//_explosionCount++;
	if (_isExplosion)
	{
		for (int i = 0; i < _vParticle.size(); ++i)
		{
			if (!_vParticle[i].fire) continue;
			_vParticle[i].gravity += 0.07f;
			_vParticle[i].x += cosf(_vParticle[i].angle) * _vParticle[i].speed;
			_vParticle[i].y += -sinf(_vParticle[i].angle) * _vParticle[i].speed + _vParticle[i].gravity;
			if (_isFrameImg)
				_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
			else
				_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());


			_vParticle[i].count++;

			if (_vParticle[i].count == 300 || _vParticle[i].y - CAMERAMANAGER->getCamera().top >= WINSIZEY || _vParticle[i].speed < 0.5f)
			{
				_vParticle[i].fire = false;
				_isRunning = false;
				_isParabola = false;
			}
		}
	}
}

void effects::activateBulletPuff(float x, float y)
{
	_isRunning = true;
	_isStaticAnim = true;
	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		_index = _count = 0;
		_vParticle[i].x = x;
		_vParticle[i].y = y;
		_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
	}
}

void effects::activateKnifePuff(float x, float y, bool isLeft)
{
	_isRunning = true;
	_isStaticAnim = true;
	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		_index = _count = 0;
		if (isLeft)
			_vParticle[i].x = x;
		else //플레이어 오른
			_vParticle[i].x = x + 89;
		_vParticle[i].y = y + 38;
		_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
	}
}

void effects::boomStaticAnim()
{
	if (_isStaticAnim)
	{
		for (int i = 0; i < _particleMax; i++)
		{
			if (_index >= _vParticle[i].particleImg->getMaxFrameX())
			{
				_vParticle[i].fire = false;
				_isRunning = false;
				_isStaticAnim = false;
				_vParticle[i].count = 0;
			}
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
		}
	}
}

void effects::activateBallExplosion(float x, float y)
{
	_isRunning = true;
	_isStaticAnim = true;

	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		_vParticle[i].x = x;
		_vParticle[i].y = y - _vParticle[i].particleImg->getFrameHeight() / 5;// * (i + 1);
		_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y,
			_vParticle[i].particleImg->getFrameWidth(),
			_vParticle[i].particleImg->getFrameHeight());
	}
}

void effects::activateParabola(float x, float y, float angle)
{
	_isRunning = true;
	_isParabola = true;
	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		if (angle == PI) //플레이어가 총알을 왼편으로 쐈을 때
			_vParticle[i].angle = PI + RND->getFromFloatTo(0.1f, 1.5f) - 0.75f;
		else if (angle == 0.0f) //플레이어 총알 오른
			_vParticle[i].angle = RND->getFromFloatTo(0.1f, 1.5f) - 0.75;
		else
			_vParticle[i].angle = angle;
		_vParticle[i].gravity = 0.0f;
		_vParticle[i].x = x;
		_vParticle[i].y = y;
		_vParticle[i].speed = RND->getFromFloatTo(1.0f, 20.0f);
		_vParticle[i].count = 0;
		if (_isFrameImg)
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(),	_vParticle[i].particleImg->getFrameHeight());
		else
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
	}
}

void effects::boomParabola()
{
	//돌무더기, 피, 탄피, 나무파편
	if (_isParabola)
	{
		for (int i = 0; i < _vParticle.size(); ++i)
		{
			if (!_vParticle[i].fire) continue;

			_vParticle[i].gravity += 0.55f;
			_vParticle[i].x += cosf(_vParticle[i].angle) * _vParticle[i].speed;
			_vParticle[i].y += -sinf(_vParticle[i].angle) * _vParticle[i].speed + _vParticle[i].gravity;
			if (_isFrameImg)
				_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
			else
				_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());

			_vParticle[i].count++;

			if (_vParticle[i].count == 500 || _vParticle[i].y - CAMERAMANAGER->getCamera().top >= WINSIZEY || _vParticle[i].speed < 1.5f)
			{
				_vParticle[i].fire = false;
				_isRunning = false;
				_isParabola = false;
			}
		}
	}
}

void effects::collisionProcess()
{
	if (_isParabola)
	{
		for (int i = 0; i < _vParticle.size(); ++i)
		{
			if (COLLISIONMANAGER->pixelCollision(_vParticle[i].rc, _vParticle[i].x, _vParticle[i].y, _vParticle[i].speed, _vParticle[i].gravity, 3)) //아래
			{
				_vParticle[i].gravity = 0;
				_vParticle[i].angle = PI2 - _vParticle[i].angle;
				_vParticle[i].speed *= 0.8;
			}
			if (COLLISIONMANAGER->pixelCollision(_vParticle[i].rc, _vParticle[i].x, _vParticle[i].y, _vParticle[i].speed, _vParticle[i].gravity, 2)) //오
			{
				_vParticle[i].angle = PI - _vParticle[i].angle;
				_vParticle[i].speed *= 0.8;
			}
			if (COLLISIONMANAGER->pixelCollision(_vParticle[i].rc, _vParticle[i].x, _vParticle[i].y, _vParticle[i].speed, _vParticle[i].gravity, 0)) //왼
			{
				_vParticle[i].angle = PI - _vParticle[i].angle;
				_vParticle[i].speed *= 0.8;
			}
			if (COLLISIONMANAGER->pixelCollision(_vParticle[i].rc, _vParticle[i].x, _vParticle[i].y, _vParticle[i].speed, _vParticle[i].gravity, 1)) //위
			{
				_vParticle[i].angle = PI2 - _vParticle[i].angle;
				_vParticle[i].speed *= 0.8;
			}
		}
	}
}

void effects::frameChange()
{
	image* img = IMAGEMANAGER->findImage(_imageName);
	FRAMEMANAGER->frameChange(img, _count, _index, _animationSpeed, false);
}
