#include "Stdafx.h"
#include "CropSprite.h"

HRESULT CropSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->CropsSeedSprite);
	for (int i = eCropKinds::CK_PARSNIP; i < eCropKinds::CK_END; i++) {
		int frameX = i % mBaseSprite->getMaxFrameX();
		int frameY = i / mBaseSprite->getMaxFrameX();

		mIdleBitmapList[i] = mBaseSprite->getFrameBitmap(frameX, frameY);
	}

	return S_OK;
}
