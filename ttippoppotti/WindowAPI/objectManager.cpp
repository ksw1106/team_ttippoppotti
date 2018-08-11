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
	if (num == 1)
	{
		OBJECT_TYPE type;

		_fPos[0].x = _mapData->getObject()[8]._rc.left, _fPos[0].y = _mapData->getObject()[8]._rc.top;
		_fPos[1].x = _mapData->getObject()[10]._rc.left, _fPos[1].y = _mapData->getObject()[10]._rc.top;
		_fPos[2].x = _mapData->getObject()[235]._rc.left, _fPos[2].y = _mapData->getObject()[235]._rc.top;
		_fPos[3].x = _mapData->getObject()[137]._rc.left, _fPos[3].y = _mapData->getObject()[137]._rc.top;
		_fPos[4].x = _mapData->getObject()[457]._rc.left, _fPos[4].y = _mapData->getObject()[457]._rc.top;
		_fPos[5].x = _mapData->getObject()[462]._rc.left, _fPos[5].y = _mapData->getObject()[462]._rc.top;
		_fPos[6].x = _mapData->getObject()[365]._rc.left, _fPos[6].y = _mapData->getObject()[365]._rc.top;
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

		//_boxPos[0].x = 800, _boxPos[0].y = 2070;
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

		//_helicopterPos[0].x = 3101, _helicopterPos[0].y = 519;
		//for (int i = 0; i < 1; i++)
		//{
		//	type = HELICOPTER;
		//
		//	objectA* object = _factory->createObject(type);
		//	object->setPosition(_helicopterPos[i].x, _helicopterPos[i].y);
		//
		//	_vObject.push_back(object);
		//}

		_amFlagPos[0].x = 1853, _amFlagPos[0].y = 1225;
		_amFlagPos[1].x = 2923, _amFlagPos[1].y = 2037;
		_amFlagPos[2].x = 3324, _amFlagPos[2].y = 902;
		for (int i = 0; i < 3; i++)
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
	}
	else if(num == 2)
	{
		//2스테이지
	}
	
	_factory = new objectFactory;

	//스테이지에 오브젝트 몇개인지 찾아서 포문돌리자
	//오브젝트 수만큼 좌표 배열에 넣어두고 밑에 포문 돌려야함

	


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
	RECT tempRc, tempRc2, tempRc3;
	
	//if (!_mapData->getObject()[406]._isActived)
	//{
	//	EFFECTMANAGER->woodDebris(_vObject[12]->getX(), _vObject[12]->getY());
	//}
	//if (!_mapData->getObject()[407]._isActived)
	//{
	//	EFFECTMANAGER->woodDebris(_vObject[13]->getX(), _vObject[13]->getY());
	//	EFFECTMANAGER->explosion(_vObject[27]->getX(), _vObject[27]->getY());
	//}
	//if (!_mapData->getObject()[433]._isActived)
	//{
	//	EFFECTMANAGER->woodDebris(_vObject[14]->getX(), _vObject[14]->getY());
	//	EFFECTMANAGER->explosion(_vObject[26]->getX(), _vObject[26]->getY());
	//}
	//if (!_mapData->getObject()[445]._isActived)
	//{
	//	EFFECTMANAGER->woodDebris(_vObject[18]->getX(), _vObject[18]->getY());
	//}
	//if (!_mapData->getObject()[446]._isActived)
	//{
	//	EFFECTMANAGER->woodDebris(_vObject[19]->getX(), _vObject[19]->getY());
	//}
	//if (!_mapData->getObject()[455]._isActived)
	//{
	//	EFFECTMANAGER->woodDebris(_vObject[15]->getX(), _vObject[15]->getY());
	//}
	//if (!_mapData->getObject()[467]._isActived)
	//{
	//	EFFECTMANAGER->woodDebris(_vObject[24]->getX(), _vObject[24]->getY());
	//	EFFECTMANAGER->woodDebris(_vObject[25]->getX(), _vObject[25]->getY());
	//}
	//if (!_mapData->getObject()[468]._isActived)
	//{
	//	EFFECTMANAGER->woodDebris(_vObject[22]->getX(), _vObject[22]->getY());
	//	EFFECTMANAGER->woodDebris(_vObject[23]->getX(), _vObject[23]->getY());
	//}
	//if (!_mapData->getObject()[469]._isActived)
	//{
	//	EFFECTMANAGER->woodDebris(_vObject[20]->getX(), _vObject[20]->getY());
	//	EFFECTMANAGER->woodDebris(_vObject[21]->getX(), _vObject[21]->getY());
	//}

	for (int i = 0; i < _vObject.size(); i++)
	{
		if (OBJECT_DESTROY == _vObject[i]->getState()) continue;
		//if (_vObject[i]->getType() == WOODENBOX || _vObject[i]->getType() == SKULL_DRUMGRAY || _vObject[i]->getType() == SKULL_DRUMRED || _vObject[i]->getType() == PRISONER || _vObject[i]->getType() == AMERICAN_FLAG)
		//{
		//	switch (_vObject[i]->getState())
		//	{
		//	case OBJECT_IDLE:
		//		if (IntersectRect(&tempRc, &_playerManager->getPlayer()->getRcRambro(), &_vObject[i]->getRect()) && _vObject[i]->getType() != AMERICAN_FLAG)
		//		{
		//			int width = _playerManager->getPlayer()->getRcRambro().right - _playerManager->getPlayer()->getRcRambro().left;
		//			int height = _playerManager->getPlayer()->getRcRambro().bottom - _playerManager->getPlayer()->getRcRambro().top;

		//			if (_playerManager->getPlayer()->getRcRambro().left + width / 2 < tempRc.left)
		//				_playerManager->getPlayer()->setX(_playerManager->getPlayer()->getX() - (tempRc.right - tempRc.left));
		//			else if (_playerManager->getPlayer()->getRcRambro().left + width / 2 > tempRc.right)
		//				_playerManager->getPlayer()->setX(_playerManager->getPlayer()->getX() + (tempRc.right - tempRc.left));

		//			if (_playerManager->getPlayer()->getRcRambro().top + height / 2 < tempRc.top)
		//				_playerManager->getPlayer()->setY(_playerManager->getPlayer()->getY() - (tempRc.bottom - tempRc.top));
		//			else if (_playerManager->getPlayer()->getRcRambro().top + height / 2 > tempRc.bottom)
		//				_playerManager->getPlayer()->setY(_playerManager->getPlayer()->getY() + (tempRc.bottom - tempRc.top));
		//		}
		//		for (int j = 0; j < _playerManager->getPBullet()->getVPlayerBullet().size(); j++)
		//		{
		//			if (!_playerManager->getPBullet()->getVPlayerBullet()[j].isActived) continue;
		//			//총알과 박스/드럼통/감옥이 부딪혔을 때
		//			if (IntersectRect(&tempRc2, &_playerManager->getPBullet()->getVPlayerBullet()[j].rc, &_vObject[i]->getRect()))
		//			{
		//				if (_vObject[i]->getType() == WOODENBOX)
		//				{
		//					EFFECTMANAGER->woodDebris(_vObject[i]->getRect().left, _vObject[i]->getRect().top, _playerManager->getPlayer()->getIsLeft());
		//					_vObject[i]->setState(OBJECT_DESTROY);
		//				}
		//				else if (_vObject[i]->getType() == SKULL_DRUMGRAY || _vObject[i]->getType() == SKULL_DRUMRED)
		//				{
		//					for (int k = 0; k < _mapData->getObject().size(); k++)
		//					{
		//						POINT pt;
		//						pt.x = (_vObject[i]->getRect().left + (_vObject[i]->getRect().right - _vObject[i]->getRect().left) / 2);
		//						pt.y = (_vObject[i]->getRect().top + (_vObject[i]->getRect().bottom - _vObject[i]->getRect().top) / 2) + 68;

		//						if (PtInRect(&_mapData->getObject()[k]._rc, pt))
		//						{
		//							_mapData->deleteMapIndexByIndex(k, 5, 5);
		//							break;
		//						}
		//					}
		//					EFFECTMANAGER->explosion(_vObject[i]->getRect().left, _vObject[i]->getRect().top);
		//					CAMERAMANAGER->CameraShake();
		//					_vObject[i]->setState(OBJECT_DESTROY);
		//				}
		//				else if (_vObject[i]->getType() == PRISONER)
		//				{
		//					EFFECTMANAGER->woodDebris(_vObject[i]->getRect().left, _vObject[i]->getRect().top, _playerManager->getPlayer()->getIsLeft());
		//					_vObject[i]->setState(OBJECT_MOVE);
		//				}
		//				_playerManager->getPBullet()->getVPlayerBullet()[j].isActived = false;
		//			}
		//		}
		//		if (IntersectRect(&tempRc3, &_playerManager->getPlayer()->getRcRambro(), &_vObject[i]->getActivationRect()))
		//		{
		//			if (_vObject[i]->getType() == PRISONER)
		//				_vObject[i]->setIsActived(true);
		//			if (_vObject[i]->getType() == AMERICAN_FLAG)
		//				_vObject[i]->setState(OBJECT_MOVE);
		//		}
		//		break;
		//	case OBJECT_MOVE:
		//		if (_vObject[i]->getType() == PRISONER)
		//		{
		//			if (IntersectRect(&tempRc, &_playerManager->getPlayer()->getRcRambro(), &_vObject[i]->getRect()))
		//			{
		//				_vObject[i]->setState(OBJECT_DESTROY);
		//			}
		//			else
		//			{
		//				_vObject[i]->setGravity(_vObject[i]->getGravity() + 0.55f);
		//				_vObject[i]->setY(_vObject[i]->getY() + (-sinf(_vObject[i]->getAngle()) * _vObject[i]->getSpeed() + _vObject[i]->getGravity()));
		//				this->collisionProcess();
		//			}
		//		}
		//		break;
		//	case OBJECT_DESTROY:
		//		break;
		//	}
		//}
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
		if (KEYMANAGER->isToggleKey('3'))
		{
			char str[32];
			sprintf_s(str, "%d", i);
			TextOut(hdc, _vObject[i]->getX() + 10 - CAMERAMANAGER->getCamera().left, _vObject[i]->getY() + 10 - CAMERAMANAGER->getCamera().top, str, strlen(str));
		}
	}
	if (KEYMANAGER->isToggleKey('2'))
	{
		Rectangle(hdc, _playerManager->getPlayer()->getRcRambro().left - CAMERAMANAGER->getCamera().left,
			_playerManager->getPlayer()->getRcRambro().top - CAMERAMANAGER->getCamera().top,
			_playerManager->getPlayer()->getRcRambro().right - CAMERAMANAGER->getCamera().left,
			_playerManager->getPlayer()->getRcRambro().bottom - CAMERAMANAGER->getCamera().top);
	}

	char str[32];
	sprintf_s(str, "%d", _vObject[0]->getTargetIsActived());
	TextOut(hdc, 100, 700, str, strlen(str));

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