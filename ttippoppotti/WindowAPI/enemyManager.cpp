#include "stdafx.h"
#include "enemyManager.h"
#include "playerManager.h"
#include "mapData.h"

HRESULT enemyManager::init(int stageNum)
{
	_stageNum = stageNum;

	// 플레이어매니저 클래스 가져오기
	this->setPlayerManager(_playerManager);
	// 맵데이터 가져오기
	this->setMapData(_mapData);	
		
	_eBullet = new eBullet;
	_eBullet->init(1, 800.f);
		
	_effectCount = _count = 0;
	_isClear = false;

	if (stageNum == 1)
	{
		//에너미 클래스 객체 생성 및 초기화
		this->setSoldier(3800, 1000);
		this->setSoldier(3300, 1200);
		this->setSoldier(3600, 1400);
		this->setSoldier(3200, 1600);
		//this->setBrovil(3700, 1000, 5);

		_brovil = new brovil;
		_brovil->init(3200, 1000);
	}
	else if (stageNum == 2)
	{
		this->setSoldier(1816,1567);
		this->setSoldier(1926,1297);
		this->setSoldier(1956,1017);
		this->setSoldier(2096, 817);
		this->setSoldier(2896,1917);
		this->setSoldier(2886,1497);
		this->setSoldier(2995,1906);
		this->setSoldier(3830, 683);
		this->setDog(1536, 1647, 1);
		this->setDog(2768, 1308, 1);
		this->setDog(3738, 1175, 0);

		_boss = new boss;
		_boss->init(3270.f, 600.f);
		_bossBullet = new bossBullet;
		_bossBullet->init();
		_bossRocket = new bossRocket;
		_bossRocket->init(50.f);
		_hpBar = new progressBar;
		_hpBar->init("enemyImage/bossImage/boss_hpbar_red", "enemyImage/bossImage/boss_hpbar_white", "enemyImage/bossImage/boss_hpbar_black",
			WINSIZEX / 2 - 1062 / 2, 57, WINSIZEX / 2 - 1062 / 2, 57, WINSIZEX / 2 - 1076 / 2, 50, 1062, 17, 1062, 17, 1076, 30);

	}

	return S_OK;
}

void enemyManager::release(void)
{
	if (_stageNum == 1)
	{
		_brovil->release();
		SAFE_DELETE(_brovil);
		
	}
	else if (_stageNum == 2)
	{
		_boss->release();
		SAFE_DELETE(_boss);
		_bossBullet->release();
		SAFE_DELETE(_bossBullet);
		_bossRocket->release();
		SAFE_DELETE(_bossRocket);
		_hpBar->release();
		SAFE_DELETE(_hpBar);
		_vDog.clear();
	}
		
	_eBullet->release();
	SAFE_DELETE(_eBullet);
	_vSoldier.clear();
	
}

void enemyManager::update(void)
{
	if (_stageNum == 1)
	{
		_brovil->update();
		// 브로빌 픽셀 충돌
		this->collideBrovilWithPixel();
		// 브로빌 시체 픽셀 충돌
		this->collideBrovilCorpseWithPixel();

	}
	else if (_stageNum == 2)
	{
		for (int i = 0; i < _vDog.size(); ++i)
		{
			_vDog[i]->update();
		}
		_boss->update();
		_bossBullet->update();
		_bossRocket->update();
		_hpBar->update();
		_hpBar->setGauge(_boss->getHP(), 1000);
	}

	_eBullet->update();
	
	// 솔져 방향바꿈
	this->changeDirection();
	
	for (int i = 0; i < _vSoldier.size(); ++i)
	{		
		_vSoldier[i]->update();			
	}
	
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		if (_vSoldier[i]->getIsAlive())
		{
			this->enemyFire(i);
		}
	}
	
		
	// 에너미 픽셀(지형) 충돌
	this->collideWithPixel();
	// 에너미 시체 픽셀 충돌
	this->collideWithCorpse();
	
	// 에너미 시야와 플레이어 충돌
	this->collideWithSight();
	// 에너미 총알과 플레이어 충돌
	this->collideWithPlayer();
	// 플레이어 총알과 에너미 충돌
	this->collideWithPBullet();		
	// 플레이어 수류탄과 에너미 충돌	
	this->collideWithPGrenade();	
	// 에너미 총알과 픽셀 충돌
	this->collideBulletWithPixel();
	// 할아버지 총알 vs 에너미 충돌
	this->collideWithGBullet();
	// 할아비 총알 vs 브로빌 충돌
	this->collideBrovilWithGBullet();
	
	if (_stageNum == 1)
	{
		// 플레이어 총알과 브로빌 충돌
		this->collideBrovilwithPBullet();
			
	}
	else if (_stageNum == 2)
	{
		// 보스 총알, 로켓 발사
		this->bossBulletFire();
		this->bossRocketFire();
		
		// 보스 총알, 로켓 vs 램브로 충돌
		this->collideWithBossBullet();
		this->collideWithBossRocket();
		this->bossDirChange();
		this->PBulletHitBoss();
		// 보스 로켓 vs 지형충돌
		this->collideBossRocketWithPixel();
		
		// 할아버지 총알 vs 보스
		this->collideBossWithGBullet();
		this->collideBossWithGGrenade();
		
		// 도그와 픽셀충돌
		this->collideDogSightWithPlayer();
		this->collideDogWithPlayer();
		this->collideDogWithPixel();
		this->collideDogWithPBullet();
		this->collideDogWithGBullet();
		this->collideDogCorpseWithPixel();
	}

}

void enemyManager::render(void)
{
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		_vSoldier[i]->render();		
	}
	
	_eBullet->render();
	if (_stageNum == 1)
	{
		_brovil->render();
	}
	
	if (_stageNum == 2)
	{
		for (int i = 0; i < _vDog.size(); ++i)
		{
			_vDog[i]->render();
		}
		_boss->render();
		_bossBullet->render();
		_bossRocket->render();
		
		if (_boss->getIsAlive())
		{			
			if (_boss->radarIn(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), 1500.f))
				_hpBar->render();
		}
	}		

	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		char str[64];
		sprintf_s(str, "%d", _vSoldier[i]->getBodyStatus());
		TextOut(getMemDC(), 300, 10+i*50, str, strlen(str));
	}
}

//=====================================================================================================================================================================================
//=====================================================================================================================================================================================
//=====================================================================================================================================================================================

void enemyManager::setSoldier(int x, int y)
{
	enemy* _soldier = new soldier;
	_soldier->initSoldier(x, y);
	_vSoldier.push_back(_soldier);
}

void enemyManager::setBrovil(int x, int y)
{
	
}

void enemyManager::setDog(int x, int y, bool isLeft)
{
	dog* _dog = new dog;
	_dog->initDog(x, y, isLeft);
	_vDog.push_back(_dog);
}

bool enemyManager::isEffect(int frame)
{	
	if (!_isEffect)
	{
		_isEffect = true;
		return true;
	}
	else
	{
		_isEffect = false;
		return false;
	}
}

