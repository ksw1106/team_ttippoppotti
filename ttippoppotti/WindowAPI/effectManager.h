#pragma once
#include "singletonBase.h"
//����Ʈ Ŭ���� ���漱��(���� ������)
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
