#pragma once

enum OBJECT_TYPE
{
	SKULL,
	SPIKE,
	HELICOPTER,
	BOX,
	CAGE,
	DRUM,
	FLAG,
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

//프레임 이미지면 업데이트에서 frameChange 하기
//모든 오브젝트를 만들자
//타겟이 false가 되면 같이 없애주기
//타겟은 자신의 소환지점 아래 좌표를 PtInRect로 계속 보면될듯?

//프레임 이미지가 아니라 이미지 한장
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