void enemyManager::enemyFire(int num)
{	
	// 총알발사
	if (_vSoldier[num]->getIsFire())
	{
		// 왼쪽이면
		if (_vSoldier[num]->getDirection())
			_eBullet->fire(_vSoldier[num]->getX() + _vSoldier[num]->getEnemyBodyImage(_vSoldier[num]->getBodyStatus())->getFrameWidth() - _vSoldier[num]->getEnemyArmImage(_vSoldier[num]->getArmStatus())->getFrameWidth(),
				getVEnemy()[num]->getY() + _vSoldier[num]->getEnemyBodyImage(_vSoldier[num]->getBodyStatus())->getFrameHeight() / 2,
				10, getVEnemy()[num]->getDirection());
		
		// 오른쪽이면
		else
			_eBullet->fire(_vSoldier[num]->getX() + _vSoldier[num]->getEnemyArmImage(_vSoldier[num]->getArmStatus())->getFrameWidth(),
				getVEnemy()[num]->getY() + _vSoldier[num]->getEnemyBodyImage(_vSoldier[num]->getBodyStatus())->getFrameHeight() / 2,
				10, getVEnemy()[num]->getDirection());
	}	
}

void enemyManager::bossBulletFire()
{
	// 총알
	if (_boss->getGunStatus() == BB_FIRE && _boss->getBodyStatus() == B_IDLE)
	{
		if (_boss->getTerrorKopter().isLeft)
			_bossBullet->fire(_boss->getTerrorKopter().rcGun.left - 64, _boss->getTerrorKopter().rcGun.top + 20, _boss->getTerrorKopter().isLeft);
		else
			_bossBullet->fire(_boss->getTerrorKopter().rcGun.right, _boss->getTerrorKopter().rcGun.top + 20, _boss->getTerrorKopter().isLeft);
	}
}

void enemyManager::bossRocketFire()
{
	// 보스 발싸! 로켓
	if (_boss->getStatus() == LEFT_FIRE_ROCKET || _boss->getStatus() == RIGHT_FIRE_ROCKET)
	{
		if (_boss->getTerrorKopter().isLeft == 1)
			_bossRocket->fire(_boss->getTerrorKopter().rcGun.left - 60, _boss->getTerrorKopter().rcGun.top + 20, 3, 1);
		else
			_bossRocket->fire(_boss->getTerrorKopter().rcGun.right, _boss->getTerrorKopter().rcGun.top + 20, 3, 0);
	}
}

// 죽은 에너미 벡터에 담기
void enemyManager::saveEnemy(enemyType enemy, deadType deadType, bool isLeft)
{
	deadEnemy _deadEnemy;
	_deadEnemy._enemyType = enemy;
	_deadEnemy._deadType = deadType;
	_deadEnemy.isLeft = isLeft;
	_vDeadEnemyInfo.push_back(_deadEnemy);
}

void enemyManager::changeDirection()
{
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		if (!_vSoldier[i]->getIsUncovered()) continue;

		// 플레이어 방향에 맞춰 적방향 바꿈 (발견상태일때)
		if ((180 / 3.14f * getAngle(_vSoldier[i]->getX(), _vSoldier[i]->getY(), _playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY())) >= 91.f
			&& (180 / 3.14f * getAngle(_vSoldier[i]->getX(), _vSoldier[i]->getY(), _playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY()) <= 270.f))
		{
			_vSoldier[i]->setDirection(true);
		}
		else
		{
			_vSoldier[i]->setDirection(false);
		}
	}
}

void enemyManager::soldierDieWithBullet(int i)
{
	
	_vSoldier[i]->setIsUncovered(false);
	_vSoldier[i]->setIsStrange(false);
	_vSoldier[i]->setHP(_vSoldier[i]->getHP() - 1);

	if (_vSoldier[i]->getBodyStatus() != ENEMY_KNOCK_BACK && _vSoldier[i]->getBodyStatus() != ENEMY_DEAD && _vSoldier[i]->getBodyStatus() != ENEMY_FLY_AWAY)
	{
		if (_vSoldier[i]->getDirection())
			_vSoldier[i]->setBodyImageIndex(_vSoldier[i]->getEnemyBodyImage(ENEMY_KNOCK_BACK)->getMaxFrameX() - 1);
		else
			_vSoldier[i]->setBodyImageIndex(0);

		_vSoldier[i]->setBodyStatus(ENEMY_KNOCK_BACK);
	}

	if (_vSoldier[i]->getBodyStatus() == ENEMY_DEAD)
	{
		_vSoldier[i]->deadMove();
	}

	// 피터지는 효과
	if (_isEffect)
	{
		EFFECTMANAGER->bloodSplash(_vSoldier[i]->getX() + _vSoldier[i]->getEnemyBodyImage(_vSoldier[i]->getBodyStatus())->getFrameWidth() / 2,
			_vSoldier[i]->getY() + _vSoldier[i]->getEnemyBodyImage(_vSoldier[i]->getBodyStatus())->getFrameHeight() / 2,
			_vSoldier[i]->getDirection());
	}

	if (_vSoldier[i]->getHP() == 10)
	// 죽은 적 벡터에 담기
	this->saveEnemy(SOLDIER, BULLET, _vSoldier[i]->getDirection());
}

void enemyManager::soldierDieWithGrenade(int i)
{
	_vSoldier[i]->setIsUncovered(false);
	_vSoldier[i]->setIsStrange(false);
	_vSoldier[i]->setHP(_vSoldier[i]->getHP() - 1);

	if (_vSoldier[i]->getBodyStatus() != ENEMY_KNOCK_BACK && _vSoldier[i]->getBodyStatus() != ENEMY_DEAD && _vSoldier[i]->getBodyStatus() != ENEMY_FLY_AWAY)
	{
		if (_vSoldier[i]->getDirection())
			_vSoldier[i]->setBodyImageIndex(_vSoldier[i]->getEnemyBodyImage(ENEMY_KNOCK_BACK)->getMaxFrameX() - 1);
		else
			_vSoldier[i]->setBodyImageIndex(0);

		_vSoldier[i]->setBodyStatus(ENEMY_FLY_AWAY);
	}

	
	if (_vSoldier[i]->getBodyStatus() == ENEMY_DEAD)
	{
		_vSoldier[i]->deadMove();
	}
	
	// 피터지는 효과
	if (_isEffect)
	{
		EFFECTMANAGER->bloodSplash(_vSoldier[i]->getX() + _vSoldier[i]->getEnemyBodyImage(_vSoldier[i]->getBodyStatus())->getFrameWidth() / 2,
			_vSoldier[i]->getY() + _vSoldier[i]->getEnemyBodyImage(_vSoldier[i]->getBodyStatus())->getFrameHeight() / 2,
			_vSoldier[i]->getDirection());
	}
	
	if (_vSoldier[i]->getHP() == 10)
	this->saveEnemy(SOLDIER, GRENADE, _vSoldier[i]->getDirection());
}

// 브로빌 죽음
void enemyManager::brovilDieWithBullet()
{
	//_brovil->setIsUncovered(false);
	//_brovil->setIsStrange(false);
	_brovil->setHP(_brovil->getHP() - 1);

	if (_brovil->getBrovilStatus() != BROVIL_KNOCK_BACK && _brovil->getBrovilStatus() != BROVIL_DEAD && _brovil->getBrovilStatus() != BROVIL_FLY_AWAY)
	{
		if (_brovil->getDirection())
			_brovil->setBrovilImageIndex(_brovil->getBrovilImage(BROVIL_KNOCK_BACK)->getMaxFrameX() - 1);
		else
			_brovil->setBrovilImageIndex(0);

		_brovil->setBrovilStatus(BROVIL_KNOCK_BACK);
	}

	if (_brovil->getBrovilStatus() == BROVIL_DEAD)
	{
		_brovil->deadMove();
	}

	//if (this->isEffect(2))
	//{
	//	EFFECTMANAGER->bloodSplash(_brovil->getX() + _brovil->getBrovilImage(_brovil->getBrovilStatus())->getFrameWidth()/2, _brovil->getY() + _brovil->getBrovilImage(_brovil->getBrovilStatus())->getFrameHeight()/2,
	//		_brovil->getDirection());
	//}
	if (_brovil->getHP() == 10)
	// 죽은 적 벡터에 담기
	this->saveEnemy(BROVIL, BULLET, _brovil->getDirection());
	_isClear = true;
}

