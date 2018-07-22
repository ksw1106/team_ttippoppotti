#pragma once
#include "gameNode.h"

struct mapObject
{
	float _width, _height; //오브젝트 가로, 세로 크기
	RECT _rc; //오브젝트 렉트 크기
	bool _isActived; //충돌처리 할건지 안할건지
	int tag; //어떤 오브젝트인지 구별용
};

class mapData : public gameNode
{
	vector<mapObject> _vObject;
	char str[128];
public:
	vector<mapObject> getObject() { return _vObject; }
	void setObject(mapObject obj, int index) { _vObject[index] = obj; }
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mapData() {}
	~mapData() {}
};

