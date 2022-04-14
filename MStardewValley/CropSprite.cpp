#include "Stdafx.h"
#include "CropSprite.h"

HRESULT CropSprite::init(void)
{
	mBaseSeedSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->CropsSeedSprite);
	mBaseStageSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->CropsStageSprite);

	mSpriteInfoList[eCropType::CT_PARSNIP].StageStartXIndex = 0;
	mSpriteInfoList[eCropType::CT_PARSNIP].StageStartYIndex = 0;
	mSpriteInfoList[eCropType::CT_PARSNIP].MaxStage = 6;
	mSpriteInfoList[eCropType::CT_PARSNIP].SeedXIndex = 0;
	mSpriteInfoList[eCropType::CT_PARSNIP].SeedYIndex = 0;

	mSpriteInfoList[eCropType::CT_POTATO].StageStartXIndex = 10;
	mSpriteInfoList[eCropType::CT_POTATO].StageStartYIndex = 2;
	mSpriteInfoList[eCropType::CT_POTATO].MaxStage = 7;
	mSpriteInfoList[eCropType::CT_POTATO].SeedXIndex = 3;
	mSpriteInfoList[eCropType::CT_POTATO].SeedYIndex = 0;

	mSpriteInfoList[eCropType::CT_BEEN].StageStartXIndex = 10;
	mSpriteInfoList[eCropType::CT_BEEN].StageStartYIndex = 0;
	mSpriteInfoList[eCropType::CT_BEEN].MaxStage = 8;
	mSpriteInfoList[eCropType::CT_BEEN].SeedXIndex = 1;
	mSpriteInfoList[eCropType::CT_BEEN].SeedYIndex = 0;

	mSpriteInfoList[eCropType::CT_CAULIFLOWER].StageStartXIndex = 0;
	mSpriteInfoList[eCropType::CT_CAULIFLOWER].StageStartYIndex = 2;
	mSpriteInfoList[eCropType::CT_CAULIFLOWER].MaxStage = 7;
	mSpriteInfoList[eCropType::CT_CAULIFLOWER].SeedXIndex = 2;
	mSpriteInfoList[eCropType::CT_CAULIFLOWER].SeedYIndex = 0;


	for (int type = eCropType::CT_PARSNIP; type < eCropType::CT_END; type++) {
		SpriteInfo& info = mSpriteInfoList[type];

		mIdleSeedBitmapList[type] = mBaseSeedSprite->getFrameBitmap(info.SeedXIndex, info.SeedYIndex);
		mIdleBitmapList[type] = mBaseStageSprite->getFrameBitmap(info.StageStartXIndex + info.MaxStage, info.StageStartYIndex + 1);

		for (int stageCount = 0; stageCount < mSpriteInfoList[type].MaxStage; stageCount++) {
			ImageGp* cropStageImg = new ImageGp;
			cropStageImg->init(getMemDc(), mBaseStageSprite->getFrameBitmapToIndex(info.StageStartXIndex + stageCount, info.StageStartYIndex, 0, 1), ITEM_SIZE_WIDTH, ITEM_SIZE_HEIGHT * 2);
			mVCropStageImg[type].push_back(cropStageImg);
		}
	}

	return S_OK;
}

void CropSprite::release()
{
}
