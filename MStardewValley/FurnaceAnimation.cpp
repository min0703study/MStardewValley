#include "Stdafx.h"
#include "FurnaceAnimation.h"

void FurnaceAnimation::init()
{
	mVCurAni = CRAFTABLESSPRITE->getVAni(eCraftablesType::CBT_FURNACE);
	mCurFrame = 0;
}

void FurnaceAnimation::release()
{
}

void FurnaceAnimation::playAniOneTime(eFuranceStat oneTimeAni)
{
}

void FurnaceAnimation::playAniLoop(eFuranceStat loopAni)
{
	if (loopAni == eFuranceStat::FS_SMELTING) {
		mCurFrame = 1;
	}
	else {
		mCurFrame = 0;
	}
}

void FurnaceAnimation::frameUpdate(float elapsedTime)
{
}

void FurnaceAnimation::render(float centerX, float centerY)
{
	mVCurAni[mCurFrame]->render(centerX, centerY);
}