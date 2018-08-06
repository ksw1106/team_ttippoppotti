#include "stdafx.h"
#include "objectManager.h"
#include "mapData.h"

HRESULT objectManager::init()
{
	//여기에서 오브젝트 객체들생성
	//팩토리 패턴에서 에너미 매니저 init 보고 하면 된다
	//그리고 bool* _targetIsActived 이거 다
	//자기 아래 렉트 isActived 연결 해줘야 한다
	//맵번호는 어케 찾냐면 받아놨으니까
	//_mapData->getObject()[렉트번호].isActived 하면 된다
	_factory = new objectFactory;


	//스테이지에 오브젝트 몇개인지 찾아서 포문돌리자
	//오브젝트 수만큼 좌표 배열에 넣어두고 밑에 포문 돌려야함

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
	//init에서 공장 만들면 해제 해야한다
	//SAFE_DELETE(_factory);
}

void objectManager::update()
{
	//오브젝트 벡터 돌리면서 업데이트 시켜주면 된다
	for (int i = 0; i < _vObject.size(); i++)
	{
		if (OBJECT_DESTROY == _vObject[i]->getState()) continue;

		_vObject[i]->update();
	}
}

void objectManager::render(HDC hdc)
{
	//오브젝트 벡터 돌리면서 활성화된 오브젝트들만 그려주면 된다.
	//getMemDC() 를 못쓰니까 hdc 쓰면 된다.
	for (int i = 0; i < _vObject.size(); i++)
	{
		if (OBJECT_DESTROY == _vObject[i]->getState()) continue;
		_vObject[i]->render(hdc);
	}

	char str[32];
	sprintf_s(str, "%d", _vObject[0]->getTargetIsActived());
	TextOut(hdc, 100, 700, str, strlen(str));

}