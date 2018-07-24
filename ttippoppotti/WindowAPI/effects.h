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
//	## effects ## (��������Ʈ)
//=============================================================
class effects : public gameNode
{
private:
	//����ü�� ���� ����, �ݺ���
	vector<tagParticle> _vParticle;

	const char* _imageName;		//���� �̹��� �̸�(Ű��)
	int _particleMax;			//���� �ִ밹��
	float _range;

public:
	HRESULT init(const char* imageName, int particleMax);
	void release(void);
	void update(void);
	void render(void);

	//����Ʈ �߻� ����
	void activate(float x, float y, float angle, float speed, float gravity);
	//����Ʈ �߻�!
	void boom();

	//����Ʈ���� ��������
	vector<tagParticle> getVParticle() { return _vParticle; }


	////rambro ź�� �������� ȿ��
	//void rambroCatridge();

	////�� ���� �������� ȿ��
	//void rockParticleFall();

	////�������� ȿ��
	//void bloodSplash();


	effects() {}
	~effects() {}
};
