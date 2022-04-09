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
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		SCENEMANAGER->init();
		
		GDIPLUSMANAGER->init(getMemDc());
		IMGCLASS->init();

		CAMERA->init(0, 0, CAMERA_X, CAMERA_Y);
		SOUNDMANAGER->init();
		UIMANAGER->init();
		JSONSAVELOADER->init();
		
		JSONMANAGER->init();
		JSONCLASS->init();

		ITEMMANAGER->init();
		MAPTILEMANAGER->init();

		SOUNDCLASS->init();
		MAPTILECLASS->init();

		TOOLSPRITE->init();
		WEAPONSPRITE->init();
		ITEMCLASS->init();

		MINESSPRITE->init();
		MONSTERSPRITE->init();
		MAPPALETTE->init();
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

		ITEMCLASS->release();
		ITEMCLASS->releaseSingleton();

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

		ITEMMANAGER->release();
		ITEMMANAGER->releaseSingleton();

		MAPTILECLASS->release();
		MAPTILECLASS->releaseSingleton();

		MAPPALETTE->release();
		MAPPALETTE->releaseSingleton();
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
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
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

