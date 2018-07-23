#include "stdafx.h"
#include "effects.h"


HRESULT effects::init(const char * imageName, int particleMax, float range)
{
	//이미지 초기화
	_imageName = imageName;
	//갯수 초기화
	_particleMax = particleMax;

	_range = range;
	
	return S_OK;
}

void effects::release(void)
{
}

void effects::update(void)
{
	this->move();
}

void effects::render(void)
{
	for (int i = 0; _vParticle.size(); ++i)
	{
		_vParticle[i].particleImg->render(getMemDC(), _vParticle[i].rc.left, _vParticle[i].rc.top);
	}
}

void effects::fire(float x, float y, float angle, float speed)
{
	//벡터에 담는것을 제한하자
	if (_particleMax < _vParticle.size() + 1) return;

	tagParticle particle;
	ZeroMemory(&particle, sizeof(tagParticle));
	particle.particleImg = IMAGEMANAGER->findImage(_imageName);
	particle.speed = speed;
	particle.angle = angle;
	particle.x = particle.fireX = x;
	particle.y = particle.fireY = y;
	particle.rc = RectMakeCenter(particle.x, particle.y,
		particle.particleImg->getWidth(),
		particle.particleImg->getHeight());

	//벡터에 담기
	_vParticle.push_back(particle);
}

void effects::move()
{
	for (int i = 0; _vParticle.size(); ++i)
	{
		_vParticle[i].x += cosf(_vParticle[i].angle) * _vParticle[i].speed;
		_vParticle[i].y += -sinf(_vParticle[i].angle) * _vParticle[i].speed;
		_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y,
			_vParticle[i].particleImg->getWidth(),
			_vParticle[i].particleImg->getHeight());

		//파편이 사거리보다 커졌을때
		float distance = getDistance(_vParticle[i].fireX, _vParticle[i].fireY,
			_vParticle[i].x, _vParticle[i].y);
		if (_range < distance)
		{
			_vParticle[i].isActive = false;
		}
		else
		{
			++i;
		}
	}
}
