#include "stdafx.h"
#include "enemyManager.h"
#include "playerManager.h"
#include "mapData.h"

HRESULT enemyManager::init(void)
{
	// �÷��̾�Ŵ��� Ŭ���� ��������
	this->setPlayerManager(_playerManager);
	// �ʵ����� ��������
	this->setMapData(_mapData);	

	//���ʹ� Ŭ���� ��ü ���� �� �ʱ�ȭ
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

		// �÷��̾� ���⿡ ���� ������ �ٲ� (�߰߻����϶�)
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

	// ���� �Ѿ�, ���� �߻�
	this->bossBulletFire();
	this->bossRocketFire();

	
	// ���ʹ� �ȼ�(����) �浹
	this->collideWithPixel();
	// ��κ� �ȼ� �浹
	this->collideBrovilWithPixel();
	// ��κ� ��ü �ȼ� �浹
	this->collideBrovilCorpseWithPixel();
	// ��ü�� �ȼ� �浹
	this->collideWithCorpse();
	
	// ���ʹ� �þ� �浹
	this->collideWithSight();
	// �÷��̾�� ���ʹ� �Ѿ��浹
	this->collideWithPlayer();
	// �÷��̾� �Ѿ˰� �浹
	this->collideWithPBullet();		
	// �÷��̾� ����ź�� �浹	
	this->collideWithPGrenade();	
	// �÷��̾�� ���ʹ� �Ѿ��浹
	this->collideBulletWithPixel();
	// �÷��̾� �Ѿ˰� ��κ� �浹
	this->collideBrovilwithPBullet();
	
	// ���� �Ѿ�, ���ϰ� �÷��̾� �浹
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
	// �Ѿ˹߻�
	if (_vSoldier[num]->getIsFire())
	{
		// �����̸�
		if (_vSoldier[num]->getDirection())
			_eBullet->fire(_vSoldier[num]->getX() + _vSoldier[num]->getEnemyBodyImage(_vSoldier[num]->getBodyStatus())->getFrameWidth() - _vSoldier[num]->getEnemyArmImage(_vSoldier[num]->getArmStatus())->getFrameWidth(),
				getVEnemy()[num]->getY() + _vSoldier[num]->getEnemyBodyImage(_vSoldier[num]->getBodyStatus())->getFrameHeight() / 2,
				1, getVEnemy()[num]->getDirection());
		
		// �������̸�
		else
			_eBullet->fire(_vSoldier[num]->getX() + _vSoldier[num]->getEnemyArmImage(_vSoldier[num]->getArmStatus())->getFrameWidth(),
				getVEnemy()[num]->getY() + _vSoldier[num]->getEnemyBodyImage(_vSoldier[num]->getBodyStatus())->getFrameHeight() / 2,
				1, getVEnemy()[num]->getDirection());
	}	
}

void enemyManager::bossBulletFire()
{
	// �Ѿ�
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
	// ���� �߽�! ����
	if (_boss->getStatus() == LEFT_FIRE_ROCKET || _boss->getStatus() == RIGHT_FIRE_ROCKET)
	{
		if (_boss->getTerrorKopter().isLeft)
			_bossRocket->fire(_boss->getTerrorKopter().rcGun.left - 60, _boss->getTerrorKopter().rcGun.top + 20, 3, _boss->getTerrorKopter().isLeft);
		else
			_bossRocket->fire(_boss->getTerrorKopter().rcGun.right, _boss->getTerrorKopter().rcGun.top + 20, 3, _boss->getTerrorKopter().isLeft);
	}
}

// ���� ���ʹ� ���Ϳ� ���
void enemyManager::saveEnemy(enemyType enemy, deadType deadType, bool isLeft)
{
	deadEnemy _deadEnemy;
	_deadEnemy._enemyType = enemy;
	_deadEnemy._deadType = deadType;
	_deadEnemy.isLeft = isLeft;
	_vDeadEnemyInfo.push_back(_deadEnemy);
}

// ���ʹ̿� �ȼ��浹
void enemyManager::collideWithPixel()
{
	// ������ �浹(�ȼ��浹)
	RECT rc;
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		float x, y;
		x = _vSoldier[i]->getX();
		y = _vSoldier[i]->getY();
		
		// �ٴڰ� �浹
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

		// �� õ��� �浹
		if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getRcEnemy(), x, y, _vSoldier[i]->getSpeed(), _vSoldier[i]->getGravity(), ENEMY_TOP))
		{
			_vSoldier[i]->setEnemyAngle(2 * PI - _vSoldier[i]->getEnemyAngle());				
		}
		else
		{
			_vSoldier[i]->setY(y);
		}

		// �� ���� ���� �浹
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
	
		// �� ������ ���� �浹
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

