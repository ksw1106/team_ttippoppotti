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
	_loading->loadImage("blood_still1", "effectImage/blood_still_01.bmp", 4, 4);
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
	_loading->loadImage("blackPixelDot", "effectImage/fly_01.bmp", 4, 4);
	_loading->loadImage("yellowPixelDot", "effectImage/spark_01.bmp", 4, 4);
	_loading->loadFrameImage("p1Bubble", "effectImage/p1_bubble_01.bmp", 1056, 92, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("saveBubble", "effectImage/save_bubble_01.bmp", 4352, 136, 25, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("saveBubble2", "effectImage/save_bubble_02.bmp", 5248, 128, 32, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bloodTrailPuff1", "effectImage/bloodTrailPuff_01.bmp", 126, 14, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bloodTrailPuff2", "effectImage/bloodTrailPuff_02.bmp", 94, 6, 16, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bloodTrailPuff3", "effectImage/bloodTrailPuff_03.bmp", 154, 13, 11, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("explosionBallFlame", "effectImage/explosionBallFlame_01.bmp", 4160, 256, 24, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("explosionBallFlame_large", "effectImage/explosionBallFlame_large_01.bmp", 8448, 256, 31, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("explosionBallFlame_larger", "effectImage/explosionBallFlame_larger_01.bmp", 11904, 512, 29, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("explosionBallFlame_small", "effectImage/explosionBallFlame_small_01.bmp", 2688, 128, 19, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("rambro_cartridge", "effectImage/rambro_cartridge_01.bmp", 40, 10, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("woodDebris1", "effectImage/wood_debris_01.bmp", 136, 34, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("woodDebris2", "effectImage/wood_debris_02.bmp", 104, 26, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("smoke1", "effectImage/smoke_01.bmp", 448, 32, 14, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("smoke2", "effectImage/smoke_02.bmp", 480, 32, 15, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("whitePuff", "effectImage/whitePuffPop_01.bmp", 384, 64, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bulletPuff", "effectImage/bulletPuff_01.bmp", 528, 66, 8, 1, true, RGB(255, 0, 255));

	_loading->loadImage("skull", "objectImage/skull_01.bmp", 20, 20, true, RGB(255, 0, 255));
	_loading->loadImage("skullPole", "objectImage/skull_pole_01.bmp", 23, 77, true, RGB(255, 0, 255));
	_loading->loadImage("doubleSkullPole", "objectImage/doubleSkull_pole_01.bmp", 47, 77, true, RGB(255, 0, 255));
	_loading->loadImage("skullDrum_red", "objectImage/skull_drum_red_01.bmp", 68, 68);
	_loading->loadImage("skullDrum_gray", "objectImage/skull_drum_gray_01.bmp", 68, 68);
	_loading->loadImage("prisoner_inJail", "objectImage/prisoner_inJail_01.bmp", 136, 136, true, RGB(255, 0, 255));
	_loading->loadImage("prisoner_freed", "objectImage/prisoner_01.bmp", 136, 136, true, RGB(255, 0, 255));
	_loading->loadImage("woodenBox", "objectImage/woodenBox_01.bmp", 68, 68);
	_loading->loadImage("bottle_green", "objectImage/bottle_green_01.bmp", 17, 39, true, RGB(255, 0, 255));
	_loading->loadImage("bottle_gray", "objectImage/bottle_gray_01.bmp", 17, 39, true, RGB(255, 0, 255));
	_loading->loadImage("bottle_brown", "objectImage/bottle_brown_01.bmp", 31, 44, true, RGB(255, 0, 255));
	_loading->loadImage("saveFlag_pole", "objectImage/saveFlag_pole_01.bmp", 22, 203, true, RGB(255, 0, 255));
	_loading->loadFrameImage("human_dead", "objectImage/human_dead.bmp", 972, 115, 12, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("truck", "objectImage/truck_01.bmp", 388, 231, true, RGB(255, 0, 255));
}

void loadingScene::Kim_Min_Young_addSound()
{

}