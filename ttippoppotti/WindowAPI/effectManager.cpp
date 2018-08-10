#include "stdafx.h"
#include "effectManager.h"
#include "effects.h"


HRESULT effectManager::init(void)
{
	addEffect("bloodSplash1", "blood_still1", 20, 5);
	addEffect("bloodSplash2", "blood_still2", 20, 5);
	addEffect("bloodSplash3", "blood_still3", 20, 5);
	addEffect("bloodSplash4", "blood_still4", 20, 5);
	addEffect("bloodSplash5", "blood_still5", 20, 5);
	addEffect("bloodSplash6", "blood_still6", 20, 5);
	addEffect("bloodSplash7", "blood_still7", 20, 5);
	addEffect("bloodSplash8", "blood_still8", 20, 5);

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

	addEffect("woodDebris1b", "woodDebris1b", 10, 2, true);
	addEffect("woodDebris2b", "woodDebris2b", 10, 2, true);

	addEffect("rambro_cartridge", "rambro_cartridge", 50, 1, true);

	addEffect("bulletPuff", "yellowPuff", 20, 1, true);
	addEffect("knifePuff", "whitePuff", 1, 1, true);
	addEffect("grenadePuff", "redPuff", 1, 1, true);

	addEffect("saveBubble", "saveBubble2", 5, 1, true);

	addEffect("flies", "blackPixelDot", 10, 5);
	addEffect("ashes", "blackPixelDot", 10, 180);
	addEffect("orangeSparks", "orangePixelDot", 20, 20);
	addEffect("lightOrangeSparks", "lightOrangePixelDot", 20, 20);
	addEffect("yellowSparks", "yellowPixelDot", 20, 20);

	addEffect("bigBang", "explosionFlame8", 10, 10);

	_count = 0;
	_isExplosion = _isGrenadePuff = _isBigBang = false;

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
		explosionStart(_x, _y);
		_count++;
	}
	else if (_isBigBang)
	{
		bigBangStart(_x, _y);
		_count++;
	}
	else if (_isGrenadePuff)
	{
		grenadePuffStart(_x, _y);
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

void effectManager::bloodSplash(float x, float y, bool isLeft)
{
	this->playParabola("bloodSplash1", x, y, isLeft);
	this->playParabola("bloodSplash2", x, y, isLeft);
	this->playParabola("bloodSplash3", x, y, isLeft);
	this->playParabola("bloodSplash4", x, y, isLeft);
	this->playParabola("bloodSplash5", x, y, isLeft);
	this->playParabola("bloodSplash6", x, y, isLeft);
	this->playParabola("bloodSplash7", x, y, isLeft);
	this->playParabola("bloodSplash8", x, y, isLeft);
}

void effectManager::bloodFountain(float x, float y)
{
	this->playFountain("bloodSplash1", x, y);
	this->playFountain("bloodSplash2", x, y);
	this->playFountain("bloodSplash3", x, y);
	this->playFountain("bloodSplash4", x, y);
	this->playFountain("bloodSplash5", x, y);
	this->playFountain("bloodSplash6", x, y);
	this->playFountain("bloodSplash7", x, y);
	this->playFountain("bloodSplash8", x, y);
}

void effectManager::cartridge(float x, float y, bool isLeft)
{
	this->playCartridge("rambro_cartridge", x, y, isLeft);
}

void effectManager::rockFall(float x, float y, bool isLeft)
{
	this->playParabola("rock1", x, y, isLeft);
	this->playParabola("rock2", x, y, isLeft);
	this->playParabola("rock3", x, y, isLeft);
	this->playParabola("rock4", x, y, isLeft);
	this->playParabola("rock5", x, y, isLeft);
}

void effectManager::woodDebris(float x, float y, bool isLeft)
{
	this->playParabola("woodDebris1b", x, y, isLeft);
	this->playParabola("woodDebris2b", x, y, isLeft);
}

void effectManager::yellowSparks(float x, float y, bool isLeft)
{
	this->playParabola("yellowSparks", x, y, isLeft);
}

void effectManager::ashes(float x, float y)
{
	this->playAshes("ashes", x, y);
}

void effectManager::bulletPuff(float x, float y)
{
	this->playEllipsePuff("bulletPuff", x, y);
}

void effectManager::grenadePuff(float x, float y)
{
	_isGrenadePuff = true;
	_x = x - 960 / 2;
	_y = y - 110 / 2;
}

void effectManager::grenadePuffStart(float x, float y)
{
	if (_count < 15)
	{
		this->playEllipsePuff("grenadePuff", x, y);
	}
	else
	{
		_isGrenadePuff = false;
		_count = 0;
	}
}

void effectManager::knifePuff(float x, float y, bool isLeft)
{
	this->playEllipsePuff("knifePuff", x, y, isLeft);
}

void effectManager::flyingFlies(float x, float y)
{
	this->playFlyingFlies("flies", x, y);
}

void effectManager::saveBubble(float x, float y)
{
	this->playLoopAnim("saveBubble", x, y);
}

void effectManager::bigBang(float x, float y)
{
	this->playBigBang("bigBang", x, y);
	//_isBigBang = true;
	//_x = x;
	//_y = y;
}

void effectManager::bigBangStart(float x, float y)
{
	this->playBigBang("bigBang", x, y);
	if (_count > 40)
	{
		_isBigBang = false;
		_count = 0;
	}
}

void effectManager::explosionStart(float x, float y)
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

void effectManager::explosion(float x, float y)
{
	_isExplosion = true;
	_x = x - 64;
	_y = y - 44;
}

void effectManager::addEffect(string effectName, const char * imageName, int buffer, int count, bool isFrameImg)
{
	vEffect vEffectBuffer;

	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effects);
		vEffectBuffer[i]->init(imageName, count, isFrameImg);
	}

	//����Ʈ���� ���͸� �ʿ� ���
	_mEffect.insert(make_pair(effectName, vEffectBuffer));
}

