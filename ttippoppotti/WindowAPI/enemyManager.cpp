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
	this->setSoldier(3700, 1244, 1);
	this->setSoldier(3700, 1450, 2);
	this->setSoldier(3600, 1655, 3);
	this->setSoldier(3600, 2190, 4);
	//this->setBrovil(3700, 1000, 5);
		
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
		_vSoldier[i]->setRandomNum(RND->getInt(10));
		
		// �Ѿ˹߻�
		if (getVEnemy()[i]->getArmStatus() == GUN_FIRE)
		{
			_eBullet->fire(getVEnemy()[i]->getX(), getVEnemy()[i]->getY(), 10, getVEnemy()[i]->getDirection());
		}		
	}
		
	_eBullet->update();			

	this->collision();
	this->collideWithPBullet();
}

void enemyManager::render(void)
{
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		_vSoldier[i]->render();		
	}

	_eBullet->render();
	
	char str[64];
	sprintf_s(str, "%f", _vSoldier[0]->getGravity());
	TextOut(getMemDC(), 300, 10, str, strlen(str));
}

void enemyManager::collision()
{	
	// �浹ó��(�÷��̾�) vs �� �þ�
	RECT rc;
	RECT rcPlayer = _playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->boudingBoxWithFrame();
	for (int i = 0; i < getVEnemy().size(); ++i)
	{
		if (IntersectRect(&rc, &getVEnemy()[i]->getRcEnemySight(), &rcPlayer))
		{
			// ��ǳ�� ����
			getVEnemy()[i]->setIsUncovered(true);
			// �� ���� ���� ( ��� )
			getVEnemy()[i]->setBodyStatus(ENEMY_DOUBT);				
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
			EFFECTMANAGER->addEffect()
		}
		else
		{
			i++;
		}
	}		

	// �浹ó�� ( �� Ÿ�� ) vs �Ϲ� ��
	for (int j = 0; j < getVEnemy().size(); ++j)
	{
		//if (!CAMERAMANAGER->CameraIn(getVEnemy()[j]->getEnemyRC())) continue;
		for (int i = 386; i < _mapData->getObject().size(); i++)
		{
			if (!_mapData->getObject()[i]._isActived) continue;

			if (IntersectRect(&rc, &_vSoldier[j]->getRcEnemy(), &_mapData->getObject()[i]._rc))
			{				
				//Ÿ�Ͽ� ����
				if (_mapData->getObject()[i]._rc.bottom > _vSoldier[j]->getRcEnemy().top && _mapData->getObject()[i]._rc.bottom < _vSoldier[j]->getRcEnemy().bottom)
				_vSoldier[j]->setY(_vSoldier[j]->getY() + 1);
				
				_vSoldier[j]->setIsOn(true);
				_vSoldier[j]->setY(_vSoldier[j]->getY() - 0.4f);
				//_vSoldier[j]->setY(_mapData->getObject()[i]._rc.top - _vSoldier[j]->getBodyImage()->getFrameHeight()/2);
				break;				
			}			
			else
			{				
				_vSoldier[j]->setIsOn(false);
			}	
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
		if (!_vSoldier[i]->getIsAlive())
		{
			_vSoldier[i]->setBodyStatus(ENEMY_DEAD);
			_vSoldier[i].
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
