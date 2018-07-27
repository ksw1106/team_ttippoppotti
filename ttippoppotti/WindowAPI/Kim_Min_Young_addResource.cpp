#include "stdafx.h"
#include "loadingScene.h"

void loadingScene::Kim_Min_Young_addImage()
{
	_loading->loadImage("rock_big1", "effectImage/rock_fragment_big_01.bmp", 16, 16, true, RGB(255, 0, 255));
	_loading->loadImage("rock_big2", "effectImage/rock_fragment_big_02.bmp", 16, 16, true, RGB(255, 0, 255));
	_loading->loadImage("rock_sml1", "effectImage/rock_fragment_sml_01.bmp", 8, 8);
	_loading->loadImage("rock_sml2", "effectImage/rock_fragment_sml_02.bmp", 9, 9);
	_loading->loadImage("rock_sml3", "effectImage/rock_fragment_sml_03.bmp", 9, 9);
	_loading->loadImage("rambro_cartridge", "effectImage/rambro_cartridge_01.bmp", 10, 5);
	_loading->loadImage("woodPiece1", "effectImage/wood_piece_01.bmp", 10, 5);
	_loading->loadImage("woodPiece2", "effectImage/wood_piece_02.bmp", 10, 5);
	//_loading->loadImage("UI_rambroWalk", "effectImage/UI_rambro_walk_01.bmp", 262, 156, true, RGB(255, 0, 255));
	//_loading->loadImage("UI_rambroGrenade", "effectImage/UI_rambro_grenade_01.bmp", 29, 38, true, RGB(255, 0, 255));
	//_loading->loadImage("UI_statBox", "effectImage/UI_statBox_temp_01.bmp", 445, 114);
	_loading->loadImage("blood_still", "effectImage/blood_still_01.bmp", 4, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bloodTrailPuff1", "effectImage/bloodTrailPuff_01.bmp", 126, 14, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bloodTrailPuff2", "effectImage/bloodTrailPuff_02.bmp", 94, 6, 16, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bloodTrailPuff3", "effectImage/bloodTrailPuff_03.bmp", 154, 13, 11, 1, true, RGB(255, 0, 255));
}

void loadingScene::Kim_Min_Young_addSound()
{

}