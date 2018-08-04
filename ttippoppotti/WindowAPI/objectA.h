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

//�ټ� �ʿ��Ѱ� �����
class objectA
{
protected:
	OBJECT_TYPE _type;
	OBJECT_STATE _state;
	image* _image[3];
	float _x, _y;
	float _oldX, _oldY;
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
	image* getImage(OBJECT_STATE state) { return _image[state]; }

	void setState(OBJECT_STATE state) { _state = state; }
	void setPosition(float x, float y) { _x = x, _y = y; }

	virtual void init() = 0;
	virtual void update();
	virtual void render(HDC hdc);
	virtual void idle() = 0;
	virtual void move() = 0;
};

//������ �̹����� ������Ʈ���� frameChange �ϱ�
//��� ������Ʈ�� ������
//Ÿ���� false�� �Ǹ� ���� �����ֱ�
//Ÿ���� �ڽ��� ��ȯ���� �Ʒ� ��ǥ�� PtInRect�� ��� ����ɵ�?

//������ �̹����� �ƴ϶� �̹��� ����

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

class objectFactory
{
public:
	objectA* createObject(OBJECT_TYPE type);
};