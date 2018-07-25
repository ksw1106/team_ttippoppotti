#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "soldier.h"

class playerManager;
class mapData;

class enemyManager : public gameNode
{
private:
	playerManager* _playerManager;
	mapData* _mapData;
	vector<enemy*> _vSoldier;
	eBullet* _eBullet;

public:
	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	void setMapData(mapData* mapData) { _mapData = mapData; }

	// 에너미클래스 벡터 가져오기
	vector<enemy*> getVEnemy() { return _vSoldier; }
	// 적 총알클래스 총알벡터 가져오기
	eBullet* getVEBullet() { return _eBullet; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
		
	void collision();
	void setEnemy(int x, int y);
	
	enemyManager() {}
	~enemyManager() {}
};

