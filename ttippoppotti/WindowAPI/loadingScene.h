#pragma once
#include "gameNode.h"
#include "loading.h"

class loadingScene : public gameNode
{
private:
	loading * _loading;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void Kim_Min_Young_addImage();
	void Kim_Min_Young_addSound();
	void Kim_Sang_Won_addImage();
	void Kim_Sang_Won_addSound();
	void Lee_Moon_Gyu_addImage();
	void Lee_Moon_Gyu_addSound();
	void Lee_Ji_Woong_addImage();
	void Lee_Ji_Woong_addSound();
	//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
	void loadingImage();
	//�ε����� �Լ�(�̰��� ���带 ���� �־��)
	void loadingSound();

	loadingScene() {}
	~loadingScene() {}
};

