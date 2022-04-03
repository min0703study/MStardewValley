#include "Stdafx.h"
#include "MineRockAnimation.h"

void MineRockAnimation::init(eMineStoneType type)
{
	mCurFrame = 0;
	mVCurAni = MINESSPRITE->getVAni(type);
}

void MineRockAnimation::release()
{
}

void MineRockAnimation::changeStatAni(int changeStat)
{
}

void MineRockAnimation::frameUpdate(float elapsedTime)
{

}

void MineRockAnimation::setStatFrameSec(int stat, float frameUpdateSec)
{
}

void MineRockAnimation::render(HDC hdc, RectF rcF)
{
	mVCurAni[mCurFrame]->render(hdc, rcF.GetLeft(), rcF.GetTop());
}
