#include "stdafx.h"
#include "testScene_kmy.h"

HRESULT testScene_kmy::init(void)
{
	EFFECTMANAGER->addEffect("rock1", "rock_big1", 10, 10);
	EFFECTMANAGER->addEffect("rock2", "rock_big2", 10, 10);
	EFFECTMANAGER->addEffect("rock3", "rock_sml1", 10, 10);
	EFFECTMANAGER->addEffect("rock4", "rock_sml2", 10, 10);
	EFFECTMANAGER->addEffect("rock5", "rock_sml3", 10, 10);
	EFFECTMANAGER->addEffect("bloodSplash1", "blood_still1", 10, 10);
	EFFECTMANAGER->addEffect("bloodSplash2", "blood_still2", 10, 10);
	EFFECTMANAGER->addEffect("bloodSplash3", "blood_still3", 10, 10);
	EFFECTMANAGER->addEffect("bloodSplash4", "blood_still4", 10, 10);
	EFFECTMANAGER->addEffect("bloodSplash5", "blood_still5", 10, 10);
	EFFECTMANAGER->addEffect("bloodSplash6", "blood_still6", 10, 10);
	EFFECTMANAGER->addEffect("bloodSplash7", "blood_still7", 10, 10);
	EFFECTMANAGER->addEffect("bloodSplash8", "blood_still8", 10, 10);
	EFFECTMANAGER->addEffect("rambro_cartridge", "rambro_cartridge", 1, 10, true);

	return S_OK;
}

void testScene_kmy::release(void)
{
}

void testScene_kmy::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		//³«¼®ÁÖÀÇ
		EFFECTMANAGER->playParabola("rock1", WINSIZEX / 2, WINSIZEY / 2, 0.0f);
		EFFECTMANAGER->playParabola("rock2", WINSIZEX / 2-10, WINSIZEY / 2, 0.0f);
		EFFECTMANAGER->playParabola("rock3", WINSIZEX / 2-20, WINSIZEY / 2, 0.0f);
		EFFECTMANAGER->playParabola("rock4", WINSIZEX / 2-30, WINSIZEY / 2, 0.0f);
		EFFECTMANAGER->playParabola("rock5", WINSIZEX / 2 - 40, WINSIZEY / 2, 0.0f);
		
		//È£·¯ÁÖÀÇ
		EFFECTMANAGER->playParabola("bloodSplash1", WINSIZEX / 3 - 10, WINSIZEY / 2 - 10, 0.0f);
		EFFECTMANAGER->playParabola("bloodSplash2", WINSIZEX / 3 - 20, WINSIZEY / 2 - 20, 0.0f);
		EFFECTMANAGER->playParabola("bloodSplash3", WINSIZEX / 3 - 30, WINSIZEY / 2 - 30, 0.0f);
		EFFECTMANAGER->playParabola("bloodSplash4", WINSIZEX / 3 - 40, WINSIZEY / 2 - 40, 0.0f);
		EFFECTMANAGER->playParabola("bloodSplash5", WINSIZEX / 3 - 50, WINSIZEY / 2 - 50, 0.0f);
		EFFECTMANAGER->playParabola("bloodSplash6", WINSIZEX / 3 - 60, WINSIZEY / 2 - 60, 0.0f);
		EFFECTMANAGER->playParabola("bloodSplash7", WINSIZEX / 3 - 70, WINSIZEY / 2 - 70, 0.0f);
		EFFECTMANAGER->playParabola("bloodSplash8", WINSIZEX / 3 - 80, WINSIZEY / 2 - 80, 0.0f);
		
		//ÅºÇÇ
		EFFECTMANAGER->playParabola("rambro_cartridge", WINSIZEX / 4, WINSIZEY / 2, PI/3);
	}
	
}

void testScene_kmy::render(void)
{
}