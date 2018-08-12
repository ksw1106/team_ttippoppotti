#include "stdafx.h"
#include "enemyManager.h"
#include "playerManager.h"
#include "mapData.h"

HRESULT enemyManager::init(int stageNum)
{
	_stageNum = stageNum;

	// �÷��̾�Ŵ��� Ŭ���� ��������
	this->setPlayerManager(_playerManager);
	// �ʵ����� ��������
	this->setMapData(_mapData);	
		
	_eBullet = new eBullet;
	_eBullet->init(1, 800.f);
		
	_effectCount = _count = 0;
	_isClear = false;

	if (stageNum == 1)
	{
		this->setDog(500, 1500, 1);
		//���ʹ� Ŭ���� ��ü ���� �� �ʱ�ȭ
		this->setSoldier(3800, 1000);
		this->setSoldier(3300, 1200);
		this->setSoldier(3600, 1400);
		this->setSoldier(3200, 1600);
		//this->setBrovil(3700, 1000, 5);

		_brovil = new brovil;
		_brovil->init(3200, 1000);
		_boss = new boss;
		_boss->init(4000.f, 800.f);
		_bossBullet = new bossBullet;
		_bossBullet->init();
		_bossRocket = new bossRocket;
		_bossRocket->init(50.f);
		_hpBar = new progressBar;
		_hpBar->init("enemyImage/bossImage/boss_hpbar_red", "enemyImage/bossImage/boss_hpbar_white", "enemyImage/bossImage/boss_hpbar_black",
			WINSIZEX / 2 - 1062 / 2, 57, WINSIZEX / 2 - 1062 / 2, 57, WINSIZEX / 2 - 1076 / 2, 50, 1062, 17, 1062, 17, 1076, 30);
	}
	else if (stageNum == 2)
	{
		//this->setSoldier();
		//this->setSoldier();
		//this->setSoldier();
		//this->setSoldier();
		//this->setSoldier();
		//this->setSoldier();
		//this->setSoldier();

	}

	return S_OK;
}

void enemyManager::release(void)
{
	//����� �������� ���� �ؾ��մϴ�.
	if (_stageNum == 1)
	{
		_brovil->release();
		SAFE_DELETE(_brovil);
		_boss->release();
		SAFE_DELETE(_boss);
		_bossBullet->release();
		SAFE_DELETE(_bossBullet);
		_bossRocket->release();
		SAFE_DELETE(_bossRocket);
		_hpBar->release();
		SAFE_DELETE(_hpBar);
		
	}
	else if (_stageNum == 2)
	{
	}
	
	_eBullet->release();
	SAFE_DELETE(_eBullet);
	
}

void enemyManager::update(void)
{
	if (_stageNum == 1)
	{
		_brovil->update();
		for (int i = 0; i < _vDog.size(); ++i)
		{
			_vDog[i]->update();
		}
		_boss->update();
		_bossBullet->update();
		_bossRocket->update();
		_hpBar->update();
		_hpBar->setGauge(_boss->getHP(), 1000);
		// ��κ� �ȼ� �浹
		this->collideBrovilWithPixel();
		// ��κ� ��ü �ȼ� �浹
		this->collideBrovilCorpseWithPixel();

	}
	else if (_stageNum == 2)
	{
	}

	_eBullet->update();
	
	// ���� ����ٲ�
	this->changeDirection();
	
	for (int i = 0; i < _vSoldier.size(); ++i)
	{		
		_vSoldier[i]->update();			
	}
	
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		if (_vSoldier[i]->getIsAlive())
		{
			this->enemyFire(i);
		}
	}
	
		
	// ���ʹ� �ȼ�(����) �浹
	this->collideWithPixel();
	// ���ʹ� ��ü �ȼ� �浹
	this->collideWithCorpse();
	
	// ���ʹ� �þ߿� �÷��̾� �浹
	this->collideWithSight();
	// ���ʹ� �Ѿ˰� �÷��̾� �浹
	this->collideWithPlayer();
	// �÷��̾� �Ѿ˰� ���ʹ� �浹
	this->collideWithPBullet();		
	// �÷��̾� ����ź�� ���ʹ� �浹	
	this->collideWithPGrenade();	
	// ���ʹ� �Ѿ˰� �ȼ� �浹
	this->collideBulletWithPixel();
	// �Ҿƹ��� �Ѿ� vs ���ʹ� �浹
	this->collideWithGBullet();
	
	if (_stageNum == 1)
	{
		// �÷��̾� �Ѿ˰� ��κ� �浹
		this->collideBrovilwithPBullet();
		// ���׿� �ȼ��浹��
		this->collideDogSightWithPlayer();
		this->collideDogWithPlayer();
		this->collideDogWithPixel();
		this->collideDogWithPBullet();
		this->collideDogWithGBullet();
		this->collideDogCorpseWithPixel();


		// ���� �Ѿ�, ���� vs ����� �浹
		this->collideWithBossBullet();
		this->collideWithBossRocket();
		this->bossDirChange();
		this->PBulletHitBoss();
		// ���� ���� vs �����浹
		this->collideBossRocketWithPixel();
		// �Ҿƹ��� �Ѿ� vs ����
		this->collideBossWithGBullet();
		this->collideBossWithGGrenade();

	
		// ���� �Ѿ�, ���� �߻�
		this->bossBulletFire();
		this->bossRocketFire();
	}
	else if (_stageNum == 2)
	{
	}

}

