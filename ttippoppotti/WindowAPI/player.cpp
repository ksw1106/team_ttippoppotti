#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

HRESULT player::init(void)
{
	_ramBro[IDLE] = IMAGEMANAGER->findImage("broforce_idle");
	_ramBro[RUN] = IMAGEMANAGER->findImage("broforce_run (1)");
	//_ramBro[FAST_RUN] = IMAGEMANAGER->addFrameImage("broforce_run (2)", "broforce_run (2).bmp", 448, 128, 8, 2, true, RGB(255, 0, 255));
	_ramBro[JUMP] = IMAGEMANAGER->findImage("broforce_jump");
	//_ramBro[ROLL] = IMAGEMANAGER->addFrameImage("broforce_roll", "broforce_roll.bmp", 936, 136, 13, 2, true, RGB(255, 0, 255));

	_state = IDLE;
	_x = 100.f;
	_y = 1900.f;
	_oldX = _x;
	_oldY = _y;
	_angle = 90.f *3.14 / 180;
	_speed = 0.f;
	_gravity = 0.f;
	_count = _index = 0;
	_animationSpeed = 5;
	_isActived = _isLeft = _isJump = _isFall = false;

	return S_OK;
}

void player::release(void)
{
}

void player::update(void)
{
	_gravity += 0.98f;

	FRAMEMANAGER->frameChange(_ramBro[_state], _count, _index, _animationSpeed, _isLeft);
}

void player::render(void)
{
	_ramBro[_state]->frameRender(getMemDC(), _x - CAMERAMANAGER->getCamera().left, _y - CAMERAMANAGER->getCamera().top);
}