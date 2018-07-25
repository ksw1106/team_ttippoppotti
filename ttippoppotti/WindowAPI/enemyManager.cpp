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

	//�� ����, �� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addFrameImage("������", "enemyImage/_enemy_with_head.bmp", 1600, 1600, 20, 20);
	IMAGEMANAGER->addFrameImage("����", "enemyImage/_enemy_gun.bmp", 1600, 800, 19, 10);

	//�˶� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addFrameImage("�˶�", "enemyImage/ExclamationMark.bmp", 1020, 60, 17, 1);

	//���ʹ� ��ġ �ʱ�ȭ
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

		// �Ѿ˹߻�
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
			if (getVEnemy()[i]->getDirection() == true)
				getVEnemy()[i]->setStatus(WARNING_LEFT);
			else
				getVEnemy()[i]->setStatus(WARNING_RIGHT);
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
	_soldier->init("������", "����", x, y, 100);
	_vSoldier.push_back(_soldier);
}