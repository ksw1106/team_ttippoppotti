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
	float speed;
	float angle;
	float gravity;
	float radius;
	bool fire;
	bool isActive;
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
	vector<tagParticle> _vFragment;

	mapdata* _mapdata;
	const char* _imageName;		//���� �̹��� �̸�(Ű��)
	int _particleMax;			//���� �ִ밹��
	int _x, _y;				//����Ʈ ��Ʈ�� ��ġ��ǥ
	int _falseCount;
	int _count;
	int _explosionCount;
	int _index;
	int _animationSpeed;
	float _randGravity;
	float _effectFPS;		//����Ʈ �ӵ�
	bool _isRunning;		//����Ʈ ������̳�?
	bool _isParabola;
	bool _isExplosion;
	bool _isFrameImg;		//�������̹�����?

public:
	HRESULT init(const char* imageName, int particleMax, bool isFrameImg);
	void release(void);
	void update(void);
	void render(void);

	//ź�� ����
	void activateCartridge(float x, float y, bool isLeft);

	//
	void activateBallExplosion(float x, float y);

	//������ �߻� ���� (��, ����)
	void activateParabola(float x, float y, float angle);
	//������ �߻�!
	void boomParabola();
	
	//���� ����
	void activateExplosion(float x, float y);
	//���� �߻�!
	void boomExplosion();

	//�浹ó��
	void collisionProcess();

	//
	void frameChange();

	//����Ʈ�� ��������� ���°� ��������
	bool getIsRunning() { return _isRunning; }

	//����Ʈ���� ��������
	vector<tagParticle> getVFragment() { return _vFragment; }

	effects() : _isRunning(false), _x(0), _y(0) {}
	~effects() {}


};
