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
}

void loadingScene::Kim_Min_Young_addSound()
{

}