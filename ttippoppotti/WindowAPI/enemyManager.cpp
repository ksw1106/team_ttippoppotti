#include "stdafx.h"
#include "enemyManager.h"
#include "playerManager.h"
#include "mapData.h"

HRESULT enemyManager::init(void)
{
	// 플레이어매니저 클래스 가져오기
	this->setPlayerManager(_playerManager);
	// 맵데이터 가져오기
	this->setMapData(_mapData);	

	//에너미 클래스 객체 생성 및 초기화
	this->setSoldier(3800, 1000);
	this->setSoldier(3300, 1200);
	this->setSoldier(3600, 1400);
	this->setSoldier(3200, 1600);
	//this->setBrovil(3700, 1000, 5);
		
	_boss = new boss;
	_boss->init(4000.f, 1000.f);
	
	_eBullet = new eBullet;
	_eBullet->init(1, 800.f);
	_bossBullet = new bossBullet;
	_bossBullet->init();
	_bossRocket = new bossRocket;
	_bossRocket->init(50.f);
	_brovil = new brovil;
	_brovil->init(3200, 1000);

	_isClear = false;

	return S_OK;
}

void enemyManager::release(void)
{
	_eBullet->release();
	SAFE_DELETE(_eBullet);
	_boss->release();
	SAFE_DELETE(_boss);
	_bossBullet->release();
	SAFE_DELETE(_bossBullet);
	_bossRocket->release();
	SAFE_DELETE(_bossRocket);
	_brovil->release();
	SAFE_DELETE(_brovil);
}

void enemyManager::update(void)
{
	for (int i = 0; i < _vSoldier.size(); ++i)
	{		
		_vSoldier[i]->update();		
				
		if (_vSoldier[i]->getIsFire() && _vSoldier[i]->getIsAlive())
		{
			this->enemyFire(i);
		}				
	}

	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		if (!_vSoldier[i]->getIsUncovered()) continue;

		// 플레이어 방향에 맞춰 적방향 바꿈 (발견상태일때)
		if ((180 / 3.14f * getAngle(_vSoldier[i]->getX(), _vSoldier[i]->getY(), _playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY())) >= 91.f
			&& (180 / 3.14f * getAngle(_vSoldier[i]->getX(), _vSoldier[i]->getY(), _playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY()) <= 270.f))
		{
			_vSoldier[i]->setDirection(true);			
		}
		else
		{
			_vSoldier[i]->setDirection(false);
		}
	}

	// 보스 총알, 로켓 발사
	this->bossBulletFire();
	this->bossRocketFire();

	
	// 에너미 픽셀(지형) 충돌
	this->collideWithPixel();
	// 브로빌 픽셀 충돌
	this->collideBrovilWithPixel();
	// 브로빌 시체 픽셀 충돌
	this->collideBrovilCorpseWithPixel();
	// 시체와 픽셀 충돌
	this->collideWithCorpse();
	
	// 에너미 시야 충돌
	this->collideWithSight();
	// 플레이어와 에너미 총알충돌
	this->collideWithPlayer();
	// 플레이어 총알과 충돌
	this->collideWithPBullet();		
	// 플레이어 수류탄과 충돌	
	this->collideWithPGrenade();	
	// 플레이어와 에너미 총알충돌
	this->collideBulletWithPixel();
	// 플레이어 총알과 브로빌 충돌
	this->collideBrovilwithPBullet();
	
	// 보스 총알, 로켓과 플레이어 충돌
	this->collideWithBossBullet();
	this->collideWithBossRocket();
	
	this->enemyDie();

	_boss->update();
	_eBullet->update();
	_bossBullet->update();
	_bossRocket->update();
	_brovil->update();
}

void enemyManager::render(void)
{
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		_vSoldier[i]->render();		
	}
	
	_boss->render();
	_eBullet->render();
	_bossBullet->render();
	_bossRocket->render();
	_brovil->render();

	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		char str[64];
		sprintf_s(str, "%d", _vSoldier[i]->getBodyStatus());
		TextOut(getMemDC(), 300, 10+i*50, str, strlen(str));
	}
}

