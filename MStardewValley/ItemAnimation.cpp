#include "Stdafx.h"
#include "ItemAnimation.h"

void ItemAnimation::initWeapon(eWeaponType type)
{
	mCurFrame = 0;
	mElapsedSec = 0;

	mAniWidth = WEAPON_SIZE_WIDTH;
	mAniHeight = WEAPON_SIZE_HEIGHT;

	mAniWidth = 50.0f;
	mAniHeight = 50.0f;

	mVCurAni = WEAPONSPRITE->getVAni(type);

	mAniInfo.StartIndex = WEAPONSPRITE->getSpriteInfo()[0].StartIndex;
	mAniInfo.EndIndex = WEAPONSPRITE->getSpriteInfo()[0].EndIndex;
	mAniInfo.IsNone = WEAPONSPRITE->getSpriteInfo()[0].IsNone;
	mAniInfo.FrameUpdateSec = 1.0f / WEAPON_ANI_FRAME_SEC;
	mAniInfo.MaxFrameCount = 6;

	mPlayerDirection = GD_LEFT;
	mDirectionInterval = (mPlayerDirection * (mAniInfo.MaxFrameCount - 1));
}

void ItemAnimation::initTool(eToolType toolType, eToolLevel toolLevel)
{
	mCurFrame = 0;
	mElapsedSec = 0;

	mVCurAni = TOOLSPRITE->getVAni(toolType, toolLevel);

	mAniInfo.FrameUpdateSec = 1.0f / TOOL_ANI_FRAME_SEC;
	mAniInfo.MaxFrameCount = 5;

	mPlayerDirection = GD_LEFT;
	mDirectionInterval = (mPlayerDirection * (mAniInfo.MaxFrameCount - 1));
}

void ItemAnimation::release()
{
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
	mVCurAni[mCurFrame + mDirectionInterval]->render(hdc, x, y, XS_CENTER, YS_CENTER);
	//GDIPLUSMANAGER->drawRectF(mVCurAni[mDirectionInterval]->getRectF(x, y, XS_CENTER, YS_CENTER));
}
