#include "stdafx.h"
#include "titleScene.h"

HRESULT titleScene::init(void)
{


	string str;

	for (int i = 0; i < 126; i++)
	{
		str = "title/title (" + to_string(i + 1) + ").bmp";

		title[i] = new image;
		title[i]->init(str.c_str(), 1920, 1080);
	}

	for (int i = 0; i < 33; i++)
	{
		str = "title/startButton/startButton (" + to_string(i + 1) + ").bmp";

		startButton[i] = new image;
		startButton[i]->init(str.c_str(), 1600, 98);

		str = "title/optionButton/optionButton (" + to_string(i + 1) + ").bmp";

		optionButton[i] = new image;
		optionButton[i]->init(str.c_str(), 1600, 100);
	}

	count = 0.f, startCount = 0.f, optionCount = 0.f;
	isStart = true;

	SOUNDMANAGER->addSound("eagle", "title/sound/eagle.wav");
	SOUNDMANAGER->addSound("title", "title/sound/title.wav", true, true);
	SOUNDMANAGER->addSound("broforce", "title/sound/broforce.wav");

	SOUNDMANAGER->play("title");
	return S_OK;
}

void titleScene::release(void)
{
}

void titleScene::update(void)
{
	count+=0.25f;

	if (isStart)
	{
		startCount += 0.5f;
	}
	else
	{
		optionCount += 0.5f;
	}


	if (startCount >= 33.f)
	{
		startCount = 0.f;
	}

	if (optionCount >= 33.f)
	{
		optionCount = 0.f;
	}

	
	if (count >= 126.f)
	{
		count = 100.f;
	}

	if (count == 32.f)
	{
		SOUNDMANAGER->play("eagle");
	}

	if (count == 58.f)
	{
		SOUNDMANAGER->play("broforce");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->stop("title");
		SCENEMANAGER->loadScene("·Îµù¾À");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (isStart)
		{

		}
		else
		{
			isStart = true;
			startCount = 0.f;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (isStart)
		{
			isStart = false;
			optionCount = 0.f;
		}
		else
		{
			
		}
	}
}

void titleScene::render(void)
{
	title[(int)count]->render(getMemDC());

	if (isStart)
	{
		startButton[(int)startCount]->render(getMemDC(), 158, 705);
	}
	else
	{
		optionButton[(int)optionCount]->render(getMemDC(), 161, 709);
	}
}
