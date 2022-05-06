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

	mFont[0] = GAME_FONT_1_S;
	mFont[1] = GAME_FONT_2_S;
	mFont[2] = GAME_FONT_3_S;

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

void FontManager::drawText(HDC hdc, string printString, RectF rcF, int fontSize, int fontWidth, int fontIndex, COLORREF color, eXStandard xPos)
{
	int destX = 0;
	int destY = rcF.GetTop();

	switch (xPos) {
	case XS_LEFT:
		destX = static_cast<int>(rcF.GetLeft());
		break;
	case XS_RIGHT:
		SetTextAlign(hdc, TA_RIGHT);
		destX = static_cast<int>(rcF.GetRight());
		break;
	case XS_CENTER:
		SetTextAlign(hdc, TA_CENTER);
		destX = static_cast<int>(rcF.GetRight() - rcF.Width * 0.5f);
		break;
	}

	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, mFont[fontIndex].c_str());

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	TextOut(hdc, destX, destY, printString.c_str(), printString.size());

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}