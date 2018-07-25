#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 씬변경
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("스테이지씬");
	}

	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	//{
	//	float num = _loading->getLoadItem().size();
	//	float cur = _loading->getCurrnetGauge();
	//	float per = cur / num * 100;
	//	cout << "전체 파일갯수 : " << num << endl;
	//	cout << "현재 로딩갯수 : " << cur << endl;
	//	cout << per << " %" << endl;
	//}
}

void loadingScene::render(void)
{
	//로딩클래스 렌더
	_loading->render();

	/*if (_loading->getCurrnetGauge() < _loading->getLoadItem().size())
	{
		char str[128];
		sprintf_s(str, "%s.bmp", _loading->getLoadItem()[_loading->getCurrnetGauge()]->getImageResource().keyName.c_str());
		TextOut(getMemDC(), 120, 430, str, strlen(str));
	}

	float num = _loading->getLoadItem().size();
	float cur = _loading->getCurrnetGauge();
	float per = cur / num * 100;
	char str[128];
	sprintf_s(str, "%.f %%", per);
	TextOut(getMemDC(), 660, 430, str, strlen(str));*/

}

//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingScene::loadingImage()
{

	Kim_Min_Young_addImage();
	Kim_Sang_Won_addImage();
	Lee_Moon_Gyu_addImage();
	Lee_Ji_Woong_addImage();
		
	//_loading->loadImage();
	//_loading->loadFrameImage();
	//_loading->loadSound();
	SetBkMode(getMemDC(), TRANSPARENT);
}

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound()
{
	Kim_Min_Young_addSound();
	Kim_Sang_Won_addSound();
	Lee_Moon_Gyu_addSound();
	Lee_Ji_Woong_addSound();
}
