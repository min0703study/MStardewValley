#include "Stdafx.h"
#include "MapPalette.h"

HRESULT MapPalette::init(void)
{
	mines1To30Palette = GDIPLUSMANAGER->cloneImage(IMGCLASS->MapMines1To30);

	float mines1To30PaletteW = (mines1To30Palette->getMaxFrameX() + 1) * TILE_SIZE;
	float mines1To30PaletteH = (mines1To30Palette->getMaxFrameY() + 1) * TILE_SIZE;

	mines1To30Palette->setSize(mines1To30PaletteW, mines1To30PaletteH);

	int xCount = mines1To30Palette->getMaxFrameX() + 1;
	int yCount = mines1To30Palette->getMaxFrameY() + 1;
	
	mMinePalette = new ImageGp*[yCount];
	for (int y = 0; y < yCount; y++) {
		mMinePalette[y] = new ImageGp[xCount];
	}

	for (int y = 0; y < yCount; y++) {
		for (int x= 0; x < xCount; x++) {
			mMinePalette[y][x].init(getMemDc(), mines1To30Palette->getFrameBitmap(x, y));
		}
	}
	return S_OK;
}

void MapPalette::release(void)
{
}

ImageGp* MapPalette::getBaseSprite()
{
	return mines1To30Palette;
}

ImageGp** MapPalette::getPalette()
{
	return mMinePalette;
}

Bitmap* MapPalette::getBitmap(int startX, int startY, int xCount, int yCount)
{
	return mines1To30Palette->getFrameBitmapToIndex(startX, startY, xCount, yCount);
}

