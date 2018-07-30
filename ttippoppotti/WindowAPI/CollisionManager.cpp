#include "stdafx.h"
#include "CollisionManager.h"

void CollisionManager::pixelCollision(RECT rc, int& x, int& y, int dir)
{
	switch (dir)
	{
	case 0: //left
		for (int i = rc.left + 5; i >= rc.left; i--)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("backGround_pixel")->getMemDC(), i, y);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				x = i + 1;
				break;
			}
		}
		break;
	case 1: //right
		for (int i = rc.right - 5; i <= rc.right; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("backGround_pixel")->getMemDC(), i, y);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				x = i - 1;//
				break;
			}
		}
		break;
	case 2: //top
		for (int i = rc.top + 5; i >= rc.top; i--)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("backGround_pixel")->getMemDC(), x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				y = i + 1;
				break;
			}
		}
		break;
	case 3: //bottom
		for (int i = rc.bottom - 5; i <= rc.bottom; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("backGround_pixel")->getMemDC(), x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				y = i - 1; //
				break;
			}
		}
		break;
	}
	
}
