#include "stdafx.h"
#include "testScene_kmy.h"

HRESULT testScene_kmy::init(void)
{
	EFFECTMANAGER->addEffect("rock1", "rock_big1", 10, 10, false);
	EFFECTMANAGER->addEffect("rock2", "rock_big2", 10, 10, false);
	EFFECTMANAGER->addEffect("rock3", "rock_sml1", 10, 10, false);
	EFFECTMANAGER->addEffect("rock4", "rock_sml2", 10, 10, false);
	EFFECTMANAGER->addEffect("rock5", "rock_sml3", 10, 10, false);
	EFFECTMANAGER->addEffect("bloodSplash1", "bloodTrailPuff1", 10, 10, true);
	EFFECTMANAGER->addEffect("bloodSplash2", "bloodTrailPuff2", 10, 10, true);
	EFFECTMANAGER->addEffect("bloodSplash3", "bloodTrailPuff3", 10, 10, true);
	EFFECTMANAGER->addEffect("bloodSplash4", "blood_still", 100, 10, false);

	return S_OK;
}

void testScene_kmy::release(void)
{
}

void testScene_kmy::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		EFFECTMANAGER->play("rock1", WINSIZEX / 2, WINSIZEY / 2, 0.0f);
		EFFECTMANAGER->play("rock2", WINSIZEX / 2-10, WINSIZEY / 2, 0.0f);
		EFFECTMANAGER->play("rock3", WINSIZEX / 2-20, WINSIZEY / 2, 0.0f);
		EFFECTMANAGER->play("rock4", WINSIZEX / 2-30, WINSIZEY / 2, 0.0f);
		EFFECTMANAGER->play("rock5", WINSIZEX / 2 - 40, WINSIZEY / 2, 0.0f);
		EFFECTMANAGER->play("bloodSplash1", WINSIZEX / 3 - 10, WINSIZEY / 2 - 10, 0.0f);
		EFFECTMANAGER->play("bloodSplash2", WINSIZEX / 3 - 20, WINSIZEY / 2 - 10, 0.0f);
		EFFECTMANAGER->play("bloodSplash3", WINSIZEX / 3 - 30, WINSIZEY / 2 - 10, 0.0f);
		EFFECTMANAGER->play("bloodSplash4", WINSIZEX / 3 - 40, WINSIZEY / 2 - 10, 0.0f);
	}
	
}

void testScene_kmy::render(void)
{
}