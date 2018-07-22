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

