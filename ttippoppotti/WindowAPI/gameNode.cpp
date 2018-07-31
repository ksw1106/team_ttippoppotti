#include "stdafx.h"
#include "gameNode.h"

//=============================================================
//	## �ʱ�ȭ ## init(void)
//=============================================================
HRESULT gameNode::init(void)
{
	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		//SetTimer(_hWnd, 1, 10, NULL);		//Ÿ�̸� �ʱ�ȭ
		KEYMANAGER->init();					//Ű�Ŵ��� �ʱ�ȭ
		RND->init();						//������� �ʱ�ȭ
		IMAGEMANAGER->init();				//�̹����Ŵ��� �ʱ�ȭ
		SCENEMANAGER->init();				//���Ŵ��� �ʱ�ȭ
		TIMEMANAGER->init();				//Ÿ�ӸŴ��� �ʱ�ȭ
		SOUNDMANAGER->init();				//����Ŵ��� �ʱ�ȭ
		//EFFECTMANAGER->init();				//����Ʈ�Ŵ��� �ʱ�ȭ

		FRAMEMANAGER->init();				//�����ӸŴ��� �ʱ�ȭ
		OBJECTMANAGER->init();				//������Ʈ�Ŵ��� �ʱ�ȭ
		CAMERAMANAGER->init();				//ī�޶�Ŵ��� �ʱ�ȭ
		COLLISIONMANAGER->init();
		SAVEDATA->init();					//���̺굥���� �ʱ�ȭ
		TXTDATA->init();					//�ؽ�Ʈ������ �ʱ�ȭ
	}

	return S_OK;
}

//=============================================================
//	## ���� ## release(void)
//=============================================================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//Ÿ�̸� ����
		//KillTimer(_hWnd, 1);
		//Ű�Ŵ��� �̱��� ����
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		//������� �̱��� ����
		RND->release();
		RND->releaseSingleton();
		//�̹����Ŵ��� �̱��� ����
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//���Ŵ��� �̱��� ����
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		//Ÿ�ӸŴ��� �̱��� ����
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		//����Ŵ��� �̱��� ����
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		//����Ʈ�Ŵ��� �̱��� ����
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		//�����ӸŴ��� �̱��� ����
		FRAMEMANAGER->release();
		FRAMEMANAGER->releaseSingleton();
		//������Ʈ�Ŵ��� �̱��� ����
		OBJECTMANAGER->release();
		OBJECTMANAGER->releaseSingleton();
		//ī�޶�Ŵ��� �̱��� ����
		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();

		COLLISIONMANAGER->release();
		COLLISIONMANAGER->releaseSingleton();
		//���̺굥���� �̱��� ����
		SAVEDATA->release();
		SAVEDATA->releaseSingleton();
		//�ؽ�Ʈ������ �̱��� ����
		TXTDATA->release();
		TXTDATA->releaseSingleton();
	}

	//DC ����
	ReleaseDC(_hWnd, _hdc);
}

//=============================================================
//	## ������Ʈ ## update(void)
//=============================================================
void gameNode::update(void)
{
}

//=============================================================
//	## ���� ## render(void)
//=============================================================
void gameNode::render(void)
{
}

//=============================================================
//	## �������ν��� ##
//=============================================================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_MOUSEMOVE:		
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:		
		switch (wParam)
		{
		case VK_ESCAPE:		
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:		
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}