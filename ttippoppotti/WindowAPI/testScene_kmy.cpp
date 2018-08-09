#include "stdafx.h"
#include "testScene_kmy.h"
//#include "playerManager.h"

HRESULT testScene_kmy::init(void)
{
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
		EFFECTMANAGER->rockFall(1000, 1800, true);
		
		//호러주의
		EFFECTMANAGER->bloodSplash(1100, 1800, true);
		
		//나무파편주의
		EFFECTMANAGER->woodDebris(900, 1800, true);

		//펑
		EFFECTMANAGER->explosionStart(500, 2000);
	}
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		//파리날림
		//EFFECTMANAGER->flyingFlies(900, 2000);

		EFFECTMANAGER->yellowSparks(800, 2000, FALSE);

		EFFECTMANAGER->ashes(700, 2000);

		EFFECTMANAGER->bigBang(900, 1800);
	}
}

void testScene_kmy::render(void)
{
}