void enemyManager::render(void)
{
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		_vSoldier[i]->render();		
	}
	
	_eBullet->render();
	if (_stageNum == 1)
	{
		_brovil->render();
		for (int i = 0; i < _vDog.size(); ++i)
		{
			_vDog[i]->render();
		}
		_boss->render();
		_bossBullet->render();
		_bossRocket->render();
		
		if (_boss->getIsAlive())
		{			
			if (_boss->radarIn(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), 1500.f))
				_hpBar->render();
		}
	}
	
	if (_stageNum == 2)
	{
	}
		

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

void enemyManager::setDog(int x, int y, bool isLeft)
{
	dog* _dog = new dog;
	_dog->initDog(x, y, isLeft);
	_vDog.push_back(_dog);
}

bool enemyManager::isEffect(int frame)
{	
	if (!_isEffect)
	{
		_isEffect = true;
		return true;
	}
	else
	{
		_isEffect = false;
		return false;
	}
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
				10, getVEnemy()[num]->getDirection());
		
		// �������̸�
		else
			_eBullet->fire(_vSoldier[num]->getX() + _vSoldier[num]->getEnemyArmImage(_vSoldier[num]->getArmStatus())->getFrameWidth(),
				getVEnemy()[num]->getY() + _vSoldier[num]->getEnemyBodyImage(_vSoldier[num]->getBodyStatus())->getFrameHeight() / 2,
				10, getVEnemy()[num]->getDirection());
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
		if (_boss->getTerrorKopter().isLeft == 1)
			_bossRocket->fire(_boss->getTerrorKopter().rcGun.left - 60, _boss->getTerrorKopter().rcGun.top + 20, 3, 1);
		else
			_bossRocket->fire(_boss->getTerrorKopter().rcGun.right, _boss->getTerrorKopter().rcGun.top + 20, 3, 0);
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

void enemyManager::changeDirection()
{
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
}

void enemyManager::soldierDieWithBullet(int i)
{
	
	_vSoldier[i]->setIsUncovered(false);
	_vSoldier[i]->setIsStrange(false);
	_vSoldier[i]->setHP(_vSoldier[i]->getHP() - 1);

	if (_vSoldier[i]->getBodyStatus() != ENEMY_KNOCK_BACK && _vSoldier[i]->getBodyStatus() != ENEMY_DEAD && _vSoldier[i]->getBodyStatus() != ENEMY_FLY_AWAY)
	{
		if (_vSoldier[i]->getDirection())
			_vSoldier[i]->setBodyImageIndex(_vSoldier[i]->getEnemyBodyImage(ENEMY_KNOCK_BACK)->getMaxFrameX() - 1);
		else
			_vSoldier[i]->setBodyImageIndex(0);

		_vSoldier[i]->setBodyStatus(ENEMY_KNOCK_BACK);
	}

	if (_vSoldier[i]->getBodyStatus() == ENEMY_DEAD)
	{
		_vSoldier[i]->deadMove();
	}

	// �������� ȿ��
	if (_isEffect)
	{
		EFFECTMANAGER->bloodSplash(_vSoldier[i]->getX() + _vSoldier[i]->getEnemyBodyImage(_vSoldier[i]->getBodyStatus())->getFrameWidth() / 2,
			_vSoldier[i]->getY() + _vSoldier[i]->getEnemyBodyImage(_vSoldier[i]->getBodyStatus())->getFrameHeight() / 2,
			_vSoldier[i]->getDirection());
	}

	// ���� �� ���Ϳ� ���
	this->saveEnemy(SOLDIER, BULLET, _vSoldier[i]->getDirection());
}

