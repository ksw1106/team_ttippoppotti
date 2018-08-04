#pragma once
#include "gameNode.h"
#include "bullet.h"  //미사일클래스 사용하기 위해

#define MAX_STATE 7

enum STATE
{
	IDLE, RUN, JUMP, 
	HANG_FRONT_HOLD, HANG_BACK_HOLD,
	KNIFE, DIE,
	FAST_RUN, ROLL
};

enum { PLAYER_LEFT, PLAYER_TOP, PLAYER_RIGHT, PLAYER_BOTTOM };

class player : public gameNode
{
private:
	image * _ramBro[MAX_STATE];
	STATE _state;
	
	float _x, _y;
	float _oldX, _oldY;
	float _angle;
	float _speed;
	float _gravity;
	float _jumpSpeed;

	int _index;
	int _count;
	int _animationSpeed;

	bool _isCollision;
	bool _isActived;
	bool _isLeft;
	bool _isJump;
	bool _isFall;
		
public:
	image * getImage(int num) { return _ramBro[num]; }

	STATE getState() { return _state; }
	void setState(STATE state) { _state = state; }

	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }
	float getOldX() { return _oldX; }
	void setOldX(float oldX) { _oldX = oldX; }
	float getOldY() { return _oldY; }
	void setOldY(float oldY) { _oldY = oldY; }
	float getAngle() { return _angle; }
	void setAngle(float angle) { _angle = angle; }
	float getSpeed() { return _speed; }
	void setSpeed(float speed) { _speed = speed; }
	float getGravity() { return _gravity; }
	void setGravity(float gravity) { _gravity = gravity; }
	float getJumpSpeed() { return _jumpSpeed; }
	void setJumpSpeed(float jumpSpeed) { _jumpSpeed = jumpSpeed; }
	
	int getIndex() { return _index; }
	void setIndex(int index) { _index = index; }
	int getCount() { return _count; }
	void setCount(int count) { _count = count; }
	int getAnimationSpeed() { return _animationSpeed; }
	void setAnimationSpeed(int animationSpeed) { _animationSpeed = animationSpeed; }

	bool getIsCollision() { return _isCollision; }
	void setIsCollision(int isCollision) { _isCollision = isCollision; }
	bool getIsActived() { return _isActived; }
	void setIsActived(int isActived) { _isActived = isActived; }
	bool getIsLeft() { return _isLeft; }
	void setIsLeft(int isLeft) { _isLeft = isLeft; }
	bool getIsJump() { return _isJump; }
	void setIsJump(int isJump) { _isJump = isJump; }
	bool getIsFall() { return _isFall; }
	void setIsFall(int isFall) { _isFall = isFall; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	player() {}
	~player() {}
};

