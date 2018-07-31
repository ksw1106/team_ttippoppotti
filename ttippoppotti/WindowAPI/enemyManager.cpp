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
	
	//알람 이미지 초기화
	IMAGEMANAGER->addFrameImage("알람", "enemyImage/ExclamationMark.bmp", 1020, 60, 17, 1);
	//의문 이미지 초기화
	IMAGEMANAGER->addFrameImage("의문", "enemyImage/QuestionMark.bmp", 960, 60, 16, 1);

	//에너미 클래스 객체 생성 및 초기화
	this->setSoldier(3700, 1240, 1);
	this->setSoldier(3700, 1410, 2);
	this->setSoldier(3600, 1630, 3);
	this->setSoldier(3600, 2170, 4);
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
		if (!_vSoldier[i]->getIsAlive()) continue;

		_vSoldier[i]->update();		
		_vSoldier[i]->setRandomNum(RND->getInt(10));
		
		// 총알발사
		if (_vSoldier[i]->getIsFire())
		{
			_eBullet->fire(_vSoldier[i]->getX() + _vSoldier[i]->getEnemyBodyImage(_vSoldier[i]->getBodyStatus())->getFrameWidth()/2,
				getVEnemy()[i]->getY() + _vSoldier[i]->getEnemyBodyImage(_vSoldier[i]->getBodyStatus())->getFrameHeight() / 2,
				10, getVEnemy()[i]->getDirection());
		}		
	
		if (!_vSoldier[i]->getIsOn())
		{
			if (_vSoldier[i]->getGravity() < 3.0f) _vSoldier[i]->setGravity(3.0f);
			_vSoldier[i]->setY(_vSoldier[i]->getY() - sinf(_vSoldier[i]->getEnemyAngle()) * _vSoldier[i]->getSpeed() + _vSoldier[i]->getGravity());
			_vSoldier[i]->setGravity(_vSoldier[i]->getGravity() + 0.5f);
		}
		else
		{
			_vSoldier[i]->setGravity(0.f);
		}

		//좌우 이동
		if (_vSoldier[i]->getBodyStatus() == ENEMY_WALK)
		{
			if (_vSoldier[i]->getDirection())
			{
				_vSoldier[i]->setX(_vSoldier[i]->getX() - _vSoldier[i]->getSpeed());
			}
			else
			{
				_vSoldier[i]->setX(_vSoldier[i]->getX() + _vSoldier[i]->getSpeed());
			}
		}
		
	}
		
	_eBullet->update();			

	this->collision();
	this->collideWithPBullet();		// 플레이어 총알과 충돌
	this->enemyDie();				// 적 죽음
		
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
	RECT rcPlayer = _playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->boudingBoxWithFrame();
	for (int i = 0; i < getVEnemy().size(); ++i)
	{
		if (IntersectRect(&rc, &getVEnemy()[i]->getRcEnemySight(), &rcPlayer))
		{
			// 말풍선 띄우기
			getVEnemy()[i]->setIsUncovered(true);
			//getVEnemy()[i]->setBodyStatus
			// 적 상태 변경 ( 경고 )
			getVEnemy()[i]->setBodyStatus(ENEMY_FIRE);				
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
			i++;
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
		if (_vSoldier[i]->getBodyStatus() == ENEMY_KNOCK_BACK)
		{
			_vSoldier[i]->setBodyStatus(ENEMY_DEAD);
			//_vSoldier[i].
		}
	}	
}

//=====================================================================================================================================================================================

void enemyManager::setSoldier(int x, int y, int randomNum)
{
	enemy* _soldier = new soldier;
	_soldier->initSoldier(x, y, 100, randomNum);
	_vSoldier.push_back(_soldier);
}

//void enemyManager::setBrovil(int x, int y, int randomNum)
//{
//	enemy* _brovil = new brovil;
//	_brovil->initBrovil(x, y, 100, randomNum);
//	_vSoldier.push_back(_brovil);
//}
