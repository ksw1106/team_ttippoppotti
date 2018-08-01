#include "stdafx.h"
#include "effects.h"
#include "mapData.h"

HRESULT effects::init(const char * imageName, int particleMax, bool isFrameImg)
{
	//�̹��� �ʱ�ȭ
	_imageName = imageName;
	//���� �ʱ�ȭ
	_particleMax = particleMax;

	_randGravity = -1;

	_isFrameImg = isFrameImg;

	_count = _index = 0;
	_animationSpeed = 5;
	_explosionCount = 0;

	//�Ѿ��� ������ŭ ����ü�� �ʱ�ȭ �� �� ���Ϳ� ���
	for (int i = 0; i < _particleMax; i++)
	{
		//�Ѿ� ����ü ����
		tagParticle particle;
		//���θ޸� �Ǵ� ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&particle, sizeof(tagParticle));
		particle.particleImg = IMAGEMANAGER->findImage(_imageName);

		//���Ϳ� ���
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
		if (_isExplosion)
			this->boomExplosion();
		else if (_isParabola)
		{
			this->boomParabola();
			this->collisionProcess();
		}

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
	for (int i = 0; i < _vFragment.size(); ++i)
	{
		if(!_vFragment[i].fire) continue;
		if (_isFrameImg)
			_vFragment[i].particleImg->frameRender(getMemDC(), _vFragment[i].rc.left - CAMERAMANAGER->getCamera().left, _vFragment[i].rc.top - CAMERAMANAGER->getCamera().top);
		else
			_vFragment[i].particleImg->render(getMemDC(), _vFragment[i].rc.left - CAMERAMANAGER->getCamera().left, _vFragment[i].rc.top - CAMERAMANAGER->getCamera().top);
	}
}

void effects::activateCartridge(float x, float y, bool isLeft)
{
	_isRunning = true;
	_isParabola = true;
	for (int i = 0; i < _particleMax; i++)
	{
		//�Ѿ� ����ü ����
		tagParticle fragment;
		//���θ޸� �Ǵ� ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&fragment, sizeof(tagParticle));
		fragment.particleImg = IMAGEMANAGER->findImage(_imageName);

		_falseCount = 0;
		//���Ϳ� ���
		_vFragment.push_back(fragment);

		_vFragment[i].fire = true;
		_vFragment[i].y = y;
		if (isLeft)
		{
			_vFragment[i].angle = PI / 4;
			_vFragment[i].x = x + 64;
		}
		else //�÷��̾ �������� �ٶ󺸰� ���� ��
		{
			_vFragment[i].angle = PI - PI / 4;
			_vFragment[i].x = x;
		}
		_vFragment[i].gravity = 0.0f;
		_vFragment[i].speed = RND->getFromFloatTo(5.0f, 10.0f);
		_vFragment[i].count = 0;
		_vFragment[i].rc = RectMakeCenter(_vFragment[i].x, _vFragment[i].y,
			_vFragment[i].particleImg->getWidth(),
			_vFragment[i].particleImg->getHeight());
	}
}

void effects::activateBallExplosion(float x, float y)
{
	_isRunning = true;
	_isExplosion = true;

	for (int i = 0; i < _particleMax; i++)
	{
		//�Ѿ� ����ü ����
		tagParticle fragment;
		//���θ޸� �Ǵ� ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&fragment, sizeof(tagParticle));
		fragment.particleImg = IMAGEMANAGER->findImage(_imageName);
		_vFragment[i].x = x;
		_vFragment[i].y = y;

		_falseCount = 0;
		//���Ϳ� ���
		_vFragment.push_back(fragment);
		_vFragment[i].rc = RectMakeCenter(_vFragment[i].x, _vFragment[i].y,
			_vFragment[i].particleImg->getWidth(),
			_vFragment[i].particleImg->getHeight());
	}
}

void effects::activateExplosion(float x, float y)
{
	_isRunning = true;
	_isExplosion = true;
	
	for (int i = 0; i < _particleMax; i++)
	{
		//�Ѿ� ����ü ����
		tagParticle fragment;
		//���θ޸� �Ǵ� ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&fragment, sizeof(tagParticle));
		fragment.particleImg = IMAGEMANAGER->findImage(_imageName);

		_falseCount = 0;
		//���Ϳ� ���
		_vFragment.push_back(fragment);

		_vFragment[i].fire = true;
		_vFragment[i].angle = PI / _particleMax * (i + 1);
		_vFragment[i].gravity = 0.0f;
		_vFragment[i].x = x;
		_vFragment[i].y = y;
		_vFragment[i].speed = 7.0f;
		_vFragment[i].count = 0;
		_vFragment[i].rc = RectMakeCenter(_vFragment[i].x, _vFragment[i].y,
			_vFragment[i].particleImg->getWidth(),
			_vFragment[i].particleImg->getHeight());
	}
}
void effects::boomExplosion()
{
	_explosionCount++;
	if (_explosionCount % 5)
	{
		for (int i = 0; i < _vFragment.size(); ++i)
		{
			if (!_vFragment[i].fire) continue;
			_vFragment[i].gravity += 0.08f;
			_vFragment[i].x += cosf(_vFragment[i].angle) * _vFragment[i].speed;
			_vFragment[i].y += -sinf(_vFragment[i].angle) * _vFragment[i].speed + _vFragment[i].gravity;
			_vFragment[i].rc = RectMakeCenter(_vFragment[i].x, _vFragment[i].y,
				_vFragment[i].particleImg->getWidth(),
				_vFragment[i].particleImg->getHeight());

			_vFragment[i].count++;

			if (_vFragment[i].count == 300 || _vFragment[i].y - CAMERAMANAGER->getCamera().top >= WINSIZEY || _vFragment[i].speed < 0.5f)
			{
				_vFragment[i].fire = false;
				_isRunning = false;
				_isParabola = false;
			}
		}
	}
}

void effects::activateParabola(float x, float y, float angle)
{
	_isRunning = true;
	_isParabola = true;
	for (int i = 0; i < _particleMax; i++)
	{
		//�Ѿ� ����ü ����
		tagParticle fragment;
		//���θ޸� �Ǵ� ���
		//����ü�� �������� ���� �ѹ��� 0���� �ʱ�ȭ �����ش�
		ZeroMemory(&fragment, sizeof(tagParticle));
		fragment.particleImg = IMAGEMANAGER->findImage(_imageName);
		
		_falseCount = 0;
		//���Ϳ� ���
		_vFragment.push_back(fragment);

		_vFragment[i].fire = true;
		if (angle == PI) //�÷��̾ �Ѿ��� �������� ���� ��
			_vFragment[i].angle = PI + RND->getFromFloatTo(0.1f, 1.5f) - 0.75f;
		else if (angle == 0.0f) //�÷��̾� �Ѿ� ����
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

		if (_vFragment[i].count == 500 || _vFragment[i].y - CAMERAMANAGER->getCamera().top >= WINSIZEY || _vFragment[i].speed < 0.5f)
		{
			_vFragment[i].fire = false;
			_isRunning = false;
			_isParabola = false;
		}
	}
}

void effects::collisionProcess()
{
	for (int i = 0; i < _vFragment.size(); ++i)
	{
		if (COLLISIONMANAGER->pixelCollision(_vFragment[i].rc, _vFragment[i].x, _vFragment[i].y, _vFragment[i].speed, _vFragment[i].gravity, 1))
		{
			_vFragment[i].angle = PI - _vFragment[i].angle;
			_vFragment[i].speed *= 0.8;
		}
		if (COLLISIONMANAGER->pixelCollision(_vFragment[i].rc, _vFragment[i].x, _vFragment[i].y, _vFragment[i].speed, _vFragment[i].gravity, 2))
		{
			_vFragment[i].angle = PI2 - _vFragment[i].angle;
			_vFragment[i].speed *= 0.8;
		}
		if (COLLISIONMANAGER->pixelCollision(_vFragment[i].rc, _vFragment[i].x, _vFragment[i].y, _vFragment[i].speed, _vFragment[i].gravity, 3))
		{
			_vFragment[i].gravity = PI2 - _vFragment[i].angle;
			_vFragment[i].speed *= 0.8;
		}
		if (COLLISIONMANAGER->pixelCollision(_vFragment[i].rc, _vFragment[i].x, _vFragment[i].y, _vFragment[i].speed, _vFragment[i].gravity, 4))
		{
			_vFragment[i].angle = PI - _vFragment[i].angle;
			_vFragment[i].speed *= 0.8;
		}
	}
}

void effects::frameChange()
{
	image* img = IMAGEMANAGER->findImage(_imageName);
	FRAMEMANAGER->frameChange(img, _count, _index, _animationSpeed, false);
}
