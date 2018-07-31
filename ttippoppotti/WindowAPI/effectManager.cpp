#include "stdafx.h"
#include "effectManager.h"
#include "effects.h"


HRESULT effectManager::init(void)
{
	addEffect("bloodSplash1", "blood_still1", 10, 10);
	addEffect("bloodSplash2", "blood_still2", 10, 10);
	addEffect("bloodSplash3", "blood_still3", 10, 10);
	addEffect("bloodSplash4", "blood_still4", 10, 10);
	addEffect("bloodSplash5", "blood_still5", 10, 10);
	addEffect("bloodSplash6", "blood_still6", 10, 10);
	addEffect("bloodSplash7", "blood_still7", 10, 10);
	addEffect("bloodSplash8", "blood_still8", 10, 10);

	addEffect("rock2", "rock_big2", 10, 10);
	addEffect("rock1", "rock_big1", 10, 10);
	addEffect("rock3", "rock_sml1", 10, 10);
	addEffect("rock4", "rock_sml2", 10, 10);
	addEffect("rock5", "rock_sml3", 10, 10);

	addEffect("rambro_cartridge", "rambro_cartridge", 1, 10, true);

	return S_OK;
}

void effectManager::release(void)
{
	miEffect iter = _mEffect.begin();
	for (iter; iter != _mEffect.end(); ++iter)
	{
		viEffect vIter = iter->second.begin();
		for (int i = 0; i < iter->second.size(); i++)
		{
			iter->second[i]->release();
			SAFE_DELETE(iter->second[i]);
		}
	}
	_mEffect.clear();
}

void effectManager::update(void)
{
	miEffect mIter;
	mIter = _mEffect.begin();
	for (mIter; mIter != _mEffect.end(); ++mIter)
	{
		for (int i = 0; i < mIter->second.size(); i++)
		{
			mIter->second[i]->update();
		}
	}
}

void effectManager::render(void)
{
	miEffect mIter;
	mIter = _mEffect.begin();
	for (mIter; mIter != _mEffect.end(); ++mIter)
	{
		for (int i = 0; i < mIter->second.size(); i++)
		{
			mIter->second[i]->render();
		}
	}
}

void effectManager::bloodSplash()
{
	playParabola("bloodSplash1", WINSIZEX / 3 - 10, WINSIZEY / 2 - 10, 0.0f);
	playParabola("bloodSplash2", WINSIZEX / 3 - 20, WINSIZEY / 2 - 20, 0.0f);
	playParabola("bloodSplash3", WINSIZEX / 3 - 30, WINSIZEY / 2 - 30, 0.0f);
	playParabola("bloodSplash4", WINSIZEX / 3 - 40, WINSIZEY / 2 - 40, 0.0f);
	playParabola("bloodSplash5", WINSIZEX / 3 - 50, WINSIZEY / 2 - 50, 0.0f);
	playParabola("bloodSplash6", WINSIZEX / 3 - 60, WINSIZEY / 2 - 60, 0.0f);
	playParabola("bloodSplash7", WINSIZEX / 3 - 70, WINSIZEY / 2 - 70, 0.0f);
	playParabola("bloodSplash8", WINSIZEX / 3 - 80, WINSIZEY / 2 - 80, 0.0f);
}

void effectManager::cartridge(float x, float y, bool isLeft)
{
	//EFFECTMANAGER->playCartridge("rambro_cartridge", x - CAMERAMANAGER->getCamera().left, y - CAMERAMANAGER->getCamera().top, isLeft);
	EFFECTMANAGER->playCartridge("rambro_cartridge", x, y, isLeft);
}

void effectManager::rockFall()
{
	EFFECTMANAGER->playParabola("rock1", WINSIZEX / 2, WINSIZEY / 2, 0.0f);
	EFFECTMANAGER->playParabola("rock2", WINSIZEX / 2 - 10, WINSIZEY / 2, 0.0f);
	EFFECTMANAGER->playParabola("rock3", WINSIZEX / 2 - 20, WINSIZEY / 2, 0.0f);
	EFFECTMANAGER->playParabola("rock4", WINSIZEX / 2 - 30, WINSIZEY / 2, 0.0f);
	EFFECTMANAGER->playParabola("rock5", WINSIZEX / 2 - 40, WINSIZEY / 2, 0.0f);
}

void effectManager::addEffect(string effectName, const char * imageName, int count, int buffer, bool isFrameImg)
{
	vEffect vEffectBuffer;

	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effects);
		vEffectBuffer[i]->init(imageName, count, isFrameImg);
	}

	//이펙트버퍼 백터를 맵에 담기
	_mEffect.insert(make_pair(effectName, vEffectBuffer));
}

void effectManager::playParabola(string effectName, int x, int y, float angle)
{
	miEffect mIter;

	for (mIter = _mEffect.begin(); mIter != _mEffect.end(); ++mIter)
	{
		if (!(mIter->first == effectName)) continue;

		//이펙트키와 일치하면 이펙트 실행
		for (int i = 0; i < mIter->second.size(); i++)
		{
			if (mIter->second[i]->getIsRunning()) continue;
			mIter->second[i]->activateParabola(x, y, angle);
			return;
		}
	}
}

void effectManager::playCartridge(string effectName, int x, int y, bool isLeft)
{
	miEffect mIter;

	for (mIter = _mEffect.begin(); mIter != _mEffect.end(); ++mIter)
	{
		if (!(mIter->first == effectName)) continue;

		//이펙트키와 일치하면 이펙트 실행
		for (int i = 0; i < mIter->second.size(); i++)
		{
			if (mIter->second[i]->getIsRunning()) continue;
			mIter->second[i]->activateCartridge(x, y, isLeft);
			return;
		}
	}
}
