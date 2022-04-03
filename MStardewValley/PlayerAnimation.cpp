#include "Stdafx.h"
#include "PlayerAnimation.h"

void PlayerAnimation::init(int initStat, eGameDirection initDirection)
{
	mSprite = new PlayerSprite;
	mSprite->init();

	mToolSprite = new ToolSprite;
	mToolSprite->init();

	mShadow = mSprite->getShawdow();

	mElapsedSec = 0;
	mElapsedToolSec = 0;

	mPlayCount = 0;
	mCurFrame = 0;
	mCurToolFrame = 0;
	mCurAniStat = initStat;
	mCurAniDirection = initDirection;

	mVCurAni = mSprite->getSpriteAction(mCurAniDirection, mCurAniStat);
	mVCurToolAni = mToolSprite->getSpriteTool(eToolType::TT_PICK, eToolLevel::TL_GOLD);
}

void PlayerAnimation::changeStatAni(int changeStat)
{
	mPlayCount = 0;
	mCurFrame = 0;
	mCurToolFrame = 0;

	mCurAniStat = changeStat;
	mVCurAni = mSprite->getSpriteAction(mCurAniDirection, changeStat);
	mUpdateToolFrameSec = 1.0f / 5.0f;
}

void PlayerAnimation::changeDirectionAni(eGameDirection direction)
{
	mPlayCount = 0;
	mCurFrame = 0;

	mCurAniDirection = direction;
	mVCurAni = mSprite->getSpriteAction(direction, mCurAniStat);
}

void PlayerAnimation::frameUpdate(float elapsedTime)
{
	if (elapsedTime < 0) return;

	mElapsedSec += elapsedTime;
	mElapsedToolSec += elapsedTime;

	if (mElapsedSec > mAniInfo[mCurAniStat].FrameUpdateSec) {
		mElapsedSec = 0;

		/*
		mCurFrame++;
		if (mCurFrame >= mCurAniInfo->MaxFrameCount) {
			mCurFrame = 0;
			mPlayCount++;
		}
		*/

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
				bLoopFlag = true;
			}
		}
	}

	if (mElapsedToolSec > mUpdateToolFrameSec) {
		mElapsedToolSec = 0;

		mCurToolFrame++;
		if (mCurToolFrame >= 4) {
			mCurToolFrame = 0;
		}
	}
}

void PlayerAnimation::setStatFrameSec(int stat, float frameUpdateSec)
{
	mAniInfo[stat].FrameUpdateSec = 1.0f / frameUpdateSec;
}

void PlayerAnimation::render(HDC hdc, RectF rcF)
{
	mVCurAni[mCurFrame]->render(hdc, rcF.GetLeft(), rcF.GetTop());
	mVCurAni[mCurFrame + mSprite->getMaxFrameCount(mCurAniStat)]->render(hdc, rcF.GetLeft(), rcF.GetTop());
	mVCurAni[mCurFrame + mSprite->getMaxFrameCount(mCurAniStat) * 2]->render(hdc, rcF.GetLeft(), rcF.GetTop());

	mShadow->render(hdc, rcF.GetLeft() + rcF.Width / 2.0f, rcF.GetBottom(), XS_CENTER, YS_CENTER);

	//if (mCurAniStat == ePlayerStat::PS_ATTACK_1) {
		//mVCurToolAni[mCurToolFrame + (mCurAniDirection * 4)]->render(hdc, x - PLAYER_WIDTH / 2.0f, y - PLAYER_HEIGHT / 2.0f);
	//}
}

void PlayerAnimation::update()
{
}
