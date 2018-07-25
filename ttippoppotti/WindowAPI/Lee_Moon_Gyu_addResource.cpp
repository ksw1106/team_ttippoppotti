#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::Lee_Moon_Gyu_addImage()
{
	_loading->loadFrameImage("broforce_idle", "broforce_idle.bmp", 60, 152, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_run (1)", "broforce_run (1).bmp", 512, 152, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_jump", "broforce_jump.bmp", 177, 152, 3, 2, true, RGB(255, 0, 255));
}

void loadingScene::Lee_Moon_Gyu_addSound()
{

}