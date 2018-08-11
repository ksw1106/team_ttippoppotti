#include "stdafx.h"
#include "bullet.h"


//=============================================================
//	## eBullet ## (적 일반총알)
//=============================================================
HRESULT eBullet::init(int bulletMax, float range)
{
	//총알갯수, 사거리 초기화
	_bulletMax = bulletMax;
	_range = range;
	_bulletCount = 0;

	for (int i = 0; i < _bulletMax; ++i)
	{
		tagBullet ebullet;
		ZeroMemory(&ebullet, sizeof(tagBullet));
		ebullet.bulletImage = new image;
		ebullet.bulletImage->init("enemyBullet/enemy_bullet.bmp", 320, 40, 5, 1);
		
		_vEBullet.push_back(ebullet);
	}

	return S_OK;
}

void eBullet::release(void)
{
	for (int i = 0; i < BOSS_BULLET_MAX; ++i)
	{
		_vEBullet[i].bulletImage->release();
		SAFE_DELETE(_vEBullet[i].bulletImage);
	}
}

void eBullet::update(void)
{
	move();	
}

void eBullet::render(void)
{
	for (int i = 0; i < _vEBullet.size(); ++i)
	{
		if (!_vEBullet[i].isActived) continue;
		_vEBullet[i].bulletImage->frameRender(getMemDC(), _vEBullet[i].rc.left - CAMERAMANAGER->getCamera().left,
			_vEBullet[i].rc.top - CAMERAMANAGER->getCamera().top,
			_vEBullet[i].bulletImage->getFrameX(), _vEBullet[i].bulletImage->getFrameY());
	}
}

void eBullet::fire(int x, int y, int fireSpeed, bool isLeft)
{
	++_bulletCount;	
	if (_bulletCount % fireSpeed != 0) return;
	
	for (int i = 0; i < _vEBullet.size(); ++i)
	{
		if (_vEBullet[i].isActived) continue;
		_vEBullet[i].isActived = true;
		_vEBullet[i].speed = 20.0f;
		_vEBullet[i].isLeft = isLeft;
		_vEBullet[i].x = _vEBullet[i].fireX = x;
		_vEBullet[i].y = _vEBullet[i].fireY = y;
		_vEBullet[i].rc = RectMakeCenter(_vEBullet[i].x, _vEBullet[i].y,
			_vEBullet[i].bulletImage->getFrameWidth(),
			_vEBullet[i].bulletImage->getFrameHeight());
	}		
}

void eBullet::move()
{
	for (int i = 0; i < _vEBullet.size(); ++i)
	{
		if (!_vEBullet[i].isActived) continue;

		if (_vEBullet[i].isLeft)
			_vEBullet[i].x -= _vEBullet[i].speed;
		else
			_vEBullet[i].x += _vEBullet[i].speed;

		_vEBullet[i].rc = RectMakeCenter(_vEBullet[i].x, _vEBullet[i].y,
			_vEBullet[i].bulletImage->getFrameWidth(),
			_vEBullet[i].bulletImage->getFrameHeight());

		float distance = getDistance(_vEBullet[i].x, _vEBullet[i].y, _vEBullet[i].fireX, _vEBullet[i].fireY);
		if (distance > _range)
		{
			_vEBullet[i].isActived = false;
		}
		this->animation(i);
	}
}

void eBullet::animation(int i)
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

//=========================================================================================================
//	## bossBullet ## (보스총알)
//=========================================================================================================
HRESULT bossBullet::init()
{		
	for (int i = 0; i < BOSS_BULLET_MAX; ++i)
	{
		ZeroMemory(&_bossBullet[i], sizeof(tagBullet));
		_bossBullet[i].bulletImage = new image;
		_bossBullet[i].bulletImage->init("enemyBullet/boss_bullet.bmp", 64, 32, true, RGB(255,0,255));
		_bossBullet[i].fire = false;
		_bossBullet[i].angle = PI;
		_bossBullet[i].speed = 20.f;
	}

	_interval = 0;
	_range = 800.f;
	
	return S_OK;
}

void bossBullet::release(void)
{
	for (int i = 0; i < BOSS_BULLET_MAX; ++i)
	{
		_bossBullet[i].bulletImage->release();
		SAFE_DELETE(_bossBullet[i].bulletImage);
	}
}

