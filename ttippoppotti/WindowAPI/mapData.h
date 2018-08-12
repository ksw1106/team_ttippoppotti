#pragma once
#include "gameNode.h"

struct mapObject
{
	float _width, _height; //������Ʈ ����, ���� ũ��
	RECT _rc; //������Ʈ ��Ʈ ũ��
	bool _isActived; //�浹ó�� �Ұ��� ���Ұ���
	int tag; //� ������Ʈ���� ������
};

class mapData : public gameNode
{
	vector<mapObject> _vObject;
	image* _backGround;
	image* _pixel;
	char str[128];
public:
	void deleteMap(int index);
	void deleteMapIndexByIndex(int num, int index, int index2);

	vector<mapObject>& getObject() { return _vObject; }
	void setObject(mapObject obj, int index) { _vObject[index] = obj; }
	void setObjectPixel(image* objectPixel) { _backGround = objectPixel; }
	void setBackGroundMap(image* backGroundMap) { _pixel = backGroundMap; }

	void stage1_setting();
	void stage2_setting();
	HRESULT init(int stage);
	void release(void);
	void update(void);
	void render(void);

	mapData() {}
	~mapData() {}
};

