#include "Stdafx.h"
#include "NPC.h"
#include "NpcAnimation.h"

HRESULT NPC::init(eNpcs npcType)
{
	mNpcType = npcType;

	mAni = new NpcAnimation;
	mAni->init(npcType);
	mVPortraitImg = NPCMANAGER->getVPortraitImage(mNpcType);

	return S_OK;
}

void NPC::update()
{
}

void NPC::render(float x, float y)
{
	mAni->render(getMemDc(), x, y);
}

void NPC::release()
{
}

void NPC::renderPortraitImg(eNpcPortraitsType type, float x, float y)
{
	mVPortraitImg[type]->render(x, y);
}
