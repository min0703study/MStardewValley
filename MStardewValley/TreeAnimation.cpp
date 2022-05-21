#include "Stdafx.h"
#include "TreeAnimation.h"

void TreeAnimation::init(eTreeType type)
{
	mCurFrame = 0;
	mElapsedSec = 0;
	mCurFrame = 0;
	mFrameStatIndex = 0;

	bIsPlaying = false;
	bIsOnetime = false;
	bIsOnetimeOver = false;

	mCurAniState = eTreeType::TTP_END;
	mVCurAni = TREESPRITE->getVAni(type);

	for (int stat = 0; stat < eTreeAniState::TAS_END; stat++) {
		mAniInfoList[stat].StartIndex = TREESPRITE->getSpriteInfo()[stat].StartIndex;
		mAniInfoList[stat].MaxFrameCount = TREESPRITE->getSpriteInfo()[stat].FrameCount;
		if (stat == TAS_CRASH) {
			mAniInfoList[stat].FrameUpdateSec = 1.0f / 4.0f;
		}
	}
}

void TreeAnimation::release()
{
}

void TreeAnimation::playAniOneTime(eTreeAniState oneTimeAni)
{
	if (mCurAniState != oneTimeAni) {
		mCurAniState = oneTimeAni;
		mElapsedSec = 0;
		mCurFrame = 0;
		mFrameStatIndex = mAniInfoList[oneTimeAni].StartIndex;

		bIsOnetime = true;
		bIsPlaying = true;
		bIsOnetimeOver = false;
	}
}

void TreeAnimation::playAniLoop(eTreeAniState loopAni)
{
	if (mCurAniState != loopAni) {
		mElapsedSec = 0;
		mCurAniState = loopAni;
		mCurFrame = 0;
		mFrameStatIndex = mAniInfoList[loopAni].StartIndex;

		bIsOnetime = false;
		bIsOnetimeOver = false;
		bIsPlaying = true;
	}
}

void TreeAnimation::frameUpdate(float elapsedTime)
{
	if (!bIsPlaying || elapsedTime < 0) return;
	if (mAniInfoList[mCurAniState].MaxFrameCount == 1) return;

	mElapsedSec += elapsedTime;

	if (mElapsedSec > mAniInfoList[mCurAniState].FrameUpdateSec) {
		mElapsedSec = 0;
		mCurFrame++;
		if (mCurFrame >= mAniInfoList[mCurAniState].MaxFrameCount) {
			mCurFrame = 0;
			if (bIsOnetime) {
				bIsOnetimeOver = true;
				bIsPlaying = false;
			}
		}
	}
}

void TreeAnimation::render(float leftX, float bottomY)
{
	mVCurAni[mCurFrame + mFrameStatIndex]->render(leftX, bottomY, XS_CENTER, YS_BOTTOM);
}
