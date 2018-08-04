#include "stdafx.h"
#include "objectManager.h"
#include "mapData.h"

HRESULT objectManager::init()
{
	//���⿡�� ������Ʈ ��ü�����
	//���丮 ���Ͽ��� ���ʹ� �Ŵ��� init ���� �ϸ� �ȴ�
	//�׸��� bool* _targetIsActived �̰� ��
	//�ڱ� �Ʒ� ��Ʈ isActived ���� ����� �Ѵ�
	//�ʹ�ȣ�� ���� ã�ĸ� �޾Ƴ����ϱ�
	//_mapData->getObject()[��Ʈ��ȣ].isActived �ϸ� �ȴ�
	_factory = new objectFactory;


	//���������� ������Ʈ ����� ã�Ƽ� ����������
	//������Ʈ ����ŭ ��ǥ �迭�� �־�ΰ� �ؿ� ���� ��������

	OBJECT_TYPE type;

	//_fPos[0].x = RND->getFromIntTo(), _fPos[0].y = ;
	//_fPos[1].x = , _fPos[1].y = ;
	//_fPos[2].x = , _fPos[2].y = ;
	//_fPos[3].x = , _fPos[3].y = ;
	//_fPos[4].x = , _fPos[4].y = ;
	//_fPos[5].x = , _fPos[5].y = ;
	//for (int i = 0; i < 6; i++)
	//{
	//	type = (OBJECT_TYPE)RND->getFromIntTo(0, 6);
	//
	//	objectA* object = _factory->createObject(type);
	//	object->setPosition(_fPos[i].x, _fPos[i].y);
	//	
	//	_vObject.push_back(object);
	//}

	_prisonerPos[0].x = 3280, _prisonerPos[0].y = 1558;
	_prisonerPos[1].x = 3686, _prisonerPos[1].y = 2099;
	for (int i = 0; i < 2; i++)
	{
		type = PRISONER;

		objectA* object = _factory->createObject(type);
		object->setPosition(_prisonerPos[i].x, _prisonerPos[i].y);
		
		_vObject.push_back(object);
	}

	_boxPos[0].x = 2873, _boxPos[0].y = 1220;
	_boxPos[1].x = 2941, _boxPos[1].y = 1132;
	_boxPos[2].x = 3009, _boxPos[2].y = 1354;
	_boxPos[3].x = 3009, _boxPos[3].y = 1557;
	_boxPos[4].x = 3009, _boxPos[4].y = 1625;
	_boxPos[5].x = 4024, _boxPos[5].y = 1354;
	_boxPos[6].x = 3956, _boxPos[6].y = 1422;
	_boxPos[7].x = 4024, _boxPos[7].y = 1422;
	_boxPos[8].x = 4024, _boxPos[8].y = 1558;
	_boxPos[9].x = 4024, _boxPos[9].y = 1626;
	_boxPos[10].x = 3956, _boxPos[10].y = 1558;
	_boxPos[11].x = 3956, _boxPos[11].y = 1626;
	_boxPos[12].x = 3888, _boxPos[12].y = 1558;
	_boxPos[13].x = 3888, _boxPos[13].y = 1626;
	for (int i = 0; i < 14; i++)
	{
		type = WOODENBOX;

		objectA* object = _factory->createObject(type);
		object->setPosition(_boxPos[i].x, _boxPos[i].y);
		
		_vObject.push_back(object);
	}

	_drumRedPos[0].x = 3009, _drumRedPos[0].y = 1422;
	for (int i = 0; i < 1; i++)
	{
		type = SKULL_DRUMRED;

		objectA* object = _factory->createObject(type);
		object->setPosition(_drumRedPos[i].x, _drumRedPos[i].y);
		
		_vObject.push_back(object);
	}

	_drumGrayPos[0].x = 2941, _drumGrayPos[0].y = 1220;
	for (int i = 0; i < 1; i++)
	{
		type = SKULL_DRUMGRAY;

		objectA* object = _factory->createObject(type);
		object->setPosition(_drumGrayPos[i].x, _drumGrayPos[i].y);
		
		_vObject.push_back(object);
	}

	return S_OK;
}

void objectManager::release()
{
	//init���� ���� ����� ���� �ؾ��Ѵ�
	SAFE_DELETE(_factory);
}

void objectManager::update()
{
	//������Ʈ ���� �����鼭 ������Ʈ �����ָ� �ȴ�
	for (int i = 0; i < _vObject.size(); i++)
	{
		if (OBJECT_DESTROY == _vObject[i]->getState()) continue;

		_vObject[i]->update();
	}
}

void objectManager::render(HDC hdc)
{
	//������Ʈ ���� �����鼭 Ȱ��ȭ�� ������Ʈ�鸸 �׷��ָ� �ȴ�.
	//getMemDC() �� �����ϱ� hdc ���� �ȴ�.
	for (int i = 0; i < _vObject.size(); i++)
	{
		if (OBJECT_DESTROY == _vObject[i]->getState()) continue;
		_vObject[i]->render(hdc);
	}

}