//=====================================================================================================================================================================================
//=====================================================================================================================================================================================
//=====================================================================================================================================================================================

void enemyManager::setSoldier(int x, int y)
{
	enemy* _soldier = new soldier;
	_soldier->initSoldier(x, y);
	_vSoldier.push_back(_soldier);
}

void enemyManager::setBrovil(int x, int y)
{
	
}

void enemyManager::enemyFire(int num)
{	
	// 총알발사
	if (_vSoldier[num]->getIsFire())
	{
		// 왼쪽이면
		if (_vSoldier[num]->getDirection())
			_eBullet->fire(_vSoldier[num]->getX() + _vSoldier[num]->getEnemyBodyImage(_vSoldier[num]->getBodyStatus())->getFrameWidth() - _vSoldier[num]->getEnemyArmImage(_vSoldier[num]->getArmStatus())->getFrameWidth(),
				getVEnemy()[num]->getY() + _vSoldier[num]->getEnemyBodyImage(_vSoldier[num]->getBodyStatus())->getFrameHeight() / 2,
				1, getVEnemy()[num]->getDirection());
		
		// 오른쪽이면
		else
			_eBullet->fire(_vSoldier[num]->getX() + _vSoldier[num]->getEnemyArmImage(_vSoldier[num]->getArmStatus())->getFrameWidth(),
				getVEnemy()[num]->getY() + _vSoldier[num]->getEnemyBodyImage(_vSoldier[num]->getBodyStatus())->getFrameHeight() / 2,
				1, getVEnemy()[num]->getDirection());
	}	
}

void enemyManager::bossBulletFire()
{
	// 총알
	if (_boss->getGunStatus() == BB_FIRE && _boss->getBodyStatus() == B_IDLE)
	{
		if (_boss->getTerrorKopter().isLeft)
			_bossBullet->fire(_boss->getTerrorKopter().rcGun.left - 64, _boss->getTerrorKopter().rcGun.top + 20, _boss->getTerrorKopter().isLeft);
		else
			_bossBullet->fire(_boss->getTerrorKopter().rcGun.right, _boss->getTerrorKopter().rcGun.top + 20, _boss->getTerrorKopter().isLeft);
	}
}

void enemyManager::bossRocketFire()
{
	// 보스 발싸! 로켓
	if (_boss->getStatus() == LEFT_FIRE_ROCKET || _boss->getStatus() == RIGHT_FIRE_ROCKET)
	{
		if (_boss->getTerrorKopter().isLeft)
			_bossRocket->fire(_boss->getTerrorKopter().rcGun.left - 60, _boss->getTerrorKopter().rcGun.top + 20, 3, _boss->getTerrorKopter().isLeft);
		else
			_bossRocket->fire(_boss->getTerrorKopter().rcGun.right, _boss->getTerrorKopter().rcGun.top + 20, 3, _boss->getTerrorKopter().isLeft);
	}
}

// 죽은 에너미 벡터에 담기
void enemyManager::saveEnemy(enemyType enemy, deadType deadType, bool isLeft)
{
	deadEnemy _deadEnemy;
	_deadEnemy._enemyType = enemy;
	_deadEnemy._deadType = deadType;
	_deadEnemy.isLeft = isLeft;
	_vDeadEnemyInfo.push_back(_deadEnemy);
}

