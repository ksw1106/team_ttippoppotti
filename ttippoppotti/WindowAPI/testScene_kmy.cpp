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
		//��������
		EFFECTMANAGER->rockFall();
		
		//ȣ������
		EFFECTMANAGER->bloodSplash();
		
		//ź��
//		EFFECTMANAGER->cartridge(true);
	}
	
}

void testScene_kmy::render(void)
{
}