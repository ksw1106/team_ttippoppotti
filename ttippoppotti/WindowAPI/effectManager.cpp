#include "stdafx.h"
#include "effectManager.h"
#include "effects.h"


HRESULT effectManager::init(void)
{
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
