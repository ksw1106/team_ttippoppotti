#include "stdafx.h"
#include "stageClear.h"
#include "enemyManager.h"


HRESULT stageClear::init(void)
{
	string str;

	for (int i = 0; i < 37; i++)
	{
		str = "stageClear/areaClear" + to_string(i + 1) + ".bmp";
		_clear[i] = new image;
		_clear[i]->init(str.c_str(), 813, 176, true, RGB(255, 0, 255));
	}
	_clearCount = _imageIndex = 0;

	_clearBlank = new image;
	_clearBlank->init("stageClear/areaClearBlank.bmp", 814, 222, true, RGB(255, 0, 255));

	_rc[0] = RectMake(1920, 0, 2100, 170);
	_rc[1] = RectMake(1920, 898, 2100, 182);
	_enemyBoard = new image;
	_enemyBoard->init("stageClear/enemyBoard.bmp", 1037, 282,true, RGB(255, 0, 255));
	_timeBoard = new image;
	_timeBoard->init("stageClear/timeBoard.bmp", 1038, 156, true, RGB(255, 0, 255));
	_calculateTime = 0.f;
	x = 1920.f;
	timeBoardX = 1920.f;
	enemyBoardX = 1920.f;

	_isPrintImage = _isPrintEnemy = _isPrintTime = _isCalculateTime = false;
	_isAddEnemy = _isShowEnemy = false;
	_enemyCount = 0;
	ZeroMemory(timePos, sizeof(POINT));

	timePos[0].x = 1135, timePos[0].y = 609;
	timePos[1].x = 1187, timePos[1].y = 609;
	timePos[2].x = 1263, timePos[2].y = 609;
	timePos[3].x = 1320, timePos[3].y = 609;
	timePos[4].x = 1394, timePos[4].y = 609;
	timePos[5].x = 1451, timePos[5].y = 609;

	ZeroMemory(timeDiv, sizeof(int));
	timeDiv[0] = 600;
	timeDiv[1] = 60;
	timeDiv[2] = 10;
	timeDiv[3] = 1;

	return S_OK;
}

void stageClear::release(void)
{
	for (int i = 0; i < 37; i++)
	{
		SAFE_DELETE(_clear[i]);
	}
	SAFE_DELETE(_clearBlank);
	SAFE_DELETE(_enemyBoard);
	SAFE_DELETE(_timeBoard);
}

