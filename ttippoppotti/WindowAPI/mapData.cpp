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
//2블록 -8
for (int i = 0; i < 1; i++)
{
	for (int j = 0; j < 17; j++)
	{
		mapObject obj;
		ZeroMemory(&obj, sizeof(mapObject));
		obj._width = 70;
		obj._height = 73;
		obj._rc = RectMake(1315 + j * obj._width, 2231 + i * obj._height, obj._width, obj._height);
		obj._isActived = true;
		_vObject.push_back(obj);
	}
}
//2블록 -9
for (int i = 0; i < 1; i++)
{
	for (int j = 0; j < 16; j++)
	{
		mapObject obj;
		ZeroMemory(&obj, sizeof(mapObject));
		obj._width = 70;
		obj._height = 73;
		obj._rc = RectMake(1315 + j * obj._width, 2304 + i * obj._height, obj._width, obj._height);
		obj._isActived = true;
		_vObject.push_back(obj);
	}
}
//2블록 -10
for (int i = 0; i < 2; i++)
{
	for (int j = 0; j < 15; j++)
	{
		mapObject obj;
		ZeroMemory(&obj, sizeof(mapObject));
		obj._width = 70;
		obj._height = 73;
		obj._rc = RectMake(1315 + j * obj._width, 2377 + i * obj._height, obj._width, obj._height);
		obj._isActived = true;
		_vObject.push_back(obj);
	}
}
//2블록 -11
for (int i = 0; i < 5; i++)
{
	for (int j = 0; j < 14; j++)
	{
		mapObject obj;
		ZeroMemory(&obj, sizeof(mapObject));
		obj._width = 70;
		obj._height = 73;
		obj._rc = RectMake(1315 + j * obj._width, 2523 + i * obj._height, obj._width, obj._height);
		obj._isActived = true;
		_vObject.push_back(obj);
	}
}
	}

	//3블록
	{
		//3블록 -1
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 77;
				obj._rc = RectMake(2869 + j * obj._width, 1079 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -1 깃발
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 70;
				obj._height = 77;
				obj._rc = RectMake(3345 + j * obj._width, 1079 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -1 다리
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 102;
				obj._rc = RectMake(3484 + j * obj._width, 1054 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -1 다리 오른쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 67;
				obj._height = 77;
				obj._rc = RectMake(3687 + j * obj._width, 1079 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -1 사다리 오른쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 73;
				obj._height = 77;
				obj._rc = RectMake(4087 + j * obj._width, 1079 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -2 왼쪽 다리
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 102;
				obj._rc = RectMake(2807 + j * obj._width, 1257 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -2 사다리 왼쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 77;
				obj._rc = RectMake(2875 + j * obj._width, 1281 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -2 사다리 오른쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 78;
				obj._rc = RectMake(3140 + j * obj._width, 1281 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -2 다리
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 102;
				obj._rc = RectMake(3480 + j * obj._width, 1257 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -2 다리 오른쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 78;
				obj._rc = RectMake(3687 + j * obj._width, 1281 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -2 오른쪽 다리
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 102;
				obj._rc = RectMake(4231 + j * obj._width, 1257 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -3 왼쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 64;
				obj._rc = RectMake(2875 + j * obj._width, 1358 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -3 오른쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 70;
				obj._height = 64;
				obj._rc = RectMake(4092+ j * obj._width, 1358 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -4 왼쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 73;
				obj._height = 69;
				obj._rc = RectMake(2937 + j * obj._width, 1421 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -4 오른쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 73;
				obj._height = 69;
				obj._rc = RectMake(4092 + j * obj._width, 1421 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -5 왼쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 73;
				obj._height = 69;
				obj._rc = RectMake(2937 + j * obj._width, 1489 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -5 다리 왼쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 74;
				obj._rc = RectMake(3139 + j * obj._width, 1484 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -5 다리
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 102;
				obj._rc = RectMake(3483 + j * obj._width, 1460 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -5 다리 오른쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 70;
				obj._height = 78;
				obj._rc = RectMake(3687 + j * obj._width, 1484 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -5 오른쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 76;
				obj._rc = RectMake(3884 + j * obj._width, 1484 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -5 오른쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 73;
				obj._height = 72;
				obj._rc = RectMake(4091 + j * obj._width, 1488 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -6,7 왼쪽
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 73;
				obj._height = 68;
				obj._rc = RectMake(2937 + j * obj._width, 1557 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -6,7 중앙`	
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 73;
				obj._height = 68;
				obj._rc = RectMake(3415 + j * obj._width, 1557 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -6,7 중앙
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 73;
				obj._height = 68;
				obj._rc = RectMake(4091 + j * obj._width, 1559 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -8 왼쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 68;
				obj._rc = RectMake(2937 + j * obj._width, 1693 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}

		//3블록 -8 오른쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 68;
				obj._rc = RectMake(3613 + j * obj._width, 1693 + i * obj._height, obj._width, obj._height);
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