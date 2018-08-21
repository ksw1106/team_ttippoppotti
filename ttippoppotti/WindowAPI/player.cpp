#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

HRESULT player::init(int num, float x, float y)
{
	if (num ==0)
	{
		// rambro
		_ramBro[IDLE] = IMAGEMANAGER->findImage("rambro_idle");
		_ramBro[RUN] = IMAGEMANAGER->findImage("rambro_run");
		//_ramBro[FAST_RUN] = IMAGEMANAGER->addFrameImage("broforce_run (2)", "broforce_run (2).bmp", 448, 128, 8, 2, true, RGB(255, 0, 255));
		_ramBro[JUMP] = IMAGEMANAGER->findImage("rambro_jump");
		_ramBro[HANG_FRONT_HOLD] = IMAGEMANAGER->findImage("rambro_hang_frontHold");
		_ramBro[HANG_BACK_HOLD] = IMAGEMANAGER->findImage("rambro_hang_backHold");
		_ramBro[KNIFE] = IMAGEMANAGER->findImage("rambro_knife");
		_ramBro[DIE] = IMAGEMANAGER->findImage("rambro_die");
		_ramBro[LADDER] = IMAGEMANAGER->findImage("rambro_ladder");
		_ramBro[FIRE] = IMAGEMANAGER->findImage("rambro_fire");
		//_ramBro[ROLL] = IMAGEMANAGER->addFrameImage("broforce_roll", "broforce_roll.bmp", 936, 136, 13, 2, true, RGB(255, 0, 255));
		_rambroGun[IDLE_GUN] = IMAGEMANAGER->findImage("rambro_idleGun");
		_rambroGun[RUN_GUN] = IMAGEMANAGER->findImage("rambro_runGun");
		//_rambroGun[FIRE_GUN] = IMAGEMANAGER->findImage("rambro_fireGun");
	}
	else
	{
		// chuck
		_ramBro[IDLE] = IMAGEMANAGER->findImage("chuck_idle");
		_ramBro[RUN] = IMAGEMANAGER->findImage("chuck_run");
		//_chuck[FAST_RUN] = IMAGEMANAGER->findImage("chuck_fast_run");
		_ramBro[JUMP] = IMAGEMANAGER->findImage("chuck_jump");
		_ramBro[HANG_FRONT_HOLD] = IMAGEMANAGER->findImage("chuck_hang_frontHold");
		_ramBro[HANG_BACK_HOLD] = IMAGEMANAGER->findImage("chuck_hang_backHold");
		_ramBro[KNIFE] = IMAGEMANAGER->findImage("chuck_knife");
		_ramBro[DIE] = IMAGEMANAGER->findImage("chuck_die");
		_ramBro[LADDER] = IMAGEMANAGER->findImage("chuck_ladder");
		_ramBro[FIRE] = IMAGEMANAGER->findImage("chuck_fire");
		//_chuck[ROLL] = IMAGEMANAGER->findImage("chuck_roll");
		_rambroGun[IDLE_GUN] = IMAGEMANAGER->findImage("chuck_idleGun");
		_rambroGun[RUN_GUN] = IMAGEMANAGER->findImage("chuck_runGun");
	}
	
	_flash = IMAGEMANAGER->findImage("rambro_flash");
	_rambroUi = IMAGEMANAGER->findImage("rambro_ui");
	_rambroUiGrenade = IMAGEMANAGER->findImage("rambro_ui_grenade");
	_rambroUiImage = IMAGEMANAGER->findImage("rambro_ui_image");
	_rambroUiImageRun = IMAGEMANAGER->findImage("rambro_ui_image_run");

	_state = IDLE;
	//if (_state == IDLE)
	//{
	//	_gun = IDLE_GUN;
	//}
	//else if  (_state == RUN)
	//{
	//	_gun = RUN_GUN;
	//}
	_gun = IDLE_GUN;

	_x = x;
	_y = y;
	_oldX = _x;
	_oldY = _y;
	_width = 60;
	_height = 76;
	_angle = 90.f *3.14 / 180;
	_speed = 5.f;
	_jumpSpeed = 0.f;
	_gravity = 0.f;
	_count = _index = 0;
	_animationSpeed = 5;
	_isActived = _isLeft = _isJump = _isFall = false;
	_isCollision = false;
	_isFlash = false;

	_rambroChange = false;

	_flashCount = _flashIndex = 0;
	_flashSpeed = 5;
	_uiCount = _uiIndex = 0;
	_uiSpeed = 5;
	_runCount, _runIndex = 0;
	_runSpeed = 5;

	_gunIndex = _gunCount = 0;
	_gunSpeed = 5;

	_rcRambro = RectMake(_x, _y, _width, _height);
	_rcFlashRight = RectMake(_x + 50, _y, 30, 30);
	_rcFlashLeft = RectMake(_x - 68, _y, 30, 30);

	//_rcMissileLeft = RectMake(1500.f, 1000.f, 100, 10);
	//_rcMissileRight = RectMake(100.f, 1000.f, 100, 10);
	_skyRightX = -100.f;
	_skyRightY = 1400.f;
	_skyRightW = 100;
	_skyRightH = 10;

	_skyLeftX = 1500.f;
	_skyLeftY = 1400.f;
	_skyLeftW = 100;
	_skyLeftH = 10;

	_rcSkyRight = RectMake(_skyRightX, _skyRightY, _skyRightW, _skyRightH);
	_rcSkyLeft = RectMake(_skyLeftX, _skyLeftY, _skyLeftW, _skyLeftH);


	skyRightX = -100.f;
	skyRightY = 600.f;

	skyLeftX = 1500.f;
	skyLeftY = 600.f;

	_skyRight = RectMake(skyRightX, skyRightY, 100, 10);
	_skyLeft = RectMake(skyLeftX, skyLeftY, 100, 10);

	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	_rcRambro = RectMake(_x, _y, _width, _height);

	_rcFlashRight = RectMake(_x + 96, _y+30, 30, 30);
	_rcFlashLeft = RectMake(_x - 68, _y, 30, 30);

	_rcSkyRight = RectMake(_skyRightX, _skyRightY, _skyRightW, _skyRightH);
	_rcSkyLeft = RectMake(_skyLeftX, _skyLeftY, _skyLeftW, _skyLeftH);

	_skyRight = RectMake(skyRightX, skyRightY, 100, 10);
	_skyLeft = RectMake(skyLeftX, skyLeftY, 100, 10);

	_gravity += 0.98f;

	if (!_isLeft)
	{

	}
	if (_state == RUN)
	{
		_gun = RUN_GUN;
	}
	if (_state == IDLE || _state == JUMP)
	{
		_gun = IDLE_GUN;
	}
	
		
	FRAMEMANAGER->frameChange(_ramBro[_state], _count, _index, _animationSpeed, _isLeft);
	FRAMEMANAGER->frameChange(_rambroGun[_gun], _gunCount, _gunIndex, _gunSpeed, _isLeft);
	
	FRAMEMANAGER->frameChange(_flash, _flashCount, _flashIndex, _flashSpeed, _isLeft);				// ÃÑ±¸ ¾Õ¿¡ ¹ÝÂ¦ÀÌ

	FRAMEMANAGER->frameChange(_rambroUi, _uiCount, _uiIndex, _uiSpeed, _isLeft);
	FRAMEMANAGER->frameChange(_rambroUiGrenade, _uiCount, _uiIndex, _uiSpeed, _isLeft);
	FRAMEMANAGER->frameChange(_rambroUiImage, _uiCount, _uiIndex, _uiSpeed, _isLeft);
	FRAMEMANAGER->frameChange(_rambroUiImageRun, _runCount, _runIndex, _runSpeed, _isLeft);

}

