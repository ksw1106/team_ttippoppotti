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
	for (int i = 0; i < _particleMax; i++)
	{
		//�Ѿ� ����ü ����
		tagParticle fragment;
		//���θ޸� �Ǵ� ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&fragment, sizeof(tagParticle));
		fragment.particleImg = IMAGEMANAGER->findImage(_imageName);
		fragment.speed = 5.0f;
		fragment.fire = false;

		//���Ϳ� ���
		_vFragment.push_back(fragment);                                                                     
	}

	return S_OK;
}

void fragments::release(void)
{
}

void fragments::update(void)
{
	if (_randGravity == -1)
		_randGravity = RND->getFromFloatTo(0.1f, 0.5f);

	this->boom(_randGravity);
	this->collisionProcess();
}

void fragments::render(void)
{
	for (int i = 0; i < _vFragment.size(); ++i)
	{
		if (!_vFragment[i].fire) continue;
		_vFragment[i].particleImg->render(getMemDC(), _vFragment[i].rc.left, _vFragment[i].rc.top);
	}
}

void fragments::activate(float x, float y, float angle)
{
	for (int i = 0; i < _particleMax; i++)
	{
		if (_vFragment[i].fire) continue;
		_vFragment[i].fire = true;
		if (angle == PI) //�Ѿ��� �������� ���� ��
			_vFragment[i].angle = PI - 45.0f;
		else if (angle == 0.0f) //�Ѿ� ����
			_vFragment[i].angle = 45.0f;
		_vFragment[i].gravity = 0.0f;
		_vFragment[i].x = x;
		_vFragment[i].y = y;
		_vFragment[i].count = 0;
		_vFragment[i].rc = RectMakeCenter(_vFragment[i].x, _vFragment[i].y,
			_vFragment[i].particleImg->getWidth(),
			_vFragment[i].particleImg->getHeight());
		break;
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
		/*_vFragment[i].count++;
		if (_vFragment[i].count == 2000)
			_vFragment[i].fire = false;*/
	}
}

void fragments::collisionProcess()
{
	for (int i = 0; i < _vFragment.size(); ++i)
	{

	}
}
