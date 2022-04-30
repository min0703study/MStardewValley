#include "Stdafx.h"
#include "NPC.h"
#include "NpcAnimation.h"

HRESULT NPC::init(string id, eNpcs npcType, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameObject::Init(id, x, y, width, height, xStandard, yStandard);

	mNpcType = npcType;

	mAni = new NpcAnimation;
	mAni->init(npcType);

	mVPortraitImg = NPCMANAGER->getVPortraitImage(mNpcType);

	return S_OK;
}

void NPC::update()
{
}

void NPC::render()
{
	mAni->render(getMemDc(), getRelRectF().GetLeft(), getRelRectF().GetBottom() - getHeight());
}

void NPC::release()
{
}

void NPC::renderPortraitImg(eNpcPortraitsType type, float x, float y)
{
	mVPortraitImg[type]->render(x, y);
}
