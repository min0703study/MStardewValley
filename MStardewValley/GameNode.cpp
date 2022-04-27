#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_backBufferKey = "backBuffer";
	_backBuffer = IMAGEMANAGER->addImage(_backBufferKey, WINSIZE_INT_X, WINSIZE_INT_Y);

	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	setlocale(LC_ALL, "Korean");
	SetTimer(_hWnd, UPDATE_TIMER_ID, 10, NULL);

	_ptMouse = { 0,0 };
	_ptfMouse = { 0,0 };

	if (_managerInit) {
		KEYMANAGER->init();
		RND->init();
		TIMEMANAGER->init();

		//json
		JSONSAVELOADER->init();
		JSONMANAGER->init();
		JSONCLASS->init();

		//image
		IMAGEMANAGER->init();
		GDIPLUSMANAGER->init(getMemDc());
		IMGCLASS->init();

		SCENEMANAGER->init();
		CAMERA->init(0, 0, CAMERA_X, CAMERA_Y);
		
		//sound
		SOUNDMANAGER->init();
		SOUNDCLASS->init();

		//item
		MINESSPRITE->init();
		WEAPONSPRITE->init();
		TOOLSPRITE->init();
		CROPSPRITE->init();
		FORAGESPRITE->init();
		ITEMMANAGER->init();

		//map
		MAPTILEMANAGER->init();
		MAPPALETTEMANAGER->init();
		MAPCLASS->init();

		PLAYERSPRITE->init();
		MONSTERSPRITE->init();

		UIMANAGER->init();

		HOEDSPRITE->init();
		TREESPRITE->init();
		NPCSPRITE->init();
		NPCMANAGER->init();

	}

	return S_OK;
}

void GameNode::release(void)
{
	KillTimer(_hWnd, UPDATE_TIMER_ID);

	if (_managerInit) {
		KEYMANAGER->releaseSingleton();

		RND->releaseSingleton();
		
		JSONCLASS->release();
		JSONCLASS->releaseSingleton();

		ITEMCLASS->releaseSingleton();

		PLAYERSPRITE->release();
		PLAYERSPRITE->releaseSingleton();

		MINESSPRITE->release();
		MINESSPRITE->releaseSingleton();

		MONSTERSPRITE->release();
		MONSTERSPRITE->releaseSingleton();

		TOOLSPRITE->release();
		TOOLSPRITE->releaseSingleton();

		WEAPONSPRITE->release();
		WEAPONSPRITE->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		MAPTILEMANAGER->release();
		MAPTILEMANAGER->releaseSingleton();

		GDIPLUSMANAGER->release();
		CAMERA->release();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		SOUNDCLASS->release();
		SOUNDCLASS->releaseSingleton();

		UIMANAGER->release();
		UIMANAGER->releaseSingleton();

		JSONMANAGER->release();
		JSONMANAGER->releaseSingleton();

		JSONSAVELOADER->release();
		JSONSAVELOADER->releaseSingleton();

		CROPSPRITE->release();
		CROPSPRITE->releaseSingleton();

		ITEMMANAGER->release();
		ITEMMANAGER->releaseSingleton();

		MAPCLASS->release();
		MAPCLASS->releaseSingleton();

		MAPPALETTEMANAGER->release();
		MAPPALETTEMANAGER->releaseSingleton();

		NPCSPRITE->release();
		NPCSPRITE->releaseSingleton();
		NPCMANAGER->releaseSingleton();

		FORAGESPRITE->release();
		FORAGESPRITE->releaseSingleton();

	}

	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void) {
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		render();
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);

		_ptfMouse.X = LOWORD(lParam);
		_ptfMouse.Y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void GameNode::render()
{
}

