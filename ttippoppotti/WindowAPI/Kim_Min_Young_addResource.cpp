#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::Kim_Min_Young_addImage()
{
	_loading->loadImage("rock_big1", "effectImage/rock_fragment_big_01.bmp", 16, 16, true, RGB(255, 0, 255));
	_loading->loadImage("rock_big2", "effectImage/rock_fragment_big_02.bmp", 16, 16, true, RGB(255, 0, 255));
	_loading->loadImage("rock_sml1", "effectImage/rock_fragment_sml_01.bmp", 8, 8);
	_loading->loadImage("rock_sml2", "effectImage/rock_fragment_sml_02.bmp", 9, 9);
	_loading->loadImage("rock_sml3", "effectImage/rock_fragment_sml_03.bmp", 9, 9);
	//_loading->loadImage("UI_rambroWalk", "effectImage/UI_rambro_walk_01.bmp", 262, 156, true, RGB(255, 0, 255));
	//_loading->loadImage("UI_rambroGrenade", "effectImage/UI_rambro_grenade_01.bmp", 29, 38, true, RGB(255, 0, 255));
	//_loading->loadImage("UI_statBox", "effectImage/UI_statBox_temp_01.bmp", 445, 114);
	_loading->loadImage("blood_still1", "effectImage/blood_still_01.bmp", 4, 4, true, RGB(255, 0, 255));
	_loading->loadImage("blood_still2", "effectImage/blood_still_02.bmp", 15, 20, true, RGB(255, 0, 255));
	_loading->loadImage("blood_still3", "effectImage/blood_still_03.bmp", 15, 20, true, RGB(255, 0, 255));
	_loading->loadImage("blood_still4", "effectImage/blood_still_04.bmp", 8, 11, true, RGB(255, 0, 255));
	_loading->loadImage("blood_still5", "effectImage/blood_still_05.bmp", 16, 16, true, RGB(255, 0, 255));
	_loading->loadImage("blood_still6", "effectImage/blood_still_06.bmp", 8, 11, true, RGB(255, 0, 255));
	_loading->loadImage("blood_still7", "effectImage/blood_still_07.bmp", 6, 8, true, RGB(255, 0, 255));
	_loading->loadImage("blood_still8", "effectImage/blood_still_08.bmp", 11, 12, true, RGB(255, 0, 255));
	_loading->loadImage("explosionFlame1", "effectImage/explosion_flame_01.bmp", 17, 17, true, RGB(255, 0, 255));
	_loading->loadImage("explosionFlame2", "effectImage/explosion_flame_02.bmp", 17, 17, true, RGB(255, 0, 255));
	_loading->loadImage("explosionFlame3", "effectImage/explosion_flame_03.bmp", 25, 25, true, RGB(255, 0, 255));
	_loading->loadImage("explosionFlame4", "effectImage/explosion_flame_04.bmp", 31, 31, true, RGB(255, 0, 255));
	_loading->loadImage("explosionFlame5", "effectImage/explosion_flame_05.bmp", 31, 31, true, RGB(255, 0, 255));
	_loading->loadImage("explosionFlame6", "effectImage/explosion_flame_06.bmp", 33, 33, true, RGB(255, 0, 255));
	_loading->loadImage("explosionFlame7", "effectImage/explosion_flame_07.bmp", 33, 33, true, RGB(255, 0, 255));
	_loading->loadImage("explosionFlame8", "effectImage/explosion_flame_08.bmp", 43, 43, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bloodTrailPuff1", "effectImage/bloodTrailPuff_01.bmp", 126, 14, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bloodTrailPuff2", "effectImage/bloodTrailPuff_02.bmp", 94, 6, 16, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bloodTrailPuff3", "effectImage/bloodTrailPuff_03.bmp", 154, 13, 11, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("explosionBallFlame", "effectImage/explosionBallFlame_01.bmp", 4160, 256, 26, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("explosionBallFlame_large", "effectImage/explosionBallFlame_large_01.bmp", 8448, 256, 33, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("explosionBallFlame_larger", "effectImage/explosionBallFlame_larger_01.bmp", 11904, 512, 31, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("explosionBallFlame_small", "effectImage/explosionBallFlame_small_01.bmp", 2688, 128, 21, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_cartridge", "effectImage/rambro_cartridge_01.bmp", 40, 10, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("woodDebris1", "effectImage/wood_debris_01.bmp", 136, 34, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("woodDebris2", "effectImage/wood_debris_02.bmp", 104, 26, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("smoke1", "effectImage/smoke_01.bmp", 448, 32, 14, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("smoke2", "effectImage/smoke_02.bmp", 480, 32, 15, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("whitePuff", "effectImage/whitePuffPop_01.bmp", 384, 64, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bulletPuff", "effectImage/bulletPuff_01.bmp", 528, 66, 8, 1, true, RGB(255, 0, 255));
	
	_loading->loadImage("skull", "objectImage/skull_01.bmp", 30, 30, true, RGB(255, 0, 255));
	_loading->loadImage("skullPole", "objectImage/skull_pole_01.bmp", 32, 114, true, RGB(255, 0, 255));
	_loading->loadImage("doubleSkullPole", "objectImage/doubleSkull_pole_01.bmp", 70, 114, true, RGB(255, 0, 255));
	_loading->loadImage("skullContainer", "objectImage/skull_container_01.bmp", 101, 108, true, RGB(255, 0, 255));
	_loading->loadImage("prisoner_InJail", "objectImage/prisoner_inJail_01.bmp", 203, 203, true, RGB(255, 0, 255));
	_loading->loadImage("prisoner", "objectImage/prisoner_01.bmp", 89, 114, true, RGB(255, 0, 255));
	_loading->loadImage("woodBox", "objectImage/woodBox_01.bmp", 101, 101);
	_loading->loadImage("bottle_green", "objectImage/bottle_green_01.bmp", 25, 57, true, RGB(255, 0, 255));
	_loading->loadImage("bottle_gray", "objectImage/bottle_gray_01.bmp", 25, 57, true, RGB(255, 0, 255));
	_loading->loadImage("bottle_brown", "objectImage/bottle_brown_01.bmp", 45, 63, true, RGB(255, 0, 255));
	/*_humanDeadImage = new image;
	_humanDeadImage->init("human_dead.bmp", 1404, 125, 13, 1);
	_spikeImage = new image;
	_spikeImage->init("spike.bmp", 3795.f, 976.f, 15, 108, true, RGB(255, 0, 255));*/
	_loading->loadFrameImage("");
	_loading->loadFrameImage("truck", "objectImage/truck_01.bmp", 528, 66, 11, 1, true, RGB(255, 0, 255));
}

void loadingScene::Kim_Min_Young_addSound()
{

}