void player::render(void)
{
	if (_state == HANG_FRONT_HOLD)
	{
		_ramBro[_state + _isCollision]->frameRender(getMemDC(), _x-30 - CAMERAMANAGER->getCamera().left, _y-25 - CAMERAMANAGER->getCamera().top);
	}
	else
	{
		_ramBro[_state]->frameRender(getMemDC(), _x - 34 - CAMERAMANAGER->getCamera().left, _y - 25 - CAMERAMANAGER->getCamera().top);
	}
	if (_state == RUN)
	{
		if (!_isLeft)
		{
			_rambroGun[_gun]->frameRender(getMemDC(), _x + 1 - CAMERAMANAGER->getCamera().left, _y + 27 - CAMERAMANAGER->getCamera().top);
		}
		else
		{
			//_gun = RUN_GUN;
			_rambroGun[_gun]->frameRender(getMemDC(), _x - 23 - CAMERAMANAGER->getCamera().left, _y + 27 - CAMERAMANAGER->getCamera().top);
		}
	}
	else if (_state == IDLE)
	{
		if (!_isLeft)
		{
			_rambroGun[0]->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y + 30 - CAMERAMANAGER->getCamera().top);
		}
		else
		{
			_rambroGun[0]->frameRender(getMemDC(), _x - 15 - CAMERAMANAGER->getCamera().left, _y + 33 - CAMERAMANAGER->getCamera().top);
		}
	}
	else if (_state == JUMP)
	{
		if (!_isLeft)
		{
			_rambroGun[0]->frameRender(getMemDC(), _x + 7 - CAMERAMANAGER->getCamera().left, _y + 30 - CAMERAMANAGER->getCamera().top);
		}
		else
		{
			_rambroGun[0]->frameRender(getMemDC(), _x - 23 - CAMERAMANAGER->getCamera().left, _y + 30 - CAMERAMANAGER->getCamera().top);
		}
	}

	if (_isFlash)
	{
		if (!_isLeft)
		{
			_flash->frameRender(getMemDC(), _x + 40 - CAMERAMANAGER->getCamera().left, _y + 3 - CAMERAMANAGER->getCamera().top);
		}	
		else
		{
			_flash->frameRender(getMemDC(), _x - 60 - CAMERAMANAGER->getCamera().left, _y + 3 - CAMERAMANAGER->getCamera().top);
		}
	}
	
	_rambroUi->frameRender(getMemDC(), 0, 930);
	_rambroUiGrenade->frameRender(getMemDC(), 130, 955);
	
	if (_state == RUN)
	{
		_rambroUiImageRun->frameRender(getMemDC(), 0, 882);
	}
	else
	{
		_rambroUiImage->frameRender(getMemDC(), 0, 882);
	}

	//RectangleMake(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y- CAMERAMANAGER->getCamera().top, 60, 70);
}