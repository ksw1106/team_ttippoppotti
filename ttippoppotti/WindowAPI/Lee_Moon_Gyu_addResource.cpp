#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::Lee_Moon_Gyu_addImage()
{
	_loading->loadFrameImage("broforce_idle", "player_ramBro/broforce_idle.bmp", 60, 152, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_run (1)", "player_ramBro/broforce_run (1).bmp", 512, 152, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_jump", "player_ramBro/broforce_jump.bmp", 177, 152, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_hang_forntHold", "player_ramBro/broforce_hang_forntHold.bmp", 72, 152, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_hang_backHold", "player_ramBro/broforce_hang_backHold.bmp", 72, 152, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_knife", "player_ramBro/broforce_knife.bmp", 449, 152, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_die", "player_ramBro/broforce_die.bmp", 76, 72, 1, 2, true, RGB(255, 0, 255));
}

void loadingScene::Lee_Moon_Gyu_addSound()
{

}