void enemyManager::brovilDieWithGrenade()
{
	_brovil->setHP(_brovil->getHP() - 1);

	if (_brovil->getBrovilStatus() != BROVIL_KNOCK_BACK && _brovil->getBrovilStatus() != BROVIL_DEAD && _brovil->getBrovilStatus() != BROVIL_FLY_AWAY)
	{
		if (_brovil->getDirection())
			_brovil->setBrovilImageIndex(_brovil->getBrovilImage(BROVIL_KNOCK_BACK)->getMaxFrameX() - 1);
		else
			_brovil->setBrovilImageIndex(0);

		_brovil->setBrovilStatus(BROVIL_FLY_AWAY);
	}

	if (_brovil->getBrovilStatus() == BROVIL_DEAD)
	{
		_brovil->deadMove();
	}

	//if (this->isEffect(2))
	//{
	//	EFFECTMANAGER->bloodSplash(_brovil->getX() + _brovil->getBrovilImage(_brovil->getBrovilStatus())->getFrameWidth()/2, _brovil->getY() + _brovil->getBrovilImage(_brovil->getBrovilStatus())->getFrameHeight()/2,
	//		_brovil->getDirection());
	//}
	if (_brovil->getHP() == 0)
	// 죽은 적 벡터에 담기
	this->saveEnemy(BROVIL, GRENADE, _brovil->getDirection());
	_isClear = true;
}

