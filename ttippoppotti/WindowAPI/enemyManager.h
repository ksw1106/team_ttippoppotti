#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "soldier.h"
#include "brovil.h"
#include "dog.h"
#include "boss.h"

class playerManager;
class mapData;

class enemyManager : public gameNode
{
private:
	playerManager* _playerManager;
	mapData* _mapData;
	
	vector<enemy*> _vSoldier;	// 일반 적	
		
	eBullet* _eBullet;			// 총알 클래스
	bossBullet* _bossBullet;
	bossRocket* _bossRocket;
	boss* _boss;				// 보스 클래스

public:
	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	void setMapData(mapData* mapData) { _mapData = mapData; }
	
	// 에너미클래스 벡터 가져오기
	vector<enemy*> getVEnemy() { return _vSoldier; }
	
	// 적 총알클래스 가져오기
	eBullet* getEBullet() { return _eBullet; }

	// 보스 클래스 가져오기
	boss* getBoss() { return _boss; }
		
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
		
	void enemyFire(int num);
	// 보스 총알,로켓 발사
	void bossFire();
	
	// 기타 충돌함수
	void collideWithPixel();
	// 시체와 픽셀 충돌
	void collideWithCorpse();
	// 에너미 시야 vs 플레이어 충돌
	void collideWithSight();
	// 에너미 총알 vs 플레이어 충돌
	void collideWithPlayer();
	// 플레이어 총알과 충돌함수
	void collideWithPBullet();	
	// 플레이어 수류탄과 충돌함수
	void collideWithPGrenade();		

	void enemyDie();
	
	// 솔져 클래스 초기화셋팅
	void setSoldier(int x, int y);
	void setBrovil(int x, int y);
		
	enemyManager() {}
	~enemyManager() {}
};

