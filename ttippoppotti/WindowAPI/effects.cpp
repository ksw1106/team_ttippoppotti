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
	_animationSpeed = 2;
	_explosionCount = 0;
	_alpha = 0;

	_isParabola = false;
	_isExplosion = false;
	_isStaticAnim = false;
	_isFlyingFlies = false;
	_isAshes = false;
	_isAlphaImg = false;
	_isBigBang = false;

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
		this->boomBigBang();
		this->boomFlyingFlies();
		this->boomAshes();
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
		{
			if (_isAlphaImg)
				_vParticle[i].particleImg->alphaRender(getMemDC(), _vParticle[i].rc.left - CAMERAMANAGER->getCamera().left, _vParticle[i].rc.top - CAMERAMANAGER->getCamera().top, _vParticle[i].alpha);
			else
			_vParticle[i].particleImg->render(getMemDC(), _vParticle[i].rc.left - CAMERAMANAGER->getCamera().left, _vParticle[i].rc.top - CAMERAMANAGER->getCamera().top);
		}
	}
}

void effects::activateCartridge(float x, float y, bool isLeft)
{
	_isRunning = true;
	_isParabola = true;
	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		_vParticle[i].x = x + 32;
		_vParticle[i].y = y + 32;
		if (isLeft)
			_vParticle[i].angle = PI / 3;
		else //플레이어가 오른쪽을 바라보고 있을 때
			_vParticle[i].angle = PI - PI / 3;
		_vParticle[i].gravity = 0.0f;
		_vParticle[i].speed = RND->getFromFloatTo(10.f, 13.0f);
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
		_vParticle[i].speed = 8.0f;
		if (_isFrameImg)
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
		else
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());

	}
}
void effects::boomExplosion()
{
	if (_isExplosion)
	{
		for (int i = 0; i < _vParticle.size(); ++i)
		{
			if (!_vParticle[i].fire) continue;
			if (_isFrameImg)
				_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
			else
				_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
			_vParticle[i].count++;
			if (_vParticle[i].count >= 100)
			{
 				_vParticle[i].fire = false;
				_isRunning = false;
				_isParabola = false;
				_vParticle[i].count = 0;
			}
			else
			{
				_vParticle[i].gravity += 0.07f;
				_vParticle[i].x += cosf(_vParticle[i].angle) * _vParticle[i].speed;
				_vParticle[i].y += - sinf(_vParticle[i].angle) * _vParticle[i].speed + _vParticle[i].gravity;
			}
		}
	}
}

void effects::activateLoopAnim(float x, float y)
{
	_isRunning = true;
	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		_animationSpeed = 2;
		_vParticle[i].x = x;
		_vParticle[i].y = y;
		_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
	}
}

void effects::activateEllipsePuff(float x, float y)
{
	_isRunning = true;
	_isStaticAnim = true;
	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		_vParticle[i].index = _count = 0;
		_animationSpeed = 0;
		_vParticle[i].x = x;
		_vParticle[i].y = y;
		_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
	}
}

void effects::activateEllipsePuff(float x, float y, bool isLeft)
{
	_isRunning = true;
	_isStaticAnim = true;
	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		_vParticle[i].index = _count = 0;
		if (isLeft)
			_vParticle[i].x = x;
		else //플레이어 오른
			_vParticle[i].x = x + 89;
		_vParticle[i].y = y + 38;
		_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
	}
}

void effects::activateBigBang(float x, float y)
{
	_isRunning = true;
	_isBigBang = true;	
	_isAlphaImg = true;

	_vParticle.clear();
	int particleMax = RND->getFromIntTo(4, 6);

	tagParticle particle;
	ZeroMemory(&particle, sizeof(tagParticle));
	for (int i = 8; i > 0; i--)
	{
		for (int j = 0; j < particleMax; j++)
		{
			particle.particleImg = IMAGEMANAGER->findImage(("explosionFlame" + to_string(i)));
			_vParticle.push_back(particle);
			particle.particleImg = IMAGEMANAGER->findImage(("explosionFlame" + to_string(i)));
			_vParticle.push_back(particle);
		}
	}
	float gravity = 0;
	for (int i = 0; i < _vParticle.size(); i += particleMax)
	{
		for (int j = 0; j < particleMax || i + j < _vParticle.size(); ++j)
		{

			_vParticle[i + j].fire = true;
			_vParticle[i + j].alpha = 0;
			_vParticle[i + j].count = 0;
			_vParticle[i + j].angle = PI / particleMax * (((i + j) % particleMax) + 1);
			//_vParticle[i + j].gravity = ((i+j) % particleMax) + 1;
			_vParticle[i + j].speed = 4.5f * ((i + j) + 1) + RND->getFloat(2.0f);
			_vParticle[i + j].fireX = x;
			_vParticle[i + j].fireY = y;
			_vParticle[i + j].x = _vParticle[i + j].fireX + cosf(_vParticle[i + j].angle) * _vParticle[i + j].speed;
			if (i > 0)
				_vParticle[i + j].y = _vParticle[i - 1].y - sinf(_vParticle[i + j].angle) * _vParticle[i + j].speed + gravity;
			else
				_vParticle[i + j].y = _vParticle[i + j].fireY - sinf(_vParticle[i + j].angle) * _vParticle[i + j].speed + gravity;
			if (_isFrameImg)
				_vParticle[i + j].rc = RectMakeCenter(_vParticle[i + j].x, _vParticle[i + j].y, _vParticle[i + j].particleImg->getFrameWidth(), _vParticle[i + j].particleImg->getFrameHeight());
			else
				_vParticle[i + j].rc = RectMakeCenter(_vParticle[i + j].x, _vParticle[i + j].y, _vParticle[i + j].particleImg->getWidth(), _vParticle[i + j].particleImg->getHeight());
		}
		gravity += 0.85;
	}
}

