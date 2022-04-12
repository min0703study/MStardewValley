#include "Stdafx.h"
#include "CropSprite.h"

HRESULT CropSprite::init(void)
{
	mBaseSeedSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->CropsSeedSprite);
	mBaseStageSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->CropsSeedSprite);

	for (int i = eCropType::CT_PARSNIP; i < eCropType::CT_END; i++) {
		int frameX = i % mBaseSeedSprite->getMaxFrameX();
		int frameY = i / mBaseSeedSprite->getMaxFrameX();

		mIdleBitmapList[i] = mBaseSeedSprite->getFrameBitmap(frameX, frameY);
	}

	return S_OK;
}

void CropSprite::release()
{
}
