#include "stdafx.h"
#include "effects.h"


HRESULT effects::init(const char * imageName, int particleMax)
{
	//�̹��� �ʱ�ȭ
	_imageName = imageName;
	//���� �ʱ�ȭ
	_particleMax = particleMax;
	
	return S_OK;
}

void effects::release(void)
{
}

void effects::update(void)
{
	this->explosionBoom();
}

void effects::render(void)
{
	for (int i = 0; _vParticle.size(); ++i)
	{
		_vParticle[i].particleImg->render(getMemDC(), _vParticle[i].rc.left, _vParticle[i].rc.top);
	}
}

void effects::activate(float x, float y, float angle, float speed, float gravity)
{
	//���Ϳ� ��°��� ��������
	if (_particleMax < _vParticle.size() + 1) return;

	tagParticle particle;
	ZeroMemory(&particle, sizeof(tagParticle));
	particle.particleImg = IMAGEMANAGER->findImage(_imageName);
	particle.speed = speed;
	particle.angle = angle;
	particle.gravity = gravity;
	particle.x = particle.fireX = x;
	particle.y = particle.fireY = y;
	particle.rc = RectMakeCenter(particle.x, particle.y,
		particle.particleImg->getWidth(),
		particle.particleImg->getHeight());

	//���Ϳ� ���
	_vParticle.push_back(particle);
}

void effects::boom()
{
	for (int i = 0; _vParticle.size(); ++i)
	{
		_vParticle[i].gravity += 0.0f;
		_vParticle[i].x += cosf(_vParticle[i].angle) * _vParticle[i].speed;
		_vParticle[i].y += -sinf(_vParticle[i].angle) * _vParticle[i].speed + _vParticle[i].gravity;
		_vParticle[i].rc = RectMakeCenter(_vParticle[i].x, _vParticle[i].y,
			_vParticle[i].particleImg->getWidth(),
			_vParticle[i].particleImg->getHeight());
	}
}