// ��ü�� �ȼ� �浹
void enemyManager::collideWithCorpse()
{
	// ��ü �丷 �浹
	RECT rc;
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		for (int j = 0; j < BODY_PART; ++j)
		{
			if (!_vSoldier[i]->getIsApart()) continue;

			float x, y;
			x = _vSoldier[i]->getCorpse()[j].x;
			y = _vSoldier[i]->getCorpse()[j].y;

			// �ٴ�
			if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getCorpse()[j].rcCorpse, x, y, _vSoldier[i]->getCorpse()[j].speed, _vSoldier[i]->getCorpse()[j].gravity, ENEMY_BOTTOM))
			{
				_vSoldier[i]->getCorpse()[j].angle = 2 * PI - _vSoldier[i]->getCorpse()[j].angle;
				_vSoldier[i]->getCorpse()[j].gravity = 0.f;
			}

			// õ��
			if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getCorpse()[j].rcCorpse, x, y, _vSoldier[i]->getCorpse()[j].speed, _vSoldier[i]->getCorpse()[j].gravity, ENEMY_TOP))
			{
				_vSoldier[i]->getCorpse()[j].angle = 2 * PI - _vSoldier[i]->getCorpse()[j].angle;
			}

			// ����
			if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getCorpse()[j].rcCorpse, x, y, _vSoldier[i]->getCorpse()[j].speed, _vSoldier[i]->getCorpse()[j].gravity, ENEMY_LEFT))
			{
				_vSoldier[i]->getCorpse()[j].angle = PI - _vSoldier[i]->getCorpse()[j].angle;
			}

			// ������
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
	// �浹ó��(�÷��̾�) vs �� �þ�	
	RECT rc;
	RECT rcPlayer = RectMake(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(),
		_playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameWidth(), _playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameHeight());
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		if (IntersectRect(&rc, &_vSoldier[i]->getRcEnemySight(), &rcPlayer))
		{
			if (!_vSoldier[i]->getIsAlive()) continue;
			// ��ǳ�� ����
			_vSoldier[i]->setIsUncovered(true);
		}
	}
}

//���ʹ� �Ѿ˰� �÷��̾� �浹
void enemyManager::collideWithPlayer()
{
	RECT rc;
	RECT rcPlayer = RectMake(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(),
		_playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameWidth(), _playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameHeight());
	// �浹ó�� (�÷��̾�, ���Ѿ�)
	for (int i = 0; i < getEBullet()->getVEnemybullet().size();)
	{
		if (IntersectRect(&rc, &getEBullet()->getVEnemybullet()[i].rc, &rcPlayer))
		{
			// �Ѿ� ����
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
	// �����Ѿ˰� �÷��̾ �浹
	RECT rc;
	for (int i = 0; i < BOSS_BULLET_MAX; ++i)
	{
		if (IntersectRect(&rc, &_playerManager->getPlayer()->getRcRambro(), &_bossBullet->getBossBullet()[i].rc))
		{
			// �Ѿ� �ʱ�ȭ
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

// �÷��̾� �Ѿ˰� ���� �浹
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

				// ���� �� ���Ϳ� ���
				this->saveEnemy(SOLDIER, BULLET, _vSoldier[i]->getDirection());
				break;
			}
		}
	}
}

// ����ź�� ���ʹ� �浹
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

				// ���� �� ���Ϳ� ���
				this->saveEnemy(SOLDIER, GRENADE, _vSoldier[i]->getDirection());
			}
		}
	}
}

