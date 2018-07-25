#include "stdafx.h"
#include "testScene_kmy.h"

HRESULT testScene_kmy::init(void)
{
	for (int i = 0; i < 5; i++)
	{
		_fragments[i] = new fragments;
		_isExplosion[i] = false;
	}

	_fragments[0]->init("rock_big1", 10);
	_fragments[1]->init("rock_big2", 10);
	_fragments[2]->init("rock_sml1", 10);
	_fragments[3]->init("rock_sml2", 10);
	_fragments[4]->init("rock_sml3", 10);

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
		for (int i = 0; i < 5; i++)
			_fragments[i]->activate(WINSIZEX / 2, WINSIZEY / 2, PI);
	}
	for (int i = 0; i < 5; i++)
		_fragments[i]->update();
}

void testScene_kmy::render(void)
{
	for (int i = 0; i < 5; i++)
		_fragments[i]->render();
}