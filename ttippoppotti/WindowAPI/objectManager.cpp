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

	for (int i = 0; i < 10; i++)
	{
		objectA* object = _factory->createObject(type);

		//��ǥ �־���� ������Ʈ��

		type = (OBJECT_TYPE)RND->getFromIntTo(0, 1);
		
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

		_vObject[i]->render();
	}

}