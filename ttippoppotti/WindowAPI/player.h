#pragma once
#include "gameNode.h"
#include "bullet.h"  //�̻���Ŭ���� ����ϱ� ����


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

