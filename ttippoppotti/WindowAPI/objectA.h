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
	HUMAN_DEAD, //이거랑 스파이크는 세트로 다시 따는게?ㅎㅎㅎ
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

//겟셋 필요한거 만들기
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

//프레임 이미지면 업데이트에서 frameChange 하기
//모든 오브젝트를 만들자
//타겟이 false가 되면 같이 없애주기
//타겟은 자신의 소환지점 아래 좌표를 PtInRect로 계속 보면될듯?

//프레임 이미지가 아니라 이미지 한장

class objectFactory
{
public:
	objectA* createObject(OBJECT_TYPE type);
};