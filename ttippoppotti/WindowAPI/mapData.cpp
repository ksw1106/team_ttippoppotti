#include "stdafx.h"
#include "mapData.h"

HRESULT mapData::init(void)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 76;
			obj._height = 70;
			obj._rc = RectMake(0+j*76, 2158+i*70, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	return S_OK;
}

void mapData::release(void)
{
}

void mapData::update(void)
{

}

void mapData::render(void)
{
	
}
