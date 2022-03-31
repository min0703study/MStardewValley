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

//==Singleton
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

#define IMGCLASS ImageClass::getSingleton()
#define SOUNDCLASS SoundClass::getSingleton()
#define TILECLASS TileClass::getSingleton()
//Singleton==

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
// # ��ũ�� �Լ� # (Ŭ�������� �����Ҵ�� �κ� ����)
// =============================================
#define SAFE_DELETE(p)         {if(p) {delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p)   {if(p) {delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p)         {if(p) {(p)->release(); (p)=nullptr;}}

//==CommonFunction
#include "RandomFunction.h"
#include "ShapeFunction.h"
#include "Utils.h"
//CommonFunction==

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
#include "GdiPlusFunction.h"

#include "ImageClass.h"
#include "SoundClass.h"
#include "TileClass.h"

#include "UIInfo.h"
#include "tileNode.h"
#include "common.h"
#include "FileUtil.h"
//MANAGER==

using namespace MY_UTIL;

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
extern Gdiplus::PointF _ptfMouse;

#define DEBUG_MODE				true

#define DEBUG_ALL_TAG			"ALL"
#define DEBUG_GAME_UI_TAG		"GAME_UI"
#define DEBUG_IMG_BASE_TAG		"IMG_BASE"
#define DEBUG_IMG_GP_TAG		"IMG GP"
#define DEBUG_MY_TAG			"��ä��"
#define DEBUG_MIN				"��ä��"
#define TRANCECOLOR				RGB(255, 0, 255)
#define GAME_FONT				L"Leferi Base Type Bold"

#define PLAYER_MOVE_SPEED		2.0f			


enum eGameDirection {
	GD_UP,
	GD_RIGHT,
	GD_LEFT,
	GD_DOWN,
};

enum ePlayerStat {
	PS_IDLE,
	PS_WALK,
	PS_ATTACK_1,
	PS_ATTACK_2,
	PS_END
};

enum eToolType {
	TT_PICK, //���
	TT_AXE, //����
	TT_WATERING_CAN, //���Ѹ���
	TT_HOE, //�����°�
	TT_END
};

enum eToolLevel {
	TL_NORMAL,
	TL_COPPER,
	TL_IRON,
	TL_GOLD,
	TL_IRIDIUM,
	TL_END
};


#define TILE_SIZE		70.0f

#define PLAYER_WIDTH		TILE_SIZE
#define PLAYER_HEIGHT		TILE_SIZE * 2.0f

#define PLAYER_HAIR_WIDTH	50.0f
#define PLAYER_HAIR_HEIGHT	100.0f
#define PLAYER_CLOTH_WIDTH	20.0f
#define PLAYER_CLOTH_HEIGHT	20.0f