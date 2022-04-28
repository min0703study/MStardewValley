#pragma once

#define UPDATE_TIMER_ID		1

#include "common.h"
#include "ImageBase.h"
#include "ImageGp.h"

static string _backBufferKey = "backBuffer";
static ImageBase* _backBuffer = IMAGEMANAGER->addImage(_backBufferKey, WINSIZE_INT_X, WINSIZE_INT_Y);

class GameNode
{
private:
	HDC _hdc;
	bool _managerInit;
public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);

	virtual void update(void);
	virtual void release(void);
	virtual void render(void);

	ImageBase* getBackBuffer(void) const { return _backBuffer; }
	string getBackBufferKey(void) { return _backBufferKey; }

	HDC getMemDc() const { return getBackBuffer()->getMemDC(); }
	HDC getHdc() { return _hdc; }
	
	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	GameNode() {};
	virtual ~GameNode() {};

};

