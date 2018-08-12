#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "mapData.h"
#include "testScene_kmy.h"
#include "stageClear.h"
#include "stageStart.h"
#include "missionFailed.h"

struct world
{
	image* _image;
	float _x, _y;
	RECT _rc;
	bool _isActived;
};

class stageScene : public gameNode
{
private:
	playerManager * _playerManager;
	enemyManager* _enemyManager;
	mapData* _mapData;
	testScene_kmy* _test;
	stageClear* _stageClear;
	stageStart* _stageStart;
	missionFailed* _missionFailed;

	RECT _rcCamera;
	world _backGround[3];

	bool _camDebug;

	bool _isClear;
	bool _isOver;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	stageScene() {}
	~stageScene() {}
};