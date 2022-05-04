#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class MinesSprite: public GameNode, public SingletonBase<MinesSprite>
{
public:
	typedef struct tagSpriteInfo {
		int FrameX;
		int FrameY;

		int HitStartIndexX;
		int HitFrameCount;
		
		int CrashStartIndexX;
		int CrashFrameCount;
	} SpriteInfo;

	HRESULT init(void);
	void release(void);

	inline vector<ImageGp*> getVAni(eRockType rockType) { return mVAni[rockType];};
	inline vector<ImageGp*> getVWeedAni(eWeedType weedType) { return mVWeedAni[weedType];};

	inline ImageGp* getStoneImg(eOreType stoneType) { return mOreItemIdle[stoneType];};
	inline const SpriteInfo* getSpriteInfo(eRockType rockType) {
		return &mSpriteInfoList[rockType];
	};

	inline Bitmap* getMinesItemIdle(eMinesItem item) { return mMinesItemIdle[item]->getBitmap(); };
	inline Bitmap* getOreBarIdle(eOreType item) { return mOreBarItemIdle[item]->getBitmap(); };
	inline Bitmap* getWeedItemIdle(eWeedType weed) { return mWeedItemIdle[weed]->getBitmap(); };
private:
	ImageGp* mBaseRockSprite;
	ImageGp* mBaseWeedSprite;
	ImageGp* mBaseItemSprite;

	vector<ImageGp*> mVAni[eRockType::RT_END];
	vector<ImageGp*> mVWeedAni[eWeedType::WDT_END];

	SpriteInfo mSpriteInfoList[eRockType::RT_END];
	SpriteInfo mSpriteInfoItemList[eRockType::RT_END];
	SpriteInfo mSpriteInfoWeedList[eRockType::RT_END];

	ImageGp* mOreItemIdle[eOreType::OT_END];
	ImageGp* mOreBarItemIdle[eOreType::OT_END];
	ImageGp* mMinesItemIdle[eMinesItem::MI_END];
	ImageGp* mWeedItemIdle[eWeedType::WDT_END];
};

