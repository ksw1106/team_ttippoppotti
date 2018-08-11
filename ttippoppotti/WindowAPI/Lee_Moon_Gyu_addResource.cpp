#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::Lee_Moon_Gyu_addImage()
{
	// rambro
	_loading->loadFrameImage("rambro_idle", "player_ramBro/rambro_idle.bmp", 130, 210, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_run", "player_ramBro/rambro_run.bmp", 1040, 210, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_jump", "player_ramBro/rambro_jump.bmp", 390, 210, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_hang_frontHold", "player_ramBro/broforce_hang_frontHold.bmp", 72, 152, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_hang_backHold", "player_ramBro/broforce_hang_backHold.bmp", 72, 152, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_knife", "player_ramBro/rambro_knife.bmp", 650, 210, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_die", "player_ramBro/broforce_die.bmp", 76, 72, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_ladder", "player_ramBro/broforce_ladder.bmp", 912, 152, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_fire", "player_ramBro/broforce_fire.bmp", 608, 152, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("broforce_flash", "player_ramBro/rambro_flash.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));

	// chuck
	_loading->loadFrameImage("chuck_idle", "player_chuck/chuck_idle.bmp", 130, 209, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_run", "player_chuck/chuck_run.bmp", 836, 209, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_jump", "player_chuck/chuck_jump.bmp", 314, 209, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_hang_frontHold", "player_chuck/chuck_hang_frontHold.bmp", 105, 209, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_hang_backHold", "player_chuck/chuck_hang_backHold.bmp", 105, 209, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_knife", "player_chuck/chuck_knife.bmp", 523, 209, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_die", "player_chuck/chuck_die.bmp", 314, 209, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_ladder", "player_chuck/chuck_ladder.bmp", 1254, 209, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_fire", "player_chuck/chuck_fire.bmp", 836, 209, 8, 2, true, RGB(255, 0, 255));
}

void loadingScene::Lee_Moon_Gyu_addSound()
{

}