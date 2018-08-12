#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::Kim_Sang_Won_addImage()
{
	_loading->loadImage("backGround_tree1", "background_tree1.bmp", 5755, 2878, true, RGB(255, 0, 255));
	_loading->loadImage("backGround_tree2", "background_tree2.bmp", 5755, 2878, true, RGB(255, 0, 255));
	_loading->loadImage("backGround_tree3", "background_tree3.bmp", 5755, 2878, true, RGB(255, 0, 255));
	_loading->loadImage("backGround_tree4", "background_tree4.bmp", 5755, 2878, true, RGB(255, 0, 255));
	
	_loading->loadImage("ladder", "objectImage/ladder.bmp", 25, 237, true, RGB(255, 0, 255));
	_loading->loadFrameImage("helicopter", "objectImage/helicopter.bmp", 1625, 419, 5, 1);
	_loading->loadFrameImage("saveFlag", "objectImage/saveFlag.bmp", 3234, 88, 33, 1);
	_loading->loadFrameImage("flag", "objectImage/flag.bmp", 3650.f, 972.f, 2048, 112, 32, 1);

	_loading->loadImage("0", "number/clear/0.bmp", 48, 76, true, RGB(255, 0, 255));
	_loading->loadImage("1", "number/clear/1.bmp", 43, 76, true, RGB(255, 0, 255));
	_loading->loadImage("2", "number/clear/2.bmp", 48, 76, true, RGB(255, 0, 255));
	_loading->loadImage("3", "number/clear/3.bmp", 50, 76, true, RGB(255, 0, 255));
	_loading->loadImage("4", "number/clear/4.bmp", 52, 76, true, RGB(255, 0, 255));
	_loading->loadImage("5", "number/clear/5.bmp", 49, 76, true, RGB(255, 0, 255));
	_loading->loadImage("6", "number/clear/6.bmp", 48, 76, true, RGB(255, 0, 255));
	_loading->loadImage("7", "number/clear/7.bmp", 50, 76, true, RGB(255, 0, 255));
	_loading->loadImage("8", "number/clear/8.bmp", 53, 76, true, RGB(255, 0, 255));
	_loading->loadImage("9", "number/clear/9.bmp", 48, 76, true, RGB(255, 0, 255));
	_loading->loadImage("timeDot", "number/clear/timeDot.bmp", 19, 19);

	_loading->loadImage("start1", "start1.bmp", 59, 197, true, RGB(255, 0, 255));
	_loading->loadImage("start2", "start2.bmp", 115, 203, true, RGB(255, 0, 255));
	_loading->loadImage("start3", "start3.bmp", 122, 203, true, RGB(255, 0, 255));
	_loading->loadImage("letsgo", "letsgo.bmp", 955, 201, true, RGB(255, 0, 255));
	_loading->loadImage("missionFailed", "missionFailed.bmp", 432, 98, true, RGB(255, 0, 255));
}

void loadingScene::Kim_Sang_Won_addSound()
{
	//게임 시작시 3, 2, 1, go!
	_loading->loadSound("1", "start_one.mp3");
	_loading->loadSound("2", "start_two.mp3");
	_loading->loadSound("3", "start_three.mp3");
	_loading->loadSound("go", "start_go.mp3");

	_loading->loadSound("1stage", "title/sound/1stage.wav", true, true);
	_loading->loadSound("clear", "stageClear/sound/clear.wav", true, true);
	_loading->loadSound("soldierDead", "stageClear/sound/soldierDead.mp3");
}