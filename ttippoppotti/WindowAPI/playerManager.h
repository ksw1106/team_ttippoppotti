#pragma once
#include "gameNode.h"
#include "player.h"

class playerManager : public gameNode
{
	player _player;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	playerManager();
	~playerManager();
};

