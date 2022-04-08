#include "Stdafx.h"
#include "ToolSprite.h"

#define TOOL_FRAME_COUNT		4

HRESULT ToolSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->ToolSprite);

	mToolTypeIndex[eToolType::TT_HOE] =				1;
	mToolTypeIndex[eToolType::TT_PICK] =			5;
	mToolTypeIndex[eToolType::TT_AXE] =				9;
	mToolTypeIndex[eToolType::TT_WATERING_CAN] =	13;

	mToolLevelIndex[eToolLevel::TL_NORMAL] =	0;
	mToolLevelIndex[eToolLevel::TL_COPPER] =	7;
	mToolLevelIndex[eToolLevel::TL_IRON] =		14;
	mToolLevelIndex[eToolLevel::TL_GOLD] =		21;
	mToolLevelIndex[eToolLevel::TL_IRIDIUM] =	28;

	//스프라이트 정보 INIT
	mVSpriteInfo[eItemStat::IS_GRAP].StartIndex = 0;
	mVSpriteInfo[eItemStat::IS_GRAP].EndIndex = 0;
	mVSpriteInfo[eItemStat::IS_GRAP].IsNone = true;

	mVSpriteInfo[eItemStat::IS_USE_UP].StartIndex = 0;
	mVSpriteInfo[eItemStat::IS_USE_UP].EndIndex = 3;
	mVSpriteInfo[eItemStat::IS_USE_UP].IsNone = false;

	mVSpriteInfo[eItemStat::IS_USE_RIGHT].StartIndex = 4;
	mVSpriteInfo[eItemStat::IS_USE_RIGHT].EndIndex = 7;
	mVSpriteInfo[eItemStat::IS_USE_RIGHT].IsNone = false;

	mVSpriteInfo[eItemStat::IS_USE_LEFT].StartIndex = 8;
	mVSpriteInfo[eItemStat::IS_USE_LEFT].EndIndex = 11;
	mVSpriteInfo[eItemStat::IS_USE_LEFT].IsNone = false;

	mVSpriteInfo[eItemStat::IS_USE_DOWN].StartIndex = 12;
	mVSpriteInfo[eItemStat::IS_USE_DOWN].EndIndex = 15;
	mVSpriteInfo[eItemStat::IS_USE_DOWN].IsNone = false;

	for (int i = eToolType::TT_PICK; i < eToolType::TT_END; i++) {
		for (int j = eToolLevel::TL_NORMAL; j < eToolLevel::TL_END; j++) {
			vector<ImageGp*> tempVImageGp;
			for (int direction = eGameDirection::GD_UP; direction <= eGameDirection::GD_DOWN; direction++) {
				if (direction == GD_LEFT || direction == GD_RIGHT) {
					for (int x = 0; x < TOOL_FRAME_COUNT; x++) {
						ImageGp* tempImageGp = new ImageGp;
						tempImageGp->initCenter(getMemDc(),
							mBaseSprite->getFrameBitmapToIndex(
								(mToolLevelIndex[j] % 14) + 2,
								mToolTypeIndex[i],
								PLAYER_WIDTH, 
								PLAYER_HEIGHT, 
								1, 
								2),
							PLAYER_HEIGHT, PLAYER_HEIGHT);
						tempImageGp->rotate(x * 35.0f);
						if (direction == GD_LEFT) {
							tempImageGp->flipX();
						}
						tempVImageGp.push_back(tempImageGp);
					}
				}

				if (direction == GD_UP || direction == GD_DOWN) {
					int startIndexX = direction == GD_UP ? 3 : 0;
					for (int x = 0; x < TOOL_FRAME_COUNT / 2.0f; x++) {
						ImageGp* tempImageGp = new ImageGp;
						tempImageGp->initCenter(getMemDc(),
							mBaseSprite->getFrameBitmapToIndex(
								(mToolLevelIndex[j] % 14) + startIndexX + x,
								mToolTypeIndex[i],
								PLAYER_WIDTH, PLAYER_HEIGHT, 1, 2),
							PLAYER_HEIGHT, PLAYER_HEIGHT);
						tempVImageGp.push_back(tempImageGp);
						tempVImageGp.push_back(tempImageGp->clone());
					}
				}
			}

			mVTool[i][j] = tempVImageGp;

			ImageGp* img = new ImageGp;
			img->initCenter(getMemDc(),
				mBaseSprite->getFrameBitmapTemp(
				(mToolLevelIndex[j] % 14) + 5,
					mToolTypeIndex[i],
					INVENTORY_BOX_HEIGHT, 1, 2), INVENTORY_BOX_WIDTH, INVENTORY_BOX_HEIGHT);

			mVOriginalImgTool[i][j] = img;
		}
	}

	return S_OK;
}

void ToolSprite::uploadJson()
{
}

vector<ImageGp*> ToolSprite::getVAni(int toolType, int toolLevel)
{
	return mVTool[toolType][toolLevel];
}

ImageGp* ToolSprite::getImgGp(int toolType, int toolLevel)
{
	return mVOriginalImgTool[toolType][toolLevel];
}