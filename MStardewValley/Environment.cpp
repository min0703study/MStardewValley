#include "Stdafx.h"
#include "Environment.h"

void Environment::init(int tileX, int tileY, int toIndexX, int toIndexY)
{
	TileObject::init(tileX, tileY, toIndexX, toIndexY);
}

///////////////////////////////////////////////////////////////////////////////////

void Rock::init(eRockType type, int tileX, int tileY)
{
	TileObject::init(tileX, tileY, 0, 0);
	mRockType = type;

	mAni = new MineRockAnimation;
	mAni->init(mRockType);
}

void Rock::update(void)
{
}

void Rock::render(void)
{
}

void Rock::release(void)
{
}

void Rock::render(float centerX, float centerY)
{
	mAni->render(getMemDc(), centerX, centerY);
}
