#pragma once
#include "gameNode.h"

class mapdata;

//���� ����ü
struct tagParticle
{
	image* particleImg;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float oldX, oldY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool fire;
	bool isActive;
	bool isFrameImg;
	bool isAlphaImg;
	int alpha;
	int count;
	int index;
};
//=============================================================
//	## effects ## (��������Ʈ)
//=============================================================
class effects : public gameNode
{
private:
	//����ü�� ���� ����, �ݺ���
	vector<tagParticle> _vParticle;

	mapdata* _mapdata;
	const char* _imageName;		//���� �̹��� �̸�(Ű��)
	int _particleMax;			//���� �ִ밹��
	int _x, _y;				//����Ʈ ��Ʈ�� ��ġ��ǥ
	int _falseCount;
	int _alpha;
	int _count;
	int _explosionCount;
	int _bigBangCount;
	int _index;
	int _animationSpeed;
	float _range;
	float _effectFPS;		//����Ʈ �ӵ�
	bool _isRunning;		//����Ʈ ������̳�?
	bool _isParabola;
	bool _isParabolaNoCollision;
	bool _isLeft;
	bool _isExplosion;
	bool _isStaticAnim;
	bool _isFlyingFlies;
	bool _isAshes;
	bool _isBigBang;
	bool _isMissileTrail;
	bool _isMissilePuff;
	bool _isFrameImg;		//�������̹�����?
	bool _isAlphaImg;		//�����̹�����?


public:
	HRESULT init(const char* imageName, int particleMax = 0, bool isFrameImg = false);
	void release(void);
	void update(void);
	void render(void);

	//ź�� ����
	void activateCartridge(float x, float y, bool isLeft);
	//�߾�����
	void activateBallExplosion(float x, float y);
	//������ �߻� ���� (��, ����, ��������)
	void activateParabola(float x, float y, bool isLeft);
	void activateParabolaNoCollision(float x, float y, bool isLeft);
	void boomParabola();
	void boomParabolaNoCollision();
	//�м�
	void activateFountain(float x, float y);
	void activateFountainNoCollision(float x, float y);

	void activateFall(float x, float y);
	//���ڱ�
	void activateBlotch(float x, float y);
	void boomBlotch();
	//�ĸ�����
	void activateFlyingFlies(float x, float y);
	void boomFlyingFlies();
	//�簡 �Ǿ� ���ư���
	void activateAshes(float x, float y);
	void boomAshes();
	//���� ����
	void activateExplosion(float x, float y);
	void boomExplosion();
	//��ǳ��
	void activateLoopAnim(float x, float y);
	//���׶�� ����Ʈ
	void activateEllipsePuff(float x, float y);
	void activateEllipsePuff(float x, float y, bool isLeft);
	//������ ����
	void activateBigBang(float x, float y);
	void boomBigBang();

	//�̻���
	void activateMissileTrail(float x, float y, bool isLeft);
	void boomMissileTrail();
	void activateMissilePuff(float x, float y, int speed, bool isLeft);
	void boomMissilePuff();

	void boomStaticAnim();

	//�浹ó��
	void collisionProcess();
	//�ִϸ��̼�
	void frameChange();

	//����Ʈ�� ��������� ���°� ��������
	bool getIsRunning() { return _isRunning; }

	//����Ʈ���� ��������
	vector<tagParticle> getVParticle() { return _vParticle; }

	effects() : _isRunning(false), _x(0), _y(0) {}
	~effects() {}


};