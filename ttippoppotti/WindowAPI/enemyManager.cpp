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
	
	//�˶� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addFrameImage("�˶�", "enemyImage/ExclamationMark.bmp", 1020, 60, 17, 1);
	//�ǹ� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addFrameImage("�ǹ�", "enemyImage/QuestionMark.bmp", 960, 60, 16, 1);

	//���ʹ� Ŭ���� ��ü ���� �� �ʱ�ȭ
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

		// �Ѿ˹߻�
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
	// �浹ó��(�÷��̾�)
	RECT rc;
	RECT rcPlayer = _playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->boudingBoxWithFrame();
	for (int i = 0; i < getVEnemy().size(); ++i)
	{
		if (IntersectRect(&rc, &getVEnemy()[i]->getEnemySightRC(), &rcPlayer))
		{
			// ��ǳ�� ����
			getVEnemy()[i]->setAlarm(true);

			// �� ���� ���� ( ��� )
			getVEnemy()[i]->setBodyStatus(E_DOUBT);
			getVEnemy()[i]->setArmStatus(G_TARGETING);
		}
	}

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
			i++;
		}
	}

	//for (int j = 0; j < getVEnemy().size(); ++j)
	//{
	//	// �ʰ� �浹 (Ÿ��)
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