void stageClear::update(void)
{
	if (!_isAddEnemy)
	{
		//테스트용 적 벡터 만들기(나중에 지워야함)
		for (int i = 0; i < 4; i++)
		{
			deadEnemy dEnemy;
			ZeroMemory(&dEnemy, sizeof(deadEnemy));

			dEnemy.isLeft = RND->getFromIntTo(0, 1);
			dEnemy._enemyType = SOLDIER;

			_enemyManager->addVDeadEnemyInfo(dEnemy);
		}

		for (int i = 0; i < _enemyManager->getVDeadEnemyInfo().size(); i++)
		{
			enemyList eList;
			ZeroMemory(&eList, sizeof(enemyList));
			eList.x = 1119 + i * 85;
			eList.y = 358;
			eList.oldX = eList.x;
			eList.oldY = eList.y+15;

			switch (_enemyManager->getVDeadEnemyInfo()[i]._deadType)
			{
			case SOLDIER:
				eList.image[0] = new image;
				eList.image[0]->init("stageClear/enemy/dead_soldier_idle.bmp", 68, 144, 1, 2);
				eList.image[1] = new image;
				eList.image[1]->init("stageClear/enemy/dead_soldier_dead.bmp", 90, 100, 1, 2);
				break;
			case BROVIL:
				break;
			case TERROCOPTER:
				break;
			}

			switch (_enemyManager->getVDeadEnemyInfo()[i].isLeft)
			{
			case TRUE:
				eList.isLeft = true;
				eList.angle = 80.f * 3.14 / 180;
				break;
			case FALSE:
				eList.isLeft = false;
				eList.angle = 100.f * 3.14 / 180;
				break;
			}
			
			eList.speed = 8.f;

			_enemyList.push_back(eList);
		}

		_isAddEnemy = true;
	}

	_imageIndex++;
	if (_imageIndex >= 37)
	{
		_imageIndex = 0;
	}

	if (x >= 0.f)
	{
		x += cosf(180.f) * 150.f;
	}
	
	if (x <= 0 && !_isPrintEnemy)
	{
		_clearCount++;
		if (_clearCount >= 20)
		{
			_isPrintEnemy = true;
			_clearCount = 0;
		}
	}

	if (_isPrintEnemy && enemyBoardX >= 745.f)
	{
		enemyBoardX += cosf(180.f) * 100.f;
	}
	
	if (enemyBoardX <= 745.f && !_isShowEnemy)
	{
		_clearCount++;
		if (_clearCount >= 20)
		{
			_isShowEnemy = true;
			_clearCount = 0;	
		}
	}
	
	//적 죽는표현
	if (_isShowEnemy)
	{
		if (0 == _enemyCount)
			_enemyCount++;

		for (int i = 0; i < _enemyList.size(); i++)
		{
			if (i == _enemyCount) break;

			if (_enemyList[i].isDead)
			{
				if (_enemyList[i].y <= _enemyList[i].oldY)
				{
					if (!_enemyList[i].isSound)
					{
						SOUNDMANAGER->play("soldierDead");
						SOUNDMANAGER->volumeSetting("clear", 0.2f);
						_enemyList[i].isSound = true;
					}

					_enemyList[i].gravity += 0.98f;
					_enemyList[i].x += cosf(_enemyList[i].angle) * _enemyList[i].speed/4;
					_enemyList[i].y += -sinf(_enemyList[i].angle) * _enemyList[i].speed + _enemyList[i].gravity;
				}
				else
				{
					_enemyList[i].waitTime++;
					if (_enemyList[i].waitTime >= 10)
					{
						if (!_enemyList[i].isCount)
						{
							_enemyCount++;
							_enemyList[i].isCount = true;
						}		
					}
				}
			}
			else
			{
				_enemyList[i].waitTime++;
				if (_enemyList[i].waitTime >= 10)
				{
					_enemyList[i].isDead = true;
					_enemyList[i].waitTime = 0;
				}
			}

			FRAMEMANAGER->frameChange(_enemyList[i].image[_enemyList[i].isDead], _enemyList[i].count, _enemyList[i].index, _enemyList[i].animationspeed, _enemyList[i].isLeft);
		}
	}

	//최대 크기만큼 출력 다해주고 +1 해주는 순간 들어옴
	if (_enemyCount >= _enemyList.size() && !_isPrintTime)
	{
		_clearCount++;
		if (_clearCount >= 15)
		{
			_isPrintTime = true;
			_clearCount = 0;
			SOUNDMANAGER->volumeSetting("clear", 1.0f);
		}
	}

	if (_isPrintTime && timeBoardX >= 745.f)
	{
		timeBoardX += cosf(180.f) * 100.f;
	}

	if (timeBoardX <= 745.f && !_isCalculateTime)
	{
		_clearCount++;
		if (_clearCount >= 25)
		{
			_isCalculateTime = true;
			_clearCount = 0;
		}
	}

	if (_isCalculateTime)
	{
		if(_claerTime > _calculateTime)
			_calculateTime += 0.17f;
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
	_clear[_imageIndex]->render(getMemDC(), 593, 38);

	if (_isPrintEnemy)
	{
		_enemyBoard->render(getMemDC(), enemyBoardX, 273);
	}

	if (_isPrintTime)
	{
		_timeBoard->render(getMemDC(), timeBoardX, 571);
	}

	if (_isCalculateTime)
	{
		float resultTimeFloat = _calculateTime;
		int tempTime = (int)_calculateTime;
		int resultTime = 0;
		string str;
		char ch[32];

		for (int i = 0; i < 4; i++)
		{
			if (i != 0)
			{
				resultTimeFloat -= (float)(resultTime * timeDiv[i - 1]);
				tempTime -= resultTime * timeDiv[i - 1];
			}
			
			resultTime = tempTime / timeDiv[i];
			str = to_string(resultTime);
			IMAGEMANAGER->findImage(str)->render(getMemDC(), timePos[i].x, timePos[i].y);
		}
		
		sprintf(ch, "%.2f", resultTimeFloat);

		str = ch[2];
		IMAGEMANAGER->findImage(str)->render(getMemDC(), 1394, 609);

		str = ch[3];
		IMAGEMANAGER->findImage(str)->render(getMemDC(), 1451, 609);
	}

	if (_isCalculateTime)
	{
		IMAGEMANAGER->findImage("timeDot")->render(getMemDC(), 1239, 629);
		IMAGEMANAGER->findImage("timeDot")->render(getMemDC(), 1239, 665);
		IMAGEMANAGER->findImage("timeDot")->render(getMemDC(), 1371, 665);
	}

	if (_isShowEnemy)
	{
		for (int i = 0; i < _enemyList.size(); i++)
		{
			if (i == _enemyCount) break;

			_enemyList[i].image[_enemyList[i].isDead]->frameRender(getMemDC(), _enemyList[i].x, _enemyList[i].y);
		}
	}
}

