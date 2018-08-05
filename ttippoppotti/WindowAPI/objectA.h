#pragma once

class playerManager;

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

//겟셋 필요한거 만들기
class objectA
{
protected:
	playerManager* _playerManager;
	OBJECT_TYPE _type;
	OBJECT_STATE _state;
	RECT _rc;
	image* _image;
	float _x, _y;
	float _destX, _destY;
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
	bool getIsFrameImage() { return _isFrameImage; }
	image* getImage() { return _image; }
	RECT getRect() { return _rc; }

	void setState(OBJECT_STATE state) { _state = state; }
	void setPosition(float x, float y) { _x = x, _y = y; }

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
private:
	void init();
	void idle();
	void move();

public:
	image * getPrisonerFreedImage() { return _prisonerFreedImage; }
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