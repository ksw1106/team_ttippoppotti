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
		
		// 총알발사
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
	// 충돌처리(플레이어) vs 적 시야
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

	// 충돌처리 ( 맵 타일 ) vs 일반 적
	for (int j = 0; j < getVEnemy().size(); ++j)
	{
		//if (!CAMERAMANAGER->CameraIn(getVEnemy()[j]->getEnemyRC())) continue;
		for (int i = 386; i < _mapData->getObject().size(); i++)
		{
			if (!_mapData->getObject()[i]._isActived) continue;

			if (IntersectRect(&rc, &_vSoldier[j]->getEnemyRC(), &_mapData->getObject()[i]._rc))
			{				
				//타일에 착지
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

	// 충돌처리 (맵 타일) vs 브로빌
	for (int i = 386; i < _mapData->getObject().size(); ++i)
	{
		if (!_mapData->getObject()[i]._isActived) continue;

		if (IntersectRect(&rc, &_brovil->getRC(), &_mapData->getObject()[i]._rc))
		{
			//타일에 착지
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

	// 충돌처리(플레이어) vs 브로빌 시야	
	if (IntersectRect(&rc, &_brovil->getRCsight(), &rcPlayer))
	{
		// 말풍선 띄우기
		_brovil->setAlarm(true);		
	}

	//적이 죽은 적 발견했을때, 물음표 표시
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
