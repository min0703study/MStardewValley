#include "Stdafx.h"
#include "NpcSprite.h"

HRESULT NpcSprite::init(void)
{
	mBaseActionImage[eNpcs::NPC_PIERRE] = GDIPLUSMANAGER->clone(IMGCLASS->NpcSpritePierreA);
	mBasePortraitImage[eNpcs::NPC_PIERRE] = GDIPLUSMANAGER->clone(IMGCLASS->NpcSpritePierreP);

	mBaseActionImage[eNpcs::NPC_MARLON] = GDIPLUSMANAGER->clone(IMGCLASS->NpcSpriteMarlonA);
	mBasePortraitImage[eNpcs::NPC_MARLON] = GDIPLUSMANAGER->clone(IMGCLASS->NpcSpriteMarlonP);

	mBaseActionImage[eNpcs::NPC_CLINT] = GDIPLUSMANAGER->clone(IMGCLASS->NpcSpriteMarlonA);
	mBasePortraitImage[eNpcs::NPC_CLINT] = GDIPLUSMANAGER->clone(IMGCLASS->NpcSpriteMarlonP);

	for (int x = 0; x < mBasePortraitImage[eNpcs::NPC_PIERRE]->getMaxFrameX(); x++) {
		for (int y = 0; y < mBasePortraitImage[eNpcs::NPC_PIERRE]->getMaxFrameY(); y++) {
			ImageGp* tempImg = new ImageGp;
			tempImg->init(getMemDc(), mBasePortraitImage[eNpcs::NPC_PIERRE]->getFrameBitmap(x, y, NPC_P_W_SIZE, NPC_P_H_SIZE));
			mVPortraits[eNpcs::NPC_PIERRE].push_back(tempImg);
		}
	}

	ImageGp* tempImg = new ImageGp;
	tempImg->init(getMemDc(), mBasePortraitImage[eNpcs::NPC_MARLON]->getBitmap(), NPC_P_W_SIZE, NPC_P_H_SIZE);
	mVPortraits[eNpcs::NPC_MARLON].push_back(tempImg);

	ImageGp* marlon = new ImageGp;
	marlon->init(getMemDc(), mBaseActionImage[eNpcs::NPC_MARLON]->getFrameBitmap(0,0));
	marlon->setSize(PLAYER_WIDTH, PLAYER_HEIGHT);
	mVAni[eNpcs::NPC_MARLON].push_back(marlon);

	ImageGp* idle = new ImageGp;
	idle->init(getMemDc(), mBaseActionImage[eNpcs::NPC_PIERRE]->getFrameBitmap(0,0));
	idle->setSize(PLAYER_WIDTH, PLAYER_HEIGHT);
	mVAni[eNpcs::NPC_PIERRE].push_back(idle);

	return S_OK;
}

void NpcSprite::release(void)
{
}
