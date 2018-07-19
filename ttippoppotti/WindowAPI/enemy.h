#pragma once
#include "gameNode.h"

//부모클래스 => 이놈을 상속받아서 보스, 일반몬스터등을 만든다
class enemy : public gameNode
{
private:

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	enemy() {}
	virtual ~enemy() {}
};

