#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "pixelCollision.h"

class mainGame : public gameNode
{
private:
	playerManager* _playerManager;
	enemyManager* _enemyManager;

	RECT _rcCamera;
	image* _backGround;
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
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame() {}
	~mainGame() {}
};

