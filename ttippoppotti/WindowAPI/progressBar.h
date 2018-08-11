#pragma once
#include "gameNode.h"
//=============================================================
//	## progressBar ## (프로그래스바 = 체력바)
//=============================================================

class progressBar : public gameNode
{
private:
	RECT _rcProgressBack;		//체력바 뒤 렉트
	RECT _rcProgressFront;		//체력바 앞 렉트
	RECT _rcProgressMiddle;	//체력바 중간(흰색) 렉트
	int _frontX, _frontY;		//체력바 위치좌표
	int _middleX, _middleY;		//체력바 중간 위치 좌표
	int _backX, _backY;			//
	float _frontWidth;			//체력바 앞 가로길이
	float _frontHeight;			//체력바 앞 세로길이
	float _middleWidth;
	float _middleHeight;
	float _backWidth;			//체력바 뒤 가로
	float _backHeight;			//체력바 뒤 세로

	image* _progressBarFront;	//체력바 앞 이미지
	image* _progressBarBack;	//체력바 뒤 이미지
	image* _progressBarMiddle;

public:
	//체력바 초기화(앞이미지키, 백이미지키, x, y, 가로길이, 세로길이)
	HRESULT init(const char* frontImageKey, const char* middleImageKey, const char* backImageKey, int frontX, int frontY, int middleX, int middleY, int backX, int backY,
		int frontWidth, int frontHeight, int middleWidth, int middleHeight, int backWidth, int backHeight);
	void release(void);
	void update(void);
	void render(void);

	//체력바 게이지 세팅하기
	void setGauge(float currentHp, float maxHp);

	//체력바 위치 좌표 세팅하기
	void setFrontX(int x) { _frontX = x; }
	void setFrontY(int y) { _frontY = y; }
	void setMiddleX(int x) { _middleX = x; }
	void setMiddleY(int y) { _middleY = y; }
	void setBackX(int x) { _backX = x; }
	void setBackY(int y) { _backY = y; }

	//체력바 렉트 가져오기
	RECT getFrontRect() { return _rcProgressFront; }
	RECT getMiddleRect() { return _rcProgressMiddle; }
	RECT getBackRect() { return _rcProgressBack; }

	progressBar() {}
	~progressBar() {}
};

