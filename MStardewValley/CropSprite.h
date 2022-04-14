#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class CropSprite: public SingletonBase<CropSprite>, public GameNode
{
public:
	typedef struct tagSpriteInfo {
		int StageStartXIndex;
		int StageStartYIndex;

		int SeedXIndex;
		int SeedYIndex;

		int FruitXIndex;
		int FruitYIndex;

		int MaxStage;
		bool IsNone;
	} SpriteInfo;

	HRESULT init(void) override;
	void release() override;

	vector<ImageGp*> getVAni(eCropType cropType) { return mVCropStageImg[cropType]; };
	Bitmap* getIdleBitmap(eCropType cropType) { return mIdleBitmapList[cropType]; };
	Bitmap* getIdleSeedBitmap(eCropType cropType) { return mIdleSeedBitmapList[cropType]; };
	inline SpriteInfo* getSpriteInfo() { return mSpriteInfoList; };
private:
	ImageGp* mBaseSeedSprite;
	ImageGp* mBaseStageSprite;

	vector<ImageGp*> mVCropStageImg[eCropType::CT_END];
	SpriteInfo mSpriteInfoList[eCropType::CT_END];

	Bitmap* mIdleSeedBitmapList[eCropType::CT_END];
	Bitmap* mIdleBitmapList[eCropType::CT_END];

	int mCropXToSprite[eCropType::CT_END];
	int mCropYToSprite[eCropType::CT_END];
	int mCropMaxStageToSprite[eCropType::CT_END];
	int mCropXToSeedSprite[eCropType::CT_END];
	int mCropYToSeedSprite[eCropType::CT_END];
	
};
