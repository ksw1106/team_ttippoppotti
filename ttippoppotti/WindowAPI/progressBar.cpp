#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(const char* frontImageKey, const char* middleImageKey, const char* backImageKey, int frontX, int frontY, int middleX, int middleY, int backX, int backY,
	int frontWidth, int frontHeight, int middleWidth, int middleHeight, int backWidth, int backHeight)
{
	//ü�¹� ��ġ �ʱ�ȭ
	_frontX = frontX;
	_frontY = frontY;
	_middleX = middleX;
	_middleY = middleY;
	_backX = backX;
	_backY = backY;
	//ü�¹� ����, ���α��� �ʱ�ȭ
	_frontWidth = frontWidth;
	_frontHeight = frontHeight;
	_middleWidth = middleWidth;
	_middleHeight = middleHeight;
	_backWidth = backWidth;
	_backHeight = backHeight;
	//ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
	_rcProgressBack = RectMake(backX, backY, backWidth, backHeight);
	_rcProgressMiddle = RectMake(middleX, middleY, middleWidth, middleHeight);
	_rcProgressFront = RectMake(frontX, frontY, frontWidth, frontHeight);

	//Ű������ �̹����̸�(~.bmp)���� �ٷ� �ʱ�ȭ
	char frontImage[128];
	char middleImage[128];
	char backImage[128];

	//�޸� ����ϰ� �о��ֱ�
	ZeroMemory(frontImage, sizeof(frontImage));
	ZeroMemory(middleImage, sizeof(middleImage));
	ZeroMemory(backImage, sizeof(backImage));

	//~.bmp�� �����
	//Ű, �����̸� IMAGEMANAGER->ADDIMAGE("background", "background.bmp",,,,)
	sprintf(frontImage, "%s.bmp", frontImageKey);
	sprintf(middleImage, "%s.bmp", middleImageKey);
	sprintf(backImage, "%s.bmp", backImageKey);

	//ü�¹� �̹��� �ʱ�ȭ
	_progressBarFront = IMAGEMANAGER->addImage(frontImageKey, frontImage, frontX, frontY, frontWidth, frontHeight, true, RGB(255, 0, 255));
	_progressBarMiddle = IMAGEMANAGER->addImage(middleImageKey, middleImage, middleX, middleY, middleWidth, middleHeight, true, RGB(255, 0, 255));
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
	_rcProgressMiddle = RectMake(_middleX, _middleY, _progressBarMiddle->getWidth(), _progressBarMiddle->getHeight());
	_rcProgressBack = RectMake(_backX, _backY, _progressBarBack->getWidth(), _progressBarBack->getHeight());

	if (_middleWidth > _frontWidth)
	{	
		_middleWidth -= 1;
	}
	//_middleWidth = _rcProgressMiddle.right - _rcProgressMiddle.left;
}

void progressBar::render(void)
{
	//������ �Ǵ� ������ ���ؼ� ������ �Ǵϱ� ������� ���� ��Ų��
	_progressBarBack->render(getMemDC(), _rcProgressBack.left, _backY);
	
	_progressBarMiddle->render(getMemDC(), _rcProgressMiddle.left, _middleY,
		0, 0, _middleWidth, _progressBarMiddle->getHeight());
	//�տ� �������� ü�¹� �̹���
	_progressBarFront->render(getMemDC(), _rcProgressFront.left, _frontY,
		0, 0, _frontWidth, _progressBarFront->getHeight());
}

void progressBar::setGauge(float currentHp, float maxHp)
{
	_frontWidth = (currentHp / maxHp) * _progressBarFront->getWidth();	
}