void enemyManager::soldierDieWithGrenade(int i)
{
	_vSoldier[i]->setIsUncovered(false);
	_vSoldier[i]->setIsStrange(false);
	_vSoldier[i]->setHP(_vSoldier[i]->getHP() - 1);

	if (_vSoldier[i]->getBodyStatus() != ENEMY_KNOCK_BACK && _vSoldier[i]->getBodyStatus() != ENEMY_DEAD && _vSoldier[i]->getBodyStatus() != ENEMY_FLY_AWAY)
	{
		if (_vSoldier[i]->getDirection())
			_vSoldier[i]->setBodyImageIndex(_vSoldier[i]->getEnemyBodyImage(ENEMY_KNOCK_BACK)->getMaxFrameX() - 1);
		else
			_vSoldier[i]->setBodyImageIndex(0);

		_vSoldier[i]->setBodyStatus(ENEMY_FLY_AWAY);
	}

	if (_vSoldier[i]->getBodyStatus() == ENEMY_DEAD)
	{
		_vSoldier[i]->deadMove();
	}

	// �������� ȿ��
	if (_isEffect)
	{
		EFFECTMANAGER->bloodSplash(_vSoldier[i]->getX() + _vSoldier[i]->getEnemyBodyImage(_vSoldier[i]->getBodyStatus())->getFrameWidth() / 2,
			_vSoldier[i]->getY() + _vSoldier[i]->getEnemyBodyImage(_vSoldier[i]->getBodyStatus())->getFrameHeight() / 2,
			_vSoldier[i]->getDirection());
	}

	this->saveEnemy(SOLDIER, GRENADE, _vSoldier[i]->getDirection());
}

// ��κ� ����
void enemyManager::brovilDieWithBullet()
{
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

	//if (this->isEffect(2))
	//{
	//	EFFECTMANAGER->bloodSplash(_brovil->getX() + _brovil->getBrovilImage(_brovil->getBrovilStatus())->getFrameWidth()/2, _brovil->getY() + _brovil->getBrovilImage(_brovil->getBrovilStatus())->getFrameHeight()/2,
	//		_brovil->getDirection());
	//}
	// ���� �� ���Ϳ� ���
	this->saveEnemy(BROVIL, BULLET, _brovil->getDirection());
	_isClear = true;
}