void effects::boomBigBang()
{
	if (_isBigBang)
	{
		for (int i = 0; i < _vParticle.size(); ++i)
		{
			if (!_vParticle[i].fire) continue;
			_vParticle[i].count++;
			if (_vParticle[i].count % 2 == 0)
			{
				if (_vParticle[i].alpha >= 255)
				{
					_vParticle[i].alpha = 255;
					if (_vParticle[i].count > 10)
					{
						_imageName = "smoke1";
						//_imageName = ("smoke" + to_string(RND->getFromIntTo(1, 2)));
						_vParticle[i].particleImg = IMAGEMANAGER->findImage(_imageName);
						if (!_isFrameImg)
						{
							_vParticle[i].index = 0;
							_isFrameImg = true;
						}
						else
						{
							if (_vParticle[i].index >= _vParticle[i].particleImg->getMaxFrameX())
							{
								_vParticle[i].fire = false;
								_explosionCount++;
							}
						}
					}
				}
				else
					_vParticle[i].alpha += 15;
			}
			if (_explosionCount >= _vParticle.size())
			{
				_isRunning = false;
				_isBigBang = false;
				_vParticle[i].count = 0;
				_explosionCount = 0;
			}
			if (_isFrameImg)
				_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
			else
				_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
		}
	}
}

void effects::boomStaticAnim()
{
	if (_isStaticAnim)
	{
		for (int i = 0; i < _particleMax; i++)
		{
			if (_vParticle[i].index >= _vParticle[i].particleImg->getMaxFrameX())
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

void effects::activateParabola(float x, float y, bool isLeft)
{
	_isRunning = true;
	_isParabola = true;
	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		if (isLeft) //플레이어 왼
			_vParticle[i].angle = PI + RND->getFromFloatTo(0.1f, 1.5f) - 0.75f;
		else //플레이어 오
			_vParticle[i].angle = RND->getFromFloatTo(0.1f, 1.5f) - 0.75;
		_vParticle[i].gravity = 0.0f;
		_vParticle[i].x = x + 32;
		_vParticle[i].y = y + 32;
		_vParticle[i].speed = RND->getFromFloatTo(5.0f, 20.0f);
		_animationSpeed = 5;
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
			if (_vParticle[i].count % 2 == 0)
			{
				if (_animationSpeed < 50)
				{
					_animationSpeed++;
				}
			}
			if (_vParticle[i].count == 500 || _vParticle[i].y - CAMERAMANAGER->getCamera().top >= WINSIZEY || _vParticle[i].speed < 1.5f)
			{
				_vParticle[i].fire = false;
				_isRunning = false;
				_isParabola = false;
			}
		}
	}
}

void effects::activateFlyingFlies(float x, float y)
{
	_isRunning = true;
	_isFlyingFlies = true;
	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		_vParticle[i].angle = RND->getFloat(PI2);
		_vParticle[i].x = x + RND->getFromFloatTo(5.0f, 10.0f) - 10.0f;
		_vParticle[i].y = y + RND->getFromFloatTo(2.0f, 10.0f) - 10.0f;
		_vParticle[i].speed = RND->getFromFloatTo(1.0f, 2.0f);
		_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
	}
}