// 에너미와 픽셀충돌
void enemyManager::collideWithPixel()
{
	// 지형과 충돌(픽셀충돌)
	RECT rc;
	for (int j = 0; j < _vSoldier.size(); ++j)
	{
		float x, y;
		x = _vSoldier[j]->getX();
		y = _vSoldier[j]->getY();
		
		// 바닥과 충돌
		if (COLLISIONMANAGER->pixelCollision(_vSoldier[j]->getRcEnemy(), x, y, _vSoldier[j]->getSpeed(), _vSoldier[j]->getGravity(), ENEMY_BOTTOM))
		{
			if (_vSoldier[j]->getBodyStatus() == ENEMY_FLY_AWAY)
			_vSoldier[j]->setEnemyAngle(2* PI - _vSoldier[j]->getEnemyAngle());

			_vSoldier[j]->setIsOn(true);			
		}
		else
		{
			_vSoldier[j]->setIsOn(false);
		}

		// 윗 천장과 충돌
		if (COLLISIONMANAGER->pixelCollision(_vSoldier[j]->getRcEnemy(), x, y, _vSoldier[j]->getSpeed(), _vSoldier[j]->getGravity(), ENEMY_TOP))
		{
			_vSoldier[j]->setEnemyAngle(2 * PI - _vSoldier[j]->getEnemyAngle());
			
		}
		else
		{
			_vSoldier[j]->setY(y);
		}
		
		// 적 왼쪽 벽과 충돌
		if (COLLISIONMANAGER->pixelCollision(_vSoldier[j]->getRcEnemy(), x, y, _vSoldier[j]->getSpeed(), _vSoldier[j]->getGravity(), ENEMY_LEFT))
		{
			_vSoldier[j]->setEnemyAngle(PI - _vSoldier[j]->getEnemyAngle());
			if (_vSoldier[j]->getIsAlive())
			{
				_vSoldier[j]->setDirection(0);
			}
		}	
		else
		{
			_vSoldier[j]->setX(x);
		}
		
		// 적 오른쪽 벽과 충돌
		if (COLLISIONMANAGER->pixelCollision(_vSoldier[j]->getRcEnemy(), x, y, _vSoldier[j]->getSpeed(), _vSoldier[j]->getGravity(), ENEMY_RIGHT))
		{
			_vSoldier[j]->setEnemyAngle(PI - _vSoldier[j]->getEnemyAngle());
			if (_vSoldier[j]->getIsAlive())
			{
				_vSoldier[j]->setDirection(1);
			}
		}	
		else
		{
			_vSoldier[j]->setX(x);
		}		
		
		//플레이어와 오브젝트 충돌
		//for (int k = 0; k < OBJECTMANAGER->getVObject().size(); k++)
		//{
		//	if (OBJECT_DESTROY == OBJECTMANAGER->getVObject()[k]->getState()) continue;
		//	if (OBJECTMANAGER->getVObject()[k]->getType() == WOODENBOX || OBJECTMANAGER->getVObject()[k]->getType() == SKULL_DRUMGRAY || OBJECTMANAGER->getVObject()[k]->getType() == SKULL_DRUMRED ||
		//		OBJECTMANAGER->getVObject()[k]->getType() == PRISONER || OBJECTMANAGER->getVObject()[k]->getType() == AMERICAN_FLAG || OBJECTMANAGER->getVObject()[k]->getType() == HELICOPTER)
		//	{
		//		switch (OBJECTMANAGER->getVObject()[k]->getState())
		//		{
		//		case OBJECT_IDLE:
		//			//오브젝트와 플레이어가 충돌했을 때 (수류탄과의 충돌도 똑같이 해줘야 한다! +앵글 바꾸는것 더해줄것)
		//			if (IntersectRect(&rc, &_vSoldier[j]->getRcEnemy(), &OBJECTMANAGER->getVObject()[k]->getRect()) &&
		//				OBJECTMANAGER->getVObject()[k]->getType() != AMERICAN_FLAG && OBJECTMANAGER->getVObject()[k]->getType() != HELICOPTER)
		//			{
		//				int width = _vSoldier[j]->getRcEnemy().right - _vSoldier[j]->getRcEnemy().left;
		//				int height = _vSoldier[j]->getRcEnemy().bottom - _vSoldier[j]->getRcEnemy().top;
		//
		//				if (_vSoldier[j]->getRcEnemy().left + width / 2 < rc.left)
		//					_vSoldier[j]->setX(_vSoldier[j]->getX() - (rc.right - rc.left)); //왼 쪽에서 부딪혔을 때
		//				else if (_vSoldier[j]->getRcEnemy().left + width / 2 > rc.right)
		//					_vSoldier[j]->setX(_vSoldier[j]->getX() + (rc.right - rc.left)); //오른쪽
		//
		//				if (_vSoldier[j]->getRcEnemy().top + height / 2 < rc.top)
		//					_vSoldier[j]->setY(_vSoldier[j]->getY() - (rc.bottom - rc.top)); //위에서 눌러찍었을 때
		//				else if (_vSoldier[j]->getRcEnemy().top + height / 2 > rc.bottom)
		//					_vSoldier[j]->setY(_vSoldier[j]->getY() + (rc.bottom - rc.top));
		//			}
		//			if (IntersectRect(&rc, &_vSoldier[j]->getRcEnemy(), &OBJECTMANAGER->getVObject()[k]->getActivationRect()))
		//			{
		//				if (OBJECTMANAGER->getVObject()[k]->getType() == PRISONER)
		//					OBJECTMANAGER->getVObject()[k]->setIsActived(true);
		//				if (OBJECTMANAGER->getVObject()[k]->getType() == AMERICAN_FLAG || OBJECTMANAGER->getVObject()[k]->getType() == HELICOPTER)
		//					OBJECTMANAGER->getVObject()[k]->setState(OBJECT_MOVE);
		//			}
		//			break;
		//		//case OBJECT_MOVE:
		//		//	if (OBJECTMANAGER->getVObject()[k]->getType() == PRISONER)
		//		//	{
		//		//		if (IntersectRect(&rc, &_vSoldier[j]->getRcEnemy(), &OBJECTMANAGER->getVObject()[k]->getRect()))
		//		//		{
		//		//			//할아버지 등장 시점 
		//		//			OBJECTMANAGER->getVObject()[k]->setState(OBJECT_DESTROY);
		//		//		}
		//		//		else
		//		//		{
		//		//			//OBJECTMANAGER->getVObject()[k]->setGravity(OBJECTMANAGER->getVObject()[k]->getGravity() + 0.55f);
		//		//			//OBJECTMANAGER->getVObject()[k]->setY(OBJECTMANAGER->getVObject()[k]->getY() + (-sinf(OBJECTMANAGER->getVObject()[k]->getAngle()) * OBJECTMANAGER->getVObject()[k]->getSpeed() + _vObject[i]->getGravity()));
		//		//			//OBJECTMANAGER->collisionProcess();
		//		//		}
		//		//	}
		//		//	//if (OBJECTMANAGER->getVObject()[k]->getType() == AMERICAN_FLAG)
		//		//	//{
		//		//	//	//부활 좌표 저장 시점
		//		//	//}
		//		//	//if (OBJECTMANAGER->getVObject()[k]->getType() == HELICOPTER)
		//		//	//{
		//		//	//	//헬리콥터 사다리에 매달림
		//		//	//}
		//		//	break;
		//		}
		//	}
		//}

		// rambro bullet 
		for (int i = 0; i < _eBullet->getVEnemybullet().size(); i++)  // 총알이랑 벽이랑 충돌하면 벽 지워주기
		{
			if (!_eBullet->getVEnemybullet()[i].isActived)continue;
			for (int k = 0; k < OBJECTMANAGER->getVObject().size(); k++)
			{
				if (OBJECT_DESTROY == OBJECTMANAGER->getVObject()[k]->getState()) continue;
				if (OBJECTMANAGER->getVObject()[k]->getType() == WOODENBOX || OBJECTMANAGER->getVObject()[k]->getType() == SKULL_DRUMGRAY ||
					OBJECTMANAGER->getVObject()[k]->getType() == SKULL_DRUMRED || OBJECTMANAGER->getVObject()[k]->getType() == PRISONER)
				{
					switch (OBJECTMANAGER->getVObject()[k]->getState())
					{
					case OBJECT_IDLE:
						//총알과 박스/드럼통/감옥이 부딪혔을 때 (수류탄에도 똑같이 적용해 줄 것!)
						if (IntersectRect(&rc, &_eBullet->getVEnemybullet()[i].rc, &OBJECTMANAGER->getVObject()[k]->getRect()))
						{
							if (OBJECTMANAGER->getVObject()[k]->getType() == WOODENBOX)
							{
								EFFECTMANAGER->woodDebris(OBJECTMANAGER->getVObject()[i]->getRect().left, OBJECTMANAGER->getVObject()[k]->getRect().top, _vSoldier[j]->getDirection());
								OBJECTMANAGER->getVObject()[k]->setState(OBJECT_DESTROY);
							}
							else if (OBJECTMANAGER->getVObject()[k]->getType() == SKULL_DRUMGRAY || OBJECTMANAGER->getVObject()[k]->getType() == SKULL_DRUMRED)
							{
								//for (int k = 0; k < _mapData->getObject().size(); k++)
								//{
								//	POINT pt;
								//	pt.x = (OBJECTMANAGER->getVObject()[k]->getRect().left + (OBJECTMANAGER->getVObject()[k]->getRect().right - OBJECTMANAGER->getVObject()[k]->getRect().left) / 2);
								//	pt.y = (OBJECTMANAGER->getVObject()[k]->getRect().top + (OBJECTMANAGER->getVObject()[k]->getRect().bottom - OBJECTMANAGER->getVObject()[k]->getRect().top) / 2) + 68;
								//
								//	if (PtInRect(&_mapData->getObject()[k]._rc, pt))
								//	{
								//		_mapData->deleteMapIndexByIndex(k, 5, 5);
								//		break;
								//	}
								//}
								EFFECTMANAGER->explosion(OBJECTMANAGER->getVObject()[k]->getRect().left, OBJECTMANAGER->getVObject()[k]->getRect().top);
								CAMERAMANAGER->CameraShake();
								OBJECTMANAGER->getVObject()[k]->setState(OBJECT_DESTROY);
							}
							else if (OBJECTMANAGER->getVObject()[k]->getType() == PRISONER)
							{
								EFFECTMANAGER->woodDebris(OBJECTMANAGER->getVObject()[k]->getRect().left, OBJECTMANAGER->getVObject()[k]->getRect().top, _vSoldier[j]->getDirection());
								OBJECTMANAGER->getVObject()[k]->setState(OBJECT_MOVE);
							}
							EFFECTMANAGER->bulletPuff(_eBullet->getVEnemybullet()[i].x, _eBullet->getVEnemybullet()[i].y);
							_eBullet->getVEnemybullet()[i].isActived = false;
						}
						break;
					case OBJECT_MOVE:
						break;
					}
				}
			}
		}

	}		
}

// 시체와 픽셀 충돌
void enemyManager::collideWithCorpse()
{
	// 시체 토막 충돌
	RECT rc;
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		for (int j = 0; j < BODY_PART; ++j)
		{
			if (!_vSoldier[i]->getIsApart()) continue;

			float x, y;
			x = _vSoldier[i]->getCorpse()[j].x;
			y = _vSoldier[i]->getCorpse()[j].y;

			// 바닥
			if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getCorpse()[j].rcCorpse, x, y, _vSoldier[i]->getCorpse()[j].speed, _vSoldier[i]->getCorpse()[j].gravity, ENEMY_BOTTOM))
			{
				_vSoldier[i]->getCorpse()[j].angle = 2 * PI - _vSoldier[i]->getCorpse()[j].angle;
				_vSoldier[i]->getCorpse()[j].gravity = 0.f;
			}

			// 천장
			if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getCorpse()[j].rcCorpse, x, y, _vSoldier[i]->getCorpse()[j].speed, _vSoldier[i]->getCorpse()[j].gravity, ENEMY_TOP))
			{
				_vSoldier[i]->getCorpse()[j].angle = 2 * PI - _vSoldier[i]->getCorpse()[j].angle;
			}

			// 왼쪽
			if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getCorpse()[j].rcCorpse, x, y, _vSoldier[i]->getCorpse()[j].speed, _vSoldier[i]->getCorpse()[j].gravity, ENEMY_LEFT))
			{
				_vSoldier[i]->getCorpse()[j].angle = PI - _vSoldier[i]->getCorpse()[j].angle;
			}

			// 오른쪽
			if (COLLISIONMANAGER->pixelCollision(_vSoldier[i]->getCorpse()[j].rcCorpse, x, y, _vSoldier[i]->getCorpse()[j].speed, _vSoldier[i]->getCorpse()[j].gravity, ENEMY_RIGHT))
			{
				_vSoldier[i]->getCorpse()[j].angle = PI - _vSoldier[i]->getCorpse()[j].angle;
			}

			_vSoldier[i]->getCorpse()[j].x = x;
			_vSoldier[i]->getCorpse()[j].y = y;

		}
	}	
}

