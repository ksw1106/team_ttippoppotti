#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::Lee_Ji_Woong_addImage()
{
	_loading->loadFrameImage("군인시체", "enemyImage/soldier_dead.bmp", 90, 100, 1, 2);
	_loading->loadFrameImage("군인걸음", "enemyImage/soldier_walk.bmp", 520, 150, 8, 2);
	_loading->loadFrameImage("군인의심", "enemyImage/soldier_doubt.bmp", 325, 152, 5, 2);
	_loading->loadFrameImage("군인평상시", "enemyImage/soldier_idle.bmp", 975, 152, 15, 2);
	_loading->loadFrameImage("군인넉백", "enemyImage/soldier_knock_back.bmp", 650, 152, 10, 2);
	_loading->loadFrameImage("군인점프", "enemyImage/soldier_fly_away.bmp", 845, 152, 13, 2);	
	_loading->loadFrameImage("군인사격", "enemyImage/soldier_fire.bmp", 520, 152, 8, 2);

	_loading->loadFrameImage("총발사", "enemyImage/gun_fire.bmp", 340, 152, 4, 2);
	_loading->loadFrameImage("총평상시", "enemyImage/gun_idle.bmp", 520, 152, 8, 2);
	_loading->loadFrameImage("총조준", "enemyImage/gun_targeting.bmp", 595, 152, 7, 2);
	_loading->loadFrameImage("총장전", "enemyImage/gun_reload.bmp", 1280, 160, 16, 2);
	_loading->loadFrameImage("총발사대기", "enemyImage/gun_ready.bmp", 1360, 152, 16, 2);

	_loading->loadFrameImage("군견시체", "enemyImage/dog_dead.bmp", 80, 160, 1, 2);
	_loading->loadFrameImage("군견뜀", "enemyImage/dog_run.bmp", 640, 160, 8, 2);
	_loading->loadFrameImage("군견잠", "enemyImage/dog_sleep.bmp", 960, 160, 12, 2);
	_loading->loadFrameImage("군견넉백", "enemyImage/dog_knock_back.bmp", 800, 160, 10, 2);
	_loading->loadFrameImage("군견평상시", "enemyImage/dog_idle.bmp", 1280, 160, 16, 2);
	_loading->loadFrameImage("군견공격", "enemyImage/dog_assault.bmp", 960, 160, 12, 2);

	_loading->loadFrameImage("브로빌시체", "enemyImage/brovil_dead.bmp", 80, 160, 1, 2);
	_loading->loadFrameImage("브로빌걸음", "enemyImage/brovil_walk.bmp", 960, 160, 12, 2);
	_loading->loadFrameImage("브로빌평상시", "enemyImage/brovil_idle.bmp", 320, 160, 4, 2);
	_loading->loadFrameImage("브로빌넉백", "enemyImage/brovil_knock_back.bmp", 800, 160, 10, 2);
	_loading->loadFrameImage("브로빌승화", "enemyImage/brovil_disappear.bmp", 1680, 160, 21, 2);	

	_loading->loadFrameImage("테러콥터 아이들(풀)", "enemyImage/bosImage/boss_idle_missile_full.bmp", 2880, 512, 9, 2);
	_loading->loadFrameImage("테러콥터 죽음", "enemyImage/bosImage/boss_dead.bmp", 300, 360, 1, 2);
	_loading->loadFrameImage("테러콥터 기관총 발사", "enemyImage/bosImage/boss_gun_fire.bmp", 480, 160, 4, 2);
	_loading->loadFrameImage("테러콥터 기관총 예열", "enemyImage/bosImage/boss_gun_ready.bmp", 480, 160, 4, 2);
	_loading->loadFrameImage("테러콥터 기관총 회전", "enemyImage/bosImage/boss_gun_rotate.bmp", 1080, 80, 9, 1);
	_loading->loadFrameImage("테러콥터 로켓", "enemyImage/bosImage/boss_rocket.bmp", 304, 96, 4, 2);
	_loading->loadFrameImage("테러콥터 프로펠러", "enemyImage/bosImage/propeller.bmp", 800, 52, 4, 1);
	_loading->loadFrameImage("테러콥터 총알", "enemyImage/bosImage/boss_bullet.bmp", 64, 32, 1, 1);
}

void loadingScene::Lee_Ji_Woong_addSound()
{

}