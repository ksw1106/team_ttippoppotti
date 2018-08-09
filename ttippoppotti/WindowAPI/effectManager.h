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
	float _x, _y;
	bool _isExplosion;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//ź��
	void cartridge(float x, float y, bool isLeft);
	//��
	void bloodSplash(float x, float y);
	//����
	void rockFall(float x, float y);
	//��������
	void woodDebris(float x, float y);
	//����ũ Ʀ
	void yellowSparks(float x, float y);
	//��� ���Ͽ� ���ư��ϴ�
	void ashes(float x, float y);
	//�Ѿ�����Ʈ
	void bulletPuff(float x, float y);
	//Į ����Ʈ
	void knifePuff(float x, float y, bool isLeft);
	//�ĸ�����
	void flyingFlies(float x, float y);
	//���ϴ� ��ǳ��
	void saveBubble(float x, float y);
	//����
	void explosion(float x, float y);
	//���� �ʱ�ȭ
	void explosionStart(float x, float y);
	
	//����Ʈ �߰�(����ƮŰ��, �̹���Ű��, 1ȸ�� ��°���, ���۰���, �ִϸ��̼��̳�?)
	void addEffect(string effectName, const char* imageName, int buffer, int count = 1, bool isFrameImg = false);
	//����Ʈ �÷���
	void playParabola(string effectName, float x, float y);
	void playExplosion(string effectName, float x, float y);
	void playBallExplosion(string effectName, float x, float y);
	void playCartridge(string effectName, float x, float y, bool isLeft);
	void playBulletPuff(string effectName, float x, float y);
	void playKnifePuff(string effectName, float x, float y, bool isLeft);
	void playLoopAnim(string effectName, float x, float y);
	void playFlyingFlies(string effectName, float x, float y);
	void playAshes(string effectName, float x, float y);
	effectManager() {}
	~effectManager() {}
};

