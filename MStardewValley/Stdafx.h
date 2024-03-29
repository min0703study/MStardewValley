#pragma once

#include <SDKDDKver.h>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#include "inc/fmod.hpp"

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
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <fstream>
#include <queue>
#include <codecvt>

#include <algorithm>
#include <functional>

using namespace std;

#include "json/json.h"

#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus")

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
#define WINSTYLE		WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX

#define WINSTART_X		0
#define WINSTART_Y		0

#define WINSIZE_X			1920.0f
#define WINSIZE_Y			1080.0f

#define WIN_DETAIL_SIZE_X	1920.0f - 40.0f
#define WIN_DETAIL_SIZE_Y	1080.0f - 40.0f

#define WINSIZE_INT_X		1920
#define WINSIZE_INT_Y		1080

#define CAMERA_X			WINSIZE_X
#define CAMERA_Y			WINSIZE_Y
#endif

#define WINSIZE_R_X			(WINSIZE_X - 15.0f)
#define WINSIZE_R_Y			(WINSIZE_Y - 45.0f)

#define WIN_CENTER_X		(WINSIZE_X / 2.0f)
#define WIN_CENTER_Y		(WINSIZE_Y / 2.0f)

#define UP_KEY					'W'
#define DOWN_KEY				'S'
#define LEFT_KEY				'A'
#define RIGHT_KEY				'D'

#define PI						3.14f

// =============================================
// # 매크로 함수 # (클래스에서 동적할당된 부분 해제)
// =============================================
#define SAFE_DELETE(p)         {if(p != nullptr || p != NULL) {delete (p); (p)=nullptr;}}
#define IS_NULL(p)				(p == nullptr || p == NULL)
#define SAFE_DELETE_ARRAY(p)   {if(p) {delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p)         {if(p) {(p)->release(); (p)=nullptr;}}

#define LOG_DEFAULT_TAG		"DEFAULT"
#define LOG_MOUSE_PT_TAG	"MOUSE"
#define LOG_KEYMNG_TAG		"KEYMNG"
#define LOG_WARNING_TAG		"!WARNING!"
#define LOG_GAME_UI_TAG		"GAME_UI"
#define LOG_IMG_BASE_TAG	"IMG_BASE"
#define LOG_IMG_GP_TAG		"IMG_GP"
#define LOG_ITEM			"ITEM"
#define LOG_MY_TAG			"민채영"

#include "common.h"
#include "LogUtil.h"
#include "tileNode.h"
// ==

//==Singleton MANAGER
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define TEXTDATAMANAGER TextDataManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define GDIPLUSMANAGER GdiPlusManager::getSingleton()
#define CAMERA Camera::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define UIMANAGER UIManager::getSingleton()
#define JSONSAVELOADER JsonSaveLoader::getSingleton()
#define JSONMANAGER JsonManager::getSingleton()
#define ITEMMANAGER ItemManager::getSingleton()
#define MAPTILEMANAGER MapManager::getSingleton()
#define MAPPALETTEMANAGER MapPaletteManager::getSingleton()
#define NPCMANAGER NpcManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define EFFECTMANAGER EffectManager::getSingleton()
//Singleton MANAGER ==

//==Singleton Resource
#define IMGCLASS ImageClass::getSingleton()
#define SOUNDCLASS SoundClass::getSingleton()
#define JSONCLASS JsonClass::getSingleton()
#define ITEMCLASS ItemClass::getSingleton()
#define MAPCLASS MapClass::getSingleton()
#define SCENECLASS SceneClass::getSingleton()
#define HOEDSPRITE HoedSprite::getSingleton()
//Singleton Resource ==

//== Singleton Player
#define PLAYER Player::getSingleton()
//Singleton Player ==

//==Sprite
#define MINESSPRITE	MinesSprite::getSingleton()
#define MONSTERSPRITE MonsterSprite::getSingleton()
#define TOOLSPRITE ToolSprite::getSingleton()
#define WEAPONSPRITE WeaponSprite::getSingleton()
#define CROPSPRITE CropSprite::getSingleton()
#define PLAYERSPRITE PlayerSprite::getSingleton()
#define TREESPRITE TreeSprite::getSingleton()
#define NPCSPRITE NpcSprite::getSingleton()
#define FORAGESPRITE ForageSprite::getSingleton()
#define CRAFTABLESSPRITE CraftablesSprite::getSingleton()
//==Sprite

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
#include "FontManager.h"
#include "TempSoundManager.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "GdiPlusManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SoundManager.h"
#include "UIManager.h"
#include "JsonSaveLoader.h"
#include "JsonManager.h"
#include "ItemManager.h"
#include "MapManager.h"
#include "MapPaletteManager.h"
#include "NpcManager.h"
#include "EffectManager.h"

#include "ImageClass.h"
#include "SoundClass.h"
#include "JsonClass.h"
#include "ItemClass.h"
#include "MapClass.h"

#include "MinesSprite.h"
#include "MonsterSprite.h"
#include "ToolSprite.h"
#include "WeaponSprite.h"
#include "CropSprite.h"
#include "PlayerSprite.h"
#include "HoedSprite.h"
#include "TreeSprite.h"
#include "NpcSprite.h"
#include "SceneClass.h"
#include "ForageSprite.h"
#include "CraftablesSprite.h"
//MANAGER==

//==PLAYER
#include "Player.h"
//PLAYER==

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
extern Gdiplus::PointF _ptfMouse;
