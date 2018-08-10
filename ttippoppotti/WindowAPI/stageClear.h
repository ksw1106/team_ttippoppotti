#pragma once
#include "gameNode.h"

class enemyManager;

struct enemyList
{
	image* image[2];
	int count;
	int index;
	int speed;
	bool isFrameImage[2];
	bool isDead;
	bool isLeft;
};

class stageClear : public gameNode
{
	enemyManager* _enemyManager;
	
	vector<enemyList> _enemyList;

	image* enemyKind[3];

	image* _clear[37];
	image* _clearBlank;
	image* _timeBoard;
	image* _enemyBoard;

	float _claerTime, _calculateTime;
	int _clearCount;
	int _imageIndex;
	int _enemyCount;
	bool _isPrintImage, _isPrintEnemy, _isPrintTime, _isCalculateTime, _isShowEnemy;
	bool _isAddEnemy;
	POINT timePos[6];
	float timeDiv[4];
	RECT _rc[2];
	float x, timeBoardX, enemyBoardX;
public:
	void setEnemyManager(enemyManager* enemyManager) { _enemyManager = enemyManager; }

	void setClearTime(float clearTime) { _claerTime = clearTime; }

	void printNumber(HDC hdc);

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	stageClear() {}
	~stageClear() {}
};

