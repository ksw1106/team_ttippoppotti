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

	this->setEnemy(3856, 1450);
	this->setEnemy(3300, 1244);
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

		if (getVEnemy()[i]->getStatus() == FIRE_LEFT)
		{
			if (getVEnemy()[i]->getFrameIndex2() == 0)
			{
				_eBullet->fire(getVEnemy()[i]->getX() - 40, getVEnemy()[i]->getY() + 10, 3, getVEnemy()[i]->getDirection());
			}
		}
		else if (getVEnemy()[i]->getStatus() == FIRE_RIGHT)
		{
			if (getVEnemy()[i]->getFrameIndex2() == 3)
			{
				_eBullet->fire(getVEnemy()[i]->getX() + 40, getVEnemy()[i]->getY() + 10, 3, getVEnemy()[i]->getDirection());
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
	RECT rc;
	if (IntersectRect(&rc, &_playerManager.)
}

//=====================================================================================================================================================================================

void enemyManager::setEnemy(int x, int y)
{
	enemy* _soldier = new soldier;
	_soldier->init("������", "����", x, y, 100);
	_vSoldier.push_back(_soldier);
}