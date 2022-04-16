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
	inline const SpriteInfo* getSpriteInfo(eRockType rockType) {
		return &mSpriteInfoList[rockType];
	};
private:
	ImageGp* mBaseSprite;

	vector<ImageGp*> mVAni[eRockType::RT_END];
	SpriteInfo mSpriteInfoList[eRockType::RT_END];
};

