#pragma once
#include "gameNode.h"
#include "bullet.h"  //미사일클래스 사용하기 위해


class player : public gameNode
{
private:

	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	player() {}
	~player() {}
};

