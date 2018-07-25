#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�̹��� �� ���� �ε�
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//�ε�Ŭ���� ����
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ������
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("����������");
	}

	//if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	//{
	//	float num = _loading->getLoadItem().size();
	//	float cur = _loading->getCurrnetGauge();
	//	float per = cur / num * 100;
	//	cout << "��ü ���ϰ��� : " << num << endl;
	//	cout << "���� �ε����� : " << cur << endl;
	//	cout << per << " %" << endl;
	//}
}

void loadingScene::render(void)
{
	//�ε�Ŭ���� ����
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

//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
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

//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound()
{
	Kim_Min_Young_addSound();
	Kim_Sang_Won_addSound();
	Lee_Moon_Gyu_addSound();
	Lee_Ji_Woong_addSound();
}
