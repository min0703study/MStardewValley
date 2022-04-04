#include "Stdafx.h"
#include "ToolSprite.h"

#define TOOL_FRAME_COUNT		4

HRESULT ToolSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->ToolSprite);

	mToolTypeIndex[eToolType::TT_HOE] =				1;
	mToolTypeIndex[eToolType::TT_PICK] =			5;
	mToolTypeIndex[eToolType::TT_AXE] =				9;
	mToolTypeIndex[eToolType::TT_WATERING_CAN] =	13;

	mToolLevelIndex[eToolLevel::TL_NORMAL] =	0;
	mToolLevelIndex[eToolLevel::TL_COPPER] =	7;
	mToolLevelIndex[eToolLevel::TL_IRON] =		14;
	mToolLevelIndex[eToolLevel::TL_GOLD] =		21;
	mToolLevelIndex[eToolLevel::TL_IRIDIUM] =	28;

	for (int i = eToolType::TT_PICK; i < eToolType::TT_END; i++) {
		for (int j = eToolLevel::TL_NORMAL; j < eToolLevel::TL_END; j++) {
			ImageGp* tempImageGp = new ImageGp;
			tempImageGp->init(getMemDc(),
				mBaseSprite->getFrameBitmapToIndexCenter(
					(mToolLevelIndex[j] % 14) + 5,
					mToolTypeIndex[i],
					INVENTORY_BOX_WIDTH,
					INVENTORY_BOX_HEIGHT,
					1, 2),
				INVENTORY_BOX_WIDTH, 
				INVENTORY_BOX_HEIGHT);

			mVOriginalImgTool[i][j] = tempImageGp;

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
		}
	}

	return S_OK;
}

void ToolSprite::uploadJson()
{
}

vector<ImageGp*> ToolSprite::getSpriteTool(int toolType, int toolLevel)
{
	return mVTool[toolType][toolLevel];
}

ImageGp* ToolSprite::getImgGp(int toolType, int toolLevel, int index)
{
	return mVOriginalImgTool[toolType][toolLevel];
}