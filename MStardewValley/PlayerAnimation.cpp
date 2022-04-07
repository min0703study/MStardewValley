#include "Stdafx.h"
#include "PlayerAnimation.h"

void PlayerAnimation::init(int initStat, eGameDirection initDirection)
{
	mSprite = new PlayerSprite;
	mSprite->init();

	mShadow = mSprite->getShawdow();

	mElapsedSec = 0;
	mPlayCount = 0;
	mCurFrame = 0;

	mCurAniStat = initStat;
	mCurAniDirection = initDirection;

	mVCurAni = mSprite->getVAni(mCurAniDirection, mCurAniStat);
}

void PlayerAnimation::changeStatAni(int changeStat)
{
	mPlayCount = 0;
	mCurFrame = 0;
	mCurAniStat = changeStat;
	mVCurAni = mSprite->getVAni(mCurAniDirection, changeStat);
}

void PlayerAnimation::changeDirectionAni(eGameDirection direction)
{
	mPlayCount = 0;
	mCurFrame = 0;

	mCurAniDirection = direction;
	mVCurAni = mSprite->getVAni(direction, mCurAniStat);
}

void PlayerAnimation::frameUpdate(float elapsedTime)
{
	if (elapsedTime < 0) return;

	mElapsedSec += elapsedTime;

	if (mElapsedSec > mAniInfo[mCurAniStat].FrameUpdateSec) {
		mElapsedSec = 0;

		
		mCurFrame++;
		if (mCurFrame >= mSprite->getMaxFrameCount(mCurAniStat)) {
			mCurFrame = 0;
			mPlayCount++;
		}
		
		/*
		if (bLoopFlag) {
			if (mCurFrame < mSprite->getMaxFrameCount(mCurAniStat) - 1) {
				mCurFrame++;
			}
			else {
				bLoopFlag = false;
			}
		}
		else {
			if (mCurFrame > 0) {
				mCurFrame--;
			}
			else {
				mPlayCount++;
				bLoopFlag = true;
			}
		}
			*/
	}
}

void PlayerAnimation::setStatFrameSec(int stat, float frameUpdateSec)
{
	mAniInfo[stat].FrameUpdateSec = 1.0f / frameUpdateSec;
}

void PlayerAnimation::render(HDC hdc, RectF rcF)
{
	mVCurAni[mCurFrame]->render(hdc, rcF.GetLeft(), rcF.GetBottom() - PLAYER_HEIGHT);
	mVCurAni[mCurFrame + mSprite->getMaxFrameCount(mCurAniStat)]->render(hdc, rcF.GetLeft(), rcF.GetBottom() - PLAYER_HEIGHT);
	mVCurAni[mCurFrame + mSprite->getMaxFrameCount(mCurAniStat) * 2]->render(hdc, rcF.GetLeft(), rcF.GetBottom() - PLAYER_HEIGHT);

	mShadow->render(hdc, rcF.GetLeft() + rcF.Width / 2.0f, rcF.GetBottom(), XS_CENTER, YS_CENTER);
}

int PlayerAnimation::getPlayCount() { return mPlayCount; }