void enemyManager::collideWithSight()
{
	// 충돌처리(플레이어) vs 적 시야	
	RECT rc;
	RECT rcPlayer = RectMake(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(),
		_playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameWidth(), _playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameHeight());
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		float x = _vSoldier[i]->getRcEnemySight().left;
		float y = _vSoldier[i]->getRcEnemySight().top;

		if (IntersectRect(&rc, &_vSoldier[i]->getRcEnemySight(), &rcPlayer))
		{
			if (!_vSoldier[i]->getIsAlive()) continue;
			// 말풍선 띄우기
			_vSoldier[i]->setIsUncovered(true);
		}				
	}
}

//에너미 총알과 플레이어 충돌
void enemyManager::collideWithPlayer()
{
	RECT rc;
	RECT rcPlayer = RectMake(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(),
		_playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameWidth(), _playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameHeight());
	// 충돌처리 (플레이어, 적총알)
	for (int i = 0; i < getEBullet()->getVEnemybullet().size(); ++i)
	{
		if (IntersectRect(&rc, &getEBullet()->getVEnemybullet()[i].rc, &rcPlayer))
		{
			// 총알 제거
			getEBullet()->getVEnemybullet()[i].isActived = false;
		}		
	}
}

void enemyManager::collideWithBossBullet()
{
	// 보스총알과 플레이어가 충돌
	RECT rc;
	for (int i = 0; i < BOSS_BULLET_MAX; ++i)
	{
		if (IntersectRect(&rc, &_playerManager->getPlayer()->getRcRambro(), &_bossBullet->getBossBullet()[i].rc))
		{
			// 총알 제거
			if (!_bossBullet->getBossBullet()[i].isActived) continue;
			_bossBullet->getBossBullet()[i].isActived = false;
		}
	}
}

void enemyManager::collideWithBossRocket()
{
	RECT rc;
	for (int i = 0; i < BOSS_ROCKET_MAX; ++i)
	{
		if (IntersectRect(&rc, &_playerManager->getPlayer()->getRcRambro(), &_bossRocket->getBossRocket()[i].rc))
		{
			// 총알 제거
			_bossRocket->getBossRocket()[i].isActived = false;
		}
	}
}

void enemyManager::collideBossRocketWithPixel()
{
	RECT rc;
	for (int i = 0; i < BOSS_ROCKET_MAX ; i++)
	{		
		if (!_bossRocket->getBossRocket()[i].isActived) continue;

		if (COLLISIONMANAGER->pixelCollision(_bossRocket->getBossRocket()[i].rc, _bossRocket->getBossRocket()[i].x, _bossRocket->getBossRocket()[i].y, _bossRocket->getBossRocket()[i].speed, _bossRocket->getBossRocket()[i].gravity, 3) == GREEN)				// 아래쪽 벽
		{
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (IntersectRect(&rc, &_mapData->getObject()[j]._rc, &_bossRocket->getBossRocket()[i].rc))
				{
					_bossRocket->getBossRocket()[i].isActived = false;
					_mapData->deleteMapIndexByIndex(j, 1, 1);
					CAMERAMANAGER->CameraShake();
					//EFFECTMANAGER->rambroGrenadeExplosion(_gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y);
					
					break;
				}
			}
		}
		else if (COLLISIONMANAGER->pixelCollision(_bossRocket->getBossRocket()[i].rc, _bossRocket->getBossRocket()[i].x, _bossRocket->getBossRocket()[i].y, _bossRocket->getBossRocket()[i].speed, _bossRocket->getBossRocket()[i].gravity, 1) == GREEN)			// 위쪽 벽
		{
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (IntersectRect(&rc, &_mapData->getObject()[j]._rc, &_bossRocket->getBossRocket()[i].rc))
				{
					_bossRocket->getBossRocket()[i].isActived = false;
					_mapData->deleteMapIndexByIndex(j, 1, 1);
					CAMERAMANAGER->CameraShake();
					//EFFECTMANAGER->rambroGrenadeExplosion(_gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y);
					
					break;
				}
			}
		}
		if (COLLISIONMANAGER->pixelCollision(_bossRocket->getBossRocket()[i].rc, _bossRocket->getBossRocket()[i].x, _bossRocket->getBossRocket()[i].y, _bossRocket->getBossRocket()[i].speed, _bossRocket->getBossRocket()[i].gravity, 2) == GREEN)				// 오른쪽 벽	
		{
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (IntersectRect(&rc, &_mapData->getObject()[j]._rc, &_bossRocket->getBossRocket()[i].rc))
				{
					_bossRocket->getBossRocket()[i].isActived = false;
					_mapData->deleteMapIndexByIndex(j, 1, 1);
					CAMERAMANAGER->CameraShake();
					//EFFECTMANAGER->rambroGrenadeExplosion(_gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y);
					
					break;
				}
			}
		}
		else if (COLLISIONMANAGER->pixelCollision(_bossRocket->getBossRocket()[i].rc, _bossRocket->getBossRocket()[i].x, _bossRocket->getBossRocket()[i].y, _bossRocket->getBossRocket()[i].speed, _bossRocket->getBossRocket()[i].gravity, 0) == GREEN)			// 왼쪽 벽	
		{
			for (int j = 0; j < _mapData->getObject().size(); j++)
			{
				if (IntersectRect(&rc, &_mapData->getObject()[j]._rc, &_bossRocket->getBossRocket()[i].rc))
				{
					_bossRocket->getBossRocket()[i].isActived = false;
					_mapData->deleteMapIndexByIndex(j, 1, 1);
					CAMERAMANAGER->CameraShake();
					//EFFECTMANAGER->rambroGrenadeExplosion(_gMissile->getVPlayergMissile()[i].x, _gMissile->getVPlayergMissile()[i].y);
					
					break;
				}
			}
		}
	}
}

