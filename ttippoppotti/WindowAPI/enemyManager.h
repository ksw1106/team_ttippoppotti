#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "soldier.h"
#include "brovil.h"

class playerManager;
class mapData;

class enemyManager : public gameNode
{
private:
	playerManager* _playerManager;
	mapData* _mapData;
	
	vector<enemy*> _vSoldier;	// 일반 적
		
	eBullet* _eBullet;			// 총알 클래스
		

public:
	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	void setMapData(mapData* mapData) { _mapData = mapData; }

	// 에너미클래스 벡터 가져오기
	vector<enemy*> getVEnemy() { return _vSoldier; }
	// 적 총알클래스 총알벡터 가져오기
	eBullet* getEBullet() { return _eBullet; }
	
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
		
	void collision();	// 충돌함수
	void collideWithPBullet();	// 플레이어 총알과 충돌함수
	void enemyDie(int num);

	void setSoldier(int x, int y);
	void setBrovil(int x, int y, int randomNum);
		
	enemyManager() {}
	~enemyManager() {}
};

