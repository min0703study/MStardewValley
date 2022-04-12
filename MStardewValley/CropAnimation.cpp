#include "Stdafx.h"
#include "CropAnimation.h"

void CropAnimation::init(eCropType type)
{
	mCurFrame = 0;
	mCurStage = 0;
	mVAni = CROPSPRITE->getVAni(type);
}

void CropAnimation::release()
{
}

void CropAnimation::chageStage(int changeStage)
{
	this->mCurStage = changeStage;
}

void CropAnimation::changeStatAni(int changeStat)
{
}

void CropAnimation::frameUpdate(float elapsedTime)
{
}

void CropAnimation::setStatFrameSec(int stat, float frameUpdateSec)
{
}

void CropAnimation::render(HDC hdc, float centerX, float bottomY)
{
	mVAni[mCurStage]->render(hdc, centerX, bottomY, XS_CENTER, YS_BOTTOM);
}