// 보스 움직임 변화 (플레이어 위치에 따라)
void enemyManager::bossDirChange()
{	
	if (_playerManager->getPlayer()->getX() < 2300) return;

	if (_boss->getTerrorKopter().x >= 2300 && _boss->getTerrorKopter().x < 3300)
	{
		if (!_boss->radarIn(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), 1000.f))
		{
			// 플레이어가 보스보다 왼쪽이면 상태 바꿔줌
			if (_playerManager->getPlayer()->getX() + 30 < _boss->getTerrorKopter().x + _boss->getTerrorKopter().img.bodyImage[_boss->getBodyStatus()]->getFrameWidth() / 2)
			{
				_boss->setStatus(LEFT_MOVE);
			}
			else if (_playerManager->getPlayer()->getX() + 30 > _boss->getTerrorKopter().x + _boss->getTerrorKopter().img.bodyImage[_boss->getBodyStatus()]->getFrameWidth() / 2)
			{
				_boss->setStatus(RIGHT_MOVE);
			}
		}
		else
		{
			++_count;
			if (_boss->getStatus() != (LEFT_FIRE_ROCKET && RIGHT_FIRE_ROCKET))
			{
				if (_count > 200)
				{
					_count = 0;
					_choice = RND->getFromIntTo(0, 3);
				}
			}
			else if (_boss->getStatus() == (LEFT_FIRE_ROCKET || RIGHT_FIRE_ROCKET))
			{
				if (_count > 100)
				{
					_count = 0;
					if (_choice == 3 || _choice == 2)
					{
						_choice = RND->getFromIntTo(0, 1);
					}
					else
					{
						_choice = RND->getFromIntTo(0, 3);
					}
				}
			}

			switch (_choice)
			{
			case 0:
			{
				_boss->setStatus(LEFT_FIRE_BULLET);
				break;
			}
			case 1:
			{
				_boss->setStatus(RIGHT_FIRE_BULLET);
				break;
			}
			case 2:
			{
				_boss->setStatus(LEFT_FIRE_ROCKET);
				break;
			}
			case 3:
			{
				_boss->setStatus(RIGHT_FIRE_ROCKET);
				break;
			}

			default:
				break;
			}

			if (_boss->getStatus() == LEFT_FIRE_BULLET || _boss->getStatus() == RIGHT_FIRE_BULLET)
			{
				_boss->verticalMove(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), _boss->getTerrorKopter().angle);
			}
			else if (_boss->getStatus() == LEFT_FIRE_ROCKET || _boss->getStatus() == RIGHT_FIRE_ROCKET)
			{
				_boss->bombAttack(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(), _boss->getTerrorKopter().angle);
			}
		}
	}
	
}

// 보스가 플레이어 총알에 맞음
void enemyManager::PBulletHitBoss()
{
	RECT rc;
	for (int i = 0; i < _playerManager->getPBullet()->getVPlayerBullet().size(); ++i)
	{
		if (IntersectRect(&rc, &_playerManager->getPBullet()->getVPlayerBullet()[i].rc, &_boss->getRcBoss()))
		{			
			if (!_playerManager->getPBullet()->getVPlayerBullet()[i].isActived) continue;
			_playerManager->getPBullet()->getVPlayerBullet()[i].isActived = false;
			_boss->setHP(_boss->getHP() - 10);
		}		
	}
}

void enemyManager::bossDie()
{
	if (_boss->getTerrorKopter().isAlive == false)
	{
		_isClear = true;
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
				if (_vSoldier[i]->getIsApart()) continue;
				_vSoldier[i]->setDirection(_playerManager->getPBullet()->getVPlayerBullet()[j].isLeft);
				_vSoldier[i]->setDirection(_playerManager->getPBullet()->getVPlayerBullet()[j].isLeft);

				soldierDieWithBullet(i);
				
				break;
			}
		}
	}
}

// 수류탄과 에너미 충돌
void enemyManager::collideWithPGrenade()
{
	RECT rc;
	for (int i = 0; i < _vSoldier.size(); ++i)
	{
		for (int j = 0; j < _playerManager->getPGrenade()->getVPlayerGrenade().size(); ++j)
		{
			if (IntersectRect(&rc, &_playerManager->getPGrenade()->getVPlayerGrenade()[j].rc, &_vSoldier[i]->getRcEnemy()))
			{
				if (_vSoldier[i]->getIsApart()) continue;
				if (_vSoldier[i]->getBodyStatus() == ENEMY_FLY_AWAY) continue;

				if (_vSoldier[i]->getDirection() != _playerManager->getPGrenade()->getVPlayerGrenade()[j].isLeft)
				{
					_vSoldier[i]->setDirection(_playerManager->getPGrenade()->getVPlayerGrenade()[j].isLeft);
				}
				soldierDieWithGrenade(i);

				// 죽은 적 벡터에 담기
				this->saveEnemy(SOLDIER, GRENADE, _vSoldier[i]->getDirection());
			}
		}
	}
}

// 할아버지 총알과 에너미 충돌
void enemyManager::collideWithGBullet()
{
	RECT rc;
	for (int i = 0; i < _playerManager->getGBullet()->getVPlayergBullet().size(); ++i)
	{
		for (int j = 0; j < _vSoldier.size(); ++j)
		{
			if (IntersectRect(&rc, &_playerManager->getGBullet()->getVPlayergBullet()[i].rc, &_vSoldier[j]->getRcEnemy()))
			{
				if (!_playerManager->getGBullet()->getVPlayergBullet()[i].isActived) continue;
				_playerManager->getGBullet()->getVPlayergBullet()[i].isActived = false;
				_vSoldier[j]->setDirection(_playerManager->getGBullet()->getVPlayergBullet()[i].isLeft);

				soldierDieWithBullet(j);
			}
		}	
	}
}

// 할아버지 총알 vs 보스
void enemyManager::collideBossWithGBullet()
{
	RECT rc;
	for (int i = 0; i < _playerManager->getGBullet()->getVPlayergBullet().size(); ++i)
	{
		if (IntersectRect(&rc, &_playerManager->getGBullet()->getVPlayergBullet()[i].rc, &_boss->getRcBoss()))
		{
			if (!_playerManager->getGBullet()->getVPlayergBullet()[i].isActived) continue;
			_playerManager->getGBullet()->getVPlayergBullet()[i].isActived = false;
			_boss->setHP(_boss->getHP() - 10);
		}
	}
}

// 할아버지 수류탄 vs 보스
void enemyManager::collideBossWithGGrenade()
{

}

// 에너미 총알과 픽셀 충돌
void enemyManager::collideBulletWithPixel()
{
	RECT rc;
	for (int i = 0; i < _eBullet->getVEnemybullet().size(); ++i)
	{
		float x, y;
		x = _eBullet->getVEnemybullet()[i].x;
		y = _eBullet->getVEnemybullet()[i].y;

		if (!_eBullet->getVEnemybullet()[i].isActived) continue;

		// 바닥
		if (COLLISIONMANAGER->pixelCollision(_eBullet->getVEnemybullet()[i].rc, x, y, _eBullet->getVEnemybullet()[i].speed, _eBullet->getVEnemybullet()[i].gravity, ENEMY_BOTTOM))
		{
			_eBullet->getVEnemybullet()[i].isActived = false;
		}
		
		// 천장
		else if (COLLISIONMANAGER->pixelCollision(_eBullet->getVEnemybullet()[i].rc, x, y, _eBullet->getVEnemybullet()[i].speed, _eBullet->getVEnemybullet()[i].gravity, ENEMY_TOP))
		{
			_eBullet->getVEnemybullet()[i].isActived = false;
		}		

		// 왼쪽
		else if (COLLISIONMANAGER->pixelCollision(_eBullet->getVEnemybullet()[i].rc, x, y, _eBullet->getVEnemybullet()[i].speed, _eBullet->getVEnemybullet()[i].gravity, ENEMY_LEFT))
		{
			_eBullet->getVEnemybullet()[i].isActived = false;
		}		

		// 오른쪽
		else if (COLLISIONMANAGER->pixelCollision(_eBullet->getVEnemybullet()[i].rc, x, y, _eBullet->getVEnemybullet()[i].speed, _eBullet->getVEnemybullet()[i].gravity, ENEMY_RIGHT))
		{
			_eBullet->getVEnemybullet()[i].isActived = false;
		}		
	}
}

