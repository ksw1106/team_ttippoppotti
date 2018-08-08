#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

HRESULT player::init(void)
{
	_ramBro[IDLE] = IMAGEMANAGER->findImage("broforce_idle");
	_ramBro[RUN] = IMAGEMANAGER->findImage("broforce_run (1)");
	//_ramBro[FAST_RUN] = IMAGEMANAGER->addFrameImage("broforce_run (2)", "broforce_run (2).bmp", 448, 128, 8, 2, true, RGB(255, 0, 255));
	_ramBro[JUMP] = IMAGEMANAGER->findImage("broforce_jump");
	_ramBro[HANG_FRONT_HOLD] = IMAGEMANAGER->findImage("broforce_hang_forntHold");
	_ramBro[HANG_BACK_HOLD] = IMAGEMANAGER->findImage("broforce_hang_backHold");
	_ramBro[KNIFE] = IMAGEMANAGER->findImage("broforce_knife");
	_ramBro[DIE] = IMAGEMANAGER->findImage("broforce_die");
	_ramBro[LADDER] = IMAGEMANAGER->findImage("broforce_ladder");
	_ramBro[FIRE] = IMAGEMANAGER->findImage("broforce_fire");
	//_ramBro[ROLL] = IMAGEMANAGER->addFrameImage("broforce_roll", "broforce_roll.bmp", 936, 136, 13, 2, true, RGB(255, 0, 255));

	_chuck[IDLE] = IMAGEMANAGER->findImage("chuck_idle");

	_flash = IMAGEMANAGER->findImage("broforce_flash");

	_state = IDLE;
	_x = 100.f;
	_y = 1900.f;
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

	_flashCount = _flashIndex = _flashSpeed = 0;

	_rcRambro = RectMake(_x, _y, _width, _height);
	_rcFlashRight = RectMake(_x + 50, _y, 30, 30);
	_rcFlashLeft = RectMake(_x - 68, _y, 30, 30);

	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	_rcRambro = RectMake(_x, _y, _width, _height);
	_rcFlashRight = RectMake(_x + 50, _y, 30, 30);
	_rcFlashLeft = RectMake(_x - 68, _y, 30, 30);

	_gravity += 0.98f;

	FRAMEMANAGER->frameChange(_ramBro[_state], _count, _index, _animationSpeed, _isLeft);

	//FRAMEMANAGER->frameChange(_chuck[_state], _count, _index, _animationSpeed, _isLeft);

	FRAMEMANAGER->frameChange(_flash, _flashCount, _flashIndex, _flashSpeed, _isLeft);				// ÃÑ±¸ ¾Õ¿¡ ¹ÝÂ¦ÀÌ

}

void player::render(void)
{
	if (_state == HANG_FRONT_HOLD)
		_ramBro[_state + _isCollision]->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
	else
		_ramBro[_state]->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);

	if (_isFlash)
	{
		if (_isLeft == false)
		{
			_flash->frameRender(getMemDC(), _x + 50 - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
		}	
		if (_isLeft == true)
		{
			_flash->frameRender(getMemDC(), _x - 68 - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
		}
	}
	

	//RectangleMake(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y- CAMERAMANAGER->getCamera().top, 60, 70);
}