// ���ʹ� �Ѿ˰� �ȼ� �浹
void enemyManager::collideBulletWithPixel()
{
	RECT rc;
	for (int i = 0; i < _eBullet->getVEnemybullet().size();)
	{
		float x, y;
		x = _eBullet->getVEnemybullet()[i].x;
		y = _eBullet->getVEnemybullet()[i].y;

		// �ٴ�
		if (COLLISIONMANAGER->pixelCollision(_eBullet->getVEnemybullet()[i].rc, x, y, _eBullet->getVEnemybullet()[i].speed, _eBullet->getVEnemybullet()[i].gravity, ENEMY_BOTTOM))
		{
			_eBullet->removeBullet(i);
		}
		
		// õ��
		else if (COLLISIONMANAGER->pixelCollision(_eBullet->getVEnemybullet()[i].rc, x, y, _eBullet->getVEnemybullet()[i].speed, _eBullet->getVEnemybullet()[i].gravity, ENEMY_TOP))
		{
			_eBullet->removeBullet(i);
		}		

		// ����
		else if (COLLISIONMANAGER->pixelCollision(_eBullet->getVEnemybullet()[i].rc, x, y, _eBullet->getVEnemybullet()[i].speed, _eBullet->getVEnemybullet()[i].gravity, ENEMY_LEFT))
		{
			_eBullet->removeBullet(i);
		}		

		// ������
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

// �÷��̾� �Ѿ˰� ��κ� �浹
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
			// ���� �� ���Ϳ� ���
			this->saveEnemy(BROVIL, BULLET, _brovil->getDirection());
			_isClear = true;
		}		
	}
}

// ��κ� �÷��̾� ����ź�� ����
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

			// ���� �� ���Ϳ� ���
			this->saveEnemy(BROVIL, GRENADE, _brovil->getDirection());
		}
	}	
}

// ��κ� �ȼ� �浹(����)
void enemyManager::collideBrovilWithPixel()
{
	float x, y;
	x = _brovil->getX();
	y = _brovil->getY();

	// �ٴڰ� �浹
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

	// �� õ��� �浹
	if (COLLISIONMANAGER->pixelCollision(_brovil->getRcBrovil(), x, y, _brovil->getSpeed(), _brovil->getGravity(), ENEMY_TOP))
	{
		_brovil->setEnemyAngle(2 * PI - _brovil->getEnemyAngle());
	}
	else
	{
		_brovil->setY(y);
	}

	// �� ���� ���� �浹
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

	// �� ������ ���� �浹
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

// ��κ� ��ü�� �ȼ�(����) �浹
void enemyManager::collideBrovilCorpseWithPixel()
{
	// ��ü �丷 �浹
	RECT rc;	
	for (int j = 0; j < BODY_PART; ++j)
	{
		if (!_brovil->getIsApart()) continue;

		float x, y;
		x = _brovil->getCorpse()[j].x;
		y = _brovil->getCorpse()[j].y;

		// �ٴ�
		if (COLLISIONMANAGER->pixelCollision(_brovil->getCorpse()[j].rcCorpse, x, y, _brovil->getCorpse()[j].speed, _brovil->getCorpse()[j].gravity, ENEMY_BOTTOM))
		{
			_brovil->getCorpse()[j].angle = 2 * PI - _brovil->getCorpse()[j].angle;
			_brovil->getCorpse()[j].gravity = 0.f;
		}

		// õ��
		if (COLLISIONMANAGER->pixelCollision(_brovil->getCorpse()[j].rcCorpse, x, y, _brovil->getCorpse()[j].speed, _brovil->getCorpse()[j].gravity, ENEMY_TOP))
		{
			_brovil->getCorpse()[j].angle = 2 * PI - _brovil->getCorpse()[j].angle;
		}

		// ����
		if (COLLISIONMANAGER->pixelCollision(_brovil->getCorpse()[j].rcCorpse, x, y, _brovil->getCorpse()[j].speed, _brovil->getCorpse()[j].gravity, ENEMY_LEFT))
		{
			_brovil->getCorpse()[j].angle = PI - _brovil->getCorpse()[j].angle;
		}

		// ������
		if (COLLISIONMANAGER->pixelCollision(_brovil->getCorpse()[j].rcCorpse, x, y, _brovil->getCorpse()[j].speed, _brovil->getCorpse()[j].gravity, ENEMY_RIGHT))
		{
			_brovil->getCorpse()[j].angle = PI - _brovil->getCorpse()[j].angle;
		}

		_brovil->getCorpse()[j].x = x;
		_brovil->getCorpse()[j].y = y;

	}	
}

// �������� Ŭ�����?
bool enemyManager::isClear()
{
	if (_isClear)
	{
		return true;
	}
	else
		return false;
}

// ���ʹ� �÷��̾� �Ѿ˸¾� ����
void enemyManager::enemyDie()
{
	
}
