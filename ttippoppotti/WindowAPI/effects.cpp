#include "stdafx.h"
#include "effects.h"
#include "mapData.h"

HRESULT fragments::init(const char * imageName, int particleMax)
{
	//이미지 초기화
	_imageName = imageName;
	//갯수 초기화
	_particleMax = particleMax;
	
	_randGravity = -1;

	//총알의 갯수만큼 구조체를 초기화 한 후 벡터에 담기
	for (int i = 0; i < _particleMax; i++)
	{
		//총알 구조체 선언
		tagParticle fragment;
		//제로메모리 또는 멤셋
		//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
		ZeroMemory(&fragment, sizeof(tagParticle));
		fragment.particleImg = IMAGEMANAGER->findImage(_imageName);
		fragment.speed = 5.0f;
		fragment.fire = false;

		//벡터에 담기
		_vFragment.push_back(fragment);                                                                     
	}

	return S_OK;
}

void fragments::release(void)
{
}

void fragments::update(void)
{
	if (_isRunning)
	{
		if (_randGravity == -1)
			_randGravity = RND->getFromFloatTo(0.1f, 0.5f);

		this->boom(_randGravity);
		this->collisionProcess();
	}
	else
	{
		_randGravity = -1;
	}
}

void fragments::render(void)
{
	for (int i = 0; i < _vFragment.size(); ++i)
	{
		if (!_vFragment[i].fire) continue;
		_vFragment[i].particleImg->render(getMemDC(), _vFragment[i].rc.left, _vFragment[i].rc.top);
	}
}

void fragments::stopEffect()
{
	_isRunning = false;
}

void fragments::activate(float x, float y, float angle)
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
		fragment.speed = RND->getFromFloatTo(3.0f, 6.0f);
		fragment.fire = false;

		//벡터에 담기
		_vFragment.push_back(fragment);
		
		_vFragment[i].fire = true;
		if (angle == PI) //플레이어가 총알을 왼편으로 쐈을 때
			_vFragment[i].angle = PI - 45.0f - RND->getFromFloatTo(0.1f, 0.5f);
		else if (angle == 0.0f) //플레이어 총알 오른
			_vFragment[i].angle = 45.0f + RND->getFromFloatTo(0.1f, 0.5f);
		_vFragment[i].gravity = 0.0f;
		_vFragment[i].x = x;
		_vFragment[i].y = y;
		_vFragment[i].count = 0;
		_vFragment[i].rc = RectMakeCenter(_vFragment[i].x, _vFragment[i].y,
			_vFragment[i].particleImg->getWidth(),
			_vFragment[i].particleImg->getHeight());
	}
}

void fragments::boom(float gravity)
{
	for (int i = 0; i < _vFragment.size(); ++i)
	{
		if (!_vFragment[i].fire) continue;

		_vFragment[i].gravity += gravity;
		_vFragment[i].x += cosf(_vFragment[i].angle) * _vFragment[i].speed;
		_vFragment[i].y += -sinf(_vFragment[i].angle) * _vFragment[i].speed + _vFragment[i].gravity;
		_vFragment[i].rc = RectMakeCenter(_vFragment[i].x, _vFragment[i].y,
			_vFragment[i].particleImg->getWidth(),
			_vFragment[i].particleImg->getHeight());
		_vFragment[i].count++;
		if (_vFragment[i].count == 1000)
			_vFragment[i].fire = false;
	}
}

void fragments::collisionProcess()
{
	for (int i = 0; i < _vFragment.size(); ++i)
	{
		//for (int j = 0; j < )
	}
}
