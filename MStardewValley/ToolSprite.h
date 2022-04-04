#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

#define START_INDEX_X	100
#define START_INDEX_Y

class ToolSprite : public SingletonBase<ToolSprite>, public GameNode
{
public:
	typedef struct tagSpriteInfo {
		eGameDirection Direction;

		int ToolType;
		int ToolLevel;

		int MaxFrameCount;

		int* SpriteIndexX;
		int* SpriteIndexY;

		bool IsFlipX;
	} SpriteInfo;

	HRESULT init(void) override;
	void uploadJson();

	vector<ImageGp*> getSpriteTool(int toolType, int toolLevel);
	ImageGp * getImgGp(int toolType, int toolLevel, int index);
private:
	ImageGp* mBaseSprite;

	int mToolTypeIndex[eToolType::TT_END];
	int mToolLevelIndex[eToolLevel::TL_END];
	
	vector<ImageGp*> mVTool[eToolType::TT_END][eToolLevel::TL_END];
	ImageGp* mVOriginalImgTool[eToolType::TT_END][eToolLevel::TL_END];

};

