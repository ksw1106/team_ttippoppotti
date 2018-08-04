#pragma once

class skull;

enum OBJECT_TYPE
{
	SKULL,
	SKULL_POLE,
	SKULL_CONTAINER,
	PRISONER,
	WOODBOX,
	BOTTLEGREEN,
	BOTTLEGRAY,
	BOTTLEBROWN,
	TRUCK,
	HUMAN_DEAD, //�̰Ŷ� ������ũ�� ��Ʈ�� �ٽ� ���°�?������
	HELICOPTER,
	BOX,
	SPIKE,
	FLAG
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
	image* _objectImg[3];
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

	virtual void init() = 0;
	virtual void update();
	virtual void render();
	virtual void idle() = 0;
	virtual void move() = 0;
};

//������ �̹����� ������Ʈ���� frameChange �ϱ�
//��� ������Ʈ�� ������
//Ÿ���� false�� �Ǹ� ���� �����ֱ�
//Ÿ���� �ڽ��� ��ȯ���� �Ʒ� ��ǥ�� PtInRect�� ��� ����ɵ�?

//������ �̹����� �ƴ϶� �̹��� ����

class objectFactory
{
public:
	objectA* createObject(OBJECT_TYPE type);
};