#include "stdafx.h"
#include "mapData.h"

void mapData::deleteMap(int index)
{
	SelectObject(_backGround->getMemDC(), GetStockObject(DC_BRUSH));
	SetDCBrushColor(_backGround->getMemDC(), RGB(255, 0, 255));
	SelectObject(_backGround->getMemDC(), GetStockObject(DC_PEN));
	SetDCPenColor(_backGround->getMemDC(), RGB(255, 0, 255));
	RectangleMake(_backGround->getMemDC(), _vObject[index]._rc.left, _vObject[index]._rc.top, _vObject[index]._width, _vObject[index]._height);
	SelectObject(_pixel->getMemDC(), GetStockObject(DC_BRUSH));
	SetDCBrushColor(_pixel->getMemDC(), RGB(255, 0, 255));
	SelectObject(_pixel->getMemDC(), GetStockObject(DC_PEN));
	SetDCPenColor(_pixel->getMemDC(), RGB(255, 0, 255));
	RectangleMake(_pixel->getMemDC(), _vObject[index]._rc.left, _vObject[index]._rc.top, _vObject[index]._width, _vObject[index]._height);

	_vObject[index]._isActived = false;
}

void mapData::deleteMapIndexByIndex(int num, int index, int index2)
{
	RECT rc = _vObject[num]._rc;
	POINT pt, tempPt;

	int iIndex = -(index / 2);
	int iIndex2 = (index / 2) + 1;
	int jIndex = -(index2 / 2);
	int jIndex2 = (index2 / 2) + 1;

	pt.x = rc.left + (rc.right - rc.left) / 2;
	pt.y = rc.top + (rc.bottom - rc.top) / 2;

	SelectObject(_backGround->getMemDC(), GetStockObject(DC_BRUSH));
	SetDCBrushColor(_backGround->getMemDC(), RGB(255, 0, 255));
	SelectObject(_backGround->getMemDC(), GetStockObject(DC_PEN));
	SetDCPenColor(_backGround->getMemDC(), RGB(255, 0, 255));
	
	SelectObject(_pixel->getMemDC(), GetStockObject(DC_BRUSH));
	SetDCBrushColor(_pixel->getMemDC(), RGB(255, 0, 255));
	SelectObject(_pixel->getMemDC(), GetStockObject(DC_PEN));
	SetDCPenColor(_pixel->getMemDC(), RGB(255, 0, 255));

	for (int i = iIndex; i < iIndex2; i++)
	{
		for (int j = jIndex; j < jIndex2; j++)
		{
			tempPt.x = pt.x + j * 68;
			tempPt.y = pt.y + i * 68;

			for (int k = 0; k < _vObject.size(); k++)
			{
				if (!_vObject[k]._isActived) continue;

				if (PtInRect(&_vObject[k]._rc, tempPt))
				{
					RectangleMake(_backGround->getMemDC(), _vObject[k]._rc.left, _vObject[k]._rc.top, _vObject[k]._width, _vObject[k]._height);
					RectangleMake(_pixel->getMemDC(), _vObject[k]._rc.left, _vObject[k]._rc.top, _vObject[k]._width, _vObject[k]._height);
					_vObject[k]._isActived = false;
					break;
				}
			}
		}
	}
}

