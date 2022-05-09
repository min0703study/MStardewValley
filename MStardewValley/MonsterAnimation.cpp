#include "Stdafx.h"
#include "MonsterAnimation.h"

void MonsterAnimation::init(eMonsterType type, eGameDirection* direction)
{
	mCurFrame = 0;
	mCurRealFrame = 0;
	mElapsedSec = 0;

	mVCurAni = MONSTERSPRITE->getVAni(type);

	mCurStat = eMonsterStat::MSS_IDLE;
	
	for (int stat = 0; stat < eMonsterStat::MSS_END; stat++) {
		mAniInfo[stat].StartIndex = MONSTERSPRITE->getSpriteInfo(type).StartIndex[stat];
		mAniInfo[stat].MaxFrameCount = MONSTERSPRITE->getSpriteInfo(type).MaxFrameCount[stat];
		mAniInfo[stat].DirectionInterval = MONSTERSPRITE->getSpriteInfo(type).DirectionInterval[stat];
		mAniInfo[stat].FrameUpdateSec = 1.0f / 3;
	}

	mRefDirection = direction;

	bIsPlaying = true;
	bIsOnetime = false;
	bIsOnetimeOver = false;
}

void MonsterAnimation::release()
{
	mRefDirection = nullptr;
	mVCurAni = vector<ImageGp*>();
}

void MonsterAnimation::changeStatAni(eMonsterStat changeStat)
{
	mCurStat = changeStat;
}

void MonsterAnimation::setStatFrameSec(int stat, float frameUpdateSec)
{
}

void MonsterAnimation::playAniOneTime(eMonsterStat oneTimeAni)
{
	if (mCurStat != oneTimeAni) {
		mCurStat = oneTimeAni;
		mCurFrame = 0;

		bIsOnetime = true;
		bIsPlaying = true;
		bIsOnetimeOver = false;
	}
}

void MonsterAnimation::playAniLoop(eMonsterStat loopAni)
{
	if (mCurStat != loopAni) {
		mCurStat = loopAni;
		mCurFrame = 0;

		bIsOnetime = false;
		bIsOnetimeOver = false;
		bIsPlaying = true;
	}
}

void MonsterAnimation::frameUpdate(float elapsedTime)
{
	if (!bIsPlaying || elapsedTime < 0) return;
	if (elapsedTime < 0) return;

	mElapsedSec += elapsedTime;

	if (mElapsedSec > mAniInfo[mCurStat].FrameUpdateSec) {
		mElapsedSec = 0;

		mCurFrame++;
		if (mCurFrame >= mAniInfo[mCurStat].MaxFrameCount) {
			mCurFrame = 0;

			if (bIsOnetime) {
				bIsOnetimeOver = true;
				bIsPlaying = false;
			}
		}
	}
}


void MonsterAnimation::render(HDC hdc, RectF rcF)
{
	mCurRealFrame = mCurFrame + mAniInfo[mCurStat].StartIndex + (*mRefDirection * mAniInfo[mCurStat].DirectionInterval);
	mVCurAni[mCurRealFrame]->render(rcF.GetLeft(), rcF.GetTop());
}
