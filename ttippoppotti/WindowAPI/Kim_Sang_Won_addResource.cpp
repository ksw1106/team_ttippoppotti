#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::Kim_Sang_Won_addImage()
{
	_loading->loadImage("backGround_pixel", "background_pixel.bmp", 5755, 2878, true, RGB(255, 0, 255));
	_loading->loadImage("backGround", "background.bmp", 5755, 2878, true, RGB(255, 0, 255));
	_loading->loadImage("backGround_tree1", "background_tree1.bmp", 5755, 2878, true, RGB(255, 0, 255));
	_loading->loadImage("backGround_tree2", "background_tree2.bmp", 5755, 2878, true, RGB(255, 0, 255));
	_loading->loadImage("backGround_tree3", "background_tree3.bmp", 5755, 2878, true, RGB(255, 0, 255));
	_loading->loadImage("backGround_tree4", "background_tree4.bmp", 5755, 2878, true, RGB(255, 0, 255));
	_loading->loadImage("backGround_rock", "background_rock.bmp", 5755, 2878, true, RGB(255, 0, 255));
	_loading->loadImage("backGround_object", "background_object.bmp", 5755, 2878, true, RGB(255, 0, 255));
	_loading->loadImage("stage2_background_object", "stage2_background_object.bmp", 5582, 2694, true, RGB(255, 0, 255));
	_loading->loadImage("stage2_background_rock", "stage2_background_rock.bmp", 5582, 2694, true, RGB(255, 0, 255));
	_loading->loadFrameImage("helicopter", "helicopter.bmp", 1625, 182, 5, 1);
	_loading->loadImage("ladder", "ladder.bmp", 25, 237, true, RGB(255, 0, 255));
	_loading->loadFrameImage("saveFlag", "saveFlag.bmp", 3234, 88, 33, 1);
	_loading->loadFrameImage("flag", "flag.bmp", 3650.f, 972.f, 2048, 112, 32, 1);
}

void loadingScene::Kim_Sang_Won_addSound()
{
	//게임 시작시 3, 2, 1, go!
	_loading->loadSound("1", "start_one.mp3");
	_loading->loadSound("2", "start_two.mp3");
	_loading->loadSound("3", "start_three.mp3");
	_loading->loadSound("go", "start_go.mp3");
}