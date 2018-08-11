#include "stdafx.h"
#include "CollisionManager.h"

int CollisionManager::pixelCollision(RECT rc, float& x, float& y, float speed, float gravity, int dir, bool isLadder)
{
	int _speed = (int)speed; //명시적
	int _gravity = (int)gravity; //명시적
	switch (dir)
	{
	case DIRECT_LEFT: //left
		for (int i = rc.left + _speed; i >= rc.left; i--)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(ladderPixel)->getMemDC(), i, y);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0))
			{
				return RED;
			}

			
			if ((r == 0 && g == 0 && b == 255))
			{
				if (!isLadder)
				{
					x = i + 1;
				}
				
				return BLUE;
			}
			
			color = GetPixel(IMAGEMANAGER->findImage(objectPixel)->getMemDC(), i, y);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if ((r == 0 && g == 255 && b == 0))
			{
				if (!isLadder)
				{
					x = i + 1;
				}

				return GREEN;
			}
		}
		break;
	case DIRECT_TOP: //top
		for (int i = rc.top + _speed; i >= rc.top; i--)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(ladderPixel)->getMemDC(), x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0))
			{
				return RED;
			}

			else if ((r == 0 && g == 0 && b == 255))
			{
				if (!isLadder)
				{

				}
					y = i + 1;
				return BLUE;
			}

			color = GetPixel(IMAGEMANAGER->findImage(objectPixel)->getMemDC(), x, i);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if ((r == 0 && g == 255 && b == 0))
			{
				if (!isLadder)
				{
					y = i + 1;
				}
				
				return GREEN;
			}
		}
		break;
	case DIRECT_RIGHT: //right
		for (int i = rc.right - _speed; i <= rc.right; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(ladderPixel)->getMemDC(), i, y);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0))
			{
				return RED;
			}

			else if ((r == 0 && g == 0 && b == 255))
			{
				if (!isLadder)
				{
					x = i - 1 - (rc.right - rc.left);
				}
				
				return BLUE;
			}

			color = GetPixel(IMAGEMANAGER->findImage(objectPixel)->getMemDC(), i, y);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if ((r == 0 && g == 255 && b == 0))
			{
				if (!isLadder)
				{
					x = i - 1 - (rc.right - rc.left);
				}
				
				return GREEN;
			}
		}
		break;
	case DIRECT_BOTTOM: //bottom
		for (int i = rc.bottom - (_speed + _gravity); i <= rc.bottom; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(ladderPixel)->getMemDC(), x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 255 && g == 0 && b == 0))
			{
				return RED;
			}

			else if ((r == 0 && g == 0 && b == 255))
			{
				if (!isLadder)
				{
					y = i - 1 - (rc.bottom - rc.top);
				}
				
				return BLUE;
			}

			color = GetPixel(IMAGEMANAGER->findImage(objectPixel)->getMemDC(), x, i);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if ((r == 0 && g == 255 && b == 0))
			{
				if (!isLadder)
				{
					y = i - 1 - (rc.bottom - rc.top);
				}
				
				return GREEN;
			}
		}
		break;
	}

	return FALSE;
}

HRESULT CollisionManager::init()
{
	return S_OK;
}

void CollisionManager::release()
{
}
