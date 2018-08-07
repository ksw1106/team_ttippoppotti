#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "soldier.h"
#include "brovil.h"
#include "dog.h"

class playerManager;
class mapData;

class enemyManager : public gameNode
{
private:
	playerManager* _playerManager;
	mapData* _mapData;
	
	vector<enemy*> _vSoldier;	// �Ϲ� ��	
		
	eBullet* _eBullet;			// �Ѿ� Ŭ����		

public:
	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	void setMapData(mapData* mapData) { _mapData = mapData; }
	
	// ���ʹ�Ŭ���� ���� ��������
	vector<enemy*> getVEnemy() { return _vSoldier; }
	
	// �� �Ѿ�Ŭ���� �Ѿ˺��� ��������
	eBullet* getEBullet() { return _eBullet; }
		
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
		
	void enemyFire(int num);
	
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

	void enemyDie();
	
	// ���� Ŭ���� �ʱ�ȭ����
	void setSoldier(int x, int y);
	void setBrovil(int x, int y);
		
	enemyManager() {}
	~enemyManager() {}
};