void enemyManager::brovilDieWithGrenade()
{
	_brovil->setHP(_brovil->getHP() - 1);

	if (_brovil->getBrovilStatus() != BROVIL_KNOCK_BACK && _brovil->getBrovilStatus() != BROVIL_DEAD && _brovil->getBrovilStatus() != BROVIL_FLY_AWAY)
	{
		if (_brovil->getDirection())
			_brovil->setBrovilImageIndex(_brovil->getBrovilImage(BROVIL_KNOCK_BACK)->getMaxFrameX() - 1);
		else
			_brovil->setBrovilImageIndex(0);

		_brovil->setBrovilStatus(BROVIL_FLY_AWAY);
	}

	if (_brovil->getBrovilStatus() == BROVIL_DEAD)
	{
		_brovil->deadMove();
	}

	//if (this->isEffect(2))
	//{
	//	EFFECTMANAGER->bloodSplash(_brovil->getX() + _brovil->getBrovilImage(_brovil->getBrovilStatus())->getFrameWidth()/2, _brovil->getY() + _brovil->getBrovilImage(_brovil->getBrovilStatus())->getFrameHeight()/2,
	//		_brovil->getDirection());
	//}
	// ���� �� ���Ϳ� ���
	this->saveEnemy(BROVIL, GRENADE, _brovil->getDirection());
	_isClear = true;
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

		//// �� õ��� �浹
		//if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getRcEnemy(), x, y, _vSoldier[i]->getSpeed(), _vSoldier[i]->getGravity(), ENEMY_TOP))
		//{
		//	_vSoldier[i]->setEnemyAngle(2 * PI - _vSoldier[i]->getEnemyAngle());	
		//	
		//}
		//else
		//{
		//	_vSoldier[i]->setY(y);
		//}
		//
		//// �� ���� ���� �浹
		//if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getRcEnemy(), x, y, _vSoldier[i]->getSpeed(), _vSoldier[i]->getGravity(), ENEMY_LEFT))
		//{
		//	_vSoldier[i]->setEnemyAngle(PI - _vSoldier[i]->getEnemyAngle());
		//	if (_vSoldier[i]->getIsAlive())
		//	{
		//		_vSoldier[i]->setDirection(0);		
		//	}
		//}	
		//else
		//{
		//	_vSoldier[i]->setX(x);
		//}
		//
		//// �� ������ ���� �浹
		//if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getRcEnemy(), x, y, _vSoldier[i]->getSpeed(), _vSoldier[i]->getGravity(), ENEMY_RIGHT))
		//{
		//	_vSoldier[i]->setEnemyAngle(PI - _vSoldier[i]->getEnemyAngle());		
		//	if (_vSoldier[i]->getIsAlive())
		//	{
		//		_vSoldier[i]->setDirection(1);			
		//	}
		//}	
		//else
		//{
		//	_vSoldier[i]->setX(x);
		//}		
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
		float x = _vSoldier[i]->getRcEnemySight().left;
		float y = _vSoldier[i]->getRcEnemySight().top;

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
	for (int i = 0; i < getEBullet()->getVEnemybullet().size(); ++i)
	{
		if (IntersectRect(&rc, &getEBullet()->getVEnemybullet()[i].rc, &rcPlayer))
		{
			// �Ѿ� ����
			getEBullet()->getVEnemybullet()[i].isActived = false;
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
			// �Ѿ� ����
			if (!_bossBullet->getBossBullet()[i].isActived) continue;
			_bossBullet->getBossBullet()[i].isActived = false;
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
			// �Ѿ� ����
			_bossRocket->getBossRocket()[i].isActived = false;
		}
	}
}

void enemyManager::collideBossRocketWithPixel()
{
	RECT rc;
	for (int i = 0; i < BOSS_ROCKET_MAX ; i++)
	{		
		if (!_bossRocket->getBossRocket()[i].isActived) continue;

		if (COLLISIONMANAGER->pixelCollision(_bossRocket->getBossRocket()[i].rc, _bossRocket->getBossRocket()[i].x, _bossRocket->getBossRocket()[i].y, _bossRocket->getBossRocket()[i].speed, _bossRocket->getBossRocket()[i].gravity, 3) == GREEN)				// �Ʒ��� ��
		{
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (IntersectRect(&rc, &_mapData->getObject()[j]._rc, &_bossRocket->getBossRocket()[i].rc))
				{
					_bossRocket->getBossRocket()[i].isActived = false;
					_mapData->deleteMapIndexByIndex(j, 1, 1);
					CAMERAMANAGER->CameraShake();
					//EFFECTMANAGER->rambroGrenadeExplosion(_gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y);
					
					break;
				}
			}
		}
		else if (COLLISIONMANAGER->pixelCollision(_bossRocket->getBossRocket()[i].rc, _bossRocket->getBossRocket()[i].x, _bossRocket->getBossRocket()[i].y, _bossRocket->getBossRocket()[i].speed, _bossRocket->getBossRocket()[i].gravity, 1) == GREEN)			// ���� ��
		{
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (IntersectRect(&rc, &_mapData->getObject()[j]._rc, &_bossRocket->getBossRocket()[i].rc))
				{
					_bossRocket->getBossRocket()[i].isActived = false;
					_mapData->deleteMapIndexByIndex(j, 1, 1);
					CAMERAMANAGER->CameraShake();
					//EFFECTMANAGER->rambroGrenadeExplosion(_gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y);
					
					break;
				}
			}
		}
		if (COLLISIONMANAGER->pixelCollision(_bossRocket->getBossRocket()[i].rc, _bossRocket->getBossRocket()[i].x, _bossRocket->getBossRocket()[i].y, _bossRocket->getBossRocket()[i].speed, _bossRocket->getBossRocket()[i].gravity, 2) == GREEN)				// ������ ��	
		{
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (IntersectRect(&rc, &_mapData->getObject()[j]._rc, &_bossRocket->getBossRocket()[i].rc))
				{
					_bossRocket->getBossRocket()[i].isActived = false;
					_mapData->deleteMapIndexByIndex(j, 1, 1);
					CAMERAMANAGER->CameraShake();
					//EFFECTMANAGER->rambroGrenadeExplosion(_gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y);
					
					break;
				}
			}
		}
		else if (COLLISIONMANAGER->pixelCollision(_bossRocket->getBossRocket()[i].rc, _bossRocket->getBossRocket()[i].x, _bossRocket->getBossRocket()[i].y, _bossRocket->getBossRocket()[i].speed, _bossRocket->getBossRocket()[i].gravity, 0) == GREEN)			// ���� ��	
		{
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (IntersectRect(&rc, &_mapData->getObject()[j]._rc, &_bossRocket->getBossRocket()[i].rc))
				{
					_bossRocket->getBossRocket()[i].isActived = false;
					_mapData->deleteMapIndexByIndex(j, 1, 1);
					CAMERAMANAGER->CameraShake();
					//EFFECTMANAGER->rambroGrenadeExplosion(_gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y);
					
					break;
				}
			}
		}
	}
}