// 플레이어 총알과 브로빌 충돌
void enemyManager::collideBrovilwithPBullet()
{
	RECT rc;
	for (int i = 0; i < _playerManager->getPBullet()->getVPlayerBullet().size(); ++i)
	{
		if (IntersectRect(&rc, &_playerManager->getPBullet()->getVPlayerBullet()[i].rc, &_brovil->getRcBrovil()))
		{
			if (_brovil->getIsApart()) continue;

			if (_brovil->getDirection() != _playerManager->getPBullet()->getVPlayerBullet()[i].isLeft)
			{
				_brovil->setDirection(_playerManager->getPBullet()->getVPlayerBullet()[i].isLeft);
			}

			brovilDieWithBullet();
		}		
	}
}

// 브로빌 플레이어 수류탄에 맞음
void enemyManager::collideBrovilwithPGrenade()
{
	RECT rc;	
	for (int j = 0; j < _playerManager->getPGrenade()->getVPlayerGrenade().size(); ++j)
	{
		if (IntersectRect(&rc, &_playerManager->getPGrenade()->getVPlayerGrenade()[j].rc, &_brovil->getRcBrovil()))
		{
			if (_brovil->getIsApart()) continue;
			if (_brovil->getBrovilStatus() == ENEMY_FLY_AWAY) continue;

			if (_brovil->getDirection() != _playerManager->getPGrenade()->getVPlayerGrenade()[j].isLeft)
			{
				_brovil->setDirection(_playerManager->getPGrenade()->getVPlayerGrenade()[j].isLeft);
			}
			
			brovilDieWithGrenade();						
		}
	}	
}

// 브로빌 픽셀 충돌(지형)
void enemyManager::collideBrovilWithPixel()
{
	float x, y;
	x = _brovil->getX();
	y = _brovil->getY();

	// 바닥과 충돌
	if (COLLISIONMANAGER->pixelCollision(_brovil->getRcBrovil(), x, y, _brovil->getSpeed(), _brovil->getGravity(), ENEMY_BOTTOM))
	{
		if (_brovil->getBrovilStatus() == BROVIL_FLY_AWAY)
			_brovil->setEnemyAngle(2 * PI - _brovil->getEnemyAngle());

		_brovil->setIsOn(true);
	}
	else
	{
		_brovil->setIsOn(false);
	}

	// 윗 천장과 충돌
	if (COLLISIONMANAGER->pixelCollision(_brovil->getRcBrovil(), x, y, _brovil->getSpeed(), _brovil->getGravity(), ENEMY_TOP))
	{
		_brovil->setEnemyAngle(2 * PI - _brovil->getEnemyAngle());
	}
	else
	{
		_brovil->setY(y);
	}

	// 적 왼쪽 벽과 충돌
	if (COLLISIONMANAGER->pixelCollision(_brovil->getRcBrovil(), x, y, _brovil->getSpeed(), _brovil->getGravity(), ENEMY_LEFT))
	{
		_brovil->setEnemyAngle(PI - _brovil->getEnemyAngle());
		//if (_vSoldier[i]->getBodyStatus() == ENEMY_KNOCK_BACK || _vSoldier[i]->getBodyStatus() == ENEMY_FLY_AWAY)
		//{
		//	//if (_vSoldier[i]->getDirection()) _vSoldier[i]->setDirection(false);
		//	//else _vSoldier[i]->setDirection(true);
		//}			
	}
	else
	{
		_brovil->setX(x);
	}

	// 적 오른쪽 벽과 충돌
	if (COLLISIONMANAGER->pixelCollision(_brovil->getRcBrovil(), x, y, _brovil->getSpeed(), _brovil->getGravity(), ENEMY_RIGHT))
	{
		_brovil->setEnemyAngle(PI - _brovil->getEnemyAngle());
		//if (_vSoldier[i]->getBodyStatus() == ENEMY_KNOCK_BACK && _vSoldier[i]->getBodyStatus() == ENEMY_FLY_AWAY)
		//{
		//	//if (_vSoldier[i]->getDirection()) _vSoldier[i]->setDirection(false);
		//	//else _vSoldier[i]->setDirection(true);
		//}			
	}
	else
	{
		_brovil->setX(x);
	}
}

// 브로빌 시체와 픽셀(지형) 충돌
void enemyManager::collideBrovilCorpseWithPixel()
{
	// 시체 토막 충돌
	RECT rc;	
	for (int j = 0; j < BODY_PART; ++j)
	{
		if (!_brovil->getIsApart()) continue;

		float x, y;
		x = _brovil->getCorpse()[j].x;
		y = _brovil->getCorpse()[j].y;

		// 바닥
		if (COLLISIONMANAGER->pixelCollision(_brovil->getCorpse()[j].rcCorpse, x, y, _brovil->getCorpse()[j].speed, _brovil->getCorpse()[j].gravity, ENEMY_BOTTOM))
		{
			_brovil->getCorpse()[j].angle = 2 * PI - _brovil->getCorpse()[j].angle;
			_brovil->getCorpse()[j].gravity = 0.f;
		}

		// 천장
		if (COLLISIONMANAGER->pixelCollision(_brovil->getCorpse()[j].rcCorpse, x, y, _brovil->getCorpse()[j].speed, _brovil->getCorpse()[j].gravity, ENEMY_TOP))
		{
			_brovil->getCorpse()[j].angle = 2 * PI - _brovil->getCorpse()[j].angle;
		}

		// 왼쪽
		if (COLLISIONMANAGER->pixelCollision(_brovil->getCorpse()[j].rcCorpse, x, y, _brovil->getCorpse()[j].speed, _brovil->getCorpse()[j].gravity, ENEMY_LEFT))
		{
			_brovil->getCorpse()[j].angle = PI - _brovil->getCorpse()[j].angle;
		}

		// 오른쪽
		if (COLLISIONMANAGER->pixelCollision(_brovil->getCorpse()[j].rcCorpse, x, y, _brovil->getCorpse()[j].speed, _brovil->getCorpse()[j].gravity, ENEMY_RIGHT))
		{
			_brovil->getCorpse()[j].angle = PI - _brovil->getCorpse()[j].angle;
		}

		_brovil->getCorpse()[j].x = x;
		_brovil->getCorpse()[j].y = y;

	}	
}

void enemyManager::collideBrovilWithGBullet()
{
	RECT rc;
	for (int i = 0; i < _playerManager->getGBullet()->getVPlayergBullet().size(); ++i)
	{
		if (IntersectRect(&rc, &_playerManager->getGBullet()->getVPlayergBullet()[i].rc, &_brovil->getRcBrovil()))
		{
			if (_brovil->getIsApart()) continue;
			_brovil->setDirection(_playerManager->getGBullet()->getVPlayergBullet()[i].isLeft);
			
			this->brovilDieWithBullet();
		}
	}
}


// 개의 시야에 플레이어가 보임!
void enemyManager::collideDogSightWithPlayer()
{
	// 충돌처리(플레이어) vs 적 시야	
	RECT rc;
	RECT rcPlayer = RectMake(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(),
		_playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameWidth(), _playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameHeight());
	for (int i = 0; i < _vDog.size(); ++i)
	{
		if (IntersectRect(&rc, &_vDog[i]->getRCsight(), &rcPlayer))
		{
			if (!_vDog[i]->getIsAlive()) continue;
			// 말풍선 띄우기
			_vDog[i]->setIsUncovered(true);
		}
	}
}

