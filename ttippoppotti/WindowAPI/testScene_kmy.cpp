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
		EFFECTMANAGER->rockFall();
		
		//È£·¯ÁÖÀÇ
		EFFECTMANAGER->bloodSplash();
		
		//ÅºÇÇ
//		EFFECTMANAGER->cartridge(true);
	}
	
}

void testScene_kmy::render(void)
{
}