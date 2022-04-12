#include "Stdafx.h"
#include "MineRock.h"

void MineRock::init(string id, eRockType type, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameObject::Init(id, x, y, width, height, xStandard, yStandard);
	mStoneType = type;

	mAni = new MineRockAnimation;
	mAni->init(type);
}

void MineRock::update(void)
{
}

void MineRock::render(void)
{
	mAni->render(getMemDc(), getRelRectF());
}

void MineRock::release(void)
{
	mAni->release();
	SAFE_DELETE(mAni);
}
