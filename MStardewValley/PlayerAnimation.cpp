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
	mHairImgList = PLAYERSPRITE->getHairImg();

	for (int i = 0; i < ePlayerAniStat::PAS_END; i++) {
		mAniInfoList[i].MaxFameCount = PLAYERSPRITE->getSpriteInfoList()[i].FrameCount;
		mAniInfoList[i].FrameUpdateSec = 1.0f / PLAYER_ANI_FRAME_SEC;
	}
}

void PlayerAnimation::release()
{
}

void PlayerAnimation::changeStatAni(ePlayerAniStat changeStat)
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
float a = 10;

void PlayerAnimation::frameUpdate(float elapsedTime)
{
	if (elapsedTime < 0) return;

	if (KEYMANAGER->isStayKeyDown('E')) {
		a += 0.5;
	}
	if (KEYMANAGER->isStayKeyDown('K')) {
		a -= 0.5;
	}
	mElapsedSec += elapsedTime;

	if (mElapsedSec > mAniInfoList[mCurAniStat].FrameUpdateSec) {
		mElapsedSec = 0;
		mCurFrame++;
		if (mCurFrame >= mAniInfoList[mCurAniStat].MaxFameCount) {
			mCurFrame = 0;
			mPlayCount++;
		}
	}
}

void PlayerAnimation::setStatFrameSec(ePlayerAniStat stat, float frameUpdateSec)
{
	mAniInfoList[stat].FrameUpdateSec = 1.0f / frameUpdateSec;
}


void PlayerAnimation::renderBase(HDC hdc, float centerX, float bottomY)
{
	int directionIndex = mCurAniDirection * mAniInfoList[mCurAniStat].MaxFameCount;
	mAniHeight = PLAYER_HEIGHT - mVCurHeight[mCurAniStat][mCurFrame];
	mVBaseAni[mCurAniStat][mCurFrame + directionIndex]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
	mHairImgList[mCurAniDirection]->render(hdc, centerX, bottomY - mAniHeight - a, XS_CENTER, YS_TOP);
	GDIPLUSMANAGER->drawRectF(hdc, mHairImgList[mCurAniDirection]->getRectF(centerX, bottomY - PLAYER_HEIGHT - a, XS_CENTER, YS_TOP));
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

float PlayerAnimation::getOneFrameUpdateSec(ePlayerAniStat stat) {
	return mAniInfoList[stat].FrameUpdateSec / mAniInfoList[mCurAniStat].MaxFameCount;
}