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

	//적 몸통, 팔 이미지 초기화
	IMAGEMANAGER->addFrameImage("적몸통", "enemyImage/_enemy_with_head.bmp", 1600, 1600, 20, 20);
	IMAGEMANAGER->addFrameImage("적팔", "enemyImage/_enemy_gun.bmp", 1600, 800, 19, 10);

	//알람 이미지 초기화
	IMAGEMANAGER->addFrameImage("알람", "enemyImage/ExclamationMark.bmp", 1020, 60, 17, 1);

	//에너미 위치 초기화
	this->setEnemy(2000, 1450);
	this->setEnemy(2000, 1244);
	this->setEnemy(3188, 1655);
	this->setEnemy(3700, 2190);

	_eBullet = new eBullet;
	_eBullet->init(20, 500.f);

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
		if (getVEnemy()[i]->getStatus() == FIRE_LEFT)
		{
			_eBullet->fire(getVEnemy()[i]->getX() - 40, getVEnemy()[i]->getY() + 10, 3, getVEnemy()[i]->getDirection());
		}
		else if (getVEnemy()[i]->getStatus() == FIRE_RIGHT)
		{
			_eBullet->fire(getVEnemy()[i]->getX() + 40, getVEnemy()[i]->getY() + 10, 3, getVEnemy()[i]->getDirection());
		}
	}
	_eBullet->update();	
		
}

void enemyManager::render(void)

{
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		_vSoldier[i]->render();		
	}
	_eBullet->render();
}

void enemyManager::isNotice()
{		
	
}

void enemyManager::collision()
{
	// 충돌처리(플레이어)
	RECT rc;
	RECT rcPlayer = _playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->boudingBoxWithFrame();
	for (int i = 0; i < getVEnemy().size(); ++i)
	{
		if (IntersectRect(&rc, &getVEnemy()[i]->getEnemySightRC(), &rcPlayer))
		{
			// 말풍선 띄우기
			getVEnemy()[i]->setAlarm(true);
			// 적 상태 변경 ( 경고 )
			if (getVEnemy()[i]->getDirection() == true)
				getVEnemy()[i]->setStatus(WARNING_LEFT);
			else
				getVEnemy()[i]->setStatus(WARNING_RIGHT);
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

	for (int i = 0; i < _mapData->getObject().size(); ++i)
	{
		for (int j = 0; j < getVEnemy().size(); ++j)
		{
			if (IntersectRect(&rc, &_mapData->getObject()[i]._rc, &getVEnemy()[j]->getEnemyRC()))
			{
				if (getVEnemy()[j]->getStatus() == WALK_LEFT)
				{
					getVEnemy()[j]->setStatus(WALK_RIGHT);
				}
				else if (getVEnemy()[j]->getStatus() == WALK_RIGHT)
				{
					getVEnemy()[j]->setStatus(WALK_LEFT);
				}
			}
		}
	}
}

//=====================================================================================================================================================================================

void enemyManager::setEnemy(int x, int y)
{
	enemy* _soldier = new soldier;
	_soldier->init("적몸통", "적팔", x, y, 100);
	_vSoldier.push_back(_soldier);
}