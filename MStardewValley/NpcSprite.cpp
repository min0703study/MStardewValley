#include "Stdafx.h"
#include "NpcSprite.h"

HRESULT NpcSprite::init(void)
{
	mBaseActionImage[eNpcs::NPC_PIERRE] = GDIPLUSMANAGER->clone(IMGCLASS->NpcSpritePierreA);
	mBasePortraitImage[eNpcs::NPC_PIERRE] = GDIPLUSMANAGER->clone(IMGCLASS->NpcSpritePierreP);

	for (int x = 0; x < mBasePortraitImage[eNpcs::NPC_PIERRE]->getMaxFrameX(); x++) {
		for (int y = 0; y < mBasePortraitImage[eNpcs::NPC_PIERRE]->getMaxFrameY(); y++) {
			ImageGp* tempImg = new ImageGp;
			tempImg->init(getMemDc(), mBasePortraitImage[eNpcs::NPC_PIERRE]->getFrameBitmap(x, y));
			mVPortraits[eNpcs::NPC_PIERRE].push_back(tempImg);
		}
	}


	return E_NOTIMPL;
}

void NpcSprite::release(void)
{
}