void bossBullet::update(void)
{
	this->move();	

	_interval++;
	if (_interval > 1000) _interval = 0;
}

void bossBullet::render(void)
{
	for (int i = 0; i < BOSS_BULLET_MAX; ++i)
	{
		if (!_bossBullet[i].isActived) continue;

		_bossBullet[i].bulletImage->render(getMemDC(), _bossBullet[i].rc.left - CAMERAMANAGER->getCamera().left, _bossBullet[i].rc.top - CAMERAMANAGER->getCamera().top);

		if (KEYMANAGER->isToggleKey(VK_F11))
		{
			RectangleMake(getMemDC(), _bossBullet[i].rc.left - CAMERAMANAGER->getCamera().left, _bossBullet[i].rc.top - CAMERAMANAGER->getCamera().top,
				_bossBullet[i].rc.right - _bossBullet[i].rc.left, _bossBullet[i].rc.bottom - _bossBullet[i].rc.top);
		}
	}
}

void bossBullet::fire(int x, int y, bool isLeft)
{
	if (_interval % 5 != 0) return;

	for (int i = 0; i < BOSS_BULLET_MAX; ++i)
	{
		if (_bossBullet[i].isActived) continue;
		
		_bossBullet[i].isActived = true;
		_bossBullet[i].x = _bossBullet[i].fireX = x;
		_bossBullet[i].y = _bossBullet[i].fireY = y;
		_bossBullet[i].rc = RectMake(_bossBullet[i].x, _bossBullet[i].y, _bossBullet[i].bulletImage->getWidth(), _bossBullet[i].bulletImage->getHeight());

		if (isLeft)
		{
			_bossBullet[i].angle = PI + RND->getFromFloatTo(-0.05f, 0.05f);
		}
		else
		{
			_bossBullet[i].angle = 0.f + RND->getFromFloatTo(-0.05f, +0.05f);
		}

		break;
	}
}

void bossBullet::move()
{
	for (int i = 0; i < BOSS_BULLET_MAX; ++i)
	{
		if (!_bossBullet[i].isActived) continue;

		_bossBullet[i].x += cosf(_bossBullet[i].angle) * _bossBullet[i].speed;
		_bossBullet[i].y += -sinf(_bossBullet[i].angle) * _bossBullet[i].speed;
		_bossBullet[i].rc = RectMake(_bossBullet[i].x, _bossBullet[i].y, _bossBullet[i].bulletImage->getWidth(), _bossBullet[i].bulletImage->getHeight());	

		float distance = getDistance(_bossBullet[i].fireX, _bossBullet[i].fireY, _bossBullet[i].x, _bossBullet[i].y);
		if (distance > _range)
		{
			_bossBullet[i].isActived = false;
		}
	}
}

//=========================================================================================================
//	## bossRocket ## (보스로켓)
//=========================================================================================================

HRESULT bossRocket::init(float range)
{
	for (int i = 0; i < BOSS_ROCKET_MAX; ++i)
	{
		ZeroMemory(&_bossRocket[i], sizeof(tagBullet));
		_bossRocket[i].bulletImage = IMAGEMANAGER->findImage("테러콥터 로켓");
		_bossRocket[i].speed = 4.f;
		_bossRocket[i].frameSpeed = 5;
	}

	_interval = 0;
	_range = range;
	
	return S_OK;
}

void bossRocket::release(void)
{	
}

void bossRocket::update(void)
{
	this->move();
	
	_interval++;
	if (_interval > 1000) _interval = 0;
}

void bossRocket::render(void)
{
	for (int i = 0; i < BOSS_ROCKET_MAX; ++i)
	{
		if (!_bossRocket[i].isActived) continue;
		_bossRocket[i].bulletImage->frameRender(getMemDC(), _bossRocket[i].rc.left - CAMERAMANAGER->getCamera().left, _bossRocket[i].rc.top - CAMERAMANAGER->getCamera().top,
			_bossRocket[i].bulletImage->getFrameX(), _bossRocket[i].bulletImage->getFrameY());		
	}
}

