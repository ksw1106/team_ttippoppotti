#include "stdafx.h"
#include "endingScene.h"

HRESULT endingScene::init(void)
{
	thankyou = new image;
	thankyou->init("thankyou.bmp", 1920, 1080);

	return S_OK;
}

void endingScene::release(void)
{
}

void endingScene::update(void)
{
}

void endingScene::render(void)
{
	thankyou->render(getMemDC());
}
