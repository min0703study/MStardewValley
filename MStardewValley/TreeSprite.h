#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class TreeSprite : public GameNode, public SingletonBase<TreeSprite>
{
public:
	typedef struct tagSpriteInfo {
		int StartIndex;
		int FrameCount;
	} SpriteInfo;

	HRESULT init(void);
	void release(void);

	inline vector<ImageGp*> getVAni(eTreeType type) { return mVAni[type]; };
	inline const SpriteInfo* getSpriteInfo() {
		return mSpriteInfo;
	};

	TreeSprite(): mBaseSprite(nullptr) {};
	~TreeSprite() {}
private:
	ImageGp* mBaseSprite;

	vector<ImageGp*> mVAni[eTreeType::TTP_END];

	SpriteInfo mSpriteInfoList[eTreeType::TTP_END];
	SpriteInfo mSpriteInfo[eTreeAniStat::TAS_END];
};

