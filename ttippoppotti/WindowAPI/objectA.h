#pragma once

//class skull;

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
	PRISONER,
	WOODENBOX,
	SKULL_DRUMRED,
	SKULL_DRUMGRAY,
	TRUCK,
	HELICOPTER,
	AMERICAN_FLAG
};

enum OBJECT_STATE
{
	OBJECT_IDLE,
	OBJECT_MOVE,
	OBJECT_DESTROY
};

//겟셋 필요한거 만들기
class objectA
{
protected:
	OBJECT_TYPE _type;
	OBJECT_STATE _state;
	float _x, _y;
	float _speed;
	float _angle;
	bool _isActived;
	bool* _targetIsActived;
	int _count, _index;
	int _animationSpeed;
	bool _isLeft;
	bool _isFrameImage;
public:
	OBJECT_TYPE getType() { return _type; }
	OBJECT_STATE getState() { return _state; }

	void setState(OBJECT_STATE state) { _state = state; }
	void setPosition(float x, float y) { _x = x, _y = y; }

	virtual void init() = 0;
	virtual void update();
	virtual void render();
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
	image * _deadBodyImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getDeadBodyImage() { return _deadBodyImage; }
};

class skull : public objectA
{
private:
	image * _skullImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getSkullImage() { return _skullImage; }
};

class skullPole : public objectA
{
private:
	image * _skullPoleImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getSkullPoleImage() { return _skullPoleImage; }
};

class doubleSkullPole : public objectA
{
private:
	image * _doubleSkullPoleImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getDoubleSkullPoleImage() { return _doubleSkullPoleImage; }
};

class skullDrumRed : public objectA
{
private:
	image * _skullDrumRedImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getSkullDrumRedImage() { return _skullDrumRedImage; }
};

class skullDrumGray : public objectA
{
private:
	image * _skullDrumGrayImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getSkullDrumGrayImage() { return _skullDrumGrayImage; }
};

class prisoner : public objectA
{
private:
	image * _prisonerImage[2];
private:
	void init();
	void idle();
	void move();

public:
	image * getPrisonerImage(int state) { return _prisonerImage[state]; }
};

class woodenBox : public objectA
{
private:
	image * _woodenBoxImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getWoodenBoxImage() { return _woodenBoxImage; }
};

class bottleGreen : public objectA
{
private:
	image * _bottleGreenImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getBottleGreenImage() { return _bottleGreenImage; }
};

class bottleGray : public objectA
{
private:
	image * _bottleGrayImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getBottleGrayImage() { return _bottleGrayImage; }
};

class bottleBrown : public objectA
{
private:
	image * _bottleBrownImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getBottleBrownImage() { return _bottleBrownImage; }
};

class truck : public objectA
{
private:
	image * _truckImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getTruckImage() { return _truckImage; }
};

class helicopter : public objectA
{
private:
	image * _helicopterImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getHelicopterImage() { return _helicopterImage; }
};
class americanFlag : public objectA
{
private:
	image * _americanFlagImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getAmericanFlagImage() { return _americanFlagImage; }
};

class objectFactory
{
public:
	objectA* createObject(OBJECT_TYPE type);
};