// 에너미와 픽셀충돌
void enemyManager::collideWithPixel()
{
	// 지형과 충돌(픽셀충돌)
	RECT rc;
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		float x, y;
		x = _vSoldier[i]->getX();
		y = _vSoldier[i]->getY();
		
		// 바닥과 충돌
		if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getRcEnemy(), x, y, _vSoldier[i]->getSpeed(), _vSoldier[i]->getGravity(), ENEMY_BOTTOM))
		{
			if (_vSoldier[i]->getBodyStatus() == ENEMY_FLY_AWAY)
			_vSoldier[i]->setEnemyAngle(2* PI - _vSoldier[i]->getEnemyAngle());

			_vSoldier[i]->setIsOn(true);			
		}
		else
		{
			_vSoldier[i]->setIsOn(false);
		}

		// 윗 천장과 충돌
		if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getRcEnemy(), x, y, _vSoldier[i]->getSpeed(), _vSoldier[i]->getGravity(), ENEMY_TOP))
		{
			_vSoldier[i]->setEnemyAngle(2 * PI - _vSoldier[i]->getEnemyAngle());				
		}
		else
		{
			_vSoldier[i]->setY(y);
		}

		// 적 왼쪽 벽과 충돌
		if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getRcEnemy(), x, y, _vSoldier[i]->getSpeed(), _vSoldier[i]->getGravity(), ENEMY_LEFT))
		{
			_vSoldier[i]->setEnemyAngle(PI - _vSoldier[i]->getEnemyAngle());					
			//if (_vSoldier[i]->getBodyStatus() == ENEMY_KNOCK_BACK || _vSoldier[i]->getBodyStatus() == ENEMY_FLY_AWAY)
			//{
			//	//if (_vSoldier[i]->getDirection()) _vSoldier[i]->setDirection(false);
			//	//else _vSoldier[i]->setDirection(true);
			//}			
		}	
		else
		{
			_vSoldier[i]->setX(x);
		}
	
		// 적 오른쪽 벽과 충돌
		if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getRcEnemy(), x, y, _vSoldier[i]->getSpeed(), _vSoldier[i]->getGravity(), ENEMY_RIGHT))
		{
			_vSoldier[i]->setEnemyAngle(PI - _vSoldier[i]->getEnemyAngle());					
			//if (_vSoldier[i]->getBodyStatus() == ENEMY_KNOCK_BACK && _vSoldier[i]->getBodyStatus() == ENEMY_FLY_AWAY)
			//{
			//	//if (_vSoldier[i]->getDirection()) _vSoldier[i]->setDirection(false);
			//	//else _vSoldier[i]->setDirection(true);
			//}			
		}	
		else
		{
			_vSoldier[i]->setX(x);
		}
	}		
}

// 시체와 픽셀 충돌
void enemyManager::collideWithCorpse()
{
	// 시체 토막 충돌
	RECT rc;
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		for (int j = 0; j < BODY_PART; ++j)
		{
			if (!_vSoldier[i]->getIsApart()) continue;

			float x, y;
			x = _vSoldier[i]->getCorpse()[j].x;
			y = _vSoldier[i]->getCorpse()[j].y;

			// 바닥
			if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getCorpse()[j].rcCorpse, x, y, _vSoldier[i]->getCorpse()[j].speed, _vSoldier[i]->getCorpse()[j].gravity, ENEMY_BOTTOM))
			{
				_vSoldier[i]->getCorpse()[j].angle = 2 * PI - _vSoldier[i]->getCorpse()[j].angle;
				_vSoldier[i]->getCorpse()[j].gravity = 0.f;
			}

			// 천장
			if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getCorpse()[j].rcCorpse, x, y, _vSoldier[i]->getCorpse()[j].speed, _vSoldier[i]->getCorpse()[j].gravity, ENEMY_TOP))
			{
				_vSoldier[i]->getCorpse()[j].angle = 2 * PI - _vSoldier[i]->getCorpse()[j].angle;
			}

			// 왼쪽
			if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getCorpse()[j].rcCorpse, x, y, _vSoldier[i]->getCorpse()[j].speed, _vSoldier[i]->getCorpse()[j].gravity, ENEMY_LEFT))
			{
				_vSoldier[i]->getCorpse()[j].angle = PI - _vSoldier[i]->getCorpse()[j].angle;
			}

			// 오른쪽
			if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getCorpse()[j].rcCorpse, x, y, _vSoldier[i]->getCorpse()[j].speed, _vSoldier[i]->getCorpse()[j].gravity, ENEMY_RIGHT))
			{
				_vSoldier[i]->getCorpse()[j].angle = PI - _vSoldier[i]->getCorpse()[j].angle;
			}

			_vSoldier[i]->getCorpse()[j].x = x;
			_vSoldier[i]->getCorpse()[j].y = y;

		}
	}	
}

