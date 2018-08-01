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
		//³«¼®ÁÖÀÇ
		EFFECTMANAGER->rockFall(1000, 1800, 0.0f);
		
		//È£·¯ÁÖÀÇ
		EFFECTMANAGER->bloodSplash(1100, 1800, 0.0f);
	}
		//Æã
		//EFFECTMANAGER->explosion(500, 2000);
}

void testScene_kmy::render(void)
{
}