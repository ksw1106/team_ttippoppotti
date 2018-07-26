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
};
//=============================================================
//	## fragments ## (��������Ʈ)
//=============================================================
class fragments : public gameNode
{
private:
	//����ü�� ���� ����, �ݺ���
	vector<tagParticle> _vFragment;

	mapdata* _mapdata;
	const char* _imageName;		//���� �̹��� �̸�(Ű��)
	int _particleMax;			//���� �ִ밹��
	float _randGravity;
	int _x, _y;				//����Ʈ ��Ʈ�� ��ġ��ǥ
	float _effectFPS;		//����Ʈ �ӵ�
	bool _isRunning;		//����Ʈ ������̳�?

public:
	HRESULT init(const char* imageName, int particleMax);
	void release(void);
	void update(void);
	void render(void);


	//����Ʈ �߻� ����
	void activate(float x, float y, float angle);
	//����Ʈ �߻�!
	void boom();

	//����Ʈ ���߱�
	void stopEffect();

	void collisionProcess();

	//����Ʈ�� ��������� ���°� ��������
	bool getIsRunning() { return _isRunning; }

	//����Ʈ���� ��������
	vector<tagParticle> getVFragment() { return _vFragment; }

	fragments() : _isRunning(false), _x(0), _y(0) {}
	~fragments() {}


};
