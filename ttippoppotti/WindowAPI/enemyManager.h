#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "soldier.h"
#include "brovil.h"
#include "dog.h"
#include "boss.h"
#include "progressBar.h"

enum enemyType
{
	SOLDIER, BROVIL, DOG, TERROCOPTER,
};

enum deadType
{
	BULLET, GRENADE, PLAYER_KNIFE, 
};

struct deadEnemy
{
	enemyType _enemyType;
	deadType _deadType;
	bool isLeft;
};

class playerManager;
class mapData;

class enemyManager : public gameNode
{
private:
	playerManager* _playerManager;
	mapData* _mapData;
	enemyType _enemyType;

private:	
	vector<enemy*> _vSoldier;	// 일반 적	
	vector<dog*> _vDog;			// 도그
		
	eBullet* _eBullet;			// 총알 클래스
	bossBullet* _bossBullet;	// 보스총알 클래스
	bossRocket* _bossRocket;	// 보스로켓 클래스
	boss* _boss;				// 보스 클래스
	brovil* _brovil;			// 브로빌 클래스
	progressBar* _hpBar;		// 체력바 클래스
	
	int _effectCount;
	int _count;
	int _choice;
	int _stageNum;
	bool _isClear;				// 스테이지 클리어했냐(브로빌 죽음)
	bool _isEffect;
	
public:
	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	void setMapData(mapData* mapData) { _mapData = mapData; }
	
	// 에너미클래스 벡터 가져오기
	vector<enemy*> getVEnemy() { return _vSoldier; }	
	// 적 총알클래스 가져오기
	eBullet* getEBullet() { return _eBullet; }
	// 보스 클래스 가져오기
	boss* getBoss() { return _boss; }
	
	// 죽은 에너미 정보 벡터에 담기
	vector<deadEnemy> _vDeadEnemyInfo;
	vector<deadEnemy> getVDeadEnemyInfo() {	return _vDeadEnemyInfo;	}
	void addVDeadEnemyInfo(deadEnemy dEnemy) { _vDeadEnemyInfo.push_back(dEnemy); }
		
	HRESULT init(int stageNum);
	void release(void);
	void update(void);
	void render(void);
		
	void enemyFire(int num);	
	void bossBulletFire();
	void bossRocketFire();
	// 죽은 적 푸쉬백
	void saveEnemy(enemyType enemy, deadType deadType, bool isLeft);
	
	// 에너미 방향 바꾸기
	void changeDirection();
	
	void soldierDieWithBullet(int i);
	void soldierDieWithGrenade(int i);

	void brovilDieWithBullet();
	void brovilDieWithGrenade();

	// 에너미 시야 vs 플레이어 충돌
	void collideWithSight();
	// 에너미 vs 픽셀
	void collideWithPixel();
	// 에너미 vs 플레이어 총알
	void collideWithPBullet();	
	// 에너미 vs 플레이어 수류탄
	void collideWithPGrenade();		
	// 에너미 vs 할아버지 총알
	void collideWithGBullet();
	// 보스 vs 할아버지 총알
	void collideBossWithGBullet();
	void collideBossWithGGrenade();
	
	// 에너미 시체 vs 픽셀 충돌
	void collideWithCorpse();
	
	// 에너미 총알 vs 픽셀
	void collideBulletWithPixel();
	// 에너미 총알 vs 플레이어 충돌
	void collideWithPlayer();
	
	// 보스
	void collideWithBossBullet();
	void collideWithBossRocket();
	void bossDirChange();
	//void bossHPbar();
	// 보스 vs 플레이어 총알
	void PBulletHitBoss();
		
	// 브로빌 vs 플레이어 총알 충돌
	void collideBrovilwithPBullet();
	// 브로빌 vs 플레이어 수류탄 충돌
	void collideBrovilwithPGrenade();
	// 브로빌 vs 지형충돌
	void collideBrovilWithPixel();	
	// 브로빌 시체 vs 지형 충돌
	void collideBrovilCorpseWithPixel();

	// 도그 vs 지형픽셀충돌
	void collideDogSightWithPlayer();
	void collideDogWithPixel();
	void collideDogWithPBullet();
	void collideDogCorpseWithPixel();
	void DogDieWithBullet(int i);

	
	// 스테이지 클리어 조건
	bool isClear();
		
	// 솔져 클래스 초기화셋팅
	void setSoldier(int x, int y);
	void setBrovil(int x, int y);
	void setDog(int x, int y, bool isLeft);

	bool isEffect(int frame);
		
	enemyManager() {}
	~enemyManager() {}
};