void enemyManager::collideWithSight()
{
	// 충돌처리(플레이어) vs 적 시야	
	RECT rc;
	RECT rcPlayer = RectMake(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(),
		_playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameWidth(), _playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameHeight());
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		if (IntersectRect(&rc, &_vSoldier[i]->getRcEnemySight(), &rcPlayer))
		{
			if (!_vSoldier[i]->getIsAlive()) continue;
			// 말풍선 띄우기
			_vSoldier[i]->setIsUncovered(true);
		}
	}
}

//에너미 총알과 플레이어 충돌
void enemyManager::collideWithPlayer()
{
	RECT rc;
	RECT rcPlayer = RectMake(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(),
		_playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameWidth(), _playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameHeight());
	// 충돌처리 (플레이어, 적총알)
	for (int i = 0; i < getEBullet()->getVEnemybullet().size();)
	{
		if (IntersectRect(&rc, &getEBullet()->getVEnemybullet()[i].rc, &rcPlayer))
		{
			// 총알 제거
			getEBullet()->getVEnemybullet()[i].bulletImage->release();
			SAFE_DELETE(getEBullet()->getVEnemybullet()[i].bulletImage);
			getEBullet()->removeBullet(i);
		}
		else
		{
			++i;
		}
	}
}

void enemyManager::collideWithBossBullet()
{
	// 보스총알과 플레이어가 충돌
	RECT rc;
	for (int i = 0; i < BOSS_BULLET_MAX; ++i)
	{
		if (IntersectRect(&rc, &_playerManager->getPlayer()->getRcRambro(), &_bossBullet->getBossBullet()[i].rc))
		{
			// 총알 초기화
			_bossBullet->getBossBullet()[i].fire = false;
		}
	}
}

void enemyManager::collideWithBossRocket()
{
	RECT rc;
	for (int i = 0; i < BOSS_ROCKET_MAX; ++i)
	{
		if (IntersectRect(&rc, &_playerManager->getPlayer()->getRcRambro(), &_bossRocket->getBossRocket()[i].rc))
		{
			_bossRocket->getBossRocket()[i].fire = false;
		}
	}
}

// 플레이어 총알과 적이 충돌
void enemyManager::collideWithPBullet()
{
	RECT rc;
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		for (int j = 0; j < _playerManager->getPBullet()->getVPlayerBullet().size(); ++j)
		{
			if (IntersectRect(&rc, &_playerManager->getPBullet()->getVPlayerBullet()[j].rc, &_vSoldier[i]->getRcEnemy()))
			{	
				if (!_playerManager->getPBullet()->getVPlayerBullet()[j].isActived) continue;
				if (_vSoldier[i]->getIsApart()) continue;

				if (_vSoldier[i]->getDirection() != _playerManager->getPBullet()->getVPlayerBullet()[j].isLeft)
				{
					_vSoldier[i]->setDirection(_playerManager->getPBullet()->getVPlayerBullet()[j].isLeft);
				}
			
				_vSoldier[i]->setIsUncovered(false);
				_vSoldier[i]->setIsStrange(false);
				_vSoldier[i]->setHP(_vSoldier[i]->getHP() - 1);

				if (_vSoldier[i]->getBodyStatus() != ENEMY_KNOCK_BACK && _vSoldier[i]->getBodyStatus() != ENEMY_DEAD && _vSoldier[i]->getBodyStatus() != ENEMY_FLY_AWAY)
				{					
					if (_vSoldier[i]->getDirection())
						_vSoldier[i]->setBodyImageIndex(_vSoldier[i]->getEnemyBodyImage(ENEMY_KNOCK_BACK)->getMaxFrameX()-1);
					else
						_vSoldier[i]->setBodyImageIndex(0);
					
					_vSoldier[i]->setBodyStatus(ENEMY_KNOCK_BACK);								
				}

				if (_vSoldier[i]->getBodyStatus() == ENEMY_DEAD)
				{
					_vSoldier[i]->deadMove();
				}

				// 죽은 적 벡터에 담기
				this->saveEnemy(SOLDIER, BULLET, _vSoldier[i]->getDirection());
				break;
			}
		}
	}
}

