#include "stdafx.h"
#include "titleScene.h"

HRESULT titleScene::init(void)
{
	string str;
	for (int i = 0; i < 126; i++)
	{
		title[i] = new image;
		str = "title/title (" + to_string(i + 1) + ").bmp";
		title[i]->init(str.c_str(), 1920, 1080);
	}

	count = 0.f;

	return S_OK;
}

void titleScene::release(void)
{
}

void titleScene::update(void)
{
	count+=0.5f;
	if (count >= 126.f)
	{
		count = 100.f;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SCENEMANAGER->loadScene("·Îµù¾À");
	}
}

void titleScene::render(void)
{
	title[(int)count]->render(getMemDC());
}