void mapData::stage1_setting()
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
				obj._rc = RectMake(4092 + j * obj._width, 1358 + i * obj._height, obj._width, obj._height);
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
		//3블록 -9 왼쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 68;
				obj._rc = RectMake(2937 + j * obj._width, 1761 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -9 오른쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 68;
				obj._rc = RectMake(3613 + j * obj._width, 1761 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -10 왼쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 68;
				obj._rc = RectMake(3006 + j * obj._width, 1829 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -10 오른쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 68;
				obj._rc = RectMake(3613 + j * obj._width, 1829 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -11 왼쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 68;
				obj._rc = RectMake(3144 + j * obj._width, 1897 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -11 오른쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 68;
				obj._rc = RectMake(3613 + j * obj._width, 1897 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -12 왼쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 68;
				obj._rc = RectMake(3213 + j * obj._width, 1965 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -12 오른쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 68;
				obj._rc = RectMake(3820 + j * obj._width, 1965 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -13 왼쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 68;
				obj._rc = RectMake(3213 + j * obj._width, 2033 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -13 오른쪽
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 68;
				obj._rc = RectMake(3820 + j * obj._width, 2033 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//나무
		//3블록 -14, 15 오른쪽
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 69;
				obj._height = 67;
				obj._rc = RectMake(3820 + j * obj._width, 2101 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -16
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 68;
				obj._rc = RectMake(2871 + j * obj._width, 2235 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -17, 18
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 68;
				obj._rc = RectMake(2871 + j * obj._width, 2303 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -19
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 18; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 68;
				obj._rc = RectMake(2871 + j * obj._width, 2439 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -20
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 17; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 68;
				obj._rc = RectMake(2871 + j * obj._width, 2507 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -21
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 17; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 68;
				obj._rc = RectMake(2803 + j * obj._width, 2575 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -22
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 68;
				obj._rc = RectMake(2667 + j * obj._width, 2643 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
		//3블록 -23
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				mapObject obj;
				ZeroMemory(&obj, sizeof(mapObject));
				obj._width = 68;
				obj._height = 68;
				obj._rc = RectMake(2599 + j * obj._width, 2779 + i * obj._height, obj._width, obj._height);
				obj._isActived = true;
				_vObject.push_back(obj);
			}
		}
	}
}

void mapData::stage2_setting()
{
	//=============================================================
	//	## 2스테이지
	//=============================================================

	//1블록 -1 왼쪽 다리
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 96;
			obj._rc = RectMake(-36 + j * obj._width, 1480 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//1블록 -1
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 72;
			obj._rc = RectMake(168 + j * obj._width, 1505 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//1블록 -2
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(168 + j * obj._width, 1577 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	//1블록 -3
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(168 + j * obj._width, 1645 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	//1블록 -4, 5
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(236 + j * obj._width, 1713 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	//1블록 -6
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(236 + j * obj._width, 1849 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	//1블록 -7. 8
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(168 + j * obj._width, 1917 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	//1블록 -9, 10, 11, 12
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(168 + j * obj._width, 2053 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	//1블록 -13
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(100 + j * obj._width, 2325 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	//1블록 -13
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(100 + j * obj._width, 2393 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	//1블록 -1 오른쪽 다리
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 67;
			obj._height = 97;
			obj._rc = RectMake(644 + j * obj._width, 1480 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	//2블록 -1
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 72;
			obj._rc = RectMake(979 + j * obj._width, 1505 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//2블록 -2
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(979 + j * obj._width, 1577 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//2블록 -3
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(1047 + j * obj._width, 1645 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//2블록 -4, 5, 6, 7
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(1115 + j * obj._width, 1713 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//2블록 -8, 9, 10, 11
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(1251 + j * obj._width, 1985 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//2블록 -12
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(1319 + j * obj._width, 2257 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//2블록 -13
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(1455 + j * obj._width, 2325 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//2블록 -14
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(1659 + j * obj._width, 1645 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	//3블록 -1
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 69;
			obj._height = 73;
			obj._rc = RectMake(1721 + j * obj._width, 624 + i * obj._height, obj._width, obj._height);
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
			obj._width = 67;
			obj._height = 98;
			obj._rc = RectMake(1658 + j * obj._width, 871 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록 -2 사다리 왼쪽
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 70;
			obj._height = 73;
			obj._rc = RectMake(1725 + j * obj._width, 896 + i * obj._height, obj._width, obj._height);
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
			obj._height = 73;
			obj._rc = RectMake(1925 + j * obj._width, 896 + i * obj._height, obj._width, obj._height);
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
			obj._width = 70;
			obj._height = 98;
			obj._rc = RectMake(2265 + j * obj._width, 871 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	//3블록 -3
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 70;
			obj._height = 72;
			obj._rc = RectMake(1721 + j * obj._width, 1104 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록 -4
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 70;
			obj._height = 70;
			obj._rc = RectMake(1721 + j * obj._width, 1176 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록 -4 오른쪽
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 73;
			obj._height = 73;
			obj._rc = RectMake(2126 + j * obj._width, 1104 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	//3블록 -5
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 73;
			obj._rc = RectMake(1530 + j * obj._width, 1370 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	//3블록 -5 오른쪽
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 70;
			obj._rc = RectMake(1795 + j * obj._width, 1370 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	
	//3블록 -6
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 73;
			obj._rc = RectMake(1598 + j * obj._width, 1443 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록 -7
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(1931 + j * obj._width, 1509 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록 -8
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(1931 + j * obj._width, 1849 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	//3블록 -5 맨 오른쪽
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 70;
			obj._rc = RectMake(2543 + j * obj._width, 1370 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록 -7
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(2543 + j * obj._width, 1577 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록 -8
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(2543 + j * obj._width, 1645 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록 -9
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(2543 + j * obj._width, 1781 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록 -10 사다리 왼쪽
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(2475 + j * obj._width, 1985 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록 -10 사다리 오른쪽
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(2815 + j * obj._width, 1985 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록 -11
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(2475 + j * obj._width, 2053 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록 -12
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(2475 + j * obj._width, 2189 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 72;
			obj._rc = RectMake(2746 + j * obj._width, 1370 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(2882 + j * obj._width, 1577 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 72;
			obj._rc = RectMake(3358 + j * obj._width, 1370 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(3358 + j * obj._width, 1441 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(3154 + j * obj._width, 1645 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(3426 + j * obj._width, 1848 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}

	//3블록
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(3290 + j * obj._width, 1984 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(3290 + j * obj._width, 2324 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(3290 + j * obj._width, 2392 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(3290 + j * obj._width, 2596 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 70;
			obj._height = 73;
			obj._rc = RectMake(3693 + j * obj._width, 752 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 70;
			obj._height = 73;
			obj._rc = RectMake(4032 + j * obj._width, 752 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 73;
			obj._height = 73;
			obj._rc = RectMake(3693 + j * obj._width, 955 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 70;
			obj._height = 73;
			obj._rc = RectMake(3895 + j * obj._width, 955 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 70;
			obj._height = 73;
			obj._rc = RectMake(4035 + j * obj._width, 1028 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 70;
			obj._rc = RectMake(3698 + j * obj._width, 1230 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 70;
			obj._rc = RectMake(3630 + j * obj._width, 1300 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 70;
			obj._rc = RectMake(4038 + j * obj._width, 1230 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 70;
			obj._rc = RectMake(4038 + j * obj._width, 1300 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 72;
			obj._rc = RectMake(3630 + j * obj._width, 1370 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(3630 + j * obj._width, 1441 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 72;
			obj._rc = RectMake(4106 + j * obj._width, 1370 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(4106 + j * obj._width, 1441 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(3630 + j * obj._width, 1509 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(3630 + j * obj._width, 1645 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(3630 + j * obj._width, 1848 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(3630 + j * obj._width, 1984 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(3630 + j * obj._width, 2120 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(4038 + j * obj._width, 2120 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(4106 + j * obj._width, 2324 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(4106 + j * obj._width, 2392 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
	//3블록
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			mapObject obj;
			ZeroMemory(&obj, sizeof(mapObject));
			obj._width = 68;
			obj._height = 68;
			obj._rc = RectMake(4174 + j * obj._width, 2460 + i * obj._height, obj._width, obj._height);
			obj._isActived = true;
			_vObject.push_back(obj);
		}
	}
}

HRESULT mapData::init(int stage)
{
	//=============================================================
	//	## 1스테이지
	//=============================================================
	switch (stage)
	{
	case 1:
		stage1_setting();
		break;
	case 2:
		stage2_setting();
		break;
	default:
		//에러
		break;
	}

	return S_OK;
}

void mapData::release(void)
{
	_vObject.clear();
}

void mapData::update(void)
{
}

void mapData::render(void)
{
}