// 도그 공격반경 안에 플레이어가 들어옴
void enemyManager::collideDogWithPlayer()
{
	RECT rc;
	for (int i = 0; i < _vDog.size(); ++i)
	{
		if (IntersectRect(&rc, &_playerManager->getPlayer()->getRcRambro(), &_vDog[i]->getRCattackRange()))
		{
			if (!_vDog[i]->getIsUncovered()) continue;
			_vDog[i]->setIsNear(true);

			if (_vDog[i]->getX() + _vDog[i]->getImage(_vDog[i]->getStatus())->getFrameWidth() / 2 <
				_playerManager->getPlayer()->getX() + _playerManager->getPlayer()->getImage(_playerManager->getPlayer()->getState())->getFrameWidth() / 2)
			{
				_vDog[i]->setIsLeft(false);
			}
			else
			{
				_vDog[i]->setIsLeft(true);
			}
			//_playerManager
		}
		else
		{
			_vDog[i]->setIsNear(false);
		}
	}
}

void enemyManager::collideDogWithPixel()
{
	// 지형과 충돌(픽셀충돌)
	RECT rc;
	for (int i = 0; i < _vDog.size(); ++i)
	{
		float x, y;
		x = _vDog[i]->getX();
		y = _vDog[i]->getY();

		// 바닥과 충돌
		if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getRC(), x, y, _vDog[i]->getSpeed(), _vDog[i]->getGravity(), ENEMY_BOTTOM))
		{
			_vDog[i]->setIsOn(true);
		}
		else
		{
			_vDog[i]->setIsOn(false);
		}

		// 윗 천장과 충돌
		if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getRC(), x, y, _vDog[i]->getSpeed(), _vDog[i]->getGravity(), ENEMY_TOP))
		{
			_vDog[i]->setAngle(2 * PI - _vDog[i]->getAngle());

		}
		else
		{
			_vDog[i]->setY(y);
		}

		// 적 왼쪽 벽과 충돌
		if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getRC(), x, y, _vDog[i]->getSpeed(), _vDog[i]->getGravity(), ENEMY_LEFT))
		{
			_vDog[i]->setAngle(PI - _vDog[i]->getAngle());
			if (_vDog[i]->getIsAlive())
			{
				_vDog[i]->setIsLeft(0);
			}
		}
		else
		{
			_vDog[i]->setX(x);
		}

		// 적 오른쪽 벽과 충돌
		if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getRC(), x, y, _vDog[i]->getSpeed(), _vDog[i]->getGravity(), ENEMY_RIGHT))
		{
			_vDog[i]->setAngle(PI - _vDog[i]->getAngle());
			if (_vDog[i]->getIsAlive())
			{
				_vDog[i]->setIsLeft(1);
			}
		}
		else
		{
			_vDog[i]->setX(x);
		}
	}
}

// 도그가 플레이어 총알에 맞음
void enemyManager::collideDogWithPBullet()
{
	RECT rc;
	for (int i = 0; i < _playerManager->getPBullet()->getVPlayerBullet().size(); ++i)
	{
		for (int j = 0; j < _vDog.size(); ++j)
		{
			if (IntersectRect(&rc, &_playerManager->getPBullet()->getVPlayerBullet()[i].rc, &_vDog[j]->getRC()))
			{
				if (_vDog[j]->getIsApart()) continue;

				if (_vDog[j]->getIsLeft() != _playerManager->getPBullet()->getVPlayerBullet()[i].isLeft)
				{
					_vDog[j]->setIsLeft(_playerManager->getPBullet()->getVPlayerBullet()[i].isLeft);
				}

				DogDieWithBullet(j);
			}
		}		
	}
}

// 할아버지 총알이랑 도그랑 충돌
void enemyManager::collideDogWithGBullet()
{
	RECT rc;
	for (int i = 0; i < _playerManager->getGBullet()->getVPlayergBullet().size(); ++i)
	{
		for (int j = 0; j < _vDog.size(); ++j)
		{
			if (IntersectRect(&rc, &_playerManager->getGBullet()->getVPlayergBullet()[i].rc, &_vDog[j]->getRC()))
			{
				if (_vDog[j]->getIsApart()) continue;

				if (_vDog[j]->getIsLeft() != _playerManager->getPBullet()->getVPlayerBullet()[i].isLeft)
				{
					_vDog[j]->setIsLeft(_playerManager->getPBullet()->getVPlayerBullet()[i].isLeft);
				}

				DogDieWithBullet(j);
			}
		}
	}
}

void enemyManager::DogDieWithBullet(int i)
{
	_vDog[i]->setHP(_vDog[i]->getHP() - 1);

	if (_vDog[i]->getStatus() != D_KNOCK_BACK && _vDog[i]->getStatus() != D_DEAD )
	{
		if (_vDog[i]->getIsLeft())
			_vDog[i]->setIndex(_vDog[i]->getImage(D_KNOCK_BACK)->getMaxFrameX() - 1);
		else
			_vDog[i]->setIndex(0);

		_vDog[i]->setStatus(D_KNOCK_BACK);
	}

	if (_brovil->getBrovilStatus() == D_DEAD)
	{
		_vDog[i]->deadMove();
	}
		
	if (_vDog[i]->getHP() == 10)
	{
		this->saveEnemy(DOG, BULLET, _vDog[i]->getIsLeft());
	}
	
}

void enemyManager::collideDogCorpseWithPixel()
{
	// 시체 토막 충돌
	RECT rc;
	for (int i = 0; i < _vDog.size(); ++i)
	{
		for (int j = 0; j < BODY_PART; ++j)
		{
			if (!_vDog[i]->getIsApart()) continue;

			float x, y;
			x = _vDog[i]->getCorpse()[j].x;
			y = _vDog[i]->getCorpse()[j].y;

			// 바닥
			if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getCorpse()[j].rcCorpse, x, y, _vDog[i]->getCorpse()[j].speed, _vDog[i]->getCorpse()[j].gravity, ENEMY_BOTTOM))
			{
				_vDog[i]->getCorpse()[j].angle = 2 * PI - _vDog[i]->getCorpse()[j].angle;
				_vDog[i]->getCorpse()[j].gravity = 0.f;
			}

			// 천장
			if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getCorpse()[j].rcCorpse, x, y, _vDog[i]->getCorpse()[j].speed, _vDog[i]->getCorpse()[j].gravity, ENEMY_TOP))
			{
				_vDog[i]->getCorpse()[j].angle = 2 * PI - _vDog[i]->getCorpse()[j].angle;
			}

			// 왼쪽
			if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getCorpse()[j].rcCorpse, x, y, _vDog[i]->getCorpse()[j].speed, _vDog[i]->getCorpse()[j].gravity, ENEMY_LEFT))
			{
				_vDog[i]->getCorpse()[j].angle = PI - _vDog[i]->getCorpse()[j].angle;
			}

			// 오른쪽
			if (COLLISIONMANAGER->pixelCollision(_vDog[i]->getCorpse()[j].rcCorpse, x, y, _vDog[i]->getCorpse()[j].speed, _vDog[i]->getCorpse()[j].gravity, ENEMY_RIGHT))
			{
				_vDog[i]->getCorpse()[j].angle = PI - _vDog[i]->getCorpse()[j].angle;
			}

			_vDog[i]->getCorpse()[j].x = x;
			_vDog[i]->getCorpse()[j].y = y;

		}
	}
	
}

// 스테이지 클리어냐?
bool enemyManager::isClear()
{
	if (_isClear)
	{
		return true;
	}
	else
		return false;
}

