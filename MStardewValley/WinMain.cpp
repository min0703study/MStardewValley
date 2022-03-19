#include "Stdafx.h"
#include "MainGame.h"

HINSTANCE _hInstance;
HWND _hWnd;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

POINT _ptMouse;

GameNode* _gm;

//min 추가 - extern
int _winsizeX, _winsizeY;
int _winRealSizeX, _winRealSizeY;

//min 추가 - 임시 주석
//void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow) {

	_hInstance = hInstance;

	ULONG_PTR gpToken;
	Gdiplus::GdiplusStartupInput gpsi;
	if (GdiplusStartup(&gpToken, &gpsi, NULL) != Gdiplus::Status::Ok) return 0;

	DEVMODE dm;
	dm.dmBitsPerPel = 32;
	dm.dmPelsWidth = 1980;
	dm.dmPelsHeight = 1080;
	dm.dmDisplayFrequency = 60;

	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	// 화면이 종료되면 자동으로 원래 화면의 해상도로 복구
	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}

	_winsizeX = WINSIZE_X;
	_winsizeY = WINSIZE_Y;

	_winRealSizeX = _winsizeX - 15;
	_winRealSizeY = _winsizeY - 40;

	_gm = new MainGame;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = _hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WINSTYLE,
		WINSTART_X,
		WINSTART_Y,
		WINSIZE_X,
		WINSIZE_Y,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	//setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

	//FALED 매크로 (winerror.h)
	if (FAILED(_gm->init())) {
		return 0;
	};

	ShowWindow(_hWnd, nCmdShow);

	MSG message;
	
	while (true) {
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else {
			TIMEMANAGER->update(60.0f);
			_gm->update();
			_gm->render();
		}
	}

	/*
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	*/
	Gdiplus::GdiplusShutdown(gpToken);
	_gm->release();
	UnregisterClass(WINNAME, _hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _gm->MainProc(hWnd, iMessage, wParam, lParam);
}

/*
void setWindowSize(int x, int y, int width, int height) {
	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, WINSTYLE, false);
	SetWindowPos(_hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}
*/