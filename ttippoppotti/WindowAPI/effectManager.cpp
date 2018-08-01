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

	addEffect("flame1", "explosionFlame1", 5, 5);
	addEffect("flame2", "explosionFlame2", 5, 5);
	addEffect("flame3", "explosionFlame3", 5, 5);
	addEffect("flame4", "explosionFlame4", 5, 5);
	addEffect("flame5", "explosionFlame5", 5, 5);
	addEffect("flame6", "explosionFlame6", 5, 5);
	addEffect("flame7", "explosionFlame7", 5, 5);
	addEffect("flame8", "explosionFlame8", 5, 5);

	addEffect("ballFlame1", "explosionBallFlame", 1, 10, true);
	addEffect("ballFlame2", "explosionBallFlame_large", 1, 10, true);
	addEffect("ballFlame3", "explosionBallFlame_larger", 1, 10, true);
	addEffect("ballFlame4", "explosionBallFlame_small", 1, 10, true);

	addEffect("rambro_cartridge", "rambro_cartridge", 1, 10, true);

	_count = 0;

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

void effectManager::bloodSplash(float x, float y, float angle)
{
	this->playParabola("bloodSplash1", x, y, angle);
	this->playParabola("bloodSplash2", x, y, angle);
	this->playParabola("bloodSplash3", x, y, angle);
	this->playParabola("bloodSplash4", x, y, angle);
	this->playParabola("bloodSplash5", x, y, angle);
	this->playParabola("bloodSplash6", x, y, angle);
	this->playParabola("bloodSplash7", x, y, angle);
	this->playParabola("bloodSplash8", x, y, angle);
}

void effectManager::cartridge(float x, float y, bool isLeft)
{
	this->playCartridge("rambro_cartridge", x, y, isLeft);
}

void effectManager::rockFall(float x, float y, float angle)
{
	this->playParabola("rock1", x, y, angle);
	this->playParabola("rock2", x, y, angle);
	this->playParabola("rock3", x, y, angle);
	this->playParabola("rock4", x, y, angle);
	this->playParabola("rock5", x, y, angle);
}

void effectManager::explosion(float x, float y)
{ 
	bool _isStart;

	_count++;

	if (_count > 40)
		_isStart = false;
	else
		_isStart = true;

	if (_isStart)
	{
		if (_count > 35)
			this->playExplosion("flame8", x, y);
		else if (_count > 30)
			this->playExplosion("flame7", x, y);
		else if (_count > 25)
			this->playExplosion("flame6", x, y);
		else if (_count > 20)
			this->playExplosion("flame5", x, y);
		else if (_count > 15)
			this->playExplosion("flame4", x, y);
		else if (_count > 10)
			this->playExplosion("flame3", x, y);
		else if (_count > 5)
			this->playExplosion("flame2", x, y);
		else
			this->playExplosion("flame1", x, y);
		this->playBallExplosion("ballFlame1", x, y);
		this->playBallExplosion("ballFlame2", x, y);
		this->playBallExplosion("ballFlame3", x, y);
	}
	else
		_count = 0;

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

void effectManager::playParabola(string effectName, float x, float y, float angle)
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

void effectManager::playExplosion(string effectName, float x, float y)
{
	miEffect mIter;

	for (mIter = _mEffect.begin(); mIter != _mEffect.end(); ++mIter)
	{
		if (!(mIter->first == effectName)) continue;

		//이펙트키와 일치하면 이펙트 실행
		for (int i = 0; i < mIter->second.size(); i++)
		{
			if (mIter->second[i]->getIsRunning()) continue;
			mIter->second[i]->activateExplosion(x, y);
			return;
		}
	}
}

void effectManager::playBallExplosion(string effectName, float x, float y)
{
	miEffect mIter;

	for (mIter = _mEffect.begin(); mIter != _mEffect.end(); ++mIter)
	{
		if (!(mIter->first == effectName)) continue;

		//이펙트키와 일치하면 이펙트 실행
		for (int i = 0; i < mIter->second.size(); i++)
		{
			if (mIter->second[i]->getIsRunning()) continue;
			mIter->second[i]->activateBallExplosion(x, y);
			return;
		}
	}
}

void effectManager::playCartridge(string effectName, float x, float y, bool isLeft)
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
