#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class ToolSprite : public SingletonBase<ToolSprite>, public GameNode
{
public:
	typedef struct tagSpriteInfo {
		int StartIndex;
		int EndIndex;

		bool IsNone;
	} SpriteInfo;

	HRESULT init(void) override;

	vector<ImageGp*> getVAni(int toolType, int toolLevel);
	Bitmap* getIdleBitmap(int toolType, int toolLevel);
	inline SpriteInfo* getSpriteInfo() { return mVSpriteInfo; };
private:
	ImageGp* mBaseSprite;

	int mToolTypeIndex[eToolType::TT_END];
	int mToolLevelIndex[eToolLevel::TL_END];
	
	SpriteInfo mVSpriteInfo[eItemStat::IS_END];
	vector<ImageGp*> mVTool[eToolType::TT_END][eToolLevel::TL_END];
	Bitmap* mIdleImgList[eToolType::TT_END][eToolLevel::TL_END];

};

