#include "Stdafx.h"
#include "MonsterAnimation.h"

void MonsterAnimation::init(eMonsterType type, eGameDirection* direction)
{
	mCurFrame = 0;
	mCurRealFrame = 0;
	mElapsedSec = 0;

	mCurAniStat = 0;
	mVCurAni = MONSTERSPRITE->getVAni(type);
	
	for (int i = 0; i < 1; i++) {
		mAniInfo[i].StartIndex = MONSTERSPRITE->getSpriteInfo(type).StartIndex[i];
		mAniInfo[i].MaxFrameCount = MONSTERSPRITE->getSpriteInfo(type).MaxFrameCount[i];
		mAniInfo[i].DirectionInterval = MONSTERSPRITE->getSpriteInfo(type).DirectionInterval[i];
		mAniInfo[i].FrameUpdateSec = 1.0f / 3;
	}

	mRefDirection = direction;
}

void MonsterAnimation::release()
{
	mRefDirection = nullptr;
	mVCurAni = vector<ImageGp*>();
}

void MonsterAnimation::changeStatAni(int changeStat)
{

}

void MonsterAnimation::setStatFrameSec(int stat, float frameUpdateSec)
{
}

void MonsterAnimation::frameUpdate(float elapsedTime)
{
	if (elapsedTime < 0) return;

	mElapsedSec += elapsedTime;

	if (mElapsedSec > mAniInfo[mCurAniStat].FrameUpdateSec) {
		mElapsedSec = 0;

		mCurFrame++;
		if (mCurFrame >= mAniInfo[mCurAniStat].MaxFrameCount) {
			mCurFrame = 0;
		}
	}
}


void MonsterAnimation::render(HDC hdc, RectF rcF)
{
	mCurRealFrame = mCurFrame + mAniInfo[mCurAniStat].StartIndex + (*mRefDirection * mAniInfo[mCurAniStat].DirectionInterval);
	mVCurAni[mCurRealFrame]->render(hdc, rcF.GetLeft(), rcF.GetTop());
}
