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
		EFFECTMANAGER->rockFall(1000, 1800, 0.0f);
		
		//ȣ������
		EFFECTMANAGER->bloodSplash(1100, 1800, 0.0f);
		
		//������������
		EFFECTMANAGER->woodDebris(900, 1800, 0.0f);

		//��
		EFFECTMANAGER->explosionStart(500, 2000);
	}
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		//�ĸ�����
		EFFECTMANAGER->flyingFlies(900, 2000);
	}
}

void testScene_kmy::render(void)
{
}
