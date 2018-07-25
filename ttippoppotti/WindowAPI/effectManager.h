#pragma once
#include "singletonBase.h"
//이펙트 클래스 전방선언(뻥남 방지용)
class effects;

class effectManager : public singletonBase <effectManager>
{
private:
	

private:
	

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	effectManager() {}
	~effectManager() {}
};
