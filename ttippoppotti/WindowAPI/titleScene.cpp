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

	start = new image;
	start->init("title/start.bmp", 84, 44);
	option = new image;
	option->init("title/option.bmp", 81, 43);

	count = 0.f, startCount = 0.f, optionCount = 0.f;
	isStart = true;

	SOUNDMANAGER->addSound("eagle", "title/sound/eagle.wav");
	SOUNDMANAGER->addSound("title", "title/sound/title.wav", true, true);
	SOUNDMANAGER->addSound("broforce", "title/sound/broforce.wav");
	SOUNDMANAGER->addSound("boom", "title/sound/boom.wav");
	SOUNDMANAGER->addSound("doodoong", "title/sound/doodoong.mp3");
	SOUNDMANAGER->addSound("shot", "title/sound/shot.wav");
	SOUNDMANAGER->addSound("slash", "title/sound/slash.mp3");
	SOUNDMANAGER->play("title");
	return S_OK;
}

void titleScene::release(void)
{
	for (int i = 0; i < 126; i++)
	{
		SAFE_DELETE(title[i]);
	}
	for (int i = 0; i < 33; i++)
	{
		SAFE_DELETE(startButton[i]);
		SAFE_DELETE(optionButton[i]);
	}

	SAFE_DELETE(start);
	SAFE_DELETE(option);
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

	if (count == 25.f)
	{
		SOUNDMANAGER->play("shot");
	}

	if (count == 32.f)
	{
		SOUNDMANAGER->play("eagle");
	}

	if (count == 56.f)
	{
		SOUNDMANAGER->play("boom");
	}
	if (count == 60.f)
	{
		SOUNDMANAGER->play("broforce");
	}

	if (count == 76.f)
	{
		SOUNDMANAGER->play("slash");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && isStart && count >= 62.f)
	{
		SOUNDMANAGER->stop("title");
		SCENEMANAGER->loadScene("·Îµù¾À");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (isStart)
		{
			isStart = false;
			optionCount = 0.f;
		}
		else
		{
			isStart = true;
			startCount = 0.f;
		}
		SOUNDMANAGER->play("doodoong");
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
			isStart = true;
			startCount = 0.f;
		}
		SOUNDMANAGER->play("doodoong");
	}
}

void titleScene::render(void)
{
	title[(int)count]->render(getMemDC());

	if (isStart && count >= 62.f)
	{
		startButton[(int)startCount]->render(getMemDC(), 158, 705);
		option->render(getMemDC(), 920, 820);
		
	}
	else if(!isStart && count >= 62.f)
	{
		optionButton[(int)optionCount]->render(getMemDC(), 161, 709);
		start->render(getMemDC(), 920, 820);
	}
}
