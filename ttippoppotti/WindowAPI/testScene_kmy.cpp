#include "stdafx.h"
#include "testScene_kmy.h"

HRESULT testScene_kmy::init(void)
{
	return S_OK;
}

void testScene_kmy::release(void)
{
}

void testScene_kmy::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		EFFECTMANAGER->rockExplosion(WINSIZEX / 2, WINSIZEY / 2, PI);
	}
}

void testScene_kmy::render(void)
{
}