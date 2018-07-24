#include "stdafx.h"
#include "enemyManager.h"
#include "playerManager.h"
#include "mapData.h"

HRESULT enemyManager::init(void)
{		
	//利 个烹, 迫 捞固瘤 檬扁拳
	IMAGEMANAGER->addFrameImage("利个烹", "enemyImage/_enemy_with_head.bmp", 1600, 1600, 20, 20);
	IMAGEMANAGER->addFrameImage("利迫", "enemyImage/_enemy_gun.bmp", 1600, 800, 19, 10);

	this->setEnemy();	

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
		
		if (getVEnemy()[i]->getStatus() == WARNING_LEFT)
		{
			if (getVEnemy()[i]->getFrameIndex2() == 0)
			{
				_eBullet->fire(getVEnemy()[i]->getX(), getVEnemy()[i]->getY(), getVEnemy()[i]->getDirection());
			}
		}
		else if (getVEnemy()[i]->getStatus() == WARNING_RIGHT)
		{
			if (getVEnemy()[i]->getFrameIndex2() == 6)
			{
				_eBullet->fire(getVEnemy()[i]->getX(), getVEnemy()[i]->getY(), getVEnemy()[i]->getDirection());
			}
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

void enemyManager::collision()
{
	
}

//=====================================================================================================================================================================================

void enemyManager::setEnemy()
{
	for (int i = 0; i < 4; ++i)
	{
		enemy* _soldier = new soldier;
		_soldier->init("利个烹", "利迫", 3000 + i*100, 2000, 100);
		_vSoldier.push_back(_soldier);
	}		
}