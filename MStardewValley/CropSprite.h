#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class CropSprite: public SingletonBase<CropSprite>, public GameNode
{
public:
	typedef struct tagSpriteInfo {
		int StartIndex;
		int EndIndex;

		int MaxStage;
		bool IsNone;
	} SpriteInfo;

	HRESULT init(void) override;
	void release() override;

	vector<ImageGp*> getVAni(eCropType cropType);
	Bitmap* getIdleBitmap(eCropType cropKinds) { return mIdleBitmapList[cropKinds]; };
	inline SpriteInfo* getSpriteInfo() { return mSpriteInfoList; };
private:
	ImageGp* mBaseSeedSprite;
	ImageGp* mBaseStageSprite;

	vector<ImageGp*> mVCropStageImg[eCropType::CT_END];
	SpriteInfo mSpriteInfoList[eCropType::CT_END];
	Bitmap* mIdleBitmapList[eCropType::CT_END];
};
