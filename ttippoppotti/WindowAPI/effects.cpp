#include "stdafx.h"
#include "effects.h"
#include "mapData.h"

HRESULT effects::init(const char * imageName, int particleMax, bool isFrameImg)
{
	//이미지 초기화
	_imageName = imageName;
	//갯수 초기화
	_particleMax = particleMax;

	_randGravity = -1;

	_isFrameImg = isFrameImg;

	_count = _index = 0;
	_animationSpeed = 5;

	//총알의 갯수만큼 구조체를 초기화 한 후 벡터에 담기
	for (int i = 0; i < _particleMax; i++)
	{
		//총알 구조체 선언
		tagParticle particle;
		//제로메모리 또는 멤셋
		//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
		ZeroMemory(&particle, sizeof(tagParticle));
		particle.particleImg = IMAGEMANAGER->findImage(_imageName);
		particle.speed = 5.0f;
		particle.fire = false;

		//벡터에 담기
		_vFragment.push_back(particle);
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
		this->boomParabola();
		this->boomExplosion();
		this->collisionProcess();
		this->frameChange();
	}
}

void effects::render(void)
{
	for (int i = 0; i < _vFragment.size(); ++i)
	{
		if (!_vFragment[i].fire) continue;
		if(_isFrameImg)
			_vFragment[i].particleImg->frameRender(getMemDC(), _vFragment[i].rc.left, _vFragment[i].rc.top);
		else
			_vFragment[i].particleImg->render(getMemDC(), _vFragment[i].rc.left, _vFragment[i].rc.top);
	}
}

void effects::activateExplosion(float x, float y)
{
	_isRunning = true;
	for (int i = 0; i < _particleMax; i++)
	{
		//총알 구조체 선언
		tagParticle fragment;
		//제로메모리 또는 멤셋
		//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
		ZeroMemory(&fragment, sizeof(tagParticle));
		fragment.particleImg = IMAGEMANAGER->findImage(_imageName);
		fragment.fire = false;

		_falseCount = 0;
		//벡터에 담기
		_vFragment.push_back(fragment);

		_vFragment[i].fire = true;
		_vFragment[i].angle = PI_2 + RND->getFromFloatTo(0.1f, 1.5f) - 0.75f;
		_vFragment[i].gravity = 0.0f;
		_vFragment[i].x = x;
		_vFragment[i].y = y;
		_vFragment[i].speed = RND->getFromFloatTo(1.0f, 20.0f);
		_vFragment[i].count = 0;
		_vFragment[i].rc = RectMakeCenter(_vFragment[i].x, _vFragment[i].y,
			_vFragment[i].particleImg->getWidth(),
			_vFragment[i].particleImg->getHeight());
	}
}

void effects::boomExplosion()
{
	
}

void effects::stopEffect()
{
	_isRunning = false;
}

void effects::activateParabola(float x, float y, float angle)
{
	_isRunning = true;
	for (int i = 0; i < _particleMax; i++)
	{
		//총알 구조체 선언
		tagParticle fragment;
		//제로메모리 또는 멤셋
		//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
		ZeroMemory(&fragment, sizeof(tagParticle));
		fragment.particleImg = IMAGEMANAGER->findImage(_imageName);
		fragment.fire = false;
		
		_falseCount = 0;
		//벡터에 담기
		_vFragment.push_back(fragment);

		_vFragment[i].fire = true;
		if (angle == PI) //플레이어가 총알을 왼편으로 쐈을 때
			_vFragment[i].angle = PI + RND->getFromFloatTo(0.1f, 1.5f) - 0.75f;
		else if (angle == 0.0f) //플레이어 총알 오른
			_vFragment[i].angle = RND->getFromFloatTo(0.1f, 1.5f) - 0.75;
		else
			_vFragment[i].angle = angle;
		_vFragment[i].gravity = 0.0f;
		_vFragment[i].x = x;
		_vFragment[i].y = y;
		_vFragment[i].speed = RND->getFromFloatTo(1.0f, 20.0f);
		_vFragment[i].count = 0;
		_vFragment[i].rc = RectMakeCenter(_vFragment[i].x, _vFragment[i].y,
			_vFragment[i].particleImg->getWidth(),
			_vFragment[i].particleImg->getHeight());
	}
}

void effects::boomParabola()
{
	for (int i = 0; i < _vFragment.size(); ++i)
	{
		if (!_vFragment[i].fire) continue;

		_vFragment[i].gravity += 0.55f;
		_vFragment[i].x += cosf(_vFragment[i].angle) * _vFragment[i].speed;
		_vFragment[i].y += -sinf(_vFragment[i].angle) * _vFragment[i].speed + _vFragment[i].gravity;
		_vFragment[i].rc = RectMakeCenter(_vFragment[i].x, _vFragment[i].y,
			_vFragment[i].particleImg->getWidth(),
			_vFragment[i].particleImg->getHeight());
		_vFragment[i].count++;
		if (_vFragment[i].count == 1000 || _vFragment[i].y >= WINSIZEY)
		{
			_vFragment[i].fire = false;
			_falseCount++;
			if (_falseCount >= _vFragment.size() - 1)
				stopEffect();
		}
	}
}

void effects::collisionProcess()
{
	for (int i = 0; i < _vFragment.size(); ++i)
	{
		//for (int j = 0; j < )
	}
}

void effects::frameChange()
{
	image* img = IMAGEMANAGER->findImage(_imageName);
	FRAMEMANAGER->frameChange(img, _count, _index, _animationSpeed, false);
}
