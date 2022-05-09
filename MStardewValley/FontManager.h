
#pragma once
#include "SingletonBase.h"

class FontManager : public SingletonBase <FontManager>
{
public:
	HFONT mFontList[3];
	string mFont[3];
public:
	HRESULT init();
	void release();

	void drawText(HDC hdc, string printString, int destX, int destY, int fontIndex, COLORREF color);

	void drawText(HDC hdc, string printString, RectF rcF, int fontSize, int fontWidth, int fontIndex = 0, COLORREF color = RGB(0,0,0), eXStandard xPos = XS_LEFT);
	void drawText(HDC hdc, string printString, float x, float y, int fontSize, int fontWidth, int fontIndex, COLORREF color);

	FontManager() {}
	~FontManager() {}
};

