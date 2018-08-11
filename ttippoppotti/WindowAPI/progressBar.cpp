#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(const char* frontImageKey, const char* backImageKey, int frontX, int frontY, int backX, int backY, int frontWidth, int frontHeight, int backWidth, int backHeight)
{
	//ü�¹� ��ġ �ʱ�ȭ
	_frontX = frontX;
	_frontY = frontY;
	_backX = backX;
	_backY = backY;
	//ü�¹� ����, ���α��� �ʱ�ȭ
	_frontWidth = frontWidth;
	_frontHeight = frontHeight;
	_backWidth = backWidth;
	_backHeight = backHeight;
	//ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
	_rcProgressBack = RectMake(backX, backY, backWidth, backHeight);
	_rcProgressFront = RectMake(frontX, frontY, frontWidth, frontHeight);

	//Ű������ �̹����̸�(~.bmp)���� �ٷ� �ʱ�ȭ
	char frontImage[128];
	char backImage[128];
	//�޸� ����ϰ� �о��ֱ�
	ZeroMemory(frontImage, sizeof(frontImage));
	ZeroMemory(backImage, sizeof(backImage));
	//~.bmp�� �����
	//Ű, �����̸� IMAGEMANAGER->ADDIMAGE("background", "background.bmp",,,,)
	sprintf(frontImage, "%s.bmp", frontImageKey);
	sprintf(backImage, "%s.bmp", backImageKey);

	//ü�¹� �̹��� �ʱ�ȭ
	_progressBarFront = IMAGEMANAGER->addImage(frontImageKey, frontImage, frontX, frontY, frontWidth, frontHeight, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage(backImageKey, backImage, backX, backY, backWidth, backHeight, true, RGB(255, 0, 255));

	return S_OK;
}

void progressBar::release(void)
{
}

void progressBar::update(void)
{
	//
	_rcProgressFront = RectMake(_frontX, _frontY, _progressBarFront->getWidth(), _progressBarFront->getHeight());
	_rcProgressBack = RectMake(_backX, _backY, _progressBarBack->getWidth(), _progressBarBack->getHeight());

}

void progressBar::render(void)
{
	//������ �Ǵ� ������ ���ؼ� ������ �Ǵϱ� ������� ���� ��Ų��
	_progressBarBack->render(getMemDC(), _rcProgressBack.left, _backY);
	//�տ� �������� ü�¹� �̹���
	_progressBarFront->render(getMemDC(), _rcProgressFront.left, _frontY,
		0, 0, _frontWidth, _progressBarFront->getHeight());
}

void progressBar::setGauge(float currentHp, float maxHp)
{
	_frontWidth = (currentHp / maxHp) * _progressBarFront->getWidth();
}
