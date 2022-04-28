#include "Stdafx.h"
#include "ForageSprite.h"

HRESULT ForageSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->clone(IMGCLASS->ForageSprite);

	mSpriteInfoList[FT_WOOD].XIndex = 5;
	mSpriteInfoList[FT_WOOD].YIndex = 12;

	for (int type = eForageType::FT_WOOD; type < eForageType::FT_END; type++) {
		SpriteInfo& info = mSpriteInfoList[type];

		mIdleBitmapList[type] = new ImageGp;
		mIdleBitmapList[type]->init(getMemDc(), mBaseSprite->getFrameBitmap(info.XIndex, info.YIndex));
	}

	return S_OK;
}

void ForageSprite::release()
{
}
