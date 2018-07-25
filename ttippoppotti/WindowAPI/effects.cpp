#include "stdafx.h"
#include "effects.h"


HRESULT fragments::init(const char * imageName, int particleMax)
{
	//�̹��� �ʱ�ȭ
	_imageName = imageName;
	//���� �ʱ�ȭ
	_particleMax = particleMax;
	
	_randGravity = -1;

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < particleMax; i++)
	{
		//�Ѿ� ����ü ����
		tagParticle particle;
		//���θ޸� �Ǵ� ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&particle, sizeof(tagParticle));
		particle.particleImg = IMAGEMANAGER->findImage(_imageName);
		particle.speed = 5.0f;
		particle.fire = false;

		//���Ϳ� ���
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
	//���Ϳ� ��°��� ��������
	if (_particleMax < _vFragment.size() + 1) return;

	tagParticle particle;
	ZeroMemory(&particle, sizeof(tagParticle));
	particle.particleImg = IMAGEMANAGER->findImage(_imageName);
	particle.speed = speed;
	if (angle == PI) //�Ѿ��� �������� ���� ��
		particle.angle = PI - 45.0f;
	else if (angle == 0.0f) //�Ѿ� ����
		particle.angle = 45.0f;
	particle.gravity = gravity;
	particle.x = particle.fireX = x;
	particle.y = particle.fireY = y;
	particle.count = 0;
	particle.rc = RectMakeCenter(particle.x, particle.y,
		particle.particleImg->getWidth(),
		particle.particleImg->getHeight());

	//���Ϳ� ���
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
