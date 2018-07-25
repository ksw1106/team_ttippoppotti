#pragma once
#include "gameNode.h"


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

	const char* _imageName;		//���� �̹��� �̸�(Ű��)
	int _particleMax;			//���� �ִ밹��
	float _randGravity;

public:
	HRESULT init(const char* imageName, int particleMax);
	void release(void);
	void update(void);
	void render(void);

	//����Ʈ �߻� ����
	void activate(float x, float y, float angle);
	//����Ʈ �߻�!
	void boom(float gravity);

	void collisionProcess();

	//����Ʈ���� ��������
	vector<tagParticle> getVFragment() { return _vFragment; }


	fragments() {}
	~fragments() {}
};