void bossRocket::fire(int x, int y, int fireSpeed, bool isLeft)
{
	if (_interval % 10 != 0) return;

	for (int i = 0; i < BOSS_ROCKET_MAX; ++i)
	{
		if (_bossRocket[i].isActived) continue;

		_bossRocket[i].x = _bossRocket[i].fireX = x;
		_bossRocket[i].y = _bossRocket[i].fireY = y;
		_bossRocket[i].gravity = 0.f;
		_bossRocket[i].rc = RectMake(_bossRocket[i].x, _bossRocket[i].y, _bossRocket[i].bulletImage->getFrameWidth(), _bossRocket[i].bulletImage->getFrameHeight());
		_bossRocket[i].isActived = true;
		_bossRocket[i].isLeft = isLeft;
		
		if (isLeft)
		{
			_bossRocket[i].angle = PI;
		}
		else
		{
			_bossRocket[i].angle = 0.f;
		}
		
		break;
	}
}

void bossRocket::move()
{
	for (int i = 0; i < BOSS_ROCKET_MAX; ++i)
	{
		if (!_bossRocket[i].isActived) continue;

		_bossRocket[i].x += cosf(_bossRocket[i].angle) * _bossRocket[i].speed;
		_bossRocket[i].y += -sinf(_bossRocket[i].angle) * _bossRocket[i].speed + _bossRocket[i].gravity;
		_bossRocket[i].rc = RectMake(_bossRocket[i].x, _bossRocket[i].y, _bossRocket[i].bulletImage->getFrameWidth(), _bossRocket[i].bulletImage->getFrameHeight());

		float distance = getDistance(_bossRocket[i].fireX, _bossRocket[i].fireY, _bossRocket[i].x, _bossRocket[i].y);
		if (distance > _range)
		{
			_bossRocket[i].gravity += 0.5f;
		}
		if (distance > 1500.f)
		{
			_bossRocket[i].isActived = false;
		}
		
		this->animation(i);
	}
}


void bossRocket::animation(int i)
{
	FRAMEMANAGER->frameChange(_bossRocket[i].bulletImage, _bossRocket[i].frameCount, _bossRocket[i].frameIndex, _bossRocket[i].frameSpeed, _bossRocket[i].isLeft);
}

// enemy bullet
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================
//==============================================================================================================================================================================================

// player bullet

//=============================================================
//	## pBullet ## (플레이어 일반총알)
//=============================================================
HRESULT pBullet::init(float range)
{
	_range = range;
	
	for (int i = 0; i < 15; i++)
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
				_vBullet[i].rc.top - CAMERAMANAGER->getCamera().top);
		}
	}
};

// 총알 발사
void pBullet::fire(int x, int y, int fireSpeed, bool isLeft)
{
			
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (_vBullet[i].isActived)continue;
		_vBullet[i].isActived = true;
		_vBullet[i].speed = fireSpeed;
		_vBullet[i].isLeft = isLeft;
		_vBullet[i].x = _vBullet[i].fireX = x;
		_vBullet[i].y = _vBullet[i].fireY = y;
		_vBullet[i].rc = RectMake(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].bulletImage->getFrameWidth(),
			_vBullet[i].bulletImage->getFrameHeight());
		if (_vBullet[i].isLeft)
		{
			_vBullet[i].angle = RND->getFromFloatTo(175.f, 183.f) * PI / 180;
		}
		else
		{
			_vBullet[i].angle = RND->getFromFloatTo(-5.f, 3.f) * PI / 180;
		}
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
			_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
			_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed + _vBullet[i].gravity;
		
			_vBullet[i].rc = RectMake(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getFrameWidth(),
				_vBullet[i].bulletImage->getFrameHeight());	

			float distance = getDistance(_vBullet[i].x, _vBullet[i].y, _vBullet[i].fireX, _vBullet[i].fireY);
			
			if (distance > _range)
			{
				_vBullet[i].isActived = false;
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
	_count = _index = 0;
	_animationSpeed = 0;
	for (int i = 0; i < 10; i++)
	{
		tagBullet pGrenade;
		ZeroMemory(&pGrenade, sizeof(tagBullet));
		//pGrenade.bulletImage = new image;
		//pGrenade.bulletImage->init("player_ramBro/rambro_grenade.bmp", 288, 72, 8, 2, true, RGB(255, 0, 255));
		//pGrenade.grenadeImage = new image;
		//pGrenade.grenadeImage->init("player_ramBro/rambro_grenade_bomb.bmp", 28, 35, true, RGB(255, 0, 255));
		pGrenade.bulletImage = IMAGEMANAGER->findImage("rambro_grenade_frame");
		pGrenade.grenadeImage = IMAGEMANAGER->findImage("rambro_grenade_frame");
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
	image* _tempImage;
	_animationSpeed++;
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		if (_vBullet[i].isActived == true)
		{
			
			if (_vBullet[i].count > 50)
			{
				if (_vBullet[i].count % 5 == 0)
				{
					_tempImage = _vBullet[i].bulletImage;
					_vBullet[i].bulletImage = _vBullet[i].grenadeImage;
					_vBullet[i].grenadeImage = _tempImage;
				}
				//_vBullet[i].grenadeImage->frameRender(getMemDC(), _vBullet[i].rc.left - CAMERAMANAGER->getCamera().left,
				//	_vBullet[i].rc.top - CAMERAMANAGER->getCamera().top);
				EFFECTMANAGER->grenadePuff(_vBullet[i].rc.left + 73, _vBullet[i].rc.top + 73);
			}
			FRAMEMANAGER->frameChange(_vBullet[i].bulletImage, _count, _index, _animationSpeed, false);
		}
	}
	move();
}

