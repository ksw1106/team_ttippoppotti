#pragma once
#include "gameNode.h"

class enemyManager;

struct enemyList
{
	image* image[2];
	float x, y;
	float oldX, oldY;
	float angle;
	float speed;
	float gravity;
	int waitTime;
	int count;
	int index;
	int animationspeed;
	bool isDead;
	bool isLeft;
	bool isCount;
	bool isSound;
};

class stageClear : public gameNode
{
	enemyManager* _enemyManager;
	
	vector<enemyList> _enemyList;

	image* enemyKind[3];

	image* _clear[37];
	image* _input[54];
	image* _clearBlank;
	image* _timeBoard;
	image* _enemyBoard;

	float _claerTime, _calculateTime;
	int _clearCount, _inputCount;
	int _imageIndex;
	int _enemyCount;
	int _currentStage;
	bool _isPrintImage, _isPrintEnemy, _isPrintTime, _isCalculateTime, _isShowEnemy, _isPrintInput, _isPrintInputBoard;
	bool _isAddEnemy;
	POINT timePos[6];
	float timeDiv[4];
	RECT _rc[2];
	float x, timeBoardX, enemyBoardX, inputBoardX;
public:
	void setEnemyManager(enemyManager* enemyManager) { _enemyManager = enemyManager; }
	void setClearTime(float clearTime) { _claerTime = clearTime; }
	void setCurrentStage(int stage) { _currentStage = stage; }
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	stageClear() {}
	~stageClear() {}
};

