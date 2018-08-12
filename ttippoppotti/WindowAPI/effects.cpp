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
	_explosionCount = _bigBangCount = 0;
	_isLeft = false;
	_alpha = 0;

	_isParabola = false;
	_isParabolaNoCollision = false;
	_isExplosion = false;
	_isStaticAnim = false;
	_isFlyingFlies = false;
	_isAshes = false;
	_isAlphaImg = false;
	_isBigBang = false;
	_isMissileTrail = false;
	_isMissilePuff = false;

	for (int i = 0; i < _particleMax; i++)
	{
		tagParticle particle;
		ZeroMemory(&particle, sizeof(tagParticle));
		particle.particleImg = IMAGEMANAGER->findImage(_imageName);
		particle.isFrameImg = isFrameImg;

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
		this->boomParabolaNoCollision();
		this->boomBigBang();
		this->boomMissileTrail();
		this->boomMissilePuff();
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
	for (int i = 0; i < _vParticle.size(); ++i)
		//for (int i = _vParticle.size() - 1; i >= 0; --i)
	{
		if (CAMERAMANAGER->CameraIn(_vParticle[i].rc))
		{
			if (!_vParticle[i].fire) continue;

			if (_vParticle[i].isFrameImg)
			{
				if (_vParticle[i].isAlphaImg)
					_vParticle[_vParticle.size() - 1 - i].particleImg->alphaFrameRender(getMemDC(), _vParticle[i].rc.left - CAMERAMANAGER->getCamera().left, _vParticle[i].rc.top - CAMERAMANAGER->getCamera().top, _vParticle[_vParticle.size() - 1 - i].alpha);
				else
					_vParticle[_vParticle.size() - 1 - i].particleImg->frameRender(getMemDC(), _vParticle[i].rc.left - CAMERAMANAGER->getCamera().left, _vParticle[i].rc.top - CAMERAMANAGER->getCamera().top);
			}
			else
			{
				if (_vParticle[i].isAlphaImg)
					_vParticle[i].particleImg->alphaRender(getMemDC(), _vParticle[i].rc.left - CAMERAMANAGER->getCamera().left, _vParticle[i].rc.top - CAMERAMANAGER->getCamera().top, _vParticle[_vParticle.size() - 1 - i].alpha);
				else
					_vParticle[i].particleImg->render(getMemDC(), _vParticle[i].rc.left - CAMERAMANAGER->getCamera().left, _vParticle[i].rc.top - CAMERAMANAGER->getCamera().top);
			}
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
		_vParticle[i].x = x + 130 / 2;
		_vParticle[i].y = y + 105 / 2;
		if (isLeft)
			_vParticle[i].angle = PI / 3;
		else //플레이어가 오른쪽을 바라보고 있을 때
			_vParticle[i].angle = PI - PI / 3;
		_vParticle[i].gravity = 0.0f;
		_vParticle[i].speed = RND->getFromFloatTo(10.f, 13.0f);
		_vParticle[i].index = RND->getInt(3);
		_vParticle[i].count = 0;
		if (_vParticle[i].isFrameImg)
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
		if (_vParticle[i].isFrameImg)
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
			if (_vParticle[i].isFrameImg)
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
				_vParticle[i].y += -sinf(_vParticle[i].angle) * _vParticle[i].speed + _vParticle[i].gravity;
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

	_animationSpeed = 5;
	_vParticle.clear();
	int particleMax = RND->getFromIntTo(4, 6);

	tagParticle particle;
	ZeroMemory(&particle, sizeof(tagParticle));
	for (int i = 8; i > 0; i--)
		//for (int i = 1; i <= 8; i++)
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
	//for (int i = _vParticle.size()-1; i >= 0; i -= particleMax)
	//for (int i = 0; i < _vParticle.size(); i += particleMax)
	//{
	//	for (int j = 0; i + j < _vParticle.size(); ++j)
	//	{
	//		if (j >= particleMax) break;
	//
	//		_vParticle[i + j].fire = true;
	//		_vParticle[i + j].alpha = (i % particleMax) + 1;
	//		_vParticle[i + j].count = 0;
	//		_vParticle[i + j].angle = PI / particleMax * (((i + j) % particleMax) + 1);
	//		//_vParticle[i + j].gravity = ((i+j) % particleMax) + 1;
	//		_vParticle[i + j].speed = 4.0f * ((i + j) + 1) + RND->getFloat(2.0f);
	//		_vParticle[i + j].fireX = x;
	//		_vParticle[i + j].fireY = y;
	//		_vParticle[i + j].x = _vParticle[i + j].fireX + cosf(_vParticle[i + j].angle) * _vParticle[i + j].speed;
	//		if (i > 0)
	//			_vParticle[i + j].y = _vParticle[i - 1].y - sinf(_vParticle[i + j].angle) * _vParticle[i + j].speed + gravity;
	//		else
	//			_vParticle[i + j].y = _vParticle[i + j].fireY - sinf(_vParticle[i + j].angle) * _vParticle[i + j].speed + gravity;
	//
	//		if (_vParticle[i].isFrameImg)
	//			_vParticle[i + j].rc = RectMakeCenter(_vParticle[i + j].x, _vParticle[i + j].y, _vParticle[i + j].particleImg->getFrameWidth(), _vParticle[i + j].particleImg->getFrameHeight());
	//		else
	//			_vParticle[i + j].rc = RectMakeCenter(_vParticle[i + j].x, _vParticle[i + j].y, _vParticle[i + j].particleImg->getWidth(), _vParticle[i + j].particleImg->getHeight());
	//	}
	//	gravity += 0.85;
	//}

	//for (int i = _vParticle.size()-1; i >= 0; i -= particleMax)
	for (int i = 0; i < _vParticle.size(); i += particleMax)
	{
		for (int j = 0; i + j < _vParticle.size(); ++j)
		{
			if (j >= particleMax) break;

			_vParticle[i + j].fire = true;
			_vParticle[i + j].alpha = 0;
			_vParticle[i + j].count = 0;
			_vParticle[i + j].angle = PI / particleMax * (((i + j) % particleMax) + 1);
			//_vParticle[i + j].gravity = ((i+j) % particleMax) + 1;
			_vParticle[i + j].speed = 5.0f * ((i + j) + 1) + RND->getFloat(2.0f);
			_vParticle[i + j].fireX = x;
			_vParticle[i + j].fireY = y;
			_vParticle[i + j].x = _vParticle[i + j].fireX + cosf(_vParticle[i + j].angle) * _vParticle[i + j].speed;
			if (i > 0)
				_vParticle[i + j].y = _vParticle[i - 1].y - sinf(_vParticle[i + j].angle) * _vParticle[i + j].speed + gravity;
			else
				_vParticle[i + j].y = _vParticle[i + j].fireY - sinf(_vParticle[i + j].angle) * _vParticle[i + j].speed + gravity;

			if (_vParticle[i].isFrameImg)
				_vParticle[i + j].rc = RectMakeCenter(_vParticle[i + j].x, _vParticle[i + j].y, _vParticle[i + j].particleImg->getFrameWidth(), _vParticle[i + j].particleImg->getFrameHeight());
			else
				_vParticle[i + j].rc = RectMakeCenter(_vParticle[i + j].x, _vParticle[i + j].y, _vParticle[i + j].particleImg->getWidth(), _vParticle[i + j].particleImg->getHeight());
		}
		gravity += 0.85;
	}

	//for (int i = 0; i < _vParticle.size(); i++)
	//{
	//	_vParticle[i].fire = true;
	//	_vParticle[i].alpha = 0;
	//	_vParticle[i].count = 0;
	//	_vParticle[i].angle = PI / particleMax * ((i % particleMax) + 1);
	//	//_vParticle[i].gravity = ((i+j) % particleMax) + 1;
	//	_vParticle[i].speed = 4.0f * (i + 1) + RND->getFloat(2.0f);
	//	_vParticle[i].fireX = x;
	//	_vParticle[i].fireY = y;
	//	_vParticle[i].x = _vParticle[i].fireX + cosf(_vParticle[i].angle) * _vParticle[i].speed;
	//	//_vParticle[i].y = _vParticle[i].fireY - sinf(_vParticle[i].angle) * _vParticle[i].speed + gravity;
	//	if (i > 0)
	//		_vParticle[i].y = _vParticle[i - 1].y - sinf(_vParticle[i].angle) * _vParticle[i].speed + gravity;
	//	else
	//		_vParticle[i].y = _vParticle[i].fireY - sinf(_vParticle[i].angle) * _vParticle[i].speed + gravity;
	//
	//	if (_vParticle[i].isFrameImg)
	//		_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
	//	else
	//		_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
	//	gravity += 2.85;
	//}
}

void effects::boomBigBang()
{
	if (_isBigBang)
	{
		//for (int i = _vParticle.size() - 1; i >= 0; i--)
		for (int i = 0; i < _vParticle.size(); i++)
		{
			if (!_vParticle[i].fire) continue;
			_vParticle[i].count += (i + 1) * 2;
			if (_vParticle[i].alpha >= 255)
			{
				_vParticle[i].alpha = 255;
				if (_vParticle[i].count > 1500)
				{
					string str;
					_imageName = "smoke1";
					//str = "smoke" + to_string(RND->getFromIntTo(1, 2));
					//_imageName = str.c_str();
					_vParticle[i].particleImg = IMAGEMANAGER->findImage(_imageName);
					if (!_vParticle[i].isFrameImg)
					{
						_vParticle[i].index = 0;
						_vParticle[i].isFrameImg = true;
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
			{
				if (_vParticle[i].count > _vParticle.size() * 2)
					_vParticle[i].alpha += (i % _particleMax + 1) * 25;
			}
			if (_explosionCount >= _particleMax)
			{
				_isRunning = false;
				_isBigBang = false;
				_vParticle[i].count = 0;
				_explosionCount = 0;
			}
			if (_vParticle[i].isFrameImg)
				_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
			else
				_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
		}
	}
}

void effects::activateMissileTrail(float x, float y, bool isLeft)
{
	_isRunning = true;
	_isMissileTrail = true;
	_isAlphaImg = true;
	_isLeft = isLeft;

	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		if (isLeft)
			_vParticle[i].angle = PI + PI_4;
		else
			_vParticle[i].angle = -PI_4;
		_vParticle[i].alpha = 255;
		_vParticle[i].fireX = x - _vParticle[i].particleImg->getFrameWidth();
		_vParticle[i].fireY = y - _vParticle[i].particleImg->getFrameHeight();
		_vParticle[i].speed = 50.0f;
		_vParticle[i].x = _vParticle[i].fireX - cosf(_vParticle[i].angle) * WINSIZEY;
		_vParticle[i].y = _vParticle[i].fireY + sinf(_vParticle[i].angle) * WINSIZEY;
		if (_vParticle[i].isFrameImg)
			_vParticle[i].rc = RectMake(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
		else
			_vParticle[i].rc = RectMake(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
	}
}

void effects::boomMissileTrail()
{
	if (_isMissileTrail)
	{
		for (int i = 0; i < _vParticle.size(); i++)
		{
			if (!_vParticle[i].fire) continue;
			if (_vParticle[i].x < _vParticle[i].fireX - _vParticle[i].speed)
				_vParticle[i].x += cosf(_vParticle[i].angle) * _vParticle[i].speed;
			else
				_vParticle[i].x = _vParticle[i].fireX;
			if (_vParticle[i].y < _vParticle[i].fireY - _vParticle[i].speed)
				_vParticle[i].y += -sinf(_vParticle[i].angle) * _vParticle[i].speed;
			else
			{
				_vParticle[i].y = _vParticle[i].fireY;
				_vParticle[i].alpha -= 25;
				if (_vParticle[i].alpha <= 25)
				{
					_isRunning = true;
					_isMissileTrail = true;
					_vParticle[i].fire = false;
				}
			}

			if (_vParticle[i].isFrameImg)
				_vParticle[i].rc = RectMake(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
			else
				_vParticle[i].rc = RectMake(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
		}
	}
}


void effects::activateMissilePuff(float x, float y, int speed, bool isLeft)
{
	_isRunning = true;
	_isMissilePuff = true;
	_isLeft = isLeft;

	_animationSpeed = 5;
	_vParticle.clear();
	tagParticle particle;
	ZeroMemory(&particle, sizeof(tagParticle));
	for (int i = 8; i > 2; i--)
		//for (int i = 1; i <= 8; i++)
	{
		particle.particleImg = IMAGEMANAGER->findImage(("explosionFlame" + to_string(i)));
		_vParticle.push_back(particle);
		particle.particleImg = IMAGEMANAGER->findImage(("explosionFlame" + to_string(i)));
		_vParticle.push_back(particle);
	}

	for (int i = 3; i > 0; i--)
	{
		particle.isFrameImg = true;
		particle.particleImg = IMAGEMANAGER->findImage(("smoke" + to_string(i)));
		_vParticle.push_back(particle);
		particle.particleImg = IMAGEMANAGER->findImage(("smoke" + to_string(i)));
		_vParticle.push_back(particle);
	}

	for (int i = 0; i < _vParticle.size(); i++)
	{
		_vParticle[i].fire = true;
		if (isLeft)
			_vParticle[i].angle = PI + PI_4;
		else
			_vParticle[i].angle = - PI_4;
		_vParticle[i].fireX = x;
		_vParticle[i].fireY = y;
		if (_vParticle[i].isFrameImg)
		{
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
			_vParticle[i].speed = _vParticle[i].particleImg->getFrameWidth() / 2 + (i + 1) * 0.8;
		}
		else
		{
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
			_vParticle[i].speed = _vParticle[i].particleImg->getWidth() / 2 + (i + 1) * 0.8;
		}
		if (i > 0)
		{
			_vParticle[i].x = _vParticle[i - 1].x - cosf(_vParticle[i].angle) * _vParticle[i].speed;
			_vParticle[i].y = _vParticle[i - 1].y + sinf(_vParticle[i].angle) * _vParticle[i].speed;
		}
		else
		{
			_vParticle[i].x = x - cosf(_vParticle[i].angle) * WINSIZEY;
			_vParticle[i].y = y + sinf(_vParticle[i].angle) * WINSIZEY;
		}
		_vParticle[i].speed = speed;

	}
}

void effects::boomMissilePuff()
{
	if (_isMissilePuff)
	{
		for (int i = 0; i < _vParticle.size(); i++)
		{
			if (!_vParticle[i].fire) continue;
			if (_vParticle[i].x < _vParticle[i].fireX)
				_vParticle[i].x += cosf(_vParticle[i].angle) * _vParticle[i].speed;
			else
				_vParticle[i].fire = false;
			if (_vParticle[i].y < _vParticle[i].fireY)
				_vParticle[i].y += -sinf(_vParticle[i].angle) * _vParticle[i].speed;
			else
			{
				_vParticle[i].fire = false;
				_isRunning = false;
				_isMissilePuff = false;
			}

			if (_vParticle[i].isFrameImg)
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
	_count = 0;
	_animationSpeed = 2;
	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		_vParticle[i].index = 0;
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
		_vParticle[i].oldY = _vParticle[i].y;
		_vParticle[i].speed = RND->getFromFloatTo(5.0f, 20.0f);
		_vParticle[i].index = RND->getInt(3);
		_animationSpeed = 0;
		_vParticle[i].count = 0;
		if (_vParticle[i].isFrameImg)
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
		else
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
	}
}

void effects::activateParabolaNoCollision(float x, float y, bool isLeft)
{
	_isRunning = true;
	_isParabolaNoCollision = true;
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
		_vParticle[i].oldY = _vParticle[i].y;
		_vParticle[i].speed = RND->getFromFloatTo(5.0f, 20.0f);
		_vParticle[i].index = RND->getInt(3);
		_animationSpeed = 0;
		_vParticle[i].count = 0;
		if (_vParticle[i].isFrameImg)
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
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
			if (_vParticle[i].isFrameImg)
				_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
			else
				_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());

			_vParticle[i].count++;
			if (_vParticle[i].count % 2 == 0)
			{
				if (_animationSpeed < 10)
				{
					_animationSpeed++;
				}
			}
			if (_vParticle[i].count == 500 || _vParticle[i].speed < 1.0f)
			{
				_vParticle[i].fire = false;
				_isRunning = false;
				_isParabola = false;
			}
		}
	}
}

void effects::boomParabolaNoCollision()
{
	if (_isParabolaNoCollision)
	{
		for (int i = 0; i < _vParticle.size(); ++i)
		{
			if (!_vParticle[i].fire) continue;

			_vParticle[i].gravity += 0.55f;
			_vParticle[i].x += cosf(_vParticle[i].angle) * _vParticle[i].speed;
			_vParticle[i].y += -sinf(_vParticle[i].angle) * _vParticle[i].speed + _vParticle[i].gravity;
			if (_vParticle[i].isFrameImg)
				_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
			else
				_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());

			_vParticle[i].count++;
			if (_vParticle[i].count % 2 == 0)
			{
				if (_animationSpeed < 10)
				{
					_animationSpeed++;
				}
			}
			if (_vParticle[i].count == 500)
			{
				_vParticle[i].fire = false;
				_isRunning = false;
				_isParabola = false;
			}
		}
	}
}

void effects::activateFountain(float x, float y)
{
	_isRunning = true;
	_isParabola = true;
	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		_vParticle[i].angle = PI_2 - RND->getFromFloatTo(0.1f, 0.8f) + 0.5f;
		_vParticle[i].gravity = 0.0f;
		_vParticle[i].x = x + 32;
		_vParticle[i].y = y + 32;
		_vParticle[i].speed = RND->getFromFloatTo(15.0f, 30.0f);
		_vParticle[i].index = RND->getInt(3);
		_animationSpeed = 5;
		_vParticle[i].count = 0;
		if (_vParticle[i].isFrameImg)
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
		else
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
	}
}

void effects::activateFountainNoCollision(float x, float y)
{
	_isRunning = true;
	_isParabolaNoCollision = true;
	for (int i = 0; i < _particleMax; i++)
	{
		_vParticle[i].fire = true;
		_vParticle[i].angle = PI_2 + RND->getFromFloatTo(0.1f, 1.0f) - 0.8f;
		_vParticle[i].gravity = 0.0f;
		_vParticle[i].x = x + 32;
		_vParticle[i].y = y + 32;
		_vParticle[i].speed = RND->getFromFloatTo(10.0f, 20.0f);
		_vParticle[i].index = RND->getInt(3);
		_animationSpeed = 5;
		_vParticle[i].count = 0;
		if (_vParticle[i].isFrameImg)
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getFrameWidth(), _vParticle[i].particleImg->getFrameHeight());
		else
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
	}
}

void effects::activateBlotch(float x, float y)
{

}

void effects::boomBlotch()
{

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
		_vParticle[i].speed = RND->getFromFloatTo(0.5f, 1.5f);
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

			_vParticle[i].x += cosf(_vParticle[i].angle + RND->getFloat(2.5f)) * _vParticle[i].speed;
			_vParticle[i].y += -sinf(_vParticle[i].angle + RND->getFloat(2.5f)) * _vParticle[i].speed;
			_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y, _vParticle[i].particleImg->getWidth(), _vParticle[i].particleImg->getHeight());
			_vParticle[i].count++;
			if (_vParticle[i].count % 5 == 0)
				_vParticle[i].angle = (i < _vParticle.size() / 2) ? _vParticle[i].angle + RND->getFloat(PI_4) : _vParticle[i].angle - RND->getFloat(PI_4);
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
		_vParticle[i].y = y;
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
				//_vParticle[i].angle = PI2 - _vParticle[i].angle;
				_vParticle[i].y -= _vParticle[i].rc.bottom - _vParticle[i].rc.top;
				_vParticle[i].speed *= 0.5;
			}
			if (COLLISIONMANAGER->pixelCollision(_vParticle[i].rc, _vParticle[i].x, _vParticle[i].y, _vParticle[i].speed, _vParticle[i].gravity, 1) == GREEN) //위
			{
				_vParticle[i].angle = PI2 - _vParticle[i].angle;
				_vParticle[i].y += _vParticle[i].rc.bottom - _vParticle[i].rc.top;
				_vParticle[i].speed *= 0.5;
			}
			if (COLLISIONMANAGER->pixelCollision(_vParticle[i].rc, _vParticle[i].x, _vParticle[i].y, _vParticle[i].speed, _vParticle[i].gravity, 2) == GREEN) //오
			{
				_vParticle[i].angle = PI - _vParticle[i].angle;
				_vParticle[i].x -= _vParticle[i].rc.right - _vParticle[i].rc.left;
				_vParticle[i].speed *= 0.5;
			}
			else if (COLLISIONMANAGER->pixelCollision(_vParticle[i].rc, _vParticle[i].x, _vParticle[i].y, _vParticle[i].speed, _vParticle[i].gravity, 0) == GREEN) //왼
			{
				_vParticle[i].angle = PI - _vParticle[i].angle;
				_vParticle[i].x += _vParticle[i].rc.right - _vParticle[i].rc.left;
				_vParticle[i].speed *= 0.5;
			}
		}
	}
}

void effects::frameChange()
{
	for (int i = 0; i < _vParticle.size(); ++i)
		FRAMEMANAGER->frameChange(_vParticle[i].particleImg, _count, _vParticle[i].index, _animationSpeed, _isLeft);
}
