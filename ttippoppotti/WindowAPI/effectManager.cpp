#include "stdafx.h"
#include "effectManager.h"

HRESULT effectManager::init()
{
	IMAGEMANAGER->addImage("rock_big1", "effectImage/rock_fragment_big_01.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rock_big2", "effectImage/rock_fragment_big_02.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rock_sml1", "effectImage/rock_fragment_sml_01.bmp", 8, 8);
	IMAGEMANAGER->addImage("rock_sml2", "effectImage/rock_fragment_sml_02.bmp", 9, 9);
	IMAGEMANAGER->addImage("rock_sml3", "effectImage/rock_fragment_sml_03.bmp", 9, 9);
	
	_isExplosion = false;

	//º® ÆøÆÄ
	for (int i = 0; i < 5; i++)
		_fragments[i] = new fragments;

	_fragments[0]->init("rock_big1", 10);
	_fragments[1]->init("rock_big2", 10);
	_fragments[2]->init("rock_sml1", 10);
	_fragments[3]->init("rock_sml2", 10);
	_fragments[4]->init("rock_sml3", 10);

	return S_OK;
}

void effectManager::release()
{
	for (int i = 0; i < 5; i++)
	{
		_fragments[i]->release();
		SAFE_DELETE(_fragments[i]);
	}
}

void effectManager::update(void)
{
	for (int i = 0; i < 5; i++)
		_fragments[i]->update();
}

void effectManager::render(HDC hdc)
{
	for (int i = 0; i < 5; i++)
		_fragments[i]->render(hdc);
}

void effectManager::rockExplosion(float x, float y, float angle)
{
	if (!_isExplosion)
	{
		for (int i = 0; i < 5; i++)
			_fragments[i]->activate(x, y, angle, 7.0, 0.0f);
	}
}
