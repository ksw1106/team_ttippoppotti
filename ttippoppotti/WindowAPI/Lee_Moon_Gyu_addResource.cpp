#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::Lee_Moon_Gyu_addImage()
{
	// rambro
	_loading->loadFrameImage("rambro_idle", "player_ramBro/rambro_idle.bmp", 130, 210, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_run", "player_ramBro/rambro_run.bmp", 1040, 210, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_jump", "player_ramBro/rambro_jump.bmp", 390, 210, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_hang_frontHold", "player_ramBro/rambro_hang_frontHold.bmp", 130, 210, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_hang_backHold", "player_ramBro/rambro_hang_backHold.bmp", 130, 210, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_knife", "player_ramBro/rambro_knife.bmp", 650, 210, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_die", "player_ramBro/rambro_die.bmp", 130, 210, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_ladder", "player_ramBro/rambro_ladder.bmp", 1560, 210, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_fire", "player_ramBro/rambro_fire.bmp", 1040, 210, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_runGun", "player_ramBro/rambro_runGun.bmp", 4020, 72, 32, 2, true, RGB(255, 0, 255));
	//_loading->loadFrameImage("rambro_fireGun", "player_ramBro/rambro_fireGun.bmp", 440, 72, 4, 2, true, RGB(255, 0, 255));

	// chuck
	_loading->loadFrameImage("chuck_idle", "player_chuck/chuck_idle.bmp", 130, 210, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_run", "player_chuck/chuck_run.bmp", 1040, 210, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_jump", "player_chuck/chuck_jump.bmp", 390, 210, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_hang_frontHold", "player_chuck/chuck_hang_frontHold.bmp", 130, 210, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_hang_backHold", "player_chuck/chuck_hang_backHold.bmp", 130, 210, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_knife", "player_chuck/chuck_knife.bmp", 650, 210, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_die", "player_chuck/chuck_die.bmp", 130, 210, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_ladder", "player_chuck/chuck_ladder.bmp", 1560, 210, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_fire", "player_chuck/chuck_fire.bmp", 1040, 210, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("chuck_runGun", "player_chuck/chuck_runGun.bmp", 1992, 56, 16, 2, true, RGB(255, 0, 255));

	// °ø¿ë
	_loading->loadFrameImage("rambro_flash", "player_ramBro/rambro_flash.bmp", 320, 80, 4, 1, true, RGB(255, 0, 255));

	// bullet
	_loading->loadFrameImage("rambro_grenade_frame", "player_ramBro/rambro_grenade_frame.bmp", 384, 96, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_grenade_bomb", "player_ramBro/rambro_grenade_bomb.bmp", 384, 96, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_grenade_blue", "player_ramBro/rambro_grenade_blue.bmp", 48, 48, 1, 1, true, RGB(255, 0, 255));

	// UI
	_loading->loadFrameImage("rambro_ui", "player_ramBro/rambro_ui.bmp", 445, 114, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_ui_grenade", "player_ramBro/rambro_ui_grenade.bmp", 29, 38, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_ui_image", "player_ramBro/rambro_ui_image.bmp", 131, 156, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_ui_image_run", "player_ramBro/rambro_ui_image_run.bmp", 262, 156, 2, 1, true, RGB(255, 0, 255));

}

void loadingScene::Lee_Moon_Gyu_addSound()
{

}