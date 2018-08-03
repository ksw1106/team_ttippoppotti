#pragma once

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
	HUMAN_DEAD,
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