#pragma once

#define UPDATE_TIMER_ID		1


#define RECT_MAKE_FUNCTION RectMakeCenter(mCenterX, mCenterY, mWidth, mHeight)
#define RECTF_MAKE_SIMPLE RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight)

#define RECT_MAKE(width, height) RectMakeCenter(mX, mY, width, height)
#define RECTF_MAKE_FUNCTION(x, y, width, height) RectF(x - (width / 2.0f), y - (height / 2.0f), width, height)

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

	ImageBase* getBackBuffer(void) { return _backBuffer; }
	string getBackBufferKey(void) { return _backBufferKey; }

	HDC getMemDc() { return getBackBuffer()->getMemDC(); }
	HDC getHdc() { return _hdc; }
	
	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	GameNode() {};
	virtual ~GameNode() {};

};

