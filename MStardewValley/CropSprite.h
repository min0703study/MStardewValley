#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class CropSprite: public SingletonBase<CropSprite>, public GameNode
{
public:
	typedef struct tagSpriteInfo {
		int StartIndex;
		int EndIndex;

		bool IsNone;
	} SpriteInfo;

	HRESULT init(void) override;

	//vector<ImageGp*> getVAni(int toolType, int toolLevel);
	Bitmap* getIdleBitmap(eCropKinds cropKinds) { return mIdleBitmapList[cropKinds]; };
	inline SpriteInfo* getSpriteInfo() { return mSpriteInfoList; };
private:
	ImageGp* mBaseSprite;

	vector<ImageGp*> mVCropStageImg[eCropKinds::CK_END];
	SpriteInfo mSpriteInfoList[eCropKinds::CK_END];
	Bitmap* mIdleBitmapList[eCropKinds::CK_END];
};
