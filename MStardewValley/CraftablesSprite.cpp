#include "Stdafx.h"
#include "CraftablesSprite.h"

HRESULT CraftablesSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->clone(IMGCLASS->CraftablesSprite);

	ImageGp* furnaceIdle = new ImageGp;
	furnaceIdle->init(getMemDc(), mBaseSprite->getFrameBitmapToIndex(5, 2, 0, 1));

	mVAni[CBT_FURNACE].push_back(furnaceIdle);

	return S_OK;
}

void CraftablesSprite::release()
{
}
