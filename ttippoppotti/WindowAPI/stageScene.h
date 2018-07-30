#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "mapData.h"
#include "testScene_kmy.h"

struct object
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
	
	RECT _rcCamera;
	object _backGround[7];
	image* _helicopter;
	image* _saveFlag;
	image* _humanDead;
	image* _flag;
	float _flagX, _flagY;
	float _x, _y;

	int _flagCount;
	int _flagIndex;
	int _flagSpeed;

	int _fcount;
	int _findex;
	int _fspeed;
	int _hcount;
	int _hindex;
	int _hspeed;
	int _count;
	int _index;
	int _speed;
	bool _isLeft;
	bool _isDown;

	const char* soundName[4];
	int soundCount;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	stageScene() {}
	~stageScene() {}
};

