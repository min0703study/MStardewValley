#include "Stdafx.h"
#include "HoedSprite.h"

HRESULT HoedSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->HoedSprite);

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			mHoedNormal[y][x] = new ImageGp;
			mHoedNormal[y][x]->init(getMemDc(), mBaseSprite->getFrameBitmap(y, x, TILE_SIZE, TILE_SIZE));
		}
	}


	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			mHoedWet[y][x] = new ImageGp;
			mHoedWet[y][x]->init(getMemDc(), mBaseSprite->getFrameBitmap(y, x + 4, TILE_SIZE, TILE_SIZE));
		}
	}

	return S_OK;
}

ImageGp* HoedSprite::getNormalHoed(int x, int y) {
	return mHoedNormal[y][x];
}

ImageGp* HoedSprite::getWetHoed(int x, int y) {
	return mHoedWet[y][x];
}

void HoedSprite::release()
{
}
