#pragma once

enum OBJECT_TYPE
{
	SPIKE,
	SKULL,
	SKULL_POLE,
	DOUBLESKULL_POLE,
	SKULL_DRUM,
	PRISONER,
	WOODENBOX,
	BOTTLEGREEN,
	BOTTLEGRAY,
	BOTTLEBROWN,
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
	virtual void init() = 0;
	virtual void update();
	virtual void idle() = 0;
	virtual void move() = 0;
};

//������ �̹����� ������Ʈ���� frameChange �ϱ�
//��� ������Ʈ�� ������
//Ÿ���� false�� �Ǹ� ���� �����ֱ�
//Ÿ���� �ڽ��� ��ȯ���� �Ʒ� ��ǥ�� PtInRect�� ��� ����ɵ�?

//������ �̹����� �ƴ϶� �̹��� ����
class spike : public objectA
{
private:
	image* _humanDeadImage;
	image* _spikeImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getHumanDeadImage() { return _humanDeadImage; }
	image* getSpikeImage() { return _spikeImage; }
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

class skullDrum : public objectA
{
private:
	image * _skullDrumImage;
private:
	void init();
	void idle();
	void move();

public:
	image * getSkullDrumImage() { return _skullDrumImage; }
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

class factory
{
public:
	virtual objectA* createObject(OBJECT_TYPE) = 0;
};

class objectFactory : public factory
{
public:
	objectA * createObject(OBJECT_TYPE type);
};