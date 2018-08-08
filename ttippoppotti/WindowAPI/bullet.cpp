#include "stdafx.h"
#include "bullet.h"


//=============================================================
//	## bullet ## (공용총알 - 너희들이 만들면 된다)
//=============================================================

//테스트 입니다.
//나도 테스트
//또 테스트
HRESULT bullet::init(const char * imageName, int bulletMax, float range)
{
	//총알 이미지 초기화
	_imageName = imageName;
	//총알갯수 및 사거리 초기화
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bullet::release(void)
{
}

void bullet::update(void)
{
	this->move();
}

void bullet::render(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void bullet::fire(float x, float y, float angle, float speed)
{
	//총알 벡터에 담는것을 제한하자
	if (_bulletMax < _vBullet.size() + 1) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.speed = speed;
	bullet.angle = angle;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	

	//벡터에 담기
	_vBullet.push_back(bullet);
}

void bullet::move()
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		//총알이 사거리보다 커졌을때
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y);
		if (_range < distance)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void bullet::removeBullet(int index)
{
	_vBullet.erase(_vBullet.begin() + index);
}


//=============================================================
//	## missile ## (missile[0] -> 배열처럼 미리 장전해두고 총알발사)
//=============================================================
HRESULT missile::init(int bulletMax, float range)
{
	//사거리, 총알갯수 초기화
	_range = range;
	_bulletMax = bulletMax;

	//총알의 갯수만큼 구조체를 초기화 한 후 벡터에 담기
	for (int i = 0; i < bulletMax; i++)
	{
		//총알 구조체 선언
		tagBullet bullet;
		//제로메모리 또는 멤셋
		//구조체의 변수들의 값을 한번에 0으로 초기화 시켜준다
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("missile.bmp", 25, 124, true, RGB(255, 0, 255));
		bullet.speed = 5.0f;
		bullet.fire = false;

		//벡터에 담기
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missile::release(void)
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

void missile::update(void)
{
	this->move();
}

void missile::render(void)
{
	/*
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (!_vBullet[i].fire) continue;
		_vBullet[i].bulletImage->render(getMemDC(), _vBullet[i].rc.left, _vBullet[i].rc.top);
	}
	*/

	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void missile::fire(float x, float y)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;

		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
		break;
	}
}

void missile::move()
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		//총알이 사거리보다 커졌을때 
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y);
		if (_range < distance)
		{
			_viBullet->fire = false;
		}
	}
}

