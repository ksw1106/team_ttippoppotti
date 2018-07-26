#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::Lee_Ji_Woong_addImage()
{
	_loading->loadImage("군인시체", "soldier_dead.bmp", 80, 160, true, RGB(255,0,255));
	_loading->loadFrameImage("군인걸음", "soldier_walk.bmp", 640, 160, 8, 2);
	_loading->loadFrameImage("군인의심", "soldier_doubt.bmp", 640, 160, 8, 2);
	_loading->loadFrameImage("군인평상시", "soldier_idle.bmp", 1200, 160, 15, 2);
	_loading->loadFrameImage("군인넉백", "soldier_knock_back.bmp", 960, 160, 12, 2);
	_loading->loadFrameImage("군인점프", "soldier_fly_away.bmp", 1040, 160, 13, 2);

	_loading->loadImage("군견시체", "dog_dead.bmp", 80, 160, true, RGB(255, 0, 255));
	_loading->loadFrameImage("군견뜀", "dog_run.bmp", 640, 160, 8, 2);
	_loading->loadFrameImage("군견잠", "dog_sleep.bmp", 960, 160, 12, 2);
	_loading->loadFrameImage("군견넉백", "dog_knock_back.bmp", 800, 160, 10, 2);
	_loading->loadFrameImage("군견평상시", "dog_idle.bmp", 1280, 160, 16, 2);
	_loading->loadFrameImage("군견공격", "dog_assault.bmp", 960, 160, 12, 2);

	_loading->loadFrameImage("브로빌공격", "dog_assault.bmp", 960, 160, 12, 2);
}

void loadingScene::Lee_Ji_Woong_addSound()
{

}