// 수류탄과 에너미 충돌
void enemyManager::collideWithPGrenade()
{
	RECT rc;
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		for (int j = 0; j < _playerManager->getPGrenade()->getVPlayerGrenade().size(); ++j)
		{
			if (IntersectRect(&rc, &_playerManager->getPGrenade()->getVPlayerGrenade()[j].rc, &_vSoldier[i]->getRcEnemy()))
			{
				if (_vSoldier[i]->getIsApart()) continue;
				if (_vSoldier[i]->getBodyStatus() == ENEMY_FLY_AWAY) continue;

				if (_vSoldier[i]->getDirection() != _playerManager->getPGrenade()->getVPlayerGrenade()[j].isLeft)
				{
					_vSoldier[i]->setDirection(_playerManager->getPGrenade()->getVPlayerGrenade()[j].isLeft);
				}
				_vSoldier[i]->setIsUncovered(false);
				_vSoldier[i]->setIsStrange(false);

				if (_vSoldier[i]->getBodyStatus() != ENEMY_KNOCK_BACK && _vSoldier[i]->getBodyStatus() != ENEMY_DEAD && _vSoldier[i]->getBodyStatus() != ENEMY_FLY_AWAY)
				{
					if (_vSoldier[i]->getDirection())
						_vSoldier[i]->setBodyImageIndex(_vSoldier[i]->getEnemyBodyImage(ENEMY_FLY_AWAY)->getMaxFrameX() - 1);
					else
						_vSoldier[i]->setBodyImageIndex(0);

					_vSoldier[i]->setBodyStatus(ENEMY_FLY_AWAY);

				}

				if (_vSoldier[i]->getBodyStatus() == ENEMY_DEAD)
				{
					_vSoldier[i]->deadMove();
				}

				// 죽은 적 벡터에 담기
				this->saveEnemy(SOLDIER, GRENADE, _vSoldier[i]->getDirection());
			}
		}
	}
}

// 에너미 총알과 픽셀 충돌
void enemyManager::collideBulletWithPixel()
{
	RECT rc;
	for (int i = 0; i < _eBullet->getVEnemybullet().size();)
	{
		float x, y;
		x = _eBullet->getVEnemybullet()[i].x;
		y = _eBullet->getVEnemybullet()[i].y;

		// 바닥
		if (COLLISIONMANAGER->pixelCollision(_eBullet->getVEnemybullet()[i].rc, x, y, _eBullet->getVEnemybullet()[i].speed, _eBullet->getVEnemybullet()[i].gravity, ENEMY_BOTTOM))
		{
			_eBullet->removeBullet(i);
		}
		
		// 천장
		else if (COLLISIONMANAGER->pixelCollision(_eBullet->getVEnemybullet()[i].rc, x, y, _eBullet->getVEnemybullet()[i].speed, _eBullet->getVEnemybullet()[i].gravity, ENEMY_TOP))
		{
			_eBullet->removeBullet(i);
		}		

		// 왼쪽
		else if (COLLISIONMANAGER->pixelCollision(_eBullet->getVEnemybullet()[i].rc, x, y, _eBullet->getVEnemybullet()[i].speed, _eBullet->getVEnemybullet()[i].gravity, ENEMY_LEFT))
		{
			_eBullet->removeBullet(i);
		}		

		// 오른쪽
		else if (COLLISIONMANAGER->pixelCollision(_eBullet->getVEnemybullet()[i].rc, x, y, _eBullet->getVEnemybullet()[i].speed, _eBullet->getVEnemybullet()[i].gravity, ENEMY_RIGHT))
		{
			_eBullet->removeBullet(i);
		}

		else
		{
			++i;
		}
	}
}