//=============================================================
//	## missileM1 ## (폭탄처럼 한발씩 발사하면서 생성하고 자동삭제)
//=============================================================
HRESULT missileM1::init(int bulletMax, float range)
{
	//총알갯수, 사거리 초기화
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void missileM1::release(void)
{
}

void missileM1::update(void)
{
	move();
}

void missileM1::render(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	
		_viBullet->count++;
		if (_viBullet->count % 3 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void missileM1::fire(float x, float y)
{
	//총알 벡터에 담는것을 제한하자
	if (_bulletMax < _vBullet.size() + 1) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->init("missile.bmp", 416, 64, 13, 1);
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	//벡터에 담기
	_vBullet.push_back(bullet);
}

void missileM1::move()
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		//총알이 사거리보다 커졌을때
		float distance = getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y);
		if (_range < distance)
		{
			_viBullet->bulletImage->release();
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void missileM1::removeMissileM1(int index)
{
	_vBullet[index].bulletImage->release();
	SAFE_DELETE(_vBullet[index].bulletImage);
	_vBullet.erase(_vBullet.begin() + index);
}

//=============================================================
//	## eBullet ## (적 일반총알)
//=============================================================
HRESULT eBullet::init(int bulletMax, float range)
{
	//총알갯수, 사거리 초기화
	_bulletMax = bulletMax;
	_range = range;
	_bulletCount = 0;

	return S_OK;
}

void eBullet::release(void)
{
}

void eBullet::update(void)
{
	move();
	animation();
}

void eBullet::render(void)
{
	for (int i = 0; i < _vEBullet.size(); ++i)
	{
		_vEBullet[i].bulletImage->frameRender(getMemDC(), _vEBullet[i].rc.left - CAMERAMANAGER->getCamera().left,
			_vEBullet[i].rc.top - CAMERAMANAGER->getCamera().top,
			_vEBullet[i].bulletImage->getFrameX(), _vEBullet[i].bulletImage->getFrameY());
	}
}

void eBullet::fire(int x, int y, int fireSpeed, bool isLeft)
{
	++_bulletCount;
	//총알 벡터에 담는것을 제한하자
	if (_bulletMax < _vEBullet.size() + 1) return;

	if (_bulletCount % fireSpeed != 0) return;

	tagBullet ebullet;
	ZeroMemory(&ebullet, sizeof(tagBullet));
	ebullet.bulletImage = new image;
	ebullet.bulletImage->init("enemyBullet/enemy_bullet.bmp", 320, 40, 5, 1);
	ebullet.speed = 20.0f;
	ebullet.isLeft = isLeft;
	ebullet.x = ebullet.fireX = x;
	ebullet.y = ebullet.fireY = y;
	ebullet.rc = RectMakeCenter(ebullet.x, ebullet.y,
		ebullet.bulletImage->getFrameWidth(),
		ebullet.bulletImage->getFrameHeight());

	//벡터에 담기
	_vEBullet.push_back(ebullet);
}

void eBullet::move()
{
	for (int i = 0; i < _vEBullet.size();)
	{
		if (_vEBullet[i].isLeft)
			_vEBullet[i].x -= _vEBullet[i].speed;

		if (!_vEBullet[i].isLeft)
			_vEBullet[i].x += _vEBullet[i].speed;

		_vEBullet[i].rc = RectMakeCenter(_vEBullet[i].x, _vEBullet[i].y,
			_vEBullet[i].bulletImage->getFrameWidth(),
			_vEBullet[i].bulletImage->getFrameHeight());

		float distance = getDistance(_vEBullet[i].x, _vEBullet[i].y, _vEBullet[i].fireX, _vEBullet[i].fireY);
		if (distance > _range)
		{
			_vEBullet[i].bulletImage->release();
			SAFE_DELETE(_vEBullet[i].bulletImage);
			_vEBullet.erase(_vEBullet.begin() + i);
		}
		else
		{
			++i;
		}
	}
}

void eBullet::animation()
{
	for (int i = 0; i < _vEBullet.size(); ++i)
	{
		_vEBullet[i].bulletImage->setFrameY(0);
		_vEBullet[i].frameCount++;
		if (_vEBullet[i].frameCount % 3 == 0)
		{
			_vEBullet[i].frameIndex++;
			if (_vEBullet[i].frameIndex > 4) _vEBullet[i].frameIndex = 0;
		}
		_vEBullet[i].bulletImage->setFrameX(_vEBullet[i].frameIndex);

		if (_vEBullet[i].frameCount > 1000) _vEBullet[i].frameCount = 0;
	}
}

void eBullet::removeBullet(int index)
{
	_vEBullet.erase(_vEBullet.begin() + index);
}

//=============================================================
//	## pBullet ## (플레이어 일반총알)
//=============================================================
HRESULT pBullet::init(float range)
{
	_range = range;
	
	for (int i = 0; i < 100; i++)
	{
		tagBullet pBullet;
		ZeroMemory(&pBullet, sizeof(tagBullet));
		pBullet.bulletImage = new image;
		pBullet.bulletImage->init("player_ramBro/rambro_bullet.bmp", 51, 26, 1, 1, true, RGB(255, 0, 255));
		
		// 벡터에 총알담기
		_vBullet.push_back(pBullet);
	}
	return S_OK;
};
void pBullet::release(void)
{

};
void pBullet::update(void)
{
	move();

};
void pBullet::render(void)
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		if (_vBullet[i].isActived == true)
		{
			_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left - CAMERAMANAGER->getCamera().left,
				_vBullet[i].rc.top - CAMERAMANAGER->getCamera().top,
				_vBullet[i].bulletImage->getFrameX(), _vBullet[i].bulletImage->getFrameY());
		}
	}
};

