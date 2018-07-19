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
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame() {}
	~mainGame() {}
};

