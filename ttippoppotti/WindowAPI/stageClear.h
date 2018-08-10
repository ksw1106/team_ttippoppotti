#pragma once
#include "gameNode.h"

class stageClear : public gameNode
{
	image* _clear[37];
	image* _clearBlank;
	image* _timeBoard;
	image* _enemyBoard;

	float _claerTime, _calculateTime;
	int _clearCount;
	int _imageIndex;
	bool _isPrintImage, _isPrintEnemy, _isPrintTime, _isCalculateTime;
	
	POINT timePos[6];
	float timeDiv[4];
	RECT _rc[2];
	float x, timeBoardX, enemyBoardX;
public:
	void setClearTime(float clearTime) { _claerTime = clearTime; }

	void printNumber(HDC hdc);

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	stageClear() {}
	~stageClear() {}
};

