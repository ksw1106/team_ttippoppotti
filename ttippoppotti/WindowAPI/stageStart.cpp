#include "stdafx.h"
#include "stageStart.h"

HRESULT stageStart::init(void)
{
	start[0] = IMAGEMANAGER->findImage("start3");
	start[1] = IMAGEMANAGER->findImage("start2");
	start[2] = IMAGEMANAGER->findImage("start1");
	start[3] = IMAGEMANAGER->findImage("letsgo");

	soundName[0] = "3";
	soundName[1] = "2";
	soundName[2] = "1";
	soundName[3] = "go";

	soundCount = 0;
	goCount = 0;
	startPosX = 200;

	return S_OK;
}

void stageStart::release(void)
{
}

void stageStart::update(void)
{
	switch (soundCount)
	{
	case 0:
		if (!SOUNDMANAGER->isPlaySound(soundName[soundCount]))
		{
			SOUNDMANAGER->play(soundName[soundCount], 0.5f);
			soundCount++;
			startPosX = 200;
		}
		break;
	case 1:
		if (!SOUNDMANAGER->isPlaySound(soundName[soundCount - 1]))
		{
			SOUNDMANAGER->play(soundName[soundCount], 0.5f);
			soundCount++;
			startPosX = 200;
		}
		break;
	case 2:
		if (!SOUNDMANAGER->isPlaySound(soundName[soundCount - 1]))
		{
			SOUNDMANAGER->play(soundName[soundCount], 0.5f);
			soundCount++;
			startPosX = 200;
		}
		break;
	case 3:
		if (!SOUNDMANAGER->isPlaySound(soundName[soundCount - 1]))
		{
			SOUNDMANAGER->play(soundName[soundCount], 0.5f);
			soundCount++;
			startPosX = 200;
		}
		break;
	case 4:
		if (SOUNDMANAGER->isPlaySound(soundName[soundCount - 1]))
		{
			SOUNDMANAGER->play("1stage", 0.5f);
			soundCount++;
			startPosX = 200;
		}
		break;
	}

	if (soundCount == 5)
	{
		goCount++;
	}
	else
	{
		startPosX -= 4;
	}
}

void stageStart::render(void)
{
	if (soundCount >= 1 && soundCount < 4)
	{
		start[soundCount-1]->render(getMemDC(), WINSIZEX / 2 - start[soundCount-1]->getWidth() / 2 - startPosX, 200);
	}
	else
	{
		if (goCount <= 25)
			start[3]->render(getMemDC(), WINSIZEX / 2 - start[3]->getWidth() / 2, 200);
	}
}