// 총알 발사
void pBullet::fire(int x, int y, int fireSpeed, bool isLeft)
{
	//if (_bulletMax < _vBullet.size() + 1)return;

	
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (_vBullet[i].isActived)continue;
		_vBullet[i].isActived = true;
		_vBullet[i].speed = fireSpeed;
		_vBullet[i].isLeft = isLeft;
		y = RND->getFromIntTo(y - 20, y + 20);			// y 값을 랜덤으로 바꿔줘서 총알 나가는게 랜덤하게 나감
		_vBullet[i].x = _vBullet[i].fireX = x;
		_vBullet[i].y = _vBullet[i].fireY = y;
		_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].bulletImage->getFrameWidth(),
			_vBullet[i].bulletImage->getFrameHeight());
		
		break;
	}
}
// 총알 무브
void pBullet::move()
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		if (_vBullet[i].isActived)
		{
			if (_vBullet[i].isLeft)					// 왼쪽
			{
				_vBullet[i].angle = 180.f * PI / 180;
				_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
				_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed + _vBullet[i].gravity;
			}
			if (!_vBullet[i].isLeft)				// 오른쪽
			{
				_vBullet[i].angle = 0.f * PI / 180;
				_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
				_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed + _vBullet[i].gravity;
			}

			_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getFrameWidth(),
				_vBullet[i].bulletImage->getFrameHeight());	

			float distance = getDistance(_vBullet[i].x, _vBullet[i].y, _vBullet[i].fireX, _vBullet[i].fireY);
			
			if (distance > _range)
			{
				_vBullet[i].isActived = false;
				if (_vBullet[i].isActived == false)
				EFFECTMANAGER->bulletPuff(_vBullet[i].x, _vBullet[i].y);
			}
		}
	}
}

// 총알제거
void pBullet::removeBullet(int index)
{
	_vBullet.erase(_vBullet.begin() + index);
}

//=============================================================
//	## pGrenade ## (플레이어 수류탄)
//=============================================================
HRESULT pGrenade::init(float range)
{
	_range = range;
	_count = 0;
	for (int i = 0; i < 50; i++)
	{
		tagBullet pGrenade;
		ZeroMemory(&pGrenade, sizeof(tagBullet));
		pGrenade.bulletImage = new image;
		pGrenade.bulletImage->init("player_ramBro/rambro_grenade.bmp", 28, 35, 1, 1, true, RGB(255, 0, 255));
		pGrenade.grenadeImage = new image;
		pGrenade.grenadeImage->init("player_ramBro/rambro_grenade_bomb.bmp", 28, 35, 1, 1, true, RGB(255, 0, 255));

		// 벡터에 총알담기
		_vBullet.push_back(pGrenade);
	}
	return S_OK;
}

void pGrenade::release(void)
{

}

void pGrenade::update(void)
{
	move();
}

void pGrenade::render(void)
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		if (_vBullet[i].isActived == true)
		{
			_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left - CAMERAMANAGER->getCamera().left,
				_vBullet[i].rc.top - CAMERAMANAGER->getCamera().top,
				_vBullet[i].bulletImage->getFrameX(), _vBullet[i].bulletImage->getFrameY());
			if (_vBullet[i].count > 50)
			{
				_vBullet[i].grenadeImage->frameRender(getMemDC(), _vBullet[i].rc.left - CAMERAMANAGER->getCamera().left,
					_vBullet[i].rc.top - CAMERAMANAGER->getCamera().top,
					_vBullet[i].grenadeImage->getFrameX(), _vBullet[i].grenadeImage->getFrameY());
			}
		}
	}
}

void pGrenade::fire(int x, int y, int fireSpeed, bool isLeft)
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (_vBullet[i].isActived)continue;
		_vBullet[i].isActived = true;
		_vBullet[i].speed = fireSpeed;
		_vBullet[i].isLeft = isLeft;
		_vBullet[i].gravity = 0.0f;
		_vBullet[i].count = 0;		
		_vBullet[i].x = _vBullet[i].fireX = x;
		_vBullet[i].y = _vBullet[i].fireY = y;
		_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].bulletImage->getFrameWidth(),
			_vBullet[i].bulletImage->getFrameHeight());
		if (_vBullet[i].isLeft)
		{
			_vBullet[i].angle = 145.f * PI / 180;
		}
		if (!_vBullet[i].isLeft)
		{
			_vBullet[i].angle = 35.f * PI / 180;
		}

		break;
	}
}

void pGrenade::move()
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		if (_vBullet[i].isActived)
		{
			if (_vBullet[i].isLeft)					// 왼쪽
			{
				_vBullet[i].gravity += 0.90f;	
				_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
				_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed + _vBullet[i].gravity;
			}
			if (!_vBullet[i].isLeft)				// 오른쪽
			{
				_vBullet[i].gravity += 0.90f;	
				_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
				_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed + _vBullet[i].gravity;
			}
	
			_vBullet[i].rc = RectMakeCenter(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getFrameWidth(),
				_vBullet[i].bulletImage->getFrameHeight());

			_vBullet[i].count++;
		}
	}
}