void pGrenade::render(void)
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		if (_vBullet[i].isActived == true)
		{
			_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left - CAMERAMANAGER->getCamera().left,
				_vBullet[i].rc.top - CAMERAMANAGER->getCamera().top);
			if (_vBullet[i].count > 50)
			{
				//_vBullet[i].grenadeImage->frameRender(getMemDC(), _vBullet[i].rc.left - CAMERAMANAGER->getCamera().left,
				//	_vBullet[i].rc.top - CAMERAMANAGER->getCamera().top);
				//EFFECTMANAGER->grenadePuff(_vBullet[i].rc.left+73 , _vBullet[i].rc.top+73);
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
		_vBullet[i].rc = RectMake(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].bulletImage->getFrameWidth(),
			_vBullet[i].bulletImage->getFrameHeight());
		if (_vBullet[i].isLeft)
		{
			_vBullet[i].angle = 145.f * PI / 180;
		}
		else
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
			_vBullet[i].gravity += 0.90f;	
			_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
			_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed + _vBullet[i].gravity;
			
			_vBullet[i].rc = RectMake(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getFrameWidth(),
				_vBullet[i].bulletImage->getFrameHeight());

			_vBullet[i].count++;
		}
	}
}
//=============================================================
//	## Gbullet ## (할아버지 일반총알)
//=============================================================
HRESULT gBullet::init(float range)
{
	_range = range;

	for (int i = 0; i < 5; i++)
	{
		tagBullet gBullet;
		ZeroMemory(&gBullet, sizeof(tagBullet));
		gBullet.bulletImage = new image;
		gBullet.bulletImage->init("player_chuck/chuck_bullet.bmp", 20, 16, 1, 1, true, RGB(255, 0, 255));
		// 벡터에 총알담기
		_vBullet.push_back(gBullet);
	}
	return S_OK;
}

void gBullet::release(void)
{	
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		_vBullet[i].bulletImage->release();
		SAFE_DELETE(_vBullet[i].bulletImage);
	}
}

void gBullet::update(void)
{
	move();
}

void gBullet::render(void)
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		if (_vBullet[i].isActived == true)
		{
			_vBullet[i].bulletImage->frameRender(getMemDC(), _vBullet[i].rc.left - CAMERAMANAGER->getCamera().left,
				_vBullet[i].rc.top - CAMERAMANAGER->getCamera().top);
		}
	}
}

void gBullet::fire(int x, int y, int fireSpeed, bool isLeft)
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
		_vBullet[i].rc = RectMake(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].bulletImage->getFrameWidth(),
			_vBullet[i].bulletImage->getFrameHeight());
		if (_vBullet[i].isLeft)
		{
			_vBullet[i].angle = (RND->getFromFloatTo(190.f, 195.f) - 7 * i) * (PI / 180);
		}
		else
		{
			_vBullet[i].angle = (RND->getFromFloatTo(-15.f, -10.f) + 7 * i) * (PI / 180);
		}
	}
}

