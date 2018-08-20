#include "stdafx.h"
#include "objectManager.h"
#include "mapData.h"
#include "playerManager.h"


HRESULT objectManager::init(int num)
{
	//여기에서 오브젝트 객체들생성
	//팩토리 패턴에서 에너미 매니저 init 보고 하면 된다
	//그리고 bool* _targetIsActived 이거 다
	//자기 아래 렉트 isActived 연결 해줘야 한다
	//맵번호는 어케 찾냐면 받아놨으니까
	//_mapData->getObject()[렉트번호].isActived 하면 된다
	_factory = new objectFactory;

	if (num == 1)
	{
		OBJECT_TYPE type;

		_fPos[0].x = _mapData->getObject()[8]._rc.left, _fPos[0].y = _mapData->getObject()[8]._rc.top;
		_fPos[1].x = _mapData->getObject()[10]._rc.left, _fPos[1].y = _mapData->getObject()[10]._rc.top;
		_fPos[2].x = _mapData->getObject()[235]._rc.left, _fPos[2].y = _mapData->getObject()[235]._rc.top;
		_fPos[3].x = _mapData->getObject()[137]._rc.left, _fPos[3].y = _mapData->getObject()[137]._rc.top;
		_fPos[4].x = _mapData->getObject()[457]._rc.left, _fPos[4].y = _mapData->getObject()[457]._rc.top;
		_fPos[5].x = _mapData->getObject()[462]._rc.left, _fPos[5].y = _mapData->getObject()[462]._rc.top;
		_fPos[6].x = _mapData->getObject()[465]._rc.left, _fPos[6].y = _mapData->getObject()[465]._rc.top;
		_fPos[7].x = _mapData->getObject()[435]._rc.left, _fPos[7].y = _mapData->getObject()[435]._rc.top;
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

		_drumRedPos[0].x = 3009, _drumRedPos[0].y = 1432, drumRedTarget[0] = 433;
		for (int i = 0; i < 1; i++)
		{
			type = SKULL_DRUMRED;
			
			objectA* object = _factory->createObject(type);
			object->setPosition(_drumRedPos[i].x, _drumRedPos[i].y);
			object->setTargetMap(drumRedTarget[i]);

			_vObject.push_back(object);
		}
		_drumGrayPos[0].x = 2941, _drumGrayPos[0].y = 1229, drumGrayTarget[0] = 407;
		for (int i = 0; i < 1; i++)
		{
			type = SKULL_DRUMGRAY;

			objectA* object = _factory->createObject(type);
			object->setPosition(_drumGrayPos[i].x, _drumGrayPos[i].y);
			object->setTargetMap(drumGrayTarget[i]);

			_vObject.push_back(object);
		}

		_truckPos[0].x = 160, _truckPos[0].y = 2164;
		for (int i = 0; i < 1; i++)
		{
			type = TRUCK;

			objectA* object = _factory->createObject(type);
			object->setPosition(_truckPos[i].x, _truckPos[i].y - object->getImage()->getHeight());
			object->init();

			_vObject.push_back(object);
		}

		_prisonerPos[0].x = 3685, _prisonerPos[0].y = 2099;
		//_prisonerPos[1].x = 3280, _prisonerPos[1].y = 1558;
		for (int i = 0; i < 1; i++)
		{
			type = PRISONER;

			objectA* object = _factory->createObject(type);
			object->setPosition(_prisonerPos[i].x, _prisonerPos[i].y);
			object->init();

			_vObject.push_back(object);
		}

		_helicopterPos[0].x = 3101, _helicopterPos[0].y = 519;
		for (int i = 0; i < 1; i++)
		{
			type = HELICOPTER;
		
			objectA* object = _factory->createObject(type);
			object->setPosition(_helicopterPos[i].x, _helicopterPos[i].y);
			object->init();

			_vObject.push_back(object);
		}

		_maxFlag = 3;
		_amFlagPos[0].x = 1853, _amFlagPos[0].y = 1225;
		_amFlagPos[1].x = 2923, _amFlagPos[1].y = 2037;
		_amFlagPos[2].x = 3324, _amFlagPos[2].y = 907;
		for (int i = 0; i < _maxFlag; i++)
		{
			type = AMERICAN_FLAG;

			objectA* object = _factory->createObject(type);
			object->setPosition(_amFlagPos[i].x, _amFlagPos[i].y);
			object->init();

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

		_vObject[0]->setTargetIsActived(&_mapData->getObject()[8]._isActived);
		_vObject[1]->setTargetIsActived(&_mapData->getObject()[10]._isActived);
		_vObject[2]->setTargetIsActived(&_mapData->getObject()[235]._isActived);
		_vObject[3]->setTargetIsActived(&_mapData->getObject()[137]._isActived);
		_vObject[4]->setTargetIsActived(&_mapData->getObject()[457]._isActived);
		_vObject[5]->setTargetIsActived(&_mapData->getObject()[462]._isActived);
		_vObject[6]->setTargetIsActived(&_mapData->getObject()[465]._isActived);
		_vObject[7]->setTargetIsActived(&_mapData->getObject()[435]._isActived);
		_vObject[8]->setTargetIsActived(&_mapData->getObject()[444]._isActived);
		_vObject[9]->setTargetIsActived(&_mapData->getObject()[410]._isActived);
		_vObject[10]->setTargetIsActived(&_mapData->getObject()[420]._isActived);
		_vObject[11]->setTargetIsActived(&_mapData->getObject()[390]._isActived);

		_vObject[12]->setTargetIsActived(&_mapData->getObject()[406]._isActived);
		_vObject[13]->setTargetIsActived(&_mapData->getObject()[407]._isActived);
		_vObject[14]->setTargetIsActived(&_mapData->getObject()[433]._isActived);
		_vObject[15]->setTargetIsActived(&_mapData->getObject()[455]._isActived);
		_vObject[16]->setTargetIsActived(&_mapData->getObject()[455]._isActived);
		_vObject[17]->setTargetIsActived(&_mapData->getObject()[446]._isActived);
		_vObject[18]->setTargetIsActived(&_mapData->getObject()[445]._isActived);
		_vObject[19]->setTargetIsActived(&_mapData->getObject()[446]._isActived);
		_vObject[20]->setTargetIsActived(&_mapData->getObject()[469]._isActived);
		_vObject[21]->setTargetIsActived(&_mapData->getObject()[469]._isActived);
		_vObject[22]->setTargetIsActived(&_mapData->getObject()[468]._isActived);
		_vObject[23]->setTargetIsActived(&_mapData->getObject()[468]._isActived);
		_vObject[24]->setTargetIsActived(&_mapData->getObject()[467]._isActived);
		_vObject[25]->setTargetIsActived(&_mapData->getObject()[467]._isActived);
		_vObject[26]->setTargetIsActived(&_mapData->getObject()[433]._isActived);	//빨간드럼통
		_vObject[27]->setTargetIsActived(&_mapData->getObject()[407]._isActived);	//회색드럼통

		for (int i = 0; i < _vObject.size(); i++)
		{
			_vObject[i]->setState(OBJECT_IDLE);
			_vObject[i]->setMapData(_mapData);
		}

		_flagCount = 0;
		_isGameClear = false;
	}
	else if(num == 2)
	{
		//2스테이지
		OBJECT_TYPE type;

		_fPos[0].x = _mapData->getObject()[9]._rc.left, _fPos[0].y = _mapData->getObject()[9]._rc.top;
		_fPos[1].x = _mapData->getObject()[208]._rc.left, _fPos[1].y = _mapData->getObject()[208]._rc.top;
		_fPos[2].x = _mapData->getObject()[304]._rc.left, _fPos[2].y = _mapData->getObject()[304]._rc.top;
		_fPos[3].x = _mapData->getObject()[305]._rc.left, _fPos[3].y = _mapData->getObject()[305]._rc.top;
		_fPos[4].x = _mapData->getObject()[285]._rc.left, _fPos[4].y = _mapData->getObject()[285]._rc.top;
		_fPos[5].x = _mapData->getObject()[288]._rc.left, _fPos[5].y = _mapData->getObject()[288]._rc.top;
		_fPos[6].x = _mapData->getObject()[272]._rc.left, _fPos[6].y = _mapData->getObject()[272]._rc.top;
		_fPos[7].x = _mapData->getObject()[274]._rc.left, _fPos[7].y = _mapData->getObject()[274]._rc.top;
		_fPos[8].x = _mapData->getObject()[472]._rc.left, _fPos[8].y = _mapData->getObject()[472]._rc.top;
		_fPos[9].x = _mapData->getObject()[473]._rc.left, _fPos[9].y = _mapData->getObject()[473]._rc.top;
		_fPos[10].x = _mapData->getObject()[592]._rc.left, _fPos[10].y = _mapData->getObject()[592]._rc.top;
		_fPos[11].x = _mapData->getObject()[708]._rc.left, _fPos[11].y = _mapData->getObject()[708]._rc.top;
		_fPos[12].x = _mapData->getObject()[601]._rc.left, _fPos[12].y = _mapData->getObject()[601]._rc.top;
		_fPos[13].x = _mapData->getObject()[603]._rc.left, _fPos[13].y = _mapData->getObject()[603]._rc.top;
		_fPos[14].x = _mapData->getObject()[490]._rc.left, _fPos[14].y = _mapData->getObject()[490]._rc.top;
		_fPos[15].x = _mapData->getObject()[498]._rc.left, _fPos[15].y = _mapData->getObject()[498]._rc.top;
		_fPos[16].x = _mapData->getObject()[499]._rc.left, _fPos[16].y = _mapData->getObject()[499]._rc.top;
		_fPos[17].x = _mapData->getObject()[689]._rc.left, _fPos[17].y = _mapData->getObject()[689]._rc.top;
		_fPos[18].x = _mapData->getObject()[698]._rc.left, _fPos[18].y = _mapData->getObject()[698]._rc.top;
		_fPos[19].x = _mapData->getObject()[705]._rc.left, _fPos[19].y = _mapData->getObject()[705]._rc.top;
		_fPos[20].x = _mapData->getObject()[707]._rc.left, _fPos[20].y = _mapData->getObject()[707]._rc.top;
		_fPos[21].x = _mapData->getObject()[713]._rc.left, _fPos[21].y = _mapData->getObject()[713]._rc.top;
		_fPos[22].x = _mapData->getObject()[714]._rc.left, _fPos[22].y = _mapData->getObject()[714]._rc.top;

		for (int i = 0; i < 23; i++)
		{
			type = (OBJECT_TYPE)RND->getFromIntTo(0, 6);

			objectA* object = _factory->createObject(type);
			object->setPosition(_fPos[i].x, _fPos[i].y - object->getImage()->getHeight() + 6);

			_vObject.push_back(object);
		}

		int boxHeight = 68;
		int boxHeight2 = 136;

		_boxPos[0].x = 508, _boxPos[0].y =1442;
		_boxPos[1].x = 979, _boxPos[1].y = 1443;
		_boxPos[2].x = 1047, _boxPos[2].y = 1443;
		_boxPos[3].x = 1047, _boxPos[3].y = 1375;
		_boxPos[4].x = 1115, _boxPos[4].y = 1443;
		_boxPos[5].x = 1115, _boxPos[5].y = 1375;
		_boxPos[6].x = 1721, _boxPos[6].y = 1036;
		_boxPos[7].x = 1789, _boxPos[7].y = 1036;
		_boxPos[8].x = 2135, _boxPos[8].y = 1307;
		_boxPos[9].x = 2203, _boxPos[9].y = 1307;
		_boxPos[10].x = 2203, _boxPos[10].y = 1239;
		_boxPos[11].x = 2271, _boxPos[11].y = 1307;
		_boxPos[12].x = 2543, _boxPos[12].y = 1510;
		_boxPos[13].x = 2543, _boxPos[13].y = 1442;
		_boxPos[14].x = 2611, _boxPos[14].y = 1510;
		_boxPos[15].x = 3086, _boxPos[15].y = 1510;
		_boxPos[16].x = 3290, _boxPos[16].y = 1441; //y
		_boxPos[17].x = 2747, _boxPos[17].y = 1713;
		_boxPos[18].x = 2747, _boxPos[18].y = 1645;
		_boxPos[19].x = 2475, _boxPos[19].y = 1917;
		_boxPos[20].x = 2475, _boxPos[20].y = 1849;
		_boxPos[21].x = 2543, _boxPos[21].y = 1917;
		_boxPos[22].x = 2543, _boxPos[22].y = 1849;
		_boxPos[23].x = 2611, _boxPos[23].y = 1917;
		_boxPos[24].x = 2679, _boxPos[24].y = 1917;
		_boxPos[25].x = 3290, _boxPos[25].y = 1916;
		_boxPos[26].x = 3358, _boxPos[26].y = 1916;
		_boxPos[27].x = 3358, _boxPos[27].y = 1848;
		_boxPos[28].x = 2679, _boxPos[28].y = 2121;
		_boxPos[29].x = 2815, _boxPos[29].y = 2121;
		_boxPos[30].x = 2883, _boxPos[30].y = 2121;
		_boxPos[31].x = 4036, _boxPos[31].y = 689;
		_boxPos[32].x = 4036, _boxPos[32].y = 621;
		_boxPos[33].x = 4104, _boxPos[33].y = 689;
		_boxPos[34].x = 4035, _boxPos[34].y = 892;
		_boxPos[35].x = 3494, _boxPos[35].y = 1303;
		_boxPos[36].x = 3562, _boxPos[36].y = 1303;
		_boxPos[37].x = 3766, _boxPos[37].y = 1441;
		_boxPos[38].x = 4038, _boxPos[38].y = 1441;
		_boxPos[39].x = 4038, _boxPos[39].y = 1373;

		for (int i = 0; i < 40; i++)
		{
			type = WOODENBOX;

			objectA* object = _factory->createObject(type);
			object->setPosition(_boxPos[i].x, _boxPos[i].y);

			_vObject.push_back(object);
		}

		_drumRedPos[0].x = 3154, _drumRedPos[0].y = 1509, drumRedTarget[0] = 605;
		_drumRedPos[1].x = 3290, _drumRedPos[1].y = 1509, drumRedTarget[1] = 607;
		_drumRedPos[2].x = 2883, _drumRedPos[2].y = 2053, drumRedTarget[2] = 514;
		_drumRedPos[3].x = 2951, _drumRedPos[3].y = 2121, drumRedTarget[3] = 515;
		_drumRedPos[4].x = 2951, _drumRedPos[4].y = 2053, drumRedTarget[4] = 515;
		_drumRedPos[5].x = 3019, _drumRedPos[5].y = 2121, drumRedTarget[5] = 516;
		
		for (int i = 0; i < 6; i++)
		{
			type = SKULL_DRUMRED;

			objectA* object = _factory->createObject(type);
			object->setPosition(_drumRedPos[i].x, _drumRedPos[i].y);
			object->setTargetMap(drumRedTarget[i]);

			_vObject.push_back(object);
		}

		_drumGrayPos[0].x = 1791, _drumGrayPos[0].y = 1036, drumGrayTarget[0] = 294;
		_drumGrayPos[1].x = 3222, _drumGrayPos[1].y = 1441, drumGrayTarget[1] = 606;
		_drumGrayPos[2].x = 3222, _drumGrayPos[2].y = 1509, drumGrayTarget[2] = 606;
		for (int i = 0; i < 3; i++)
		{
			type = SKULL_DRUMGRAY;

			objectA* object = _factory->createObject(type);
			object->setPosition(_drumGrayPos[i].x, _drumGrayPos[i].y);
			object->setTargetMap(drumGrayTarget[i]);

			_vObject.push_back(object);
		}

		_prisonerPos[0].x = _mapData->getObject()[210]._rc.left, _prisonerPos[0].y = _mapData->getObject()[210]._rc.top;
		for (int i = 0; i < 1; i++)
		{
			type = PRISONER;

			objectA* object = _factory->createObject(type);
			object->setPosition(_prisonerPos[i].x, _prisonerPos[i].y - object->getImage()->getHeight());
			object->init();

			_vObject.push_back(object);
		}

		_maxFlag = 2;
		_amFlagPos[0].x = 409, _amFlagPos[0].y = 1008;
		_amFlagPos[1].x = 2963, _amFlagPos[1].y = 1105;
		for (int i = 0; i < _maxFlag; i++)
		{
			type = AMERICAN_FLAG;

			objectA* object = _factory->createObject(type);
			object->setPosition(_amFlagPos[i].x, _amFlagPos[i].y);
			object->init();

			_vObject.push_back(object);
		}

		_amFlagPolePos[0].x = _mapData->getObject()[595]._rc.left, _amFlagPolePos[0].y = _mapData->getObject()[595]._rc.top;
		for (int i = 0; i < 1; i++)
		{
			type = AMFLAG_POLE;

			objectA* object = _factory->createObject(type);
			object->setPosition(_amFlagPolePos[i].x, _amFlagPolePos[i].y - object->getImage()->getHeight());

			_vObject.push_back(object);
		}

		//랜덤 오브젝트
		_vObject[0]->setTargetIsActived(&_mapData->getObject()[9]._isActived);
		_vObject[1]->setTargetIsActived(&_mapData->getObject()[208]._isActived);
		_vObject[2]->setTargetIsActived(&_mapData->getObject()[304]._isActived);
		_vObject[3]->setTargetIsActived(&_mapData->getObject()[305]._isActived);
		_vObject[4]->setTargetIsActived(&_mapData->getObject()[285]._isActived);
		_vObject[5]->setTargetIsActived(&_mapData->getObject()[288]._isActived);
		_vObject[6]->setTargetIsActived(&_mapData->getObject()[272]._isActived);
		_vObject[7]->setTargetIsActived(&_mapData->getObject()[274]._isActived);
		_vObject[8]->setTargetIsActived(&_mapData->getObject()[472]._isActived);
		_vObject[9]->setTargetIsActived(&_mapData->getObject()[473]._isActived);
		_vObject[10]->setTargetIsActived(&_mapData->getObject()[592]._isActived);
		_vObject[11]->setTargetIsActived(&_mapData->getObject()[708]._isActived);
		_vObject[12]->setTargetIsActived(&_mapData->getObject()[601]._isActived);
		_vObject[13]->setTargetIsActived(&_mapData->getObject()[603]._isActived);
		_vObject[14]->setTargetIsActived(&_mapData->getObject()[490]._isActived);
		_vObject[15]->setTargetIsActived(&_mapData->getObject()[498]._isActived);
		_vObject[16]->setTargetIsActived(&_mapData->getObject()[499]._isActived);
		_vObject[17]->setTargetIsActived(&_mapData->getObject()[689]._isActived);
		_vObject[18]->setTargetIsActived(&_mapData->getObject()[698]._isActived);
		_vObject[19]->setTargetIsActived(&_mapData->getObject()[705]._isActived);
		_vObject[20]->setTargetIsActived(&_mapData->getObject()[707]._isActived);
		_vObject[21]->setTargetIsActived(&_mapData->getObject()[713]._isActived);
		_vObject[22]->setTargetIsActived(&_mapData->getObject()[714]._isActived);
		//우든박스
		_vObject[23]->setTargetIsActived(&_mapData->getObject()[8]._isActived);
		_vObject[24]->setTargetIsActived(&_mapData->getObject()[119]._isActived);
		_vObject[25]->setTargetIsActived(&_mapData->getObject()[120]._isActived);
		_vObject[26]->setTargetIsActived(&_mapData->getObject()[120]._isActived);
		_vObject[27]->setTargetIsActived(&_mapData->getObject()[121]._isActived);
		_vObject[28]->setTargetIsActived(&_mapData->getObject()[121]._isActived);
		_vObject[29]->setTargetIsActived(&_mapData->getObject()[293]._isActived);
		_vObject[30]->setTargetIsActived(&_mapData->getObject()[294]._isActived);
		_vObject[31]->setTargetIsActived(&_mapData->getObject()[312]._isActived);
		_vObject[32]->setTargetIsActived(&_mapData->getObject()[313]._isActived);
		_vObject[33]->setTargetIsActived(&_mapData->getObject()[313]._isActived);
		_vObject[34]->setTargetIsActived(&_mapData->getObject()[314]._isActived);
		_vObject[35]->setTargetIsActived(&_mapData->getObject()[474]._isActived);
		_vObject[36]->setTargetIsActived(&_mapData->getObject()[474]._isActived);
		_vObject[37]->setTargetIsActived(&_mapData->getObject()[475]._isActived);
		_vObject[38]->setTargetIsActived(&_mapData->getObject()[604]._isActived);
		_vObject[39]->setTargetIsActived(&_mapData->getObject()[607]._isActived);
		_vObject[40]->setTargetIsActived(&_mapData->getObject()[487]._isActived);
		_vObject[41]->setTargetIsActived(&_mapData->getObject()[487]._isActived);
		_vObject[42]->setTargetIsActived(&_mapData->getObject()[492]._isActived);
		_vObject[43]->setTargetIsActived(&_mapData->getObject()[492]._isActived);
		_vObject[44]->setTargetIsActived(&_mapData->getObject()[493]._isActived);
		_vObject[45]->setTargetIsActived(&_mapData->getObject()[493]._isActived);
		_vObject[46]->setTargetIsActived(&_mapData->getObject()[494]._isActived);
		_vObject[47]->setTargetIsActived(&_mapData->getObject()[495]._isActived);
		_vObject[48]->setTargetIsActived(&_mapData->getObject()[651]._isActived);
		_vObject[49]->setTargetIsActived(&_mapData->getObject()[652]._isActived);
		_vObject[50]->setTargetIsActived(&_mapData->getObject()[652]._isActived);
		_vObject[51]->setTargetIsActived(&_mapData->getObject()[511]._isActived);
		_vObject[52]->setTargetIsActived(&_mapData->getObject()[513]._isActived);
		_vObject[53]->setTargetIsActived(&_mapData->getObject()[514]._isActived);
		_vObject[54]->setTargetIsActived(&_mapData->getObject()[692]._isActived);
		_vObject[55]->setTargetIsActived(&_mapData->getObject()[692]._isActived);
		_vObject[56]->setTargetIsActived(&_mapData->getObject()[693]._isActived);
		_vObject[57]->setTargetIsActived(&_mapData->getObject()[700]._isActived);
		_vObject[58]->setTargetIsActived(&_mapData->getObject()[610]._isActived);
		_vObject[59]->setTargetIsActived(&_mapData->getObject()[611]._isActived);
		_vObject[60]->setTargetIsActived(&_mapData->getObject()[732]._isActived);
		_vObject[61]->setTargetIsActived(&_mapData->getObject()[736]._isActived);
		_vObject[62]->setTargetIsActived(&_mapData->getObject()[736]._isActived);
		//빨드
		_vObject[63]->setTargetIsActived(&_mapData->getObject()[605]._isActived);
		_vObject[64]->setTargetIsActived(&_mapData->getObject()[607]._isActived);
		_vObject[65]->setTargetIsActived(&_mapData->getObject()[514]._isActived);
		_vObject[66]->setTargetIsActived(&_mapData->getObject()[515]._isActived);
		_vObject[67]->setTargetIsActived(&_mapData->getObject()[515]._isActived);
		_vObject[68]->setTargetIsActived(&_mapData->getObject()[516]._isActived);
		//검드
		_vObject[69]->setTargetIsActived(&_mapData->getObject()[294]._isActived);
		_vObject[70]->setTargetIsActived(&_mapData->getObject()[606]._isActived);
		_vObject[71]->setTargetIsActived(&_mapData->getObject()[606]._isActived);

		for (int i = 0; i < _vObject.size(); i++)
		{
			_vObject[i]->setState(OBJECT_IDLE);
			_vObject[i]->setMapData(_mapData);
		}

		_flagCount = 0;
		_isGameClear = false;
	}
	
	

	//스테이지에 오브젝트 몇개인지 찾아서 포문돌리자
	//오브젝트 수만큼 좌표 배열에 넣어두고 밑에 포문 돌려야함

	


	return S_OK;
}

void objectManager::release()
{
	_vObject.clear();
}

void objectManager::update()
{
	//오브젝트 벡터 돌리면서 업데이트 시켜주면 된다
	RECT tempRc, tempRc2, tempRc3;
	float x, y;

	for (int i = 0; i < _vObject.size(); i++)
	{
		if (OBJECT_DESTROY == _vObject[i]->getState()) continue;
		if (_vObject[i]->getType() == WOODENBOX || _vObject[i]->getType() == SKULL_DRUMGRAY || _vObject[i]->getType() == SKULL_DRUMRED || 
			_vObject[i]->getType() == PRISONER || _vObject[i]->getType() == AMERICAN_FLAG || _vObject[i]->getType() == HELICOPTER)
		{
			switch (_vObject[i]->getState())
			{
			case OBJECT_IDLE:
				//if (IntersectRect(&tempRc, &_playerManager->getPlayer()->getRcRambro(), &_vObject[i]->getRect()) && _vObject[i]->getType())
				//{
				//	int width = _playerManager->getPlayer()->getRcRambro().right - _playerManager->getPlayer()->getRcRambro().left;
				//	int height = _playerManager->getPlayer()->getRcRambro().bottom - _playerManager->getPlayer()->getRcRambro().top;
				//
				//	if (_playerManager->getPlayer()->getRcRambro().left + width / 2 < tempRc.left)
				//		_playerManager->getPlayer()->setX(_playerManager->getPlayer()->getX() - (tempRc.right - tempRc.left));
				//	else if (_playerManager->getPlayer()->getRcRambro().left + width / 2 > tempRc.right)
				//		_playerManager->getPlayer()->setX(_playerManager->getPlayer()->getX() + (tempRc.right - tempRc.left));
				//
				//	if (_playerManager->getPlayer()->getRcRambro().top + height / 2 < tempRc.top)
				//		_playerManager->getPlayer()->setY(_playerManager->getPlayer()->getY() - (tempRc.bottom - tempRc.top));
				//	else if (_playerManager->getPlayer()->getRcRambro().top + height / 2 > tempRc.bottom)
				//		_playerManager->getPlayer()->setY(_playerManager->getPlayer()->getY() + (tempRc.bottom - tempRc.top));
				//}
				if (_vObject[i]->getType() == HELICOPTER)
				{
					if (KEYMANAGER->isOnceKeyDown('M'))
					{
						_vObject[i]->setIsStart(true);
					}
					if (KEYMANAGER->isOnceKeyDown('N'))
					{
						_vObject[i]->setState(OBJECT_MOVE);
					}
					if (_flagCount >= _maxFlag - 1)
					{
						_isGameClear = true;
					}
					//if (_isGameClear && _isDead)
					if (_isDead)
						_vObject[i]->setIsStart(true);
				}
				if (_vObject[i]->getType() == PRISONER) // ||_vObject[i]->getType() == WOODENBOX)
				{
					_vObject[i]->setOldY(_vObject[i]->getY());
					_vObject[i]->setGravity(_vObject[i]->getGravity() + 0.55f);
					_vObject[i]->setSpeed(8.0f);
					_vObject[i]->setY(_vObject[i]->getY() - sinf(-PI_2) * _vObject[i]->getSpeed() + _vObject[i]->getGravity());
					this->collisionProcess();
					if (_vObject[i]->getType() == PRISONER)
					{
						if (_vObject[i]->getY() >= _vObject[i]->getOldY() + 5)
						{
							_vObject[i]->setGravity(0);
							_vObject[i]->setState(OBJECT_MOVE);
							_vObject[i]->setIsActived(true);
							EFFECTMANAGER->woodDebris(_vObject[i]->getX(), _vObject[i]->getY(), true);
						}
					}
				}
			case OBJECT_MOVE:
				if (_vObject[i]->getType() == PRISONER) // ||_vObject[i]->getType() == WOODENBOX)
				{
					_vObject[i]->setOldY(_vObject[i]->getY());
					_vObject[i]->setGravity(_vObject[i]->getGravity() + 0.55f);
					_vObject[i]->setSpeed(8.0f);
					_vObject[i]->setY(_vObject[i]->getY() - sinf(-PI_2) * _vObject[i]->getSpeed() + _vObject[i]->getGravity());
					this->collisionProcess();
				}
				if (_vObject[i]->getType() == HELICOPTER && _vObject[i]->getisArrived())
				{
					//float x = _mapData->getObject()[390]._rc.left, y = _mapData->getObject()[390]._rc.top;
					//EFFECTMANAGER->explosion(x, y);
					//x = _mapData->getObject()[394]._rc.left, y = _mapData->getObject()[394]._rc.top;
					//EFFECTMANAGER->rambroGrenadeExplosion(_mapData->getObject()[396]._rc.left, _mapData->getObject()[396]._rc.top);
					//EFFECTMANAGER->playFountainNoCollision("orangeSparks", x, y);
					//EFFECTMANAGER->playFountainNoCollision("lightOrangeSparks", x, y);
					//EFFECTMANAGER->playFountain("yellowSparks", x, y);
					//EFFECTMANAGER->playFountainNoCollision("rock1", _mapData->getObject()[396]._rc.left, _mapData->getObject()[396]._rc.top);
					//EFFECTMANAGER->playFountainNoCollision("rock2", _mapData->getObject()[397]._rc.left, _mapData->getObject()[397]._rc.top);
					//EFFECTMANAGER->playFountainNoCollision("rock3", _mapData->getObject()[398]._rc.left, _mapData->getObject()[398]._rc.top);
					//EFFECTMANAGER->playFountainNoCollision("rock4", _mapData->getObject()[399]._rc.left, _mapData->getObject()[399]._rc.top);
					//EFFECTMANAGER->playFountainNoCollision("rock5", _mapData->getObject()[400]._rc.left, _mapData->getObject()[400]._rc.top);
				}
				break;
			case OBJECT_DESTROY:
				break;
			}
		}
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
		if (KEYMANAGER->isToggleKey('2'))
		{
			if (_vObject[i]->getType() == HELICOPTER)
				Rectangle(hdc, _vObject[i]->getActivationRect().left - CAMERAMANAGER->getCamera().left, _vObject[i]->getActivationRect().top - CAMERAMANAGER->getCamera().top, _vObject[i]->getActivationRect().right - CAMERAMANAGER->getCamera().left, _vObject[i]->getActivationRect().bottom - CAMERAMANAGER->getCamera().top);
			
			char str[64];
			sprintf_s(str, "%d", i);
			TextOut(hdc, _vObject[i]->getX() + 5 - CAMERAMANAGER->getCamera().left, _vObject[i]->getY() - 10 - CAMERAMANAGER->getCamera().top, str, strlen(str));
		}
	}
}

void objectManager::collisionProcess()
{
	for (int i = 0; i < _vObject.size(); ++i)
	{
		float x = _vObject[i]->getX();
		float y = _vObject[i]->getY();

		if (COLLISIONMANAGER->pixelCollision(_vObject[i]->getRect(), x, y, _vObject[i]->getSpeed(), _vObject[i]->getGravity(), 3) == GREEN) //아래
		{
			_vObject[i]->setGravity(0);
			_vObject[i]->setSpeed(0);
		}
		if (COLLISIONMANAGER->pixelCollision(_vObject[i]->getRect(), x, y, _vObject[i]->getSpeed(), _vObject[i]->getGravity(), 2) == GREEN) //오
		{
			_vObject[i]->setSpeed(0);
		}
		if (COLLISIONMANAGER->pixelCollision(_vObject[i]->getRect(), x, y, _vObject[i]->getSpeed(), _vObject[i]->getGravity(), 0) == GREEN) //왼
		{
			_vObject[i]->setSpeed(0);
		}
		if (COLLISIONMANAGER->pixelCollision(_vObject[i]->getRect(), x, y, _vObject[i]->getSpeed(), _vObject[i]->getGravity(), 1) == GREEN) //위
		{
			_vObject[i]->setAngle(PI2 - _vObject[i]->getAngle());
		}
		_vObject[i]->setX(x);
		_vObject[i]->setY(y);
	}
}