#include "stdafx.h"
#include "mapData.h"

HRESULT mapData::init(void)
{
	//1블록 + 다리
	{
		//1블록 - 1
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 76;
				obj._height = 70;
				obj._rc = RectMake(0 + j * obj._width, 2158 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//1블록 - 2
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 76;
				obj._height = 66;
				obj._rc = RectMake(0 + j * obj._width, 2298 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//1블록 - 3
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 76;
				obj._height = 68;
				obj._rc = RectMake(0 + j * obj._width, 2562 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//1블록 - 4
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 76;
				obj._height = 68;
				obj._rc = RectMake(0 + j * obj._width, 2766 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//다리
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 81;
				obj._height = 98;
				obj._rc = RectMake(912 + j * obj._width, 2138 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
	}
	
	//2블록
	{
		//2블록 - 1 왼쪽
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 82;
				obj._height = 75;
				obj._rc = RectMake(1523 + j * obj._width, 1414 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//2블록 - 1 오른쪽1
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 70;
				obj._height = 77;
				obj._rc = RectMake(1665 + j * obj._width, 1414 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}//2블록 - 1 오른쪽2
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 70;
				obj._height = 63;
				obj._rc = RectMake(1665 + j * obj._width, 1491 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//2블록 -2
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 70;
				obj._height = 68;
				obj._rc = RectMake(1665 + j * obj._width, 1617 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//2블록 -3
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 70;
				obj._height = 67;
				obj._rc = RectMake(1525 + j * obj._width, 1752 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//2블록 -4
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 70;
				obj._height = 68;
				obj._rc = RectMake(1525 + j * obj._width, 1886 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//2블록 -5
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 70;
				obj._height = 68;
				obj._rc = RectMake(1525 + j * obj._width, 1954 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//2블록 -6
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 70;
				obj._height = 68;
				obj._rc = RectMake(1525 + j * obj._width, 2022 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//2블록 -7
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 70;
				obj._height = 73;
				obj._rc = RectMake(1315 + j * obj._width, 2158 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
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