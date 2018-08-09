#include "stdafx.h"
#include "stageClear.h"

HRESULT stageClear::init(void)
{
	string str;

	for (int i = 0; i < 37; i++)
	{
		str = "areaClear/areaClear" + to_string(i + 1) + ".bmp";
		_clear[i] = new image;
		_clear[i]->init(str.c_str(), 813, 176, true, RGB(255, 0, 255));
	}
	_clearCount = 0;

	_clearBlank = new image;
	_clearBlank->init("areaClear/areaClearBlank.bmp", 814, 222, true, RGB(255, 0, 255));

	_rc[0] = RectMake(1920, 0, 2100, 170);
	_rc[1] = RectMake(1920, 898, 2100, 182);

	x = 1920.f;
	return S_OK;
}

void stageClear::release(void)
{
}

void stageClear::update(void)
{
	_clearCount++;
	if (_clearCount >= 37)
		_clearCount = 0;


	if (x >= 0)
	{
		x += cosf(180.f) * 150.f;
	}

	_rc[0] = RectMake(x, 0, 2000, 170);
	_rc[1] = RectMake(x, 898, 2000, 182);
}

void stageClear::render(void)
{
	SelectObject(getMemDC(), GetStockObject(DC_BRUSH));
	SetDCBrushColor(getMemDC(), RGB(0, 0, 0));
	SelectObject(getMemDC(), GetStockObject(DC_PEN));
	SetDCPenColor(getMemDC(), RGB(0, 0, 0));
	
	for (int i = 0; i < 2; i++)
	{
		RectangleMake(getMemDC(), _rc[i].left, _rc[i].top, _rc[i].right - _rc[i].left, _rc[i].bottom - _rc[i].top);
	}
	
	_clearBlank->render(getMemDC(), 593, 38);
	_clear[_clearCount]->render(getMemDC(), 593, 38);
}