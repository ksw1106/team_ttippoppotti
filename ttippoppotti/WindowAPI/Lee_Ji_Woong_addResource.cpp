#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::Lee_Ji_Woong_addImage()
{
	_loading->loadFrameImage("���ν�ü", "enemyImage/soldier_dead.bmp", 90, 100, 1, 2);
	_loading->loadFrameImage("���ΰ���", "enemyImage/soldier_walk.bmp", 520, 150, 8, 2);
	_loading->loadFrameImage("�����ǽ�", "enemyImage/soldier_doubt.bmp", 325, 152, 5, 2);
	_loading->loadFrameImage("��������", "enemyImage/soldier_idle.bmp", 975, 152, 15, 2);
	_loading->loadFrameImage("���γ˹�", "enemyImage/soldier_knock_back.bmp", 650, 152, 10, 2);
	_loading->loadFrameImage("��������", "enemyImage/soldier_fly_away.bmp", 845, 152, 13, 2);	
	_loading->loadFrameImage("���λ��", "enemyImage/soldier_fire.bmp", 520, 152, 8, 2);

	_loading->loadFrameImage("�ѹ߻�", "enemyImage/gun_fire.bmp", 340, 152, 4, 2);
	_loading->loadFrameImage("������", "enemyImage/gun_idle.bmp", 520, 152, 8, 2);
	_loading->loadFrameImage("������", "enemyImage/gun_targeting.bmp", 595, 152, 7, 2);
	_loading->loadFrameImage("������", "enemyImage/gun_reload.bmp", 1280, 160, 16, 2);
	_loading->loadFrameImage("�ѹ߻���", "enemyImage/gun_ready.bmp", 1360, 152, 16, 2);

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

	_loading->loadFrameImage("�׷����� ���̵�(Ǯ)", "enemyImage/bosImage/boss_idle_missile_full.bmp", 2880, 512, 9, 2);
	_loading->loadFrameImage("�׷����� ����", "enemyImage/bosImage/boss_dead.bmp", 300, 360, 1, 2);
	_loading->loadFrameImage("�׷����� ����� �߻�", "enemyImage/bosImage/boss_gun_fire.bmp", 480, 160, 4, 2);
	_loading->loadFrameImage("�׷����� ����� ����", "enemyImage/bosImage/boss_gun_ready.bmp", 480, 160, 4, 2);
	_loading->loadFrameImage("�׷����� ����� ȸ��", "enemyImage/bosImage/boss_gun_rotate.bmp", 1080, 80, 9, 1);
	_loading->loadFrameImage("�׷����� ����", "enemyImage/bosImage/boss_rocket.bmp", 304, 96, 4, 2);
	_loading->loadFrameImage("�׷����� �����緯", "enemyImage/bosImage/propeller.bmp", 800, 52, 4, 1);
	_loading->loadFrameImage("�׷����� �Ѿ�", "enemyImage/bosImage/boss_bullet.bmp", 64, 32, 1, 1);
}

void loadingScene::Lee_Ji_Woong_addSound()
{

}