// 플레이어 총알과 브로빌 충돌
void enemyManager::collideBrovilwithPBullet()
{
	RECT rc;
	for (int i = 0; i < _playerManager->getPBullet()->getVPlayerBullet().size(); ++i)
	{
		if (IntersectRect(&rc, &_playerManager->getPBullet()->getVPlayerBullet()[i].rc, &_brovil->getRcBrovil()))
		{
			if (_brovil->getIsApart()) continue;

			if (_brovil->getDirection() != _playerManager->getPBullet()->getVPlayerBullet()[i].isLeft)
			{
				_brovil->setDirection(_playerManager->getPBullet()->getVPlayerBullet()[i].isLeft);
			}

			//_brovil->setIsUncovered(false);
			//_brovil->setIsStrange(false);
			_brovil->setHP(_brovil->getHP() - 1);

			if (_brovil->getBrovilStatus() != BROVIL_KNOCK_BACK && _brovil->getBrovilStatus() != BROVIL_DEAD && _brovil->getBrovilStatus() != BROVIL_FLY_AWAY)
			{
				if (_brovil->getDirection())
					_brovil->setBrovilImageIndex(_brovil->getBrovilImage(BROVIL_KNOCK_BACK)->getMaxFrameX() - 1);
				else
					_brovil->setBrovilImageIndex(0);

				_brovil->setBrovilStatus(BROVIL_KNOCK_BACK);
			}

			if (_brovil->getBrovilStatus() == BROVIL_DEAD)
			{
				_brovil->deadMove();
			}

			EFFECTMANAGER->bloodSplash(_brovil->getX() + _brovil->getBrovilImage(_brovil->getBrovilStatus())->getFrameWidth()/2, _brovil->getY() + _brovil->getBrovilImage(_brovil->getBrovilStatus())->getFrameHeight()/2,
				_brovil->getDirection());
			// 죽은 적 벡터에 담기
			this->saveEnemy(BROVIL, BULLET, _brovil->getDirection());
			_isClear = true;
		}		
	}
}

// 브로빌 플레이어 수류탄에 맞음
void enemyManager::collideBrovilwithPGrenade()
{
	RECT rc;	
	for (int j = 0; j < _playerManager->getPGrenade()->getVPlayerGrenade().size(); ++j)
	{
		if (IntersectRect(&rc, &_playerManager->getPGrenade()->getVPlayerGrenade()[j].rc, &_brovil->getRcBrovil()))
		{
			if (_brovil->getIsApart()) continue;
			if (_brovil->getBrovilStatus() == ENEMY_FLY_AWAY) continue;

			if (_brovil->getDirection() != _playerManager->getPGrenade()->getVPlayerGrenade()[j].isLeft)
			{
				_brovil->setDirection(_playerManager->getPGrenade()->getVPlayerGrenade()[j].isLeft);
			}
			//_brovil->setIsUncovered(false);
			//_brovil->setIsStrange(false);

			if (_brovil->getBrovilStatus() != BROVIL_KNOCK_BACK && _brovil->getBrovilStatus() != BROVIL_DEAD && _brovil->getBrovilStatus() != BROVIL_FLY_AWAY)
			{
				if (_brovil->getDirection())
					_brovil->setBrovilImageIndex(_brovil->getBrovilImage(BROVIL_FLY_AWAY)->getMaxFrameX() - 1);
				else
					_brovil->setBrovilImageIndex(0);

				_brovil->setBrovilStatus(BROVIL_FLY_AWAY);

			}

			if (_brovil->getBrovilStatus() == ENEMY_DEAD)
			{
				_brovil->deadMove();
			}

			// 죽은 적 벡터에 담기
			this->saveEnemy(BROVIL, GRENADE, _brovil->getDirection());
		}
	}	
}

