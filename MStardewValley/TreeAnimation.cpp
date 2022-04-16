#include "Stdafx.h"
#include "TreeAnimation.h"

void TreeAnimation::init(eTreeType type)
{
	mCurFrame = 0;
	mElapsedSec = 0;
	mCurFrame = 0;

	bIsPlaying = false;
	bIsOnetime = false;
	bIsOnetimeOver = false;

	mCurStat = eTreeType::TTP_END;
	mVCurAni = TREESPRITE->getVAni(type);

	mAniInfoList[RA_IDLE].StartIndexX = 0;
	mAniInfoList[RA_IDLE].MaxFrameCount = 1;

	mAniInfoList[RA_HIT].StartIndexX = TREESPRITE->getSpriteInfo(type)->HitStartIndexX;
	mAniInfoList[RA_HIT].MaxFrameCount = TREESPRITE->getSpriteInfo(type)->HitFrameCount;
	mAniInfoList[RA_HIT].FrameUpdateSec = 1.0f / 7.0f;

	mAniInfoList[RA_CRASH].StartIndexX = TREESPRITE->getSpriteInfo(type)->CrashStartIndexX;
	mAniInfoList[RA_CRASH].MaxFrameCount = TREESPRITE->getSpriteInfo(type)->CrashFrameCount;
	mAniInfoList[RA_CRASH].FrameUpdateSec = 1.0f / 7.0f;
}

void TreeAnimation::release()
{
}
void TreeAnimation::playAniOneTime(eRockAniStat oneTimeAni)
{
	if (mCurStat != oneTimeAni) {
		mCurStat = oneTimeAni;
		mCurFrame = 0;

		bIsOnetime = true;
		bIsPlaying = true;
		bIsOnetimeOver - false;
	}
}

void TreeAnimation::playAniLoop(eRockAniStat loopAni)
{
	if (mCurStat != loopAni) {
		mCurStat = loopAni;
		mCurFrame = 0;

		bIsOnetime = false;
		bIsOnetimeOver = false;
		bIsPlaying = true;
	}
}

void TreeAnimation::frameUpdate(float elapsedTime)
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

void TreeAnimation::render(float leftX, float topY)
{
	mVCurAni[mCurFrame]->render(leftX, topY);
}
