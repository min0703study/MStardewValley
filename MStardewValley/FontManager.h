
#pragma once
#include "SingletonBase.h"

class FontManager : public SingletonBase <FontManager>
{
public:
	HFONT mFontList[3];
public:
	HRESULT init();
	void release();

	void drawText(HDC hdc, string printString, int destX, int destY, int fontIndex, COLORREF color);

	FontManager() {}
	~FontManager() {}
};