void gBullet::move()
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		if (_vBullet[i].isActived)
		{
			_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
			_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed + _vBullet[i].gravity;

			_vBullet[i].rc = RectMake(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].bulletImage->getFrameWidth(),
				_vBullet[i].bulletImage->getFrameHeight());

			float distance = getDistance(_vBullet[i].x, _vBullet[i].y, _vBullet[i].fireX, _vBullet[i].fireY);

			if (distance > _range)
			{
				_vBullet[i].isActived = false;
				EFFECTMANAGER->bulletPuff(_vBullet[i].x, _vBullet[i].y);
			}
		}
	}
}
//=============================================================
//	## gMissile ## (할아버지 미사일)
//=============================================================
HRESULT gMissile::init(float range)
{
	_range = range;
	for (int i = 0; i < 5; i++)
	{
		tagBullet pMissile;
		ZeroMemory(&pMissile, sizeof(tagBullet));
		pMissile.missileImageRight = new image;
		pMissile.missileImageRight->init("player_chuck/chuck_missile_right.bmp", 62, 63, 1, 1, true, RGB(255, 0, 255));
		pMissile.missileImageLeft = new image;
		pMissile.missileImageLeft->init("player_chuck/chuck_missile_left.bmp", 62, 63, 1, 1, true, RGB(255, 0, 255));

		_vBullet.push_back(pMissile);
	}
	return S_OK;
}

void gMissile::release(void)
{
}

void gMissile::update(void)
{
	move();
}

void gMissile::render(void)
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		if (_vBullet[i].isActived)
		{
			if (!_vBullet[i].isLeft)
			{
				_vBullet[i].missileImageRight->frameRender(getMemDC(), _vBullet[i].rc.left - CAMERAMANAGER->getCamera().left,
					_vBullet[i].rc.top - CAMERAMANAGER->getCamera().top);
			}
			else
			{
				_vBullet[i].missileImageLeft->frameRender(getMemDC(), _vBullet[i].rc.left - CAMERAMANAGER->getCamera().left,
					_vBullet[i].rc.top - CAMERAMANAGER->getCamera().top);
			}
			
		}
	}
}

void gMissile::fire(int x, int y, int fireSpeed, bool isLeft)
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (_vBullet[i].isActived)continue;
		_vBullet[i].isActived = true;
		_vBullet[i].speed = fireSpeed;
		_vBullet[i].isLeft = isLeft;
		_vBullet[i].gravity = 0.0f;
		_vBullet[i].count = 0;
		if (!_vBullet[i].isLeft)
		{
			x = 110 + x;
			y = y - 60;
		}
		else
		{
			x = x - 90;
			y = y - 80;
		}
		_vBullet[i].x = _vBullet[i].fireX = x;
		_vBullet[i].y = _vBullet[i].fireY = y;
		_vBullet[i].rc = RectMake(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].missileImageRight->getFrameWidth(),
			_vBullet[i].missileImageRight->getFrameHeight());
		if (_vBullet[i].isLeft)
		{
			//_vBullet[i].angle = 190.f * (PI / 180);
			_vBullet[i].angle = PI + PI_4;
		}
		else
		{
			//_vBullet[i].angle = -20.f * (PI / 180);
			_vBullet[i].angle = - PI_4;
		}
	}
}

void gMissile::move()
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		if (_vBullet[i].isActived)
		{
			_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
			_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed + _vBullet[i].gravity;
		
			_vBullet[i].rc = RectMake(_vBullet[i].x, _vBullet[i].y,
				_vBullet[i].missileImageRight->getFrameWidth(),
				_vBullet[i].missileImageRight->getFrameHeight());

			float distance = getDistance(_vBullet[i].x, _vBullet[i].y, _vBullet[i].fireX, _vBullet[i].fireY);

			if (distance > _range)
			{
				_vBullet[i].isActived = false;
			}
		}
	}
}
//=============================================================
//	## xMissile ## (할아버지 미사일 x)
//=============================================================
HRESULT xMissile::init(float range)
{
	_range = range;
	
	for (int i = 0; i < 5; i++)
	{
		tagBullet xMissile;
		ZeroMemory(&xMissile, sizeof(tagBullet));
		xMissile.missileImageRight = new image;
		xMissile.missileImageRight->init("player_chuck/missile_xx.bmp", 46, 52, 1, 1, true, RGB(255, 0, 255));

		_vBullet.push_back(xMissile);
	}
	return S_OK;
}