// 브로빌 픽셀 충돌(지형)
void enemyManager::collideBrovilWithPixel()
{
	float x, y;
	x = _brovil->getX();
	y = _brovil->getY();

	// 바닥과 충돌
	if (COLLISIONMANAGER->pixelCollision(_brovil->getRcBrovil(), x, y, _brovil->getSpeed(), _brovil->getGravity(), ENEMY_BOTTOM))
	{
		if (_brovil->getBrovilStatus() == BROVIL_FLY_AWAY)
			_brovil->setEnemyAngle(2 * PI - _brovil->getEnemyAngle());

		_brovil->setIsOn(true);
	}
	else
	{
		_brovil->setIsOn(false);
	}

	// 윗 천장과 충돌
	if (COLLISIONMANAGER->pixelCollision(_brovil->getRcBrovil(), x, y, _brovil->getSpeed(), _brovil->getGravity(), ENEMY_TOP))
	{
		_brovil->setEnemyAngle(2 * PI - _brovil->getEnemyAngle());
	}
	else
	{
		_brovil->setY(y);
	}

	// 적 왼쪽 벽과 충돌
	if (COLLISIONMANAGER->pixelCollision(_brovil->getRcBrovil(), x, y, _brovil->getSpeed(), _brovil->getGravity(), ENEMY_LEFT))
	{
		_brovil->setEnemyAngle(PI - _brovil->getEnemyAngle());
		//if (_vSoldier[i]->getBodyStatus() == ENEMY_KNOCK_BACK || _vSoldier[i]->getBodyStatus() == ENEMY_FLY_AWAY)
		//{
		//	//if (_vSoldier[i]->getDirection()) _vSoldier[i]->setDirection(false);
		//	//else _vSoldier[i]->setDirection(true);
		//}			
	}
	else
	{
		_brovil->setX(x);
	}

	// 적 오른쪽 벽과 충돌
	if (COLLISIONMANAGER->pixelCollision(_brovil->getRcBrovil(), x, y, _brovil->getSpeed(), _brovil->getGravity(), ENEMY_RIGHT))
	{
		_brovil->setEnemyAngle(PI - _brovil->getEnemyAngle());
		//if (_vSoldier[i]->getBodyStatus() == ENEMY_KNOCK_BACK && _vSoldier[i]->getBodyStatus() == ENEMY_FLY_AWAY)
		//{
		//	//if (_vSoldier[i]->getDirection()) _vSoldier[i]->setDirection(false);
		//	//else _vSoldier[i]->setDirection(true);
		//}			
	}
	else
	{
		_brovil->setX(x);
	}
}

// 브로빌 시체와 픽셀(지형) 충돌
void enemyManager::collideBrovilCorpseWithPixel()
{
	// 시체 토막 충돌
	RECT rc;	
	for (int j = 0; j < BODY_PART; ++j)
	{
		if (!_brovil->getIsApart()) continue;

		float x, y;
		x = _brovil->getCorpse()[j].x;
		y = _brovil->getCorpse()[j].y;

		// 바닥
		if (COLLISIONMANAGER->pixelCollision(_brovil->getCorpse()[j].rcCorpse, x, y, _brovil->getCorpse()[j].speed, _brovil->getCorpse()[j].gravity, ENEMY_BOTTOM))
		{
			_brovil->getCorpse()[j].angle = 2 * PI - _brovil->getCorpse()[j].angle;
			_brovil->getCorpse()[j].gravity = 0.f;
		}

		// 천장
		if (COLLISIONMANAGER->pixelCollision(_brovil->getCorpse()[j].rcCorpse, x, y, _brovil->getCorpse()[j].speed, _brovil->getCorpse()[j].gravity, ENEMY_TOP))
		{
			_brovil->getCorpse()[j].angle = 2 * PI - _brovil->getCorpse()[j].angle;
		}

		// 왼쪽
		if (COLLISIONMANAGER->pixelCollision(_brovil->getCorpse()[j].rcCorpse, x, y, _brovil->getCorpse()[j].speed, _brovil->getCorpse()[j].gravity, ENEMY_LEFT))
		{
			_brovil->getCorpse()[j].angle = PI - _brovil->getCorpse()[j].angle;
		}

		// 오른쪽
		if (COLLISIONMANAGER->pixelCollision(_brovil->getCorpse()[j].rcCorpse, x, y, _brovil->getCorpse()[j].speed, _brovil->getCorpse()[j].gravity, ENEMY_RIGHT))
		{
			_brovil->getCorpse()[j].angle = PI - _brovil->getCorpse()[j].angle;
		}

		_brovil->getCorpse()[j].x = x;
		_brovil->getCorpse()[j].y = y;

	}	
}

// 스테이지 클리어냐?
bool enemyManager::isClear()
{
	if (_isClear)
	{
		return true;
	}
	else
		return false;
}

// 에너미 플레이어 총알맞아 죽음
void enemyManager::enemyDie()
{
	
}
