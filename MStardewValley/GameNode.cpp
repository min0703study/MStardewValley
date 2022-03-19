#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_backBufferKey = "backBuffer";
	_backBuffer = IMAGEMANAGER->addImage(_backBufferKey, WINSIZE_X, WINSIZE_Y);

	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit) {
		setlocale(LC_ALL, "Korean");

		SetTimer(_hWnd, UPDATE_TIMER_ID, 10, NULL);

		KEYMANAGER->init();
		RND->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		SCENEMANAGER->init();
		GDIPLUSMANAGER->init(getMemDc());
		CAMERA->init(0, 0, 1000, 1000);
		SOUNDMANAGER->init();
		UIMANAGER->init();

		IMGCLASS->init();
		SOUNDCLASS->init();
		_ptMouse = { 0,0 };
	}

	return S_OK;
}

void GameNode::release(void)
{
	if (_managerInit) {
		KillTimer(_hWnd, UPDATE_TIMER_ID);

		KEYMANAGER->releaseSingleton();

		RND->releaseSingleton();
		
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		GDIPLUSMANAGER->release();
		CAMERA->release();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		SOUNDCLASS->release();
		SOUNDCLASS->releaseSingleton();

		UIMANAGER->release();
		UIMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void) {
	//InvalidateRect(_hWnd, NULL, false);
	UIMANAGER->update();
}

void GameNode::addTimer(int sec, int timerId)
{
	SetTimer(_hWnd, timerId, sec * 1000, NULL);
}

void GameNode::deleteTimer(int timerId)
{
	KillTimer(_hWnd, timerId);
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		render();
		EndPaint(hWnd, &ps);
		break;
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

void GameNode::render()
{
	//·»´õ¸µ event
}