// ���� ������ ��ȭ (�÷��̾� ��ġ�� ����)
void enemyManager::bossDirChange()
{	
	if (!_boss->radarIn(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), 1000.f))
	{
		// �÷��̾ �������� �����̸� ���� �ٲ���
		if (_playerManager->getPlayer()->getX() + 30 < _boss->getTerrorKopter().x + _boss->getTerrorKopter().img.bodyImage[_boss->getBodyStatus()]->getFrameWidth() / 2)
		{
			_boss->setStatus(LEFT_MOVE);
		}
		else if (_playerManager->getPlayer()->getX() + 30 > _boss->getTerrorKopter().x + _boss->getTerrorKopter().img.bodyImage[_boss->getBodyStatus()]->getFrameWidth() / 2)
		{
			_boss->setStatus(RIGHT_MOVE);
		}
	}
	else
	{
		++_count;
		if (_boss->getStatus() != (LEFT_FIRE_ROCKET && RIGHT_FIRE_ROCKET))
		{
			if (_count > 200)
			{
				_count = 0;
				_choice = RND->getFromIntTo(0, 3);
			}
		}
		else if (_boss->getStatus() == (LEFT_FIRE_ROCKET || RIGHT_FIRE_ROCKET))
		{
			if (_count > 100)
			{
				_count = 0;
				if (_choice == 3 || _choice == 2)
				{
					_choice = RND->getFromIntTo(0, 1);
				}
				else
				{
					_choice = RND->getFromIntTo(0, 3);
				}
			}
		}

		switch (_choice)
		{
		case 0:
		{
			_boss->setStatus(LEFT_FIRE_BULLET);
			break;
		}
		case 1:
		{
			_boss->setStatus(RIGHT_FIRE_BULLET);
			break;
		}
		case 2:
		{
			_boss->setStatus(LEFT_FIRE_ROCKET);
			break;
		}
		case 3:
		{
			_boss->setStatus(RIGHT_FIRE_ROCKET);
			break;
		}

		default:
			break;
		}

		if (_boss->getStatus() == LEFT_FIRE_BULLET || _boss->getStatus() == RIGHT_FIRE_BULLET)
		{
			_boss->verticalMove(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), _boss->getTerrorKopter().angle);
		}
		else if (_boss->getStatus() == LEFT_FIRE_ROCKET || _boss->getStatus() == RIGHT_FIRE_ROCKET)
		{
			_boss->bombAttack(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), _boss->getTerrorKopter().angle);
		}
	}	
}