void effects::boomFlyingFlies()
{
	if (_isFlyingFlies)
	{
		for (int i = 0; i < _vParticle.size(); ++i)
		{
			if (!_vParticle[i].fire) continue;

			_vParticle[i].x += cosf(_vParticle[i].angle + RND->getFloat(2.0f)) * _vParticle[i].speed;
			_vParticle[i].y += -sinf(_vParticle[i].angle + RND->getFloat(2.0f)) * _vParticle[i].speed;
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
			_vParticle[i].count++;
			if (_vParticle[i].count % 5 == 0)
				_vParticle[i].angle = (i < _vParticle.size() / 2)? _vParticle[i].angle + RND->getFloat(PI_4) : _vParticle[i].angle - RND->getFloat(PI_4);
		}
	}
}

void effects::activateAshes(float x, float y)
{
	_isRunning = true;
	_isAshes = true;
	_isAlphaImg = true;
	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		_vParticle[i].angle = RND->getFloat(PI);
		_vParticle[i].x = x + RND->getFloat(50.0f);
		_vParticle[i].y = y ;
		_vParticle[i].speed = RND->getFromFloatTo(1.0f, 15.0f);
		_vParticle[i].alpha = 255;
		_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
	}
}

void effects::boomAshes()
{
	if (_isAshes)
	{
		for (int i = 0; i < _vParticle.size(); ++i)
		{
			if (!_vParticle[i].fire) continue;

			_vParticle[i].x += cosf(_vParticle[i].angle + RND->getFloat(PI) - PI_2) * _vParticle[i].speed;
			_vParticle[i].y += -sinf(_vParticle[i].angle + RND->getFloat(PI) - PI_2) * _vParticle[i].speed;
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
			//_vParticle[i].angle = RND->getFloat(PI);

			if (_vParticle[i].count >= 100)
			{
				_vParticle[i].fire = false;
				_isRunning = false;
				_vParticle[i].count = 0;
			}
			else
				_vParticle[i].count++;

			if (_vParticle[i].alpha <= 8)
				_vParticle[i].fire = false;
			else
				_vParticle[i].alpha = (i < _vParticle.size() / 2) ? _vParticle[i].alpha - RND->getInt(8) : _vParticle[i].alpha - RND->getInt(12);
		}
	}
}

void effects::collisionProcess()
{
	if (_isParabola)
	{
		for (int i = 0; i < _vParticle.size(); ++i)
		{
			if (COLLISIONMANAGER->pixelCollision(_vParticle[i].rc, _vParticle[i].x, _vParticle[i].y, _vParticle[i].speed, _vParticle[i].gravity, 3) == GREEN) //아래
			{
				_vParticle[i].gravity = 0;
				_vParticle[i].angle = PI2 - _vParticle[i].angle;
				_vParticle[i].y -= _vParticle[i].rc.bottom - _vParticle[i].rc.top;
				_vParticle[i].speed *= 0.9;
			}
			else if (COLLISIONMANAGER->pixelCollision(_vParticle[i].rc, _vParticle[i].x, _vParticle[i].y, _vParticle[i].speed, _vParticle[i].gravity, 1) == GREEN) //위
			{
				_vParticle[i].angle = PI2 - _vParticle[i].angle;
				_vParticle[i].y += _vParticle[i].rc.bottom - _vParticle[i].rc.top;
				_vParticle[i].speed *= 0.9;
			}
			if (COLLISIONMANAGER->pixelCollision(_vParticle[i].rc, _vParticle[i].x, _vParticle[i].y, _vParticle[i].speed, _vParticle[i].gravity, 2) == GREEN) //오
			//if (COLLISIONMANAGER->pixelCollision(_vParticle[i].rc, _vParticle[i].x, _vParticle[i].y, 1, _vParticle[i].gravity, 2) == GREEN) //오
			{
				_vParticle[i].angle = PI - _vParticle[i].angle;
				_vParticle[i].x -= _vParticle[i].rc.right - _vParticle[i].rc.left;
				_vParticle[i].speed *= 0.9;
			}
			else if (COLLISIONMANAGER->pixelCollision(_vParticle[i].rc, _vParticle[i].x, _vParticle[i].y, _vParticle[i].speed, _vParticle[i].gravity, 0) == GREEN) //왼
			//else if (COLLISIONMANAGER->pixelCollision(_vParticle[i].rc, _vParticle[i].x, _vParticle[i].y, 1, _vParticle[i].gravity, 0) == GREEN) //왼
			{
				_vParticle[i].angle = PI - _vParticle[i].angle;
				_vParticle[i].x += _vParticle[i].rc.right - _vParticle[i].rc.left;
				_vParticle[i].speed *= 0.9;
			}
		}
	}
}

void effects::frameChange()
{
	image* img = IMAGEMANAGER->findImage(_imageName);
	for (int i = 0; i < _vParticle.size(); ++i)
		FRAMEMANAGER->frameChange(img, _count, _vParticle[i].index, _animationSpeed, false);
}