void effectManager::playParabola(string effectName, float x, float y, bool isLeft)
{
	miEffect mIter;

	for (mIter = _mEffect.begin(); mIter != _mEffect.end(); ++mIter)
	{
		if (!(mIter->first == effectName)) continue;

		//����ƮŰ�� ��ġ�ϸ� ����Ʈ ����
		for (int i = 0; i < mIter->second.size(); i++)
		{
			if (mIter->second[i]->getIsRunning()) continue;
			mIter->second[i]->activateParabola(x, y, isLeft);
			return;
		}
	}
}

void effectManager::playFountain(string effectName, float x, float y)
{
	miEffect mIter;

	for (mIter = _mEffect.begin(); mIter != _mEffect.end(); ++mIter)
	{
		if (!(mIter->first == effectName)) continue;

		//����ƮŰ�� ��ġ�ϸ� ����Ʈ ����
		for (int i = 0; i < mIter->second.size(); i++)
		{
			if (mIter->second[i]->getIsRunning()) continue;
			mIter->second[i]->activateFountain(x, y);
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

		//����ƮŰ�� ��ġ�ϸ� ����Ʈ ����
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

		//����ƮŰ�� ��ġ�ϸ� ����Ʈ ����
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

		//����ƮŰ�� ��ġ�ϸ� ����Ʈ ����
		for (int i = 0; i < mIter->second.size(); i++)
		{
			if (mIter->second[i]->getIsRunning()) continue;
			mIter->second[i]->activateCartridge(x, y, isLeft);
			return;
		}
	}
}

void effectManager::playEllipsePuff(string effectName, float x, float y)
{
	miEffect mIter;

	for (mIter = _mEffect.begin(); mIter != _mEffect.end(); ++mIter)
	{
		if (!(mIter->first == effectName)) continue;

		//����ƮŰ�� ��ġ�ϸ� ����Ʈ ����
		for (int i = 0; i < mIter->second.size(); i++)
		{
			if (mIter->second[i]->getIsRunning()) continue;
			mIter->second[i]->activateEllipsePuff(x, y);
			return;
		}
	}
}

void effectManager::playEllipsePuff(string effectName, float x, float y, bool isLeft)
{
	miEffect mIter;

	for (mIter = _mEffect.begin(); mIter != _mEffect.end(); ++mIter)
	{
		if (!(mIter->first == effectName)) continue;

		//����ƮŰ�� ��ġ�ϸ� ����Ʈ ����
		for (int i = 0; i < mIter->second.size(); i++)
		{
			if (mIter->second[i]->getIsRunning()) continue;
			mIter->second[i]->activateEllipsePuff(x, y, isLeft);
			return;
		}
	}
}

void effectManager::playLoopAnim(string effectName, float x, float y)
{
	miEffect mIter;

	for (mIter = _mEffect.begin(); mIter != _mEffect.end(); ++mIter)
	{
		if (!(mIter->first == effectName)) continue;

		//����ƮŰ�� ��ġ�ϸ� ����Ʈ ����
		for (int i = 0; i < mIter->second.size(); i++)
		{
			if (mIter->second[i]->getIsRunning()) continue;
			mIter->second[i]->activateLoopAnim(x, y);
			return;
		}
	}
}

void effectManager::playFlyingFlies(string effectName, float x, float y)
{
	miEffect mIter;

	for (mIter = _mEffect.begin(); mIter != _mEffect.end(); ++mIter)
	{
		if (!(mIter->first == effectName)) continue;

		//����ƮŰ�� ��ġ�ϸ� ����Ʈ ����
		for (int i = 0; i < mIter->second.size(); i++)
		{
			if (mIter->second[i]->getIsRunning()) continue;
			mIter->second[i]->activateFlyingFlies(x, y);
			return;
		}
	}
}

void effectManager::playAshes(string effectName, float x, float y)
{
	miEffect mIter;

	for (mIter = _mEffect.begin(); mIter != _mEffect.end(); ++mIter)
	{
		if (!(mIter->first == effectName)) continue;

		//����ƮŰ�� ��ġ�ϸ� ����Ʈ ����
		for (int i = 0; i < mIter->second.size(); i++)
		{
			if (mIter->second[i]->getIsRunning()) continue;
			mIter->second[i]->activateAshes(x, y);
			return;
		}
	}
}

void effectManager::playBigBang(string effectName, float x, float y)
{
	miEffect mIter;

	for (mIter = _mEffect.begin(); mIter != _mEffect.end(); ++mIter)
	{
		if (!(mIter->first == effectName)) continue;

		//����ƮŰ�� ��ġ�ϸ� ����Ʈ ����
		for (int i = 0; i < mIter->second.size(); i++)
		{
			if (mIter->second[i]->getIsRunning()) continue;
			mIter->second[i]->activateBigBang(x, y);
			return;
		}
	}
}
