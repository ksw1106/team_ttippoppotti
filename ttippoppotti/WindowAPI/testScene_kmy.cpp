#include "stdafx.h"
#include "testScene_kmy.h"

HRESULT testScene_kmy::init(void)
{
	for (int i = 0; i < 5; i++)
	{
		_fragments[i] = new fragments;
	}

	//_fragments[0]->init("rock_big1", 10);
	//_fragments[1]->init("rock_big2", 10);
	//_fragments[2]->init("rock_sml1", 10);
	//_fragments[3]->init("rock_sml2", 10);
	//_fragments[4]->init("rock_sml3", 10);
	EFFECTMANAGER->addEffect("rock1", "rock_big1", 1, 10);
	EFFECTMANAGER->addEffect("rock2", "rock_big2", 1, 10);
	EFFECTMANAGER->addEffect("rock3", "rock_sml1", 1, 10);
	EFFECTMANAGER->addEffect("rock4", "rock_sml2", 1, 10);
	EFFECTMANAGER->addEffect("rock5", "rock_sml3", 1, 10);

	return S_OK;
}

void testScene_kmy::release(void)
{
	for (int i = 0; i < 5; i++)
	{
		_fragments[i]->release();
		SAFE_DELETE(_fragments[i]);
	}
}

void testScene_kmy::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		//for (int i = 0; i < 5; i++)
		//	_fragments[i]->activate(WINSIZEX / 2, WINSIZEY / 2, PI);
		EFFECTMANAGER->play("rock1", WINSIZEX / 2, WINSIZEY / 2, 0.0f);
		EFFECTMANAGER->play("rock2", WINSIZEX / 2-10, WINSIZEY / 2, 0.0f);
		EFFECTMANAGER->play("rock3", WINSIZEX / 2-20, WINSIZEY / 2, 0.0f);
		EFFECTMANAGER->play("rock4", WINSIZEX / 2-30, WINSIZEY / 2, 0.0f);
		EFFECTMANAGER->play("rock5", WINSIZEX / 2-40, WINSIZEY / 2, 0.0f);
	}
	//for (int i = 0; i < 5; i++)
	//	_fragments[i]->update();
}

void testScene_kmy::render(void)
{
	//for (int i = 0; i < 5; i++)
	//	_fragments[i]->render();

}