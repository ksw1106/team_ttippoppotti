#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::Lee_Ji_Woong_addImage()
{
	_loading->loadFrameImage("���ν�ü", "enemyImage/soldier_dead.bmp", 80, 160, 1, 2);
	_loading->loadFrameImage("���ΰ���", "enemyImage/soldier_walk.bmp", 640, 160, 8, 2);
	_loading->loadFrameImage("�����ǽ�", "enemyImage/soldier_doubt.bmp", 640, 160, 8, 2);
	_loading->loadFrameImage("��������", "enemyImage/soldier_idle.bmp", 1200, 160, 15, 2);
	_loading->loadFrameImage("���γ˹�", "enemyImage/soldier_knock_back.bmp", 960, 160, 12, 2);
	_loading->loadFrameImage("��������", "enemyImage/soldier_fly_away.bmp", 1040, 160, 13, 2);	

	_loading->loadFrameImage("�ѹ߻�", "enemyImage/gun_fire.bmp", 320, 160, 4, 2);
	_loading->loadFrameImage("������", "enemyImage/gun_idle.bmp", 640, 160, 8, 2);
	_loading->loadFrameImage("������", "enemyImage/gun_targeting.bmp", 560, 160, 7, 2);
	_loading->loadFrameImage("������", "enemyImage/gun_reload.bmp", 1280, 160, 16, 2);
	_loading->loadFrameImage("�ѹ߻���", "enemyImage/gun_ready.bmp", 1280, 160, 16, 2);

	_loading->loadFrameImage("���߽�ü", "enemyImage/dog_dead.bmp", 80, 160, 1, 2);
	_loading->loadFrameImage("���߶�", "enemyImage/dog_run.bmp", 640, 160, 8, 2);
	_loading->loadFrameImage("������", "enemyImage/dog_sleep.bmp", 960, 160, 12, 2);
	_loading->loadFrameImage("���߳˹�", "enemyImage/dog_knock_back.bmp", 800, 160, 10, 2);
	_loading->loadFrameImage("��������", "enemyImage/dog_idle.bmp", 1280, 160, 16, 2);
	_loading->loadFrameImage("���߰���", "enemyImage/dog_assault.bmp", 960, 160, 12, 2);

	_loading->loadFrameImage("��κ���ü", "enemyImage/brovil_dead.bmp", 80, 160, 1, 2);
	_loading->loadFrameImage("��κ�����", "enemyImage/brovil_walk.bmp", 960, 160, 12, 2);
	_loading->loadFrameImage("��κ�����", "enemyImage/brovil_idle.bmp", 320, 160, 4, 2);
	_loading->loadFrameImage("��κ��˹�", "enemyImage/brovil_knock_back.bmp", 800, 160, 10, 2);
	_loading->loadFrameImage("��κ���ȭ", "enemyImage/brovil_disappear.bmp", 1680, 160, 21, 2);	
}

void loadingScene::Lee_Ji_Woong_addSound()
{

}