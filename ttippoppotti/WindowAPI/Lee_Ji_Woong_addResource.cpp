#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::Lee_Ji_Woong_addImage()
{
	_loading->loadImage("���ν�ü", "soldier_dead.bmp", 80, 160, true, RGB(255,0,255));
	_loading->loadFrameImage("���ΰ���", "soldier_walk.bmp", 640, 160, 8, 2);
	_loading->loadFrameImage("�����ǽ�", "soldier_doubt.bmp", 640, 160, 8, 2);
	_loading->loadFrameImage("��������", "soldier_idle.bmp", 1200, 160, 15, 2);
	_loading->loadFrameImage("���γ˹�", "soldier_knock_back.bmp", 960, 160, 12, 2);
	_loading->loadFrameImage("��������", "soldier_fly_away.bmp", 1040, 160, 13, 2);

	_loading->loadImage("���߽�ü", "dog_dead.bmp", 80, 160, true, RGB(255, 0, 255));
	_loading->loadFrameImage("���߶�", "dog_run.bmp", 640, 160, 8, 2);
	_loading->loadFrameImage("������", "dog_sleep.bmp", 960, 160, 12, 2);
	_loading->loadFrameImage("���߳˹�", "dog_knock_back.bmp", 800, 160, 10, 2);
	_loading->loadFrameImage("��������", "dog_idle.bmp", 1280, 160, 16, 2);
	_loading->loadFrameImage("���߰���", "dog_assault.bmp", 960, 160, 12, 2);

	_loading->loadFrameImage("��κ�����", "dog_assault.bmp", 960, 160, 12, 2);
}

void loadingScene::Lee_Ji_Woong_addSound()
{

}