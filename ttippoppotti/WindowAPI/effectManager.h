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

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	//��
	void bloodSplash();
	//ź��
	void cartridge(float x, float y, bool isLeft);
	//����
	void rockFall();
	
	//����Ʈ �߰�(����ƮŰ��, �̹���Ű��, 1ȸ�� ��°���, ���۰���)
	void addEffect(string effectName, const char* imageName, int count, int buffer, bool isFrameImg = false);
	//����Ʈ �÷���
	void playParabola(string effectName, int x, int y, float angle);

	void playCartridge(string effectName, int x, int y, bool isLeft);

	effectManager() {}
	~effectManager() {}
};

