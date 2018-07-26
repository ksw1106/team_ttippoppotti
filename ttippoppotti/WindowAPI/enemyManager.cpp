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
	this->setEnemy(3700, 1450, 3);
	this->setEnemy(3700, 1244, 3);
	this->setEnemy(3600, 1655, 3);
	this->setEnemy(3600, 2190, 3);
	

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
		if (getVEnemy()[i]->getArmStatus() == G_FIRE)
		{
			_eBullet->fire(getVEnemy()[i]->getX(), getVEnemy()[i]->getY(), 10, getVEnemy()[i]->getDirection());
		}		
	}

	_eBullet->update();		

	this->collision();
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
			getVEnemy()[i]->setBodyStatus(E_DOUBT);
			getVEnemy()[i]->setArmStatus(G_TARGETING);
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

	//for (int j = 0; j < getVEnemy().size(); ++j)
	//{
	//	// 맵과 충돌 (타일)
	//	for (int i = 0; i < 470; ++i)
	//	{			
	//		if (IntersectRect(&rc, &_mapData->getObject()[i]._rc, &getVEnemy()[j]->getEnemyRC()))
	//		{
	//			if (getVEnemy()[j]->getDirection() == true) getVEnemy()[j]->setDirection(false);
	//			else getVEnemy()[j]->setDirection(true);
	//		}
	//	}
	//}

	for (int j = 0; j < getVEnemy().size(); ++j)
	{
		if (!CAMERAMANAGER->CameraIn(getVEnemy()[j]->getEnemyRC())) continue;
		
		for (int i = 386; i < _mapData->getObject().size(); i++)
		{
			RECT rc;
			if (IntersectRect(&rc, &getVEnemy()[j]->getEnemyRC(), &_mapData->getObject()[i]._rc))
			{
				if (getVEnemy()[j]->getDirection())
				{
					getVEnemy()[j]->setDirection(false);
				}
				else
					getVEnemy()[j]->setDirection(true);
			}			
		}
	}
	
	
}

//=====================================================================================================================================================================================

void enemyManager::setEnemy(int x, int y, int randomNum)
{
	enemy* _soldier = new soldier;
	_soldier->init(x, y, 100, randomNum);
	_vSoldier.push_back(_soldier);
}