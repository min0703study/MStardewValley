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
	mSpriteInfoList[eItemStat::IS_GRAP].StartIndex = 0;
	mSpriteInfoList[eItemStat::IS_GRAP].EndIndex = 0;
	mSpriteInfoList[eItemStat::IS_GRAP].IsNone = true;

	mSpriteInfoList[eItemStat::IS_USE_UP].StartIndex = 0;
	mSpriteInfoList[eItemStat::IS_USE_UP].EndIndex = 3;
	mSpriteInfoList[eItemStat::IS_USE_UP].IsNone = false;

	mSpriteInfoList[eItemStat::IS_USE_RIGHT].StartIndex = 4;
	mSpriteInfoList[eItemStat::IS_USE_RIGHT].EndIndex = 7;
	mSpriteInfoList[eItemStat::IS_USE_RIGHT].IsNone = false;

	mSpriteInfoList[eItemStat::IS_USE_LEFT].StartIndex = 8;
	mSpriteInfoList[eItemStat::IS_USE_LEFT].EndIndex = 11;
	mSpriteInfoList[eItemStat::IS_USE_LEFT].IsNone = false;

	mSpriteInfoList[eItemStat::IS_USE_DOWN].StartIndex = 12;
	mSpriteInfoList[eItemStat::IS_USE_DOWN].EndIndex = 15;
	mSpriteInfoList[eItemStat::IS_USE_DOWN].IsNone = false;

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

			mVToolAni[i][j] = tempVImageGp;

			//make idle img
			mIdleImgList[i][j] = 
				mBaseSprite->clippingAlpha(
					(mToolLevelIndex[j] % 14) + 5,
					mToolTypeIndex[i], 
					0, 
					1);
		}
	}

	return S_OK;
}

void ToolSprite::release(void)
{
}

vector<ImageGp*> ToolSprite::getVAni(int toolType, int toolLevel)
{
	return mVToolAni[toolType][toolLevel];
}

Bitmap* ToolSprite::getIdleBitmap(int toolType, int toolLevel)
{
	return mIdleImgList[toolType][toolLevel];
}