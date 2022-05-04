#include "Stdafx.h"
#include "NpcAnimation.h"

void NpcAnimation::init(eNpcs type)
{
	mVAni = NPCSPRITE->getVAni(type);
}

void NpcAnimation::release()
{
}

void NpcAnimation::frameUpdate(float elapsedTime)
{
	if (!bIsPlaying || elapsedTime < 0) return;
}

void NpcAnimation::setStatFrameSec(int stat, float frameUpdateSec)
{
}

void NpcAnimation::render(HDC hdc, float centerX, float bottomY)
{
	mVAni[0]->render(centerX, bottomY);
}
