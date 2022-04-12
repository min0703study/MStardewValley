#include "Stdafx.h"
#include "PlayerAnimation.h"

void PlayerAnimation::init(int initStat, eGameDirection initDirection)
{
	mShadow = PLAYERSPRITE->getShawdow();

	mElapsedSec = 0;
	mPlayCount = 0;
	mCurFrame = 0;

	mCurAniStat = initStat;
	mCurAniDirection = initDirection;

	mAniHeight = PLAYER_HEIGHT;
	mAniWidth = PLAYER_WIDTH;

	mVBaseAni = PLAYERSPRITE->getVBaseAni();
	mVArmAni = PLAYERSPRITE->getVArmAni();
	mVLegAni = PLAYERSPRITE->getVLegAni();
	mVCurHeight = PLAYERSPRITE->getVAniHeight();

	for (int i = 0; i < ePlayerStat::PS_END; i++) {
		mAniInfoList[i].MaxFameCount = PLAYERSPRITE->getSpriteInfoList()[i].FrameCount;
		mAniInfoList[i].FrameUpdateSec = 1.0f / PLAYER_ANI_FRAME_SEC;
	}
}

void PlayerAnimation::release()
{
}

void PlayerAnimation::changeStatAni(ePlayerStat changeStat)
{
	mPlayCount = 0;
	mCurFrame = 0;

	mCurAniStat = changeStat;
}

void PlayerAnimation::changeDirectionAni(eGameDirection direction)
{
	mPlayCount = 0;
	mCurFrame = 0;

	mCurAniDirection = direction;
}

void PlayerAnimation::frameUpdate(float elapsedTime)
{
	if (elapsedTime < 0) return;

	mElapsedSec += elapsedTime;

	if (mElapsedSec > mAniInfoList[mCurAniStat].FrameUpdateSec) {
		mElapsedSec = 0;

		mAniHeight = PLAYER_HEIGHT - mVCurHeight[mCurAniStat][mCurFrame];

		mCurFrame++;
		if (mCurFrame >= mAniInfoList[mCurAniStat].MaxFameCount) {
			mCurFrame = 0;
			mPlayCount++;
		}
	}
}

void PlayerAnimation::setStatFrameSec(ePlayerStat stat, float frameUpdateSec)
{
	mAniInfoList[stat].FrameUpdateSec = 1.0f / frameUpdateSec;
}

void PlayerAnimation::renderBase(HDC hdc, float centerX, float bottomY)
{
	int directionIndex = mCurAniDirection * mAniInfoList[mCurAniStat].MaxFameCount;
	mVBaseAni[mCurAniStat][mCurFrame + directionIndex]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
}

void PlayerAnimation::renderArm(HDC hdc, float centerX, float bottomY) {
	int directionIndex = mCurAniDirection * mAniInfoList[mCurAniStat].MaxFameCount;
	mVArmAni[mCurAniStat][mCurFrame + directionIndex]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);

};

void PlayerAnimation::renderLeg(HDC hdc, float centerX, float bottomY) {
	int directionIndex = mCurAniDirection * mAniInfoList[mCurAniStat].MaxFameCount;
	mVLegAni[mCurAniStat][mCurFrame + directionIndex]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
	mShadow->render(hdc, centerX, bottomY, XS_CENTER, YS_CENTER);
};

int PlayerAnimation::getPlayCount() { return mPlayCount; }

float PlayerAnimation::getOneFrameUpdateSec(ePlayerStat stat) {
	return mAniInfoList[stat].FrameUpdateSec / mAniInfoList[mCurAniStat].MaxFameCount;
}