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
}

void objectManager::render(HDC hdc)
{
	//������Ʈ ���� �����鼭 Ȱ��ȭ�� ������Ʈ�鸸 �׷��ָ� �ȴ�.
	//getMemDC() �� �����ϱ� hdc ���� �ȴ�.
}