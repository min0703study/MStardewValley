#include "Stdafx.h"
#include "CraftablesSprite.h"

HRESULT CraftablesSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->clone(IMGCLASS->CraftablesSprite);

	ImageGp* furnaceIdle = new ImageGp;
	furnaceIdle->init(getMemDc(), mBaseSprite->getFrameBitmapToIndex(5, 2, 0, 1, TILE_SIZE, TILE_SIZE*2.0f));

	mVAni[CBT_FURNACE].push_back(furnaceIdle);

	ImageGp* furanaceMake = new ImageGp;
	furanaceMake->init(getMemDc(), mBaseSprite->getFrameBitmapToIndex(6, 2, 0, 1, TILE_SIZE, TILE_SIZE * 2.0f));
	mVAni[CBT_FURNACE].push_back(furanaceMake);

	return S_OK;
}

void CraftablesSprite::release()
{
}
