#include "Stdafx.h"
#include "MineRockAnimation.h"

void MineRockAnimation::init(eRockType type)
{
	mCurFrame = 0;
	mElapsedSec = 0;
	mCurFrame = 0;

	bIsPlaying = false;
	bIsOnetime = false;
	bIsOnetimeOver = false;

	mCurStat = eRockAniStat::RA_END;
	mVCurAni = MINESSPRITE->getVAni(type);
	
	mAniInfoList[RA_IDLE].StartIndexX = 0;
	mAniInfoList[RA_IDLE].MaxFrameCount = 1;

	mAniInfoList[RA_HIT].StartIndexX = MINESSPRITE->getSpriteInfo(type)->HitStartIndexX;
	mAniInfoList[RA_HIT].MaxFrameCount = MINESSPRITE->getSpriteInfo(type)->HitFrameCount;
	mAniInfoList[RA_HIT].FrameUpdateSec = 1.0f / 7.0f;

	mAniInfoList[RA_CRASH].StartIndexX = MINESSPRITE->getSpriteInfo(type)->CrashStartIndexX;
	mAniInfoList[RA_CRASH].MaxFrameCount = MINESSPRITE->getSpriteInfo(type)->CrashFrameCount;
	mAniInfoList[RA_CRASH].FrameUpdateSec = 1.0f / 7.0f;
}

void MineRockAnimation::release()
{
}
void MineRockAnimation::playAniOneTime(eRockAniStat oneTimeAni)
{
	if (mCurStat != oneTimeAni) {
		mCurStat = oneTimeAni;
		mCurFrame = 0;

		bIsOnetime = true;
		bIsPlaying = true;
		bIsOnetimeOver - false;
	}
}

void MineRockAnimation::playAniLoop(eRockAniStat loopAni)
{
	if (mCurStat != loopAni) {
		mCurStat = loopAni;
		mCurFrame = 0;

		bIsOnetime = false;
		bIsOnetimeOver = false;
		bIsPlaying = true;
	}
}

void MineRockAnimation::frameUpdate(float elapsedTime)
{
	if (!bIsPlaying || elapsedTime < 0) return;
	if (mAniInfoList[mCurStat].MaxFrameCount == 1) return;

	mElapsedSec += elapsedTime;

	if (mElapsedSec > mAniInfoList[mCurStat].FrameUpdateSec) {
		mElapsedSec = 0;
		mCurFrame++;
		if (mCurFrame >= mAniInfoList[mCurStat].MaxFrameCount) {
			mCurFrame = 0;
			if (bIsOnetime) {
				bIsOnetimeOver = true;
				bIsPlaying = false;
			}
		}
	}
}

void MineRockAnimation::render(HDC hdc, float x, float y)
{
	mVCurAni[mCurFrame]->render(x, y, XS_LEFT, YS_TOP);
}
