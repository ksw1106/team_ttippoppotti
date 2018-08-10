#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "mapData.h"
#include "testScene_kmy.h"
#include "stageClear.h"

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

	RECT _rcCamera;
	world _backGround[7];

	bool _camDebug;

	const char* soundName[4];
	int soundCount;

	bool _isClear;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	stageScene() {}
	~stageScene() {}
};