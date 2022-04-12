#include "Stdafx.h"
#include "CropSprite.h"

HRESULT CropSprite::init(void)
{
	mBaseSeedSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->CropsSeedSprite);
	mBaseStageSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->CropsStageSprite);

	mCropXToSprite[eCropType::CT_PARSNIP] = 0;
	mCropYToSprite[eCropType::CT_PARSNIP] = 0;
	mCropMaxStageToSprite[eCropType::CT_PARSNIP] = 6;

	for (int i = eCropType::CT_PARSNIP; i < eCropType::CT_END; i++) {
		int frameX = i % mBaseSeedSprite->getMaxFrameX();
		int frameY = i / mBaseSeedSprite->getMaxFrameX();

		mIdleSeedBitmapList[i] = mBaseSeedSprite->getFrameBitmap(frameX, frameY);
		mIdleBitmapList[i] = mBaseStageSprite->getFrameBitmap(mCropXToSprite[i] + mCropMaxStageToSprite[i], mCropYToSprite[i] + 1);

		for (int stageCount = 0; stageCount < mCropMaxStageToSprite[i]; stageCount++) {
			ImageGp* cropStageImg = new ImageGp;
			cropStageImg->init(getMemDc(), mBaseStageSprite->getFrameBitmapToIndex(mCropXToSprite[i] + stageCount, mCropYToSprite[i], 0, 1));
			mVCropStageImg[i].push_back(cropStageImg);
		}
	}

	return S_OK;
}

void CropSprite::release()
{
}
