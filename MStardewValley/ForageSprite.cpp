#include "Stdafx.h"
#include "ForageSprite.h"

HRESULT ForageSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->clone(IMGCLASS->ForageSprite);
	mSpriteInfoList[FT_WOOD].XIndex = 2;
	mSpriteInfoList[FT_WOOD].YIndex = 6;

	for (int type = eForageType::FT_WOOD; type < eForageType::FT_END; type++) {
		SpriteInfo& info = mSpriteInfoList[type];

		mIdleBitmapList[type] = mBaseSprite->getFrameBitmap(info.XIndex, info.YIndex);
	}

	return S_OK;
}

void ForageSprite::release()
{
}
