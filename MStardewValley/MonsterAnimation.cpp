#include "Stdafx.h"
#include "MonsterAnimation.h"

void MonsterAnimation::init(eMonsterType type)
{
	mCurFrame = 0;
	mElapsedSec = 0;
	mFrameUpdateSec = 1.0f / 3;
	mCurAniStat = 0;

	mVCurAni = MONSTERSPRITE->getVAni(type);
}

void MonsterAnimation::release()
{
}

void MonsterAnimation::changeStatAni(int changeStat)
{
}

void MonsterAnimation::frameUpdate(float elapsedTime)
{
	if (elapsedTime < 0) return;

	mElapsedSec += elapsedTime;

	if (mElapsedSec > mFrameUpdateSec) {
		mElapsedSec = 0;

		mCurFrame++;
		if (mCurFrame >= 4) {
			mCurFrame = 0;
		}
	}
}

void MonsterAnimation::setStatFrameSec(int stat, float frameUpdateSec)
{
}

void MonsterAnimation::render(HDC hdc, RectF rcF)
{
	mVCurAni[(int)mCurFrame + mCurAniStat]->render(hdc, rcF.GetLeft(), rcF.GetTop());
}
