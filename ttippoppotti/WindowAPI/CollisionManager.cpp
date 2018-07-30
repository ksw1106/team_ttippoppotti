#include "stdafx.h"
#include "CollisionManager.h"

bool CollisionManager::pixelCollision(image* img, float& x, float& y, float speed, float gravity, int dir)
{
	RECT _rc = img->boudingBoxWithFrame();
	int _speed = (int)speed; //명시적
	int _gravity = (int)gravity; //명시적
	switch (dir)
	{
	case DIRECT_LEFT: //left
		for (int i = _rc.left + _speed; i >= _rc.left; i--)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("backGround_pixel")->getMemDC(), i, y);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				x = i + 1;
				return true;
			}
		}
		break;
	case DIRECT_TOP: //top
		for (int i = _rc.top + _speed; i >= _rc.top; i--)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("backGround_pixel")->getMemDC(), x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				y = i + 1;
				return true;
			}
		}
		break;
	case DIRECT_RIGHT: //right
		for (int i = _rc.right - _speed; i <= _rc.right; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("backGround_pixel")->getMemDC(), i, y);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				x = i - 1 - img->getFrameWidth();//
				return true;
			}
		}
		break;
	case DIRECT_BOTTOM: //bottom
		for (int i = _rc.bottom - (_speed + _gravity); i <= _rc.bottom; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("backGround_pixel")->getMemDC(), x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				y = i - 1 - img->getFrameHeight(); //
				return true;
			}
		}
		break;
	}

	return false;
}


HRESULT CollisionManager::init()
{
	return S_OK;
}

void CollisionManager::release()
{
}
