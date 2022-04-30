#include "Stdafx.h"
#include "FontManager.h"

HRESULT FontManager::init()
{
	mFontList[0] = CreateFont
	(
		20.0f, 0, 0, 5, 20.0f,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Leferi Base Type Bold")
	);

	/*
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
	*/

	return E_NOTIMPL;
}

void FontManager::release()
{
}

void FontManager::drawText(HDC hdc, string printString, int destX, int destY, int fontIndex, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	auto oldFont = (HFONT)SelectObject(hdc, mFontList[fontIndex]);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	TextOut(hdc, destX, destY, printString.c_str(), printString.size());

	SetTextColor(hdc, oldColor);
}