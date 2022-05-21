#include "Stdafx.h"
#include "MonsterAnimation.h"

void MonsterAnimation::init(eMonsterType type, eGameDirection* direction)
{
	mCurFrame = 0;
	mCurRealFrame = 0;
	mElapsedSec = 0;

	mVCurAni = MONSTERSPRITE->getVAni(type);

	mCurState = eMonsterState::MSS_IDLE;
	
	for (int stat = 0; stat < eMonsterState::MSS_END; stat++) {
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

void MonsterAnimation::changeAniState(eMonsterState changeState)
{
	mCurState = changeState;
}

void MonsterAnimation::setStatFrameSec(int stat, float frameUpdateSec)
{
}

void MonsterAnimation::playAniOneTime(eMonsterState oneTimeAni)
{
	if (mCurState != oneTimeAni) {
		mCurState = oneTimeAni;
		mCurFrame = 0;

		bIsOnetime = true;
		bIsPlaying = true;
		bIsOnetimeOver = false;
	}
}

void MonsterAnimation::playAniLoop(eMonsterState loopAni)
{
	if (mCurState != loopAni) {
		mCurState = loopAni;
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

	if (mElapsedSec > mAniInfo[mCurState].FrameUpdateSec) {
		mElapsedSec = 0;

		mCurFrame++;
		if (mCurFrame >= mAniInfo[mCurState].MaxFrameCount) {
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
	mCurRealFrame = mCurFrame + mAniInfo[mCurState].StartIndex + (*mRefDirection * mAniInfo[mCurState].DirectionInterval);
	mVCurAni[mCurRealFrame]->render(rcF.GetLeft(), rcF.GetTop());
}
