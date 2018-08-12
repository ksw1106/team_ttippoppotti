#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "soldier.h"
#include "brovil.h"
#include "dog.h"
#include "boss.h"
#include "progressBar.h"

enum enemyType
{
	SOLDIER, BROVIL, DOG, TERROCOPTER,
};

enum deadType
{
	BULLET, GRENADE, PLAYER_KNIFE, 
};

struct deadEnemy
{
	enemyType _enemyType;
	deadType _deadType;
	bool isLeft;
};

class playerManager;
class mapData;

class enemyManager : public gameNode
{
private:
	playerManager* _playerManager;
	mapData* _mapData;
	enemyType _enemyType;

private:	
	vector<enemy*> _vSoldier;	// �Ϲ� ��	
	vector<dog*> _vDog;			// ����
		
	eBullet* _eBullet;			// �Ѿ� Ŭ����
	bossBullet* _bossBullet;	// �����Ѿ� Ŭ����
	bossRocket* _bossRocket;	// �������� Ŭ����
	boss* _boss;				// ���� Ŭ����
	brovil* _brovil;			// ��κ� Ŭ����
	progressBar* _hpBar;		// ü�¹� Ŭ����
	
	int _effectCount;
	int _count;
	int _choice;
	int _stageNum;
	bool _isClear;				// �������� Ŭ�����߳�(��κ� ����)
	bool _isEffect;
	
public:
	void setPlayerManager(playerManager* playerManager) { _playerManager = playerManager; }
	void setMapData(mapData* mapData) { _mapData = mapData; }
	
	// ���ʹ�Ŭ���� ���� ��������
	vector<enemy*> getVEnemy() { return _vSoldier; }	
	// �� �Ѿ�Ŭ���� ��������
	eBullet* getEBullet() { return _eBullet; }
	// ���� Ŭ���� ��������
	boss* getBoss() { return _boss; }
	
	// ���� ���ʹ� ���� ���Ϳ� ���
	vector<deadEnemy> _vDeadEnemyInfo;
	vector<deadEnemy> getVDeadEnemyInfo() {	return _vDeadEnemyInfo;	}
	void addVDeadEnemyInfo(deadEnemy dEnemy) { _vDeadEnemyInfo.push_back(dEnemy); }
		
	HRESULT init(int stageNum);
	void release(void);
	void update(void);
	void render(void);
		
	void enemyFire(int num);	
	void bossBulletFire();
	void bossRocketFire();
	// ���� �� Ǫ����
	void saveEnemy(enemyType enemy, deadType deadType, bool isLeft);
	
	// ���ʹ� ���� �ٲٱ�
	void changeDirection();
	
	void soldierDieWithBullet(int i);
	void soldierDieWithGrenade(int i);

	void brovilDieWithBullet();
	void brovilDieWithGrenade();

	// ���ʹ� �þ� vs �÷��̾� �浹
	void collideWithSight();
	// ���ʹ� vs �ȼ�
	void collideWithPixel();
	// ���ʹ� vs �÷��̾� �Ѿ�
	void collideWithPBullet();	
	// ���ʹ� vs �÷��̾� ����ź
	void collideWithPGrenade();		
	// ���ʹ� vs �Ҿƹ��� �Ѿ�
	void collideWithGBullet();
	// ���� vs �Ҿƹ��� �Ѿ�
	void collideBossWithGBullet();
	void collideBossWithGGrenade();
	
	// ���ʹ� ��ü vs �ȼ� �浹
	void collideWithCorpse();
	
	// ���ʹ� �Ѿ� vs �ȼ�
	void collideBulletWithPixel();
	// ���ʹ� �Ѿ� vs �÷��̾� �浹
	void collideWithPlayer();
	
	// ����
	void collideWithBossBullet();
	void collideWithBossRocket();
	void bossDirChange();
	//void bossHPbar();
	// ���� vs �÷��̾� �Ѿ�
	void PBulletHitBoss();
		
	// ��κ� vs �÷��̾� �Ѿ� �浹
	void collideBrovilwithPBullet();
	// ��κ� vs �÷��̾� ����ź �浹
	void collideBrovilwithPGrenade();
	// ��κ� vs �����浹
	void collideBrovilWithPixel();	
	// ��κ� ��ü vs ���� �浹
	void collideBrovilCorpseWithPixel();

	// ���� vs �����ȼ��浹
	void collideDogSightWithPlayer();
	void collideDogWithPixel();
	void collideDogWithPBullet();
	void collideDogCorpseWithPixel();
	void DogDieWithBullet(int i);

	
	// �������� Ŭ���� ����
	bool isClear();
		
	// ���� Ŭ���� �ʱ�ȭ����
	void setSoldier(int x, int y);
	void setBrovil(int x, int y);
	void setDog(int x, int y, bool isLeft);

	bool isEffect(int frame);
		
	enemyManager() {}
	~enemyManager() {}
};

