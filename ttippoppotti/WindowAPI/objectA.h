#pragma once

enum OBJECT_TYPE
{
	//random
	DEADBODY,
	SKULL,
	SKULL_POLE,
	DOUBLESKULL_POLE,
	BOTTLEGREEN,
	BOTTLEGRAY,
	BOTTLEBROWN,
	//static
	WOODENBOX,
	SKULL_DRUMRED,
	SKULL_DRUMGRAY,
	PRISONER,
	TRUCK,
	HELICOPTER,
	AMFLAG_POLE,
	AMERICAN_FLAG,
	ENEMY_FLAG
};

enum OBJECT_STATE
{
	OBJECT_IDLE,
	OBJECT_MOVE,
	OBJECT_DESTROY
};

struct tagElement
{
	image* elementImg;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool fire;
	bool isActive;
	bool isFrameImg;
	int alpha;
	int count;
	int index;
};

class mapData;

//겟셋 필요한거 만들기
class objectA
{
protected:
	mapData * _mapData;
	vector<tagElement> _vElement;
	OBJECT_TYPE _type;
	OBJECT_STATE _state;
	RECT _rc;
	RECT _activationRc;
	image* _image;
	float _x, _y;
	float _destX, _destY;
	float _oldX, _oldY;
	float _speed;
	float _angle;
	float _gravity;
	bool _isStart;
	bool _isActived;
	bool* _targetIsActived;
	bool _isLeft;
	bool _isFrameImage;
	int _count, _index;
	int _animationSpeed;
	int _targetMap;
	
public:
	vector<tagElement> getVElement() { return _vElement; }
	OBJECT_TYPE getType() { return _type; }
	OBJECT_STATE getState() { return _state; }
	float getX() { return _x; }
	float getY() { return _y; }
	float getDestX() { return _destX; }
	float getDestY() { return _destY; }
	float getGravity() { return _gravity; }
	float getSpeed() { return _speed; }
	float getAngle() { return _angle; }
	bool* getTargetIsActived() { return _targetIsActived; }
	bool getIsActived() { return _isActived; }
	bool getIsStart() { return _isStart; }
	bool getIsFrameImage() { return _isFrameImage; }
	image* getImage() { return _image; }
	RECT getRect()
	{
		switch (_isFrameImage)
		{
		case TRUE:
			return RectMake(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
			break;
		default:
			return RectMake(_x, _y, _image->getWidth(), _image->getHeight());
			break;
		}
	}
	RECT getActivationRect() { return _activationRc; }

	void setMapData(mapData* mapData) { _mapData = mapData; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setState(OBJECT_STATE state) { _state = state; }
	void setPosition(float x, float y) { _x = x, _y = y; }
	void setDestPosition(float destX, float destY) { _destX = destX, _destY = destY; }
	void setAngle(float angle) { _angle = angle; }
	void setSpeed(float speed) { _speed = speed; }
	void setGravity(float gravity) { _gravity = gravity; }
	void setTargetIsActived(bool* targetIsActived) { _targetIsActived = targetIsActived; }
	void setIsActived(bool isActived) { _isActived = isActived; }
	void setIsStart(bool isStart) { _isStart = isStart; }
	void setType(OBJECT_TYPE type) { _type = type; }
	void setIndex(int index) { _index = index; }
	void setTargetMap(int targetMap) { _targetMap = targetMap; }
	virtual void init() = 0;
	virtual void update();
	virtual void render(HDC hdc);
	virtual void idle() = 0;
	virtual void move() = 0;
};

//프레임 이미지면 업데이트에서 frameChange 하기
//모든 오브젝트를 만들자
//타겟이 false가 되면 같이 없애주기
//타겟은 자신의 소환지점 아래 좌표를 PtInRect로 계속 보면될듯?

//프레임 이미지가 아니라 이미지 한장

class deadBody : public objectA
{
private:
	void init();
	void idle();
	void move();

public:
};

class skull : public objectA
{
private:
	void init();
	void idle();
	void move();

public:
};

class skullPole : public objectA
{
private:
	void init();
	void idle();
	void move();

public:
};

class doubleSkullPole : public objectA
{
private:
	void init();
	void idle();
	void move();

public:
};

class skullDrumRed : public objectA
{
private:
	void init();
	void idle();
	void move();

public:
};

class skullDrumGray : public objectA
{
private:
	void init();
	void idle();
	void move();

public:
};

class prisoner : public objectA
{
private:
	image * _prisonerFreedImage;
	image * _prisonerFreedFrameImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getPrisonerFreedImage() { return _prisonerFreedImage; }
	image * getPrisonerFreedFrameImage() { return _prisonerFreedFrameImage; }
};

class woodenBox : public objectA
{
private:
	void init();
	void idle();
	void move();

public:
};

class bottleGreen : public objectA
{
private:
	void init();
	void idle();
	void move();

public:
};

class bottleGray : public objectA
{
private:
	void init();
	void idle();
	void move();

public:
};

class bottleBrown : public objectA
{
private:
	void init();
	void idle();
	void move();

public:
};

class truck : public objectA
{
private:
	void init();
	void idle();
	void move();

public:
};

class helicopter : public objectA
{
private:
	void init();
	void idle();
	void move();

public:
};

class americanFlag : public objectA
{
private:
	void init();
	void idle();
	void move();

public:
};

class amFlagPole : public objectA
{
private:
	void init();
	void idle();
	void move();

public:
};

class enemyFlag : public objectA
{
private:
	void init();
	void idle();
	void move();

public:
};

class objectFactory
{
public:
	objectA* createObject(OBJECT_TYPE type);
};