void xMissile::release(void)
{
}

void xMissile::update(void)
{
	move();
}

void xMissile::render(void)
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		if (_vBullet[i].isActived == true)
		{
			_vBullet[i].missileImageRight->frameRender(getMemDC(), _vBullet[i].rc.left - CAMERAMANAGER->getCamera().left,
				_vBullet[i].rc.top - CAMERAMANAGER->getCamera().top);
		}
	}
}

void xMissile::fire(int x, int y, int fireSpeed, bool isLeft)
{
	for (int i = 0; i < _vBullet.size(); i++)
	{
		if (_vBullet[i].isActived)continue;
		_vBullet[i].isActived = true;
		_vBullet[i].speed = fireSpeed;
		_vBullet[i].isLeft = isLeft;
		_vBullet[i].gravity = 0.0f;
		_vBullet[i].count = 0;
		if (!_vBullet[i].isLeft)
		{
			x = 110 + x;
			y = y - 60;
		}
		if (_vBullet[i].isLeft)
		{
			x = x - 90;
			y = y - 80;
		}
		_vBullet[i].x = _vBullet[i].fireX = x;
		_vBullet[i].y = _vBullet[i].fireY = y;
		_vBullet[i].rc = RectMake(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].missileImageRight->getFrameWidth(),
			_vBullet[i].missileImageRight->getFrameHeight());
		if (_vBullet[i].isLeft)
		{
			//_vBullet[i].angle = 190.f * (PI / 180);
			_vBullet[i].angle = PI + PI_4;
		}
		else
		{
			//_vBullet[i].angle = -20.f * (PI / 180);
			_vBullet[i].angle = -PI_4;
		}
	}
}

void xMissile::move()
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		if (_vBullet[i].isActived == false)continue;

		_vBullet[i].x += cosf(_vBullet[i].angle) * _vBullet[i].speed;
		_vBullet[i].y += -sinf(_vBullet[i].angle) * _vBullet[i].speed + _vBullet[i].gravity;
		
		_vBullet[i].rc = RectMake(_vBullet[i].x, _vBullet[i].y,
			_vBullet[i].missileImageRight->getFrameWidth(),
			_vBullet[i].missileImageRight->getFrameHeight());

		if (COLLISIONMANAGER->pixelCollision(_vBullet[i].rc, _vBullet[i].x, _vBullet[i].y, _vBullet[i].speed, _vBullet[i].gravity, 3) == GREEN)			// 아래쪽 벽
		{
			_vBullet[i].isCollision = true;
			_vBullet[i].speed = 0.0f;
		}
		else if (COLLISIONMANAGER->pixelCollision(_vBullet[i].rc, _vBullet[i].x, _vBullet[i].y, _vBullet[i].speed, _vBullet[i].gravity, 1) == GREEN)			// 위쪽 벽
		{
			_vBullet[i].isCollision = true;
			_vBullet[i].speed = 0.0f;
		}
		if (COLLISIONMANAGER->pixelCollision(_vBullet[i].rc,_vBullet[i].x, _vBullet[i].y, _vBullet[i].speed, _vBullet[i].gravity, 2) == GREEN)			// 오른쪽 벽	
		{
			_vBullet[i].isCollision = true;
			_vBullet[i].speed = 0.0f;
		}
		else if (COLLISIONMANAGER->pixelCollision(_vBullet[i].rc,_vBullet[i].x, _vBullet[i].y, _vBullet[i].speed, _vBullet[i].gravity, 0) == GREEN)			// 왼쪽 벽	
		{
			_vBullet[i].isCollision = true;
			_vBullet[i].speed = 0.0f;
		}
	}
}
