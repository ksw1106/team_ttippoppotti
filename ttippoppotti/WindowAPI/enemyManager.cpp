#include "stdafx.h"
#include "enemyManager.h"
#include "playerManager.h"
#include "mapData.h"
HRESULT enemyManager::init(void)
{
	_enemy = new enemy;
	_enemy->init(481, 2071, 100);

	return S_OK;
}

void enemyManager::release(void)
{
	_enemy->release();
}

void enemyManager::update(void)
{
	_enemy->update();

	
}

void enemyManager::render(void)
{
	_enemy->render();
}