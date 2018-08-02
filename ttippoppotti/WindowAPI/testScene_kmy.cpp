#include "stdafx.h"
#include "testScene_kmy.h"

HRESULT testScene_kmy::init(void)
{
	

	EFFECTMANAGER->init();
	return S_OK;
}

void testScene_kmy::release(void)
{
}

void testScene_kmy::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		//낙석주의
		EFFECTMANAGER->rockFall(1000, 1800, 0.0f);
		
		//호러주의
		EFFECTMANAGER->bloodSplash(1100, 1800, 0.0f);
		
		//나무파편주의
		EFFECTMANAGER->woodDebris(900, 1800, 0.0f);

			//펑
		EFFECTMANAGER->explosionStart(500, 2000);


	}
		
}

void testScene_kmy::render(void)
{
}