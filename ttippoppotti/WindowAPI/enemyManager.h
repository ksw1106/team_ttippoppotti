#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "soldier.h"
#include "brovil.h"
#include "dog.h"
#include "boss.h"

class playerManager;
class mapData;

class enemyManager : public gameNode
{
private:
	playerManager* _playerManager;
	mapData* _mapData;
	
	vector<enemy*> _vSoldier;	// �Ϲ� ��	
		
	eBullet* _eBullet;			// �Ѿ� Ŭ����
	bossBullet* _bossBullet;	// �����Ѿ� Ŭ����
	bossRocket* _bossRocket;	// �������� Ŭ����
	boss* _boss;				// ���� Ŭ����
	brovil* _brovil;			// ��κ� Ŭ����

public:
	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	void setMapData(mapData* mapData) { _mapData = mapData; }
	
	// ���ʹ�Ŭ���� ���� ��������
	vector<enemy*> getVEnemy() { return _vSoldier; }
	
	// �� �Ѿ�Ŭ���� ��������
	eBullet* getEBullet() { return _eBullet; }

	// ���� Ŭ���� ��������
	boss* getBoss() { return _boss; }	
		
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
		
	void enemyFire(int num);
	// ���� �Ѿ�,���� �߻�
	void bossFire();
	
	// ��Ÿ �浹�Լ�
	void collideWithPixel();
	// ��ü�� �ȼ� �浹
	void collideWithCorpse();
	// ���ʹ� �þ� vs �÷��̾� �浹
	void collideWithSight();
	// ���ʹ� �Ѿ� vs �÷��̾� �浹
	void collideWithPlayer();
	// �÷��̾� �Ѿ˰� �浹�Լ�
	void collideWithPBullet();	
	// �÷��̾� ����ź�� �浹�Լ�
	void collideWithPGrenade();		
	// ���ʹ� �Ѿ� vs �ȼ�
	void collideBulletWithPixel();
	// ��κ��� �÷��̾� �Ѿ� �浹
	void collideBrovilwithPBullet();

	void enemyDie();
	
	// ���� Ŭ���� �ʱ�ȭ����
	void setSoldier(int x, int y);
	void setBrovil(int x, int y);
		
	enemyManager() {}
	~enemyManager() {}
};

