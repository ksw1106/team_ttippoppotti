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
		//³«¼®ÁÖÀÇ
		EFFECTMANAGER->rockFall(1000, 1800, 0.0f);
		
		//È£·¯ÁÖÀÇ
		EFFECTMANAGER->bloodSplash(1100, 1800, 0.0f);
		
		//³ª¹«ÆÄÆíÁÖÀÇ
		EFFECTMANAGER->woodDebris(900, 1800, 0.0f);

		//Æã
		EFFECTMANAGER->explosionStart(500, 2000);
	}
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		//¶ÑµÎ¶ÑµÎ
		EFFECTMANAGER->bulletPuff(800, 2000);

		//Ä®
		EFFECTMANAGER->knifePuff(900, 2000, false);
	}
}

void testScene_kmy::render(void)
{
}