// ������ �÷��̾� �Ѿ˿� ����
void enemyManager::PBulletHitBoss()
{
	RECT rc;
	for (int i = 0; i < _playerManager->getPBullet()->getVPlayerBullet().size(); ++i)
	{
		if (IntersectRect(&rc, &_playerManager->getPBullet()->getVPlayerBullet()[i].rc, &_boss->getRcBoss()))
		{			
			if (!_playerManager->getPBullet()->getVPlayerBullet()[i].isActived) continue;
			_playerManager->getPBullet()->getVPlayerBullet()[i].isActived = false;
			_boss->setHP(_boss->getHP() - 10);
		}		
	}
}

void enemyManager::bossDie()
{
	if (_boss->getTerrorKopter().isAlive == false)
	{
		_isClear = true;
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
				if (_vSoldier[i]->getIsApart()) continue;
				_vSoldier[i]->setDirection(_playerManager->getPBullet()->getVPlayerBullet()[j].isLeft);
				soldierDieWithBullet(i);
				
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
				soldierDieWithGrenade(i);

				// ���� �� ���Ϳ� ���
				this->saveEnemy(SOLDIER, GRENADE, _vSoldier[i]->getDirection());
			}
		}
	}
}

// �Ҿƹ��� �Ѿ˰� ���ʹ� �浹
void enemyManager::collideWithGBullet()
{
	RECT rc;
	for (int i = 0; i < _playerManager->getGBullet()->getVPlayergBullet().size(); ++i)
	{
		for (int j = 0; j < _vSoldier.size(); ++j)
		{
			if (IntersectRect(&rc, &_playerManager->getGBullet()->getVPlayergBullet()[i].rc, &_vSoldier[j]->getRcEnemy()))
			{
				if (!_playerManager->getGBullet()->getVPlayergBullet()[i].isActived) continue;
				_playerManager->getGBullet()->getVPlayergBullet()[i].isActived = false;
				
				soldierDieWithBullet(j);
			}
		}	
	}
}

// �Ҿƹ��� �Ѿ� vs ����
void enemyManager::collideBossWithGBullet()
{
	RECT rc;
	for (int i = 0; i < _playerManager->getGBullet()->getVPlayergBullet().size(); ++i)
	{
		if (IntersectRect(&rc, &_playerManager->getGBullet()->getVPlayergBullet()[i].rc, &_boss->getRcBoss()))
		{
			if (!_playerManager->getGBullet()->getVPlayergBullet()[i].isActived) continue;
			_playerManager->getGBullet()->getVPlayergBullet()[i].isActived = false;
			_boss->setHP(_boss->getHP() - 10);
		}
	}
}

// �Ҿƹ��� ����ź vs ����
void enemyManager::collideBossWithGGrenade()
{

}

