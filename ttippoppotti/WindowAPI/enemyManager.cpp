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
	this->setEnemy(3700, 1244, 1);
	this->setEnemy(3700, 1450, 2);
	this->setEnemy(3600, 1655, 3);
	this->setEnemy(3600, 2190, 4);
		
	_eBullet = new eBullet;
	_eBullet->init(20, 500.f);
	_brovil = new brovil;
	_brovil->init(3700, 1000, 5);

	return S_OK;
}

void enemyManager::release(void)
{
	_eBullet->release();
	_brovil->release();
}
void enemyManager::update(void)
{
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		_vSoldier[i]->update();
		_vSoldier[i]->setRandomNum(RND->getInt(10));
		
		// �Ѿ˹߻�
		if (getVEnemy()[i]->getArmStatus() == G_FIRE)
		{
			_eBullet->fire(getVEnemy()[i]->getX(), getVEnemy()[i]->getY(), 10, getVEnemy()[i]->getDirection());
		}		
	}

	_eBullet->update();		
	_brovil->update();

	this->collision();
}

void enemyManager::render(void)
{
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		_vSoldier[i]->render();		
	}

	_eBullet->render();
	_brovil->render();

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
		if (IntersectRect(&rc, &getVEnemy()[i]->getEnemySightRC(), &rcPlayer))
		{
			// ��ǳ�� ����
			getVEnemy()[i]->setAlarm(true);
			// �� ���� ���� ( ��� )
			getVEnemy()[i]->setBodyStatus(E_DOUBT);				
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

	// �浹ó�� ( �� Ÿ�� ) vs �Ϲ� ��
	for (int j = 0; j < getVEnemy().size(); ++j)
	{
		//if (!CAMERAMANAGER->CameraIn(getVEnemy()[j]->getEnemyRC())) continue;
		for (int i = 386; i < _mapData->getObject().size(); i++)
		{
			if (!_mapData->getObject()[i]._isActived) continue;

			if (IntersectRect(&rc, &_vSoldier[j]->getEnemyRC(), &_mapData->getObject()[i]._rc))
			{				
				//Ÿ�Ͽ� ����
				if (_mapData->getObject()[i]._rc.bottom > _vSoldier[j]->getEnemyRC().top && _mapData->getObject()[i]._rc.bottom < _vSoldier[j]->getEnemyRC().bottom)
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

	// �浹ó�� (�� Ÿ��) vs ��κ�
	for (int i = 386; i < _mapData->getObject().size(); ++i)
	{
		if (!_mapData->getObject()[i]._isActived) continue;

		if (IntersectRect(&rc, &_brovil->getRC(), &_mapData->getObject()[i]._rc))
		{
			//Ÿ�Ͽ� ����
			if (_mapData->getObject()[i]._rc.bottom > _brovil->getRC().top && _mapData->getObject()[i]._rc.bottom < _brovil->getRC().bottom)
				_brovil->setY(_brovil->getY() + 1);

			_brovil->setIsOn(true);
			_brovil->setY(_brovil->getY() - 0.4f);
			//_vSoldier[j]->setY(_mapData->getObject()[i]._rc.top - _vSoldier[j]->getBodyImage()->getFrameHeight()/2);
			break;
		}
		else
		{
			_brovil->setIsOn(false);
		}
	}

	// �浹ó��(�÷��̾�) vs ��κ� �þ�	
	if (IntersectRect(&rc, &_brovil->getRCsight(), &rcPlayer))
	{
		// ��ǳ�� ����
		_brovil->setAlarm(true);		
	}

	//���� ���� �� �߰�������, ����ǥ ǥ��
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		for (int j = 0 ; j < _vSoldier.size(); ++j)
		{
			if (i == j) continue;
			
			if (IntersectRect(&rc, &_vSoldier[i]->getEnemySightRC(), &_vSoldier[j]->getEnemyRC()))
			{
				if (_vSoldier[j]->getBodyStatus() == E_DEAD)
				_vSoldier[i]->setAlarm2(true);
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
