#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::Lee_Moon_Gyu_addImage()
{
	// rambro
	_loading->loadFrameImage("broforce_idle", "player_ramBro/broforce_idle.bmp", 60, 152, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_run (1)", "player_ramBro/broforce_run (1).bmp", 512, 152, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_jump", "player_ramBro/broforce_jump.bmp", 177, 152, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_hang_forntHold", "player_ramBro/broforce_hang_forntHold.bmp", 72, 152, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_hang_backHold", "player_ramBro/broforce_hang_backHold.bmp", 72, 152, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_knife", "player_ramBro/broforce_knife.bmp", 449, 152, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_die", "player_ramBro/broforce_die.bmp", 76, 72, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_ladder", "player_ramBro/broforce_ladder.bmp", 912, 152, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_fire", "player_ramBro/broforce_fire.bmp", 608, 152, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_flash", "player_ramBro/rambro_flash.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));

	// chuck
	_loading->loadFrameImage("chuck_idle", "player_chuck/chuck_idle.bmp", 130, 209, 1, 2, true, RGB(255, 0, 255));
}

void loadingScene::Lee_Moon_Gyu_addSound()
{

}