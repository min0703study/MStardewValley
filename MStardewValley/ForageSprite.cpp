#include "Stdafx.h"
#include "ForageSprite.h"

HRESULT ForageSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->clone(IMGCLASS->ForageSprite);

	mSpriteInfoList[FT_WOOD].XIndex = 1;
	mSpriteInfoList[FT_WOOD].YIndex = 6;

	mSpriteInfoList[FT_FIBER].XIndex = 2;
	mSpriteInfoList[FT_FIBER].YIndex = 6;

	mSpriteInfoList[FT_STONE].XIndex = 4;
	mSpriteInfoList[FT_STONE].YIndex = 6;

	for (int type = FT_WOOD; type != FT_END; type++) {
		mIdleBitmapList[type] = new ImageGp;
		mIdleBitmapList[type]->init(getMemDc(), mBaseSprite->getFrameBitmap(mSpriteInfoList[type].XIndex, mSpriteInfoList[type].YIndex));
	}

	return S_OK;
}

void ForageSprite::release()
{
}
