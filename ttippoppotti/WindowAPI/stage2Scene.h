#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "mapData.h"

class stage2Scene : public gameNode
{
	playerManager * _playerManager;
	enemyManager* _enemyManager;
	mapData* _mapData;

	RECT _rcCamera;
	bool _camDebug;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	stage2Scene() {}
	~stage2Scene() {}
};