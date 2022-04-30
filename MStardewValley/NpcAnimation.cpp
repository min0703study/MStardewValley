#include "Stdafx.h"
#include "NpcAnimation.h"

void NpcAnimation::init(eNpcs type)
{
	mVAni = NPCSPRITE->getVAni(type);
}

void NpcAnimation::release()
{
}

void NpcAnimation::frameUpdate(float elapsedTime)
{
	if (!bIsPlaying || elapsedTime < 0) return;
	/*
	if (mAniInfoList[mCurStat].MaxFameCount == 1) return;
	mElapsedSec += elapsedTime;

	if (mElapsedSec > mAniInfoList[mCurStat].FrameUpdateSec) {
		mElapsedSec = 0;

		if (mCurFrame == mAniInfoList[mCurStat].MaxFameCount - 1) {
			if (bIsOnetime) {
				bIsOnetimeOver = true;
				bIsPlaying = false;
			}
			else {
				mCurFrame = 0;
			}
		}
		else {
			mCurFrame++;
		}
	}
	*/
}

void NpcAnimation::setStatFrameSec(int stat, float frameUpdateSec)
{
}

void NpcAnimation::render(HDC hdc, float centerX, float bottomY)
{
	mVAni[0]->render(centerX, bottomY);
}
