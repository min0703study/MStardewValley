#include "Stdafx.h"
#include "MapPalette.h"

HRESULT MapPalette::init(void)
{
	ImageGp* mines1To30Palette = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapMines1To30);

	int xCount = mines1To30Palette->getMaxFrameX() + 1;
	int yCount = mines1To30Palette->getMaxFrameY() + 1;
	
	mMinePalette = new ImageGp*[yCount];
	for (int y = 0; y < yCount; y++) {
		mMinePalette[y] = new ImageGp[xCount];
	}

	for (int y = 0; y < yCount; y++) {
		for (int x= 0; x < xCount; x++) {
			mMinePalette[y][x].init(getMemDc(), mines1To30Palette->getFrameBitmap(x, y, TILE_SIZE, TILE_SIZE));
		}
	}
	return S_OK;
}

void MapPalette::release(void)
{
}

ImageGp** MapPalette::getPalette()
{
	return mMinePalette;
}
