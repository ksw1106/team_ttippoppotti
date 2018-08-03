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

	for (int i = 0; i < 10; i++)
	{
		objectA* object = _factory->createObject(type);

		//좌표 넣어야함 오브젝트에

		type = (OBJECT_TYPE)RND->getFromIntTo(0, 1);
		
		_vObject.push_back(object);
	}

	return S_OK;
}

void objectManager::release()
{
	//init에서 공장 만들면 해제 해야한다
	SAFE_DELETE(_factory);
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

		_vObject[i]->render();
	}

}