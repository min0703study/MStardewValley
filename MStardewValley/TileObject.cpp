#include "Stdafx.h"
#include "TileObject.h"

void TileObject::init(int indexX, int indexY, int xCount, int yCount, eXStandard xStandard, eYStandard yStandard)
{
	mIndexX = indexX;
	mIndexY = indexY;

	switch (xStandard) {
	case XS_LEFT:
		mStartIndexX = indexX;
		mEndIndexX = indexX + (xCount - 1);
		break;
	case XS_RIGHT:
		mStartIndexX = indexX - (xCount - 1);
		mEndIndexX = indexX;
		break;
	case XS_CENTER:
		mStartIndexX = indexX - (xCount - 1) * 0.5f;
		mEndIndexX = indexX + (xCount - 1) * 0.5f;
		break;
	}
	switch (yStandard) {
	case YS_TOP:
		mStartIndexY = indexY;
		mEndIndexY = indexY + (yCount - 1);
		break;
	case YS_BOTTOM:
		mStartIndexY = indexY - (yCount - 1);
		mEndIndexY = indexY;
		break;
	case YS_CENTER:
		mStartIndexY = indexY - (yCount - 1) * 0.5f;
		mEndIndexY = indexY + (yCount - 1) * 0.5f;
		break;
	}
	
	mAbsX = mStartIndexX * TILE_SIZE;
	mAbsY = mStartIndexY * TILE_SIZE;
	
	mWidth = TILE_SIZE * xCount;
	mHeight = TILE_SIZE * xCount;

	mRectF = RectFMake(mAbsX, mAbsY, mWidth, mHeight);
}

void TileObject::release(void)
{
}

void TileObject::draw(void)
{

}

void TileObject::animation(void)
{
}

void TileObject::move(void)
{
}

void TileObject::action(void)
{
}
