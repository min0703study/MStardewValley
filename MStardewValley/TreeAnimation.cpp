#include "Stdafx.h"
#include "TreeAnimation.h"

void TreeAnimation::init(eTreeType type)
{
	mCurFrame = 0;
	mElapsedSec = 0;
	mCurFrame = 0;
	mStatStartIndex = 0;

	bIsPlaying = false;
	bIsOnetime = false;
	bIsOnetimeOver = false;

	mCurStat = eTreeType::TTP_END;
	mVCurAni = TREESPRITE->getVAni(type);

	mAniInfoList[TAS_IDLE].StartIndex = 0;
	mAniInfoList[TAS_IDLE].MaxFrameCount = 1;

	mAniInfoList[TAS_HIT].StartIndex = TREESPRITE->getSpriteInfo(type)->HitStartIndex;
	mAniInfoList[TAS_HIT].MaxFrameCount = TREESPRITE->getSpriteInfo(type)->HitFrameCount;
	mAniInfoList[TAS_HIT].FrameUpdateSec = 1.0f / 7.0f;

	mAniInfoList[TAS_CRASH].StartIndex = TREESPRITE->getSpriteInfo(type)->CrashStartIndex;
	mAniInfoList[TAS_CRASH].MaxFrameCount = TREESPRITE->getSpriteInfo(type)->CrashFrameCount;
	mAniInfoList[TAS_CRASH].FrameUpdateSec = 1.0f / 7.0f;

	mAniInfoList[TAS_TRANS].StartIndex = 7;
	mAniInfoList[TAS_TRANS].MaxFrameCount = 1;
}

void TreeAnimation::release()
{
}
void TreeAnimation::playAniOneTime(eTreeAniStat oneTimeAni)
{
	if (mCurStat != oneTimeAni) {
		mCurStat = oneTimeAni;
		mCurFrame = 0;
		mStatStartIndex = mAniInfoList[oneTimeAni].StartIndex;

		bIsOnetime = true;
		bIsPlaying = true;
		bIsOnetimeOver = false;
	}
}

void TreeAnimation::playAniLoop(eTreeAniStat loopAni)
{
	if (mCurStat != loopAni) {
		mCurStat = loopAni;
		mCurFrame = 0;
		mStatStartIndex = mAniInfoList[loopAni].StartIndex;

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
	mVCurAni[mCurFrame + mStatStartIndex]->render(leftX, topY);
}
