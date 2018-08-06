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

	_fPos[0].x = _mapData->getObject()[9]._rc.left, _fPos[0].y = _mapData->getObject()[9]._rc.top;
	_fPos[1].x = _mapData->getObject()[11]._rc.left, _fPos[1].y = _mapData->getObject()[11]._rc.top;
	_fPos[2].x = _mapData->getObject()[234]._rc.left, _fPos[2].y = _mapData->getObject()[234]._rc.top;
	_fPos[3].x = _mapData->getObject()[137]._rc.left, _fPos[3].y = _mapData->getObject()[137]._rc.top;
	_fPos[4].x = _mapData->getObject()[457]._rc.left, _fPos[4].y = _mapData->getObject()[457]._rc.top;
	_fPos[5].x = _mapData->getObject()[462]._rc.left, _fPos[5].y = _mapData->getObject()[462]._rc.top;
	_fPos[6].x = _mapData->getObject()[365]._rc.left, _fPos[6].y = _mapData->getObject()[365]._rc.top;
	_fPos[7].x = _mapData->getObject()[434]._rc.left, _fPos[7].y = _mapData->getObject()[434]._rc.top;
	_fPos[8].x = _mapData->getObject()[444]._rc.left, _fPos[8].y = _mapData->getObject()[444]._rc.top;
	_fPos[9].x = _mapData->getObject()[410]._rc.left, _fPos[9].y = _mapData->getObject()[410]._rc.top;
	_fPos[10].x = _mapData->getObject()[420]._rc.left, _fPos[10].y = _mapData->getObject()[420]._rc.top;
	_fPos[11].x = _mapData->getObject()[390]._rc.left, _fPos[11].y = _mapData->getObject()[390]._rc.top;

	for (int i = 0; i < 12; i++)
	{
		type = (OBJECT_TYPE)RND->getFromIntTo(0, 6);
	
		objectA* object = _factory->createObject(type);
		object->setPosition(_fPos[i].x, _fPos[i].y - object->getImage()->getHeight() + 6);
		
		_vObject.push_back(object);
	}

	_vObject[0]->setTargetIsActived(&_mapData->getObject()[9]._isActived);
	_vObject[1]->setTargetIsActived(&_mapData->getObject()[11]._isActived);
	_vObject[2]->setTargetIsActived(&_mapData->getObject()[234]._isActived);
	_vObject[3]->setTargetIsActived(&_mapData->getObject()[137]._isActived);
	_vObject[4]->setTargetIsActived(&_mapData->getObject()[457]._isActived);
	_vObject[5]->setTargetIsActived(&_mapData->getObject()[462]._isActived);
	_vObject[6]->setTargetIsActived(&_mapData->getObject()[465]._isActived);
	_vObject[7]->setTargetIsActived(&_mapData->getObject()[434]._isActived);
	_vObject[8]->setTargetIsActived(&_mapData->getObject()[444]._isActived);
	_vObject[9]->setTargetIsActived(&_mapData->getObject()[410]._isActived);
	_vObject[10]->setTargetIsActived(&_mapData->getObject()[420]._isActived);
	_vObject[11]->setTargetIsActived(&_mapData->getObject()[390]._isActived);

	_prisonerPos[0].x = 3280, _prisonerPos[0].y = 1558;
	_prisonerPos[1].x = 3685, _prisonerPos[1].y = 2099;
	for (int i = 0; i < 2; i++)
	{
		type = PRISONER;
	
		objectA* object = _factory->createObject(type);
		object->setPosition(_prisonerPos[i].x, _prisonerPos[i].y);
		
		_vObject.push_back(object);
	}

	_boxPos[0].x = 2873, _boxPos[0].y = 1220;
	_boxPos[1].x = 2941, _boxPos[1].y = 1152;
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
	
	_truckPos[0].x = 160, _truckPos[0].y = 2164;
	for (int i = 0; i < 1; i++)
	{
		type = TRUCK;
	
		objectA* object = _factory->createObject(type);
		object->setPosition(_truckPos[i].x, _truckPos[i].y - object->getImage()->getHeight());
	
		_vObject.push_back(object);
	}

	_helicopterPos[0].x = 3101, _helicopterPos[0].y = 519;
	for (int i = 0; i < 1; i++)
	{
		type = TRUCK;

		objectA* object = _factory->createObject(type);
		object->setPosition(_helicopterPos[i].x, _helicopterPos[i].y);

		_vObject.push_back(object);
	}

	_amFlagPos[0].x = 1853, _amFlagPos[0].y = 1225;
	_amFlagPos[1].x = 2923, _amFlagPos[1].y = 2037;
	_amFlagPos[2].x = 3324, _amFlagPos[2].y = 902;
	for (int i = 0; i < 3; i++)
	{
		type = AMERICAN_FLAG;
	
		objectA* object = _factory->createObject(type);
		object->setPosition(_amFlagPos[i].x, _amFlagPos[i].y);
	
		_vObject.push_back(object);
	}

	_amFlagPolePos[0].x = 1840, _amFlagPolePos[0].y = 1424;
	_amFlagPolePos[1].x = 2909, _amFlagPolePos[1].y = 2236;
	for (int i = 0; i < 2; i++)
	{
		type = AMFLAG_POLE;
	
		objectA* object = _factory->createObject(type);
		object->setPosition(_amFlagPolePos[i].x, _amFlagPolePos[i].y - object->getImage()->getHeight());
	
		_vObject.push_back(object);
	}

	_enemyFlagPos[0].x = 2949, _enemyFlagPos[0].y = 1084;
	_enemyFlagPos[1].x = 4099, _enemyFlagPos[1].y = 1084;
	for (int i = 0; i < 2; i++)
	{
		type = ENEMY_FLAG;
	
		objectA* object = _factory->createObject(type);
		object->setPosition(_enemyFlagPos[i].x, _enemyFlagPos[i].y - object->getImage()->getHeight());
	
		_vObject.push_back(object);
	}

	for (int i = 0; i < _vObject.size(); i++)
		_vObject[i]->setState(OBJECT_IDLE);

	return S_OK;
}

void objectManager::release()
{
	//init���� ���� ����� ���� �ؾ��Ѵ�
	//SAFE_DELETE(_factory);
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

	char str[32];
	sprintf_s(str, "%d", _vObject[0]->getTargetIsActived());
	TextOut(hdc, 100, 700, str, strlen(str));

}