#pragma once
#include "gameNode.h"
//=============================================================
//	## progressBar ## (���α׷����� = ü�¹�)
//=============================================================

class progressBar : public gameNode
{
private:
	RECT _rcProgressBack;		//ü�¹� �� ��Ʈ
	RECT _rcProgressFront;		//ü�¹� �� ��Ʈ
	RECT _rcProgressMiddle;	//ü�¹� �߰�(���) ��Ʈ
	int _frontX, _frontY;		//ü�¹� ��ġ��ǥ
	int _middleX, _middleY;		//ü�¹� �߰� ��ġ ��ǥ
	int _backX, _backY;			//
	float _frontWidth;			//ü�¹� �� ���α���
	float _frontHeight;			//ü�¹� �� ���α���
	float _middleWidth;
	float _middleHeight;
	float _backWidth;			//ü�¹� �� ����
	float _backHeight;			//ü�¹� �� ����

	image* _progressBarFront;	//ü�¹� �� �̹���
	image* _progressBarBack;	//ü�¹� �� �̹���
	image* _progressBarMiddle;

public:
	//ü�¹� �ʱ�ȭ(���̹���Ű, ���̹���Ű, x, y, ���α���, ���α���)
	HRESULT init(const char* frontImageKey, const char* middleImageKey, const char* backImageKey, int frontX, int frontY, int middleX, int middleY, int backX, int backY,
		int frontWidth, int frontHeight, int middleWidth, int middleHeight, int backWidth, int backHeight);
	void release(void);
	void update(void);
	void render(void);

	//ü�¹� ������ �����ϱ�
	void setGauge(float currentHp, float maxHp);

	//ü�¹� ��ġ ��ǥ �����ϱ�
	void setFrontX(int x) { _frontX = x; }
	void setFrontY(int y) { _frontY = y; }
	void setMiddleX(int x) { _middleX = x; }
	void setMiddleY(int y) { _middleY = y; }
	void setBackX(int x) { _backX = x; }
	void setBackY(int y) { _backY = y; }

	//ü�¹� ��Ʈ ��������
	RECT getFrontRect() { return _rcProgressFront; }
	RECT getMiddleRect() { return _rcProgressMiddle; }
	RECT getBackRect() { return _rcProgressBack; }

	progressBar() {}
	~progressBar() {}
};

