#include "stdafx.h"
#include "testScene_kmy.h"
//#include "playerManager.h"

HRESULT testScene_kmy::init(void)
{
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
		EFFECTMANAGER->rockFall(1000, 1800, true);
		
		//ȣ������
		EFFECTMANAGER->bloodSplash(1100, 1800, true);
		
		//������������
		EFFECTMANAGER->woodDebris(900, 1800, true);

		//��
		EFFECTMANAGER->explosion(500, 2000);
	}
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		//�ĸ�����
		//EFFECTMANAGER->flyingFlies(900, 2000);

		EFFECTMANAGER->yellowSparks(800, 2000, false);

		EFFECTMANAGER->ashes(700, 2000);

		EFFECTMANAGER->bigBang(900, 1900);

		EFFECTMANAGER->grenadePuff(800, 1800);
	}
	if (KEYMANAGER->isOnceKeyDown('U'))
	{
		EFFECTMANAGER->RambroBloodFountain(1000, 2100);

		EFFECTMANAGER->rambroGrenadeExplosion(800, 1800);
	}
	if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		float x = 900, y = 2000;
		x++;
		y++;x++;
		y++;x++;
		y++;x++;
		y++;x++;
		y++;x++;
		y++;x++;
		y++;
	//	EFFECTMANAGER->missileTrail(900, 2200, false);
		EFFECTMANAGER->missilePuff(x, y, false);
	}
}

void testScene_kmy::render(void)
{
}