// ���ʹ� �Ѿ˰� �ȼ� �浹
void enemyManager::collideBulletWithPixel()
{
	RECT rc;
	for (int i = 0; i < _eBullet->getVEnemybullet().size(); ++i)
	{
		float x, y;
		x = _eBullet->getVEnemybullet()[i].x;
		y = _eBullet->getVEnemybullet()[i].y;

		if (!_eBullet->getVEnemybullet()[i].isActived) continue;

		// �ٴ�
		if (COLLISIONMANAGER->pixelCollision(_eBullet->getVEnemybullet()[i].rc, x, y, _eBullet->getVEnemybullet()[i].speed, _eBullet->getVEnemybullet()[i].gravity, ENEMY_BOTTOM))
		{
			_eBullet->getVEnemybullet()[i].isActived = false;
		}
		
		// õ��
		else if (COLLISIONMANAGER->pixelCollision(_eBullet->getVEnemybullet()[i].rc, x, y, _eBullet->getVEnemybullet()[i].speed, _eBullet->getVEnemybullet()[i].gravity, ENEMY_TOP))
		{
			_eBullet->getVEnemybullet()[i].isActived = false;
		}		

		// ����
		else if (COLLISIONMANAGER->pixelCollision(_eBullet->getVEnemybullet()[i].rc, x, y, _eBullet->getVEnemybullet()[i].speed, _eBullet->getVEnemybullet()[i].gravity, ENEMY_LEFT))
		{
			_eBullet->getVEnemybullet()[i].isActived = false;
		}		

		// ������
		else if (COLLISIONMANAGER->pixelCollision(_eBullet->getVEnemybullet()[i].rc, x, y, _eBullet->getVEnemybullet()[i].speed, _eBullet->getVEnemybullet()[i].gravity, ENEMY_RIGHT))
		{
			_eBullet->getVEnemybullet()[i].isActived = false;
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

			brovilDieWithBullet();
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
			
			brovilDieWithGrenade();						
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

void enemyManager::collideDogSightWithPlayer()
{
	// �浹ó��(�÷��̾�) vs �� �þ�	
	RECT rc;
	RECT rcPlayer = RectMake(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(),
		_playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameWidth(), _playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameHeight());
	for (int i = 0; i < _vDog.size(); ++i)
	{
		if (IntersectRect(&rc, &_vDog[i]->getRCsight(), &rcPlayer))
		{
			if (!_vDog[i]->getIsAlive()) continue;
			// ��ǳ�� ����
			_vDog[i]->setIsUncovered(true);
		}
	}
}

// ���� ���ݹݰ� �ȿ� �÷��̾ ����
void enemyManager::collideDogWithPlayer()
{
	RECT rc;
	for (int i = 0; i < _vDog.size(); ++i)
	{
		if (IntersectRect(&rc, &_playerManager->getPlayer()->getRcRambro(), &_vDog[i]->getRCattackRange()))
		{
			if (!_vDog[i]->getIsUncovered()) continue;
			_vDog[i]->setIsNear(true);

			if (_vDog[i]->getX() + _vDog[i]->getImage(_vDog[i]->getStatus())->getFrameWidth() / 2 <
				_playerManager->getPlayer()->getX() + _playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameWidth() / 2)
			{
				_vDog[i]->setIsLeft(false);
			}
			else
			{
				_vDog[i]->setIsLeft(true);
			}
		}
		else
		{
			_vDog[i]->setIsNear(false);
		}
	}
}

void enemyManager::collideDogWithPixel()
{
	// ������ �浹(�ȼ��浹)
	RECT rc;
	for (int i = 0; i < _vDog.size(); ++i)
	{
		float x, y;
		x = _vDog[i]->getX();
		y = _vDog[i]->getY();

		// �ٴڰ� �浹
		if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getRC(), x, y, _vDog[i]->getSpeed(), _vDog[i]->getGravity(), ENEMY_BOTTOM))
		{
			_vDog[i]->setIsOn(true);
		}
		else
		{
			_vDog[i]->setIsOn(false);
		}

		// �� õ��� �浹
		if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getRC(), x, y, _vDog[i]->getSpeed(), _vDog[i]->getGravity(), ENEMY_TOP))
		{
			_vDog[i]->setAngle(2 * PI - _vDog[i]->getAngle());

		}
		else
		{
			_vDog[i]->setY(y);
		}

		// �� ���� ���� �浹
		if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getRC(), x, y, _vDog[i]->getSpeed(), _vDog[i]->getGravity(), ENEMY_LEFT))
		{
			_vDog[i]->setAngle(PI - _vDog[i]->getAngle());
			if (_vDog[i]->getIsAlive())
			{
				_vDog[i]->setIsLeft(0);
			}
		}
		else
		{
			_vDog[i]->setX(x);
		}

		// �� ������ ���� �浹
		if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getRC(), x, y, _vDog[i]->getSpeed(), _vDog[i]->getGravity(), ENEMY_RIGHT))
		{
			_vDog[i]->setAngle(PI - _vDog[i]->getAngle());
			if (_vDog[i]->getIsAlive())
			{
				_vDog[i]->setIsLeft(1);
			}
		}
		else
		{
			_vDog[i]->setX(x);
		}
	}
}

// ���װ� �÷��̾� �Ѿ˿� ����
void enemyManager::collideDogWithPBullet()
{
	RECT rc;
	for (int i = 0; i < _playerManager->getPBullet()->getVPlayerBullet().size(); ++i)
	{
		for (int j = 0; j < _vDog.size(); ++j)
		{
			if (IntersectRect(&rc, &_playerManager->getPBullet()->getVPlayerBullet()[i].rc, &_vDog[j]->getRC()))
			{
				if (_vDog[j]->getIsApart()) continue;

				if (_vDog[j]->getIsLeft() != _playerManager->getPBullet()->getVPlayerBullet()[i].isLeft)
				{
					_vDog[j]->setIsLeft(_playerManager->getPBullet()->getVPlayerBullet()[i].isLeft);
				}

				DogDieWithBullet(j);
			}
		}		
	}
}

// �Ҿƹ��� �Ѿ��̶� ���׶� �浹
void enemyManager::collideDogWithGBullet()
{
	RECT rc;
	for (int i = 0; i < _playerManager->getGBullet()->getVPlayergBullet().size(); ++i)
	{
		for (int j = 0; j < _vDog.size(); ++j)
		{
			if (IntersectRect(&rc, &_playerManager->getGBullet()->getVPlayergBullet()[i].rc, &_vDog[j]->getRC()))
			{
				if (_vDog[j]->getIsApart()) continue;

				if (_vDog[j]->getIsLeft() != _playerManager->getPBullet()->getVPlayerBullet()[i].isLeft)
				{
					_vDog[j]->setIsLeft(_playerManager->getPBullet()->getVPlayerBullet()[i].isLeft);
				}

				DogDieWithBullet(j);
			}
		}
	}
}

void enemyManager::DogDieWithBullet(int i)
{
	_vDog[i]->setHP(_vDog[i]->getHP() - 1);

	if (_vDog[i]->getStatus() != D_KNOCK_BACK && _vDog[i]->getStatus() != D_DEAD )
	{
		if (_vDog[i]->getIsLeft())
			_vDog[i]->setIndex(_vDog[i]->getImage(D_KNOCK_BACK)->getMaxFrameX() - 1);
		else
			_vDog[i]->setIndex(0);

		_vDog[i]->setStatus(D_KNOCK_BACK);
	}

	if (_brovil->getBrovilStatus() == D_DEAD)
	{
		_vDog[i]->deadMove();
	}
		
	this->saveEnemy(DOG, BULLET, _vDog[i]->getIsLeft());
	_isClear = true;
}

void enemyManager::collideDogCorpseWithPixel()
{
	// ��ü �丷 �浹
	RECT rc;
	for (int i = 0; i < _vDog.size(); ++i)
	{
		for (int j = 0; j < BODY_PART; ++j)
		{
			if (!_vDog[i]->getIsApart()) continue;

			float x, y;
			x = _vDog[i]->getCorpse()[j].x;
			y = _vDog[i]->getCorpse()[j].y;

			// �ٴ�
			if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getCorpse()[j].rcCorpse, x, y, _vDog[i]->getCorpse()[j].speed, _vDog[i]->getCorpse()[j].gravity, ENEMY_BOTTOM))
			{
				_vDog[i]->getCorpse()[j].angle = 2 * PI - _vDog[i]->getCorpse()[j].angle;
				_vDog[i]->getCorpse()[j].gravity = 0.f;
			}

			// õ��
			if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getCorpse()[j].rcCorpse, x, y, _vDog[i]->getCorpse()[j].speed, _vDog[i]->getCorpse()[j].gravity, ENEMY_TOP))
			{
				_vDog[i]->getCorpse()[j].angle = 2 * PI - _vDog[i]->getCorpse()[j].angle;
			}

			// ����
			if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getCorpse()[j].rcCorpse, x, y, _vDog[i]->getCorpse()[j].speed, _vDog[i]->getCorpse()[j].gravity, ENEMY_LEFT))
			{
				_vDog[i]->getCorpse()[j].angle = PI - _vDog[i]->getCorpse()[j].angle;
			}

			// ������
			if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getCorpse()[j].rcCorpse, x, y, _vDog[i]->getCorpse()[j].speed, _vDog[i]->getCorpse()[j].gravity, ENEMY_RIGHT))
			{
				_vDog[i]->getCorpse()[j].angle = PI - _vDog[i]->getCorpse()[j].angle;
			}

			_vDog[i]->getCorpse()[j].x = x;
			_vDog[i]->getCorpse()[j].y = y;

		}
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

