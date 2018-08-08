#pragma once
#include "gameNode.h"
#include "bullet.h"  //미사일클래스 사용하기 위해

#define MAX_STATE 9
#define MAX_STATE1 1

enum STATE
{
	IDLE, RUN, JUMP, 
	HANG_FRONT_HOLD, HANG_BACK_HOLD,
	KNIFE, DIE, LADDER, FIRE,
	FAST_RUN, ROLL
};

enum { PLAYER_LEFT, PLAYER_TOP, PLAYER_RIGHT, PLAYER_BOTTOM };

class player : public gameNode
{
private:
	image * _ramBro[MAX_STATE];
	image * _chuck[MAX_STATE1];
	image * _flash;
	STATE _state;
	RECT _rcRambro;
	
	float _x, _y;
	float _oldX, _oldY;
	float _width;
	float _height;
	float _angle;
	float _speed;
	float _gravity;
	float _jumpSpeed;

	int _index;
	int _count;
	int _animationSpeed;

	int _flashIndex;
	int _flashCount;
	int _flashSpeed;

	bool _isCollision;
	bool _isActived;
	bool _isLeft;
	bool _isJump;
	bool _isFall;
	bool _isKnife;

	bool _isFlash;

	RECT _rcFlashRight;
	RECT _rcFlashLeft;
		
public:
	image * getImage(int num) { return _ramBro[num]; }

	STATE getState() { return _state; }
	void setState(STATE state) { _state = state; }

	RECT getRcRambro() { return _rcRambro; }
	void setRcRambro(RECT rcRambro) { _rcRambro = rcRambro; }

	RECT getrcFlashRight() { return _rcFlashRight; }
	void setrcFlashRight(RECT rcFlashRight) { _rcFlashRight = rcFlashRight; }
	RECT getrcFlashLeft() { return _rcFlashLeft; }
	void setrcFlashLeft(RECT rcFlashLeft) { _rcFlashLeft = rcFlashLeft; }

	

	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }
	float getOldX() { return _oldX; }
	void setOldX(float oldX) { _oldX = oldX; }
	float getOldY() { return _oldY; }
	void setOldY(float oldY) { _oldY = oldY; }
	float getWidth() { return _width; }
	void setWidth(float width) { _width = width; }
	float getHeight() { return _height; }
	void setHeight(float height) { _height = height; }
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
	void setIsCollision(bool isCollision) { _isCollision = isCollision; }
	bool getIsActived() { return _isActived; }
	void setIsActived(bool isActived) { _isActived = isActived; }
	bool getIsLeft() { return _isLeft; }
	void setIsLeft(bool isLeft) { _isLeft = isLeft; }
	bool getIsJump() { return _isJump; }
	void setIsJump(bool isJump) { _isJump = isJump; }
	bool getIsFall() { return _isFall; }
	void setIsFall(bool isFall) { _isFall = isFall; }
	bool getIsKnife() { return _isKnife; }
	void setIsKnife(bool isKnife) { _isKnife = isKnife; }
	bool getIsFlash() { return _isFlash; }
	void setIsFlash(bool isFlash) { _isFlash = isFlash; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	player() {}
	~player() {}
};

