#include "stdafx.h"
#include "effects.h"


HRESULT fragments::init(const char * imageName, int particleMax)
{
	//이미지 초기화
	_imageName = imageName;
	//갯수 초기화
	_particleMax = particleMax;
	
	_randGravity = -1;

	//총알의 갯수만큼 구조체를 초기화 한 후 벡터에 담기
	for (int i = 0; i < particleMax; i++)
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

void fragments::release(void)
{
}

void fragments::update(void)
{
	if (_randGravity == -1)
	{
		_randGravity = RND->getFromFloatTo(0.1f, 0.5f);
	}
	this->boom(_randGravity);
}

void fragments::render(void)
{
	for (int i = 0; _vFragment.size(); ++i)
	{
		if (!_vFragment[i].fire) continue;
		_vFragment[i].particleImg->render(getMemDC(), _vFragment[i].rc.left, _vFragment[i].rc.top);
	}
}

void fragments::activate(float x, float y, float angle, float speed, float gravity)
{
	//벡터에 담는것을 제한하자
	if (_particleMax < _vFragment.size() + 1) return;

	tagParticle particle;
	ZeroMemory(&particle, sizeof(tagParticle));
	particle.particleImg = IMAGEMANAGER->findImage(_imageName);
	particle.speed = speed;
	if (angle == PI) //총알을 왼편으로 쐈을 때
		particle.angle = PI - 45.0f;
	else if (angle == 0.0f) //총알 오른
		particle.angle = 45.0f;
	particle.gravity = gravity;
	particle.x = particle.fireX = x;
	particle.y = particle.fireY = y;
	particle.count = 0;
	particle.rc = RectMakeCenter(particle.x, particle.y,
		particle.particleImg->getWidth(),
		particle.particleImg->getHeight());

	//벡터에 담기
	_vFragment.push_back(particle);
}

void fragments::boom(float gravity)
{
	for (int i = 0; _vFragment.size(); ++i)
	{
		_vFragment[i].gravity += gravity;
		_vFragment[i].x += cosf(_vFragment[i].angle) * _vFragment[i].speed;
		_vFragment[i].y += -sinf(_vFragment[i].angle) * _vFragment[i].speed + _vFragment[i].gravity;
		_vFragment[i].rc = RectMakeCenter(_vFragment[i].x, _vFragment[i].y,
			_vFragment[i].particleImg->getWidth(),
			_vFragment[i].particleImg->getHeight());
		_vFragment[i].count++;
		if (_vFragment[i].count == 2000)
			_vFragment[i].isActive = false;
	}
}
