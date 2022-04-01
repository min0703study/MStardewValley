#pragma once
#include <SDKDDKver.h>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib, "jsoncpp/lib_json/json_vc71_libmtd.lib")

#include "inc/fmod.hpp"
#include "jsoncpp/include/json/json.h"

#include <Windows.h>

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <assert.h>
#include <mmsystem.h>
#include <iostream>
#include <iomanip>
#include <random>

#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <fstream>
#include <queue>

#include <algorithm>
#include <functional>

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus")

using namespace std;

#define FLOAT_EPSILON		0.001f
#define FLOAT_TO_INT(f1)	static_cast<int>(f1 + FLOAT_EPSILON)
#define FLOAT_TO_LONG(f1)	static_cast<long>(f1 + FLOAT_EPSILON)
#define FLOAT_EQUAL(f1, f2) (fabs(f1 - f2) <= FLOAT_EPSILON)

#define USE_FULLSCREEN			FALSE

#if USE_FULLSCREEN
#define WINNAME			(LPSTR)(TEXT("WindowsAPI"))
#define WINSTYLE		WS_POPUPWINDOW | WS_MAXIMIZE
#define WINSTART_X		0
#define WINSTART_Y		0

#define WINSIZE_X		GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y		GetSystemMetrics(SM_CYSCREEN)

#define CAMERA_X		GetSystemMetrics(SM_CXSCREEN)
#define CAMERA_Y		GetSystemMetrics(SM_CYSCREEN)
#else
#define WINNAME			(LPSTR)(TEXT("MStardewBalley"))
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

#define WINSTART_X		0
#define WINSTART_Y		0

#define WINSIZE_X		1920.0f
#define WINSIZE_Y		1080.0f

#define CAMERA_X		WINSIZE_X
#define CAMERA_Y		WINSIZE_Y

#endif

#define WINSIZE_R_X		(WINSIZE_X - 15.0f)
#define WINSIZE_R_Y		(WINSIZE_Y - 45.0f)

#define WIN_CENTER_X		(WINSIZE_R_X / 2.0f)
#define WIN_CENTER_Y		(WINSIZE_R_Y / 2.0f)

#define UP_KEY					'W'
#define DOWN_KEY				'S'
#define LEFT_KEY				'A'
#define RIGHT_KEY				'D'

// =============================================
// # 매크로 함수 # (클래스에서 동적할당된 부분 해제)
// =============================================
#define SAFE_DELETE(p)         {if(p) {delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p)   {if(p) {delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p)         {if(p) {(p)->release(); (p)=nullptr;}}

#define DEBUG_MODE				true

#define LOG_DEFAULT_TAG		"DEFAULT"
#define LOG_WARNING_TAG		"!WARNING!"
#define LOG_GAME_UI_TAG		"GAME_UI"
#define LOG_IMG_BASE_TAG	"IMG_BASE"
#define LOG_IMG_GP_TAG		"IMG_GP"
#define LOG_MY_TAG			"민채영"

#include "LogUtil.h"

// ==
#include "common.h"
#include "UIInfo.h"
#include "tileNode.h"
// ==

//==Singleton MANAGER
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEXTDATAMANAGER TextDataManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define GDIPLUSMANAGER GdiPlusManager::getSingleton()
#define CAMERA Camera::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define UIMANAGER UIManager::getSingleton()
//Singleton MANAGER ==

//==Singleton Resource
#define IMGCLASS ImageClass::getSingleton()
#define SOUNDCLASS SoundClass::getSingleton()
#define TILECLASS TileClass::getSingleton()
//Singleton Resource ==

//==CommonFunction
#include "RandomFunction.h"
#include "ShapeFunction.h"
#include "GdiPlusFunction.h"
//CommonFunction==

//== Util
#include "FileUtil.h"
//Util==

using namespace LOG;

//==MANAGER
#include "TimeManager.h"
#include "TempSoundManager.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "GdiPlusManager.h"
#include "FontManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SoundManager.h"
#include "UIManager.h"

#include "ImageClass.h"
#include "SoundClass.h"
#include "TileClass.h"
//MANAGER==

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
extern Gdiplus::PointF _ptfMouse;
