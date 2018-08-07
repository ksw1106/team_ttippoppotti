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
		
	_eBullet = new eBullet;
	_eBullet->init(1, 800.f);
	
	return S_OK;
}

void enemyManager::release(void)
{
	_eBullet->release();
	SAFE_DELETE(_eBullet);
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

	_eBullet->update();
	
	// ��� �浹
	this->collideWithPixel();
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

	this->enemyDie();			
}

void enemyManager::render(void)
{
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		_vSoldier[i]->render();		
	}

	_eBullet->render();	

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
				//if (!_playerManager->getPBullet()->getVPlayerBullet()[j].isActived) continue;

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
					_vSoldier[i]->move();
				}
			}
		}
	}
}

// ����ź�� �÷��̾� �浹
void enemyManager::collideWithPGrenade()
{
	RECT rc;
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		for (int j = 0; j < _playerManager->getPGrenade()->getVPlayerGrenade().size(); ++j)
		{
			if (IntersectRect(&rc, &_playerManager->getPGrenade()->getVPlayerGrenade()[j].rc, &_vSoldier[i]->getRcEnemy()))
			{
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
					_vSoldier[i]->move();
				}
			}
		}
	}
}

// ���ʹ� �÷��̾� �Ѿ˸¾� ����
void enemyManager::enemyDie()
{
	
}
