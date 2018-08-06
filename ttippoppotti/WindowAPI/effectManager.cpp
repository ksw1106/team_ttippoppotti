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

	addEffect("rock1", "rock_big1", 10, 10);
	addEffect("rock2", "rock_big2", 10, 10);
	addEffect("rock3", "rock_sml1", 10, 10);
	addEffect("rock4", "rock_sml2", 10, 10);
	addEffect("rock5", "rock_sml3", 10, 10);

	addEffect("flame1", "explosionFlame1", 20, 5);
	addEffect("flame2", "explosionFlame2", 20, 5);
	addEffect("flame3", "explosionFlame3", 20, 5);
	addEffect("flame4", "explosionFlame4", 20, 5);
	addEffect("flame5", "explosionFlame5", 20, 5);
	addEffect("flame6", "explosionFlame6", 20, 5);
	addEffect("flame7", "explosionFlame7", 20, 5);
	addEffect("flame8", "explosionFlame8", 20, 5);

	addEffect("ballFlame1", "explosionBallFlame", 10, 1, true);
	addEffect("ballFlame2", "explosionBallFlame_large", 10, 1, true);
	addEffect("ballFlame3", "explosionBallFlame_larger", 10, 1, true);
	addEffect("ballFlame4", "explosionBallFlame_small", 10, 1, true);

	addEffect("woodDebris1", "woodDebris1", 10, 5, true);
	addEffect("woodDebris2", "woodDebris2", 10, 5, true);

	addEffect("rambro_cartridge", "rambro_cartridge", 10, 1, true);

	_count = 0;
	_isExplosion = false;

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
	if (_isExplosion)
	{
		explosion(_x, _y);
		_count++;
	}

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
	/*
	for (mIter; mIter != _mEffect.end(); ++mIter)
	{
		//for (int i = mIter->second.size() - 1; i >= 0 ; i--)
		for (int i = 0; i < mIter->second.size(); i++)
		{
			mIter->second[i]->render();
		}
	}
	*/
	
	vector<vector<effects*>> temp;
	for (mIter; mIter != _mEffect.end(); ++mIter)
	{
		temp.push_back(mIter->second);
	}
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		for (int j = temp[i].size() - 1; j >= 0; --j)
		{
			temp[i][j]->render();
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

void effectManager::woodDebris(float x, float y, float angle)
{
	this->playParabola("woodDebris1", x, y, angle);
	this->playParabola("woodDebris2", x, y, angle);
}

void effectManager::explosion(float x, float y)
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

	if (_count > 40)
	{
		_isExplosion = false;
		_count = 0;
	}

	//this->playBallExplosion("ballFlame1", x, y);
	this->playBallExplosion("ballFlame2", x, y);
	//this->playBallExplosion("ballFlame3", x, y);


}

void effectManager::explosionStart(float x, float y)
{
	_isExplosion = true;
	_x = x;
	_y = y;
}

void effectManager::addEffect(string effectName, const char * imageName, int buffer, int count, bool isFrameImg)
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
