#pragma once
#include "singletonBase.h"
//����Ʈ Ŭ���� ���漱��(���� ������)
class effects;

class effectManager : public singletonBase <effectManager>
{
private:
	//����Ʈ Ŭ������ ���� ���� �� �ݺ���
	typedef vector<effects*> vEffect;
	typedef vector<effects*>::iterator viEffect;
	//����Ʈ�� ��Ƴ��� ���͸� ���� ��
	typedef map<string, vEffect> mEffect;
	typedef map<string, vEffect>::iterator miEffect;

private:
	mEffect _mEffect;		//����Ʈ���Ͱ� ����ִ� ��
	int _count;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//ź��
	void cartridge(float x, float y, bool isLeft);
	//��
	void bloodSplash(float x, float y, float angle);
	//����
	void rockFall(float x, float y, float angle);
	//����
	void explosion(float x, float y);
	
	//����Ʈ �߰�(����ƮŰ��, �̹���Ű��, 1ȸ�� ��°���, ���۰���)
	void addEffect(string effectName, const char* imageName, int count, int buffer, bool isFrameImg = false);
	//����Ʈ �÷���
	void playParabola(string effectName, float x, float y, float angle);

	void playExplosion(string effectName, float x, float y);
	void playBallExplosion(string effectName, float x, float y);

	void playCartridge(string effectName, float x, float y, bool isLeft);

	effectManager() {}
	~effectManager() {}
};

