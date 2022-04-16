#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class TreeSprite : public GameNode, public SingletonBase<TreeSprite>
{
public:
	typedef struct tagSpriteInfo {
		int FrameX;
		int FrameY;
		int FrameToXCount;
		int FrameToYCount;

		int HitStartIndexX;
		int HitFrameCount;

		int CrashStartIndexX;
		int CrashFrameCount;
	} SpriteInfo;

	HRESULT init(void);
	void release(void);

	inline vector<ImageGp*> getVAni(eTreeType type) { return mVAni[type]; };
	inline const SpriteInfo* getSpriteInfo(eTreeType type) {
		return &mSpriteInfoList[type];
	};
private:
	ImageGp* mBaseSprite;

	vector<ImageGp*> mVAni[eTreeType::TTP_END];
	SpriteInfo mSpriteInfoList[eTreeType::TTP_END];
};

