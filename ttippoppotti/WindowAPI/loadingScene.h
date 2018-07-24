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
	//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
	void loadingImage();
	//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
	void loadingSound();

	loadingScene() {}
	~loadingScene() {}
};

