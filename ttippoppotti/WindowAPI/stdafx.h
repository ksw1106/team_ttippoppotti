// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include <SDKDDKVer.h>


#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <Windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
// C++ 런타임 헤더 파일입니다.
#include <iostream>
using namespace std;
// 자주사용하는 STL
#include <string>
#include <vector>
#include <map>
// 네임스페이스
#include "util.h"
using namespace MY_UTIL;


//=============================================================
//	## 내가 만든 헤더파일을 이곳에 추가한다 ##
//=============================================================
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "imageManager.h"
#include "sceneManager.h"
#include "timeManager.h"
#include "soundManager.h"
#include "effectManager.h"
#include "cameraManager.h"

#include "frameManager.h"
#include "objectManager.h"
#include "CollisionManager.h"
#include "saveData.h"
#include "txtData.h"

//=============================================================
//	## 싱글톤을 추가한다 ##
//=============================================================
#define KEYMANAGER keyManager::getSingleton()
#define RND randomFunction::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define CAMERAMANAGER cameraManager::getSingleton()

#define FRAMEMANAGER frameManager::getSingleton()
#define OBJECTMANAGER objectManager::getSingleton()
#define COLLISIONMANAGER CollisionManager::getSingleton()

#define SAVEDATA saveData::getSingleton()
#define TXTDATA txtData::getSingleton()
//=============================================================
//	## 디파인문 ## (윈도우창 초기화)
//=============================================================
#define WINNAME (LPTSTR)(TEXT(" TTIPPO FORCE -> 김민영, 김상원, 이문규, 이지웅"))
#define WINSTARTX	-9 // 1920/2 - 1280/2 380
#define WINSTARTY	0 // 1080/2 - 720/2 180
#define WINSIZEX		1920
#define WINSIZEY		1080
#define WINSTYLE		WS_CAPTION | WS_SYSMENU


//=============================================================
//	## 내가 만든 디파인 ##
//=============================================================
#define RED 101
#define GREEN 102
#define BLUE 103
#define MAGENTA RGB(255, 0 ,255)
//=============================================================
//	## 매크로함수 ## (클래스에서 동적할당된 부분 해제)
//=============================================================
#define SAFE_DELETE(p)		{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//=============================================================
//	## 전역변수 ##
//=============================================================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;