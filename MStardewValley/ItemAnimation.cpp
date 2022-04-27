#include "Stdafx.h"
#include "ItemAnimation.h"

void ItemAnimation::initWeapon(eWeaponType type)
{
	mCurFrame = 0;
	mElapsedSec = 0;

	mVCurAni = WEAPONSPRITE->getVAni(type);

	mAniInfo.FrameUpdateSec = 1.0f / WEAPON_ANI_FRAME_SEC;
	mAniInfo.MaxFrameCount = 6;

	mPlayerDirection = GD_END;
	mDirectionInterval = 0;
}

void ItemAnimation::initTool(eToolType toolType, eToolLevel toolLevel)
{
	mCurFrame = 0;
	mElapsedSec = 0;

	mVCurAni = TOOLSPRITE->getVAni(toolType, toolLevel);

	if (toolType == eToolType::TT_WATERING_CAN) {
		mAniInfo.FrameUpdateSec = 1.0f / PLAYER_ANI_FRAME_SEC;
	}
	else {
		mAniInfo.FrameUpdateSec = 1.0f / TOOL_ANI_FRAME_SEC;
	}
	mAniInfo.MaxFrameCount = 5;

	mPlayerDirection = GD_END;
	mDirectionInterval = 0;
}

void ItemAnimation::frameUpdate(float elapsedTime)
{
	if (!bIsPlaying || elapsedTime < 0) return;
	mElapsedSec += elapsedTime;

	if (mElapsedSec > mAniInfo.FrameUpdateSec) {
		mElapsedSec = 0;
		if (mCurFrame == mAniInfo.MaxFrameCount - 1) {
			if (bIsOnetime) {
				bIsOnetimeOver = true;
				bIsPlaying = false;
			} else {
				mCurFrame = 0;
			}
		} else {
			mCurFrame++;
		}
	}
}

void ItemAnimation::playAniOneTime()
{
	mCurFrame = 0;

	if (mPlayerDirection != PLAYER->getDirection()) {
		mPlayerDirection = PLAYER->getDirection();
		mDirectionInterval = (mPlayerDirection * mAniInfo.MaxFrameCount);
	}

	bIsOnetime = true;
	bIsPlaying = true;
	bIsOnetimeOver = false;
}

void ItemAnimation::render(HDC hdc, float x, float y, eXStandard xStandard, eYStandard yStandard)
{
	mVCurAni[mCurFrame + mDirectionInterval]->render(hdc, x, y, xStandard, yStandard);
}

void ItemAnimation::release()
{
}