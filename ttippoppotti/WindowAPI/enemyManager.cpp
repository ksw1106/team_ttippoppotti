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
	this->setSoldier(3600, 1210);
	this->setSoldier(3700, 1410);
	this->setSoldier(3500, 1620);
	this->setSoldier(3400, 2160);
	//this->setBrovil(3700, 1000, 5);
		
	_eBullet = new eBullet;
	_eBullet->init(10, 800.f);
	
	return S_OK;
}

void enemyManager::release(void)
{
	_eBullet->release();	
}

void enemyManager::update(void)
{
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		_vSoldier[i]->update();		
		
		// 총알발사
		if (_vSoldier[i]->getIsFire())
		{
			// 왼쪽이면
			if (_vSoldier[i]->getDirection())
				_eBullet->fire(_vSoldier[i]->getX() + _vSoldier[i]->getEnemyBodyImage(_vSoldier[i]->getBodyStatus())->getFrameWidth() - _vSoldier[i]->getEnemyArmImage(_vSoldier[i]->getArmStatus())->getFrameWidth(),
					getVEnemy()[i]->getY() + _vSoldier[i]->getEnemyBodyImage(_vSoldier[i]->getBodyStatus())->getFrameHeight() / 2,
					200, getVEnemy()[i]->getDirection());
			// 오른쪽이면
			else
				_eBullet->fire(_vSoldier[i]->getX() + _vSoldier[i]->getEnemyArmImage(_vSoldier[i]->getArmStatus())->getFrameWidth(),
					getVEnemy()[i]->getY() + _vSoldier[i]->getEnemyBodyImage(_vSoldier[i]->getBodyStatus())->getFrameHeight() / 2,
					200, getVEnemy()[i]->getDirection());
		}	
	}			
	_eBullet->update();			
	
	this->collision();
	this->collideWithPBullet();		// 플레이어 총알과 충돌
	//this->enemyDie();				// 적 죽음
		
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
		sprintf_s(str, "%f", _vSoldier[i]->getIsOn());
		TextOut(getMemDC(), 300, 10+i*50, str, strlen(str));
	}
}

void enemyManager::collision()
{	
	// 충돌처리(플레이어) vs 적 시야
	RECT rc;
	RECT rcPlayer = RectMake(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(),
		_playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameWidth(), _playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameHeight());
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		if (IntersectRect(&rc, &_vSoldier[i]->getRcEnemySight(), &rcPlayer))
		{
			// 말풍선 띄우기
			_vSoldier[i]->setIsUncovered(true);
						
		}
	}

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
		
	// 적 착지 ( 픽셀충돌 )
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		float x, y;
		x = _vSoldier[i]->getX();
		y = _vSoldier[i]->getY();

		if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getRcEnemy(), x, y, _vSoldier[i]->getSpeed(), _vSoldier[i]->getGravity(), ENEMY_BOTTOM))
		{
			_vSoldier[i]->setIsOn(true);					
		}
		else
		{
			_vSoldier[i]->setIsOn(false);				
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
				_vSoldier[i]->setIsAlive(false);
				_vSoldier[i]->setBodyStatus(ENEMY_KNOCK_BACK);
				_vSoldier[i]->setEnemyAngle(_playerManager->getPBullet()->getVPlayerBullet()[j].angle);
				_vSoldier[i]->knockBackMove(_vSoldier[i]->getEnemyAngle());
				break;
			}
		}
	}
}

void enemyManager::enemyDie()
{
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		
	}	
}

//=====================================================================================================================================================================================

void enemyManager::setSoldier(int x, int y)
{
	enemy* _soldier = new soldier;
	_soldier->initSoldier(x, y);
	_vSoldier.push_back(_soldier);
}

//void enemyManager::setBrovil(int x, int y, int randomNum)
//{
//	enemy* _brovil = new brovil;
//	_brovil->initBrovil(x, y, 100, randomNum);
//	_vSoldier.push_back(_brovil);
//}
