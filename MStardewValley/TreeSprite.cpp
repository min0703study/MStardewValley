#include "Stdafx.h"
#include "TreeSprite.h"

#define TREE_X_COUNT 2
#define TREE_Y_COUNT 5

HRESULT TreeSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->clone(IMGCLASS->TreeSprite);

	int frameX = 0;
	int frameY = 0;

	mSpriteInfo[TAS_IDLE].StartIndex = 0;
	mSpriteInfo[TAS_IDLE].FrameCount = 1;

	mSpriteInfo[TAS_TRANS].StartIndex = 1;
	mSpriteInfo[TAS_TRANS].FrameCount = 1;

	mSpriteInfo[TAS_HIT].StartIndex = 2;
	mSpriteInfo[TAS_HIT].FrameCount = 4;

	mSpriteInfo[TAS_CRASH].StartIndex = 6;
	mSpriteInfo[TAS_CRASH].FrameCount = 6;

	mSpriteInfo[TAS_STUMP_IDLE].StartIndex = 12;
	mSpriteInfo[TAS_STUMP_IDLE].FrameCount = 1;

	for (int type = eTreeType::TTP_NORMAL; type < eTreeType::TTP_END; type++) {
		SpriteInfo& info = mSpriteInfoList[type];
		ImageGp* treeTop = new ImageGp;
		ImageGp* treeStump = new ImageGp;

		treeTop->init(getMemDc(),
			mBaseSprite->getFrameBitmapToIndex(
				frameX,
				type * 11,
				TREE_X_COUNT,
				TREE_Y_COUNT,
				TREE_IMG_TOP_WIDTH, TREE_IMG_TOP_HEIGHT)
		);

		treeStump->init(getMemDc(),
			mBaseSprite->getFrameBitmapToIndex(
				frameX + 2,
				type * 11 + 6,
				0,
				1,
				TREE_IMG_STUMP_WIDTH, TREE_IMG_STUMP_HEIGHT));

		//idle
		ImageGp* idleImg = new ImageGp;
		idleImg->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(TREE_IMG_WIDTH, TREE_IMG_HEIGHT));
		
		idleImg->overlayImageGp(treeStump, XS_CENTER, YS_BOTTOM);
		idleImg->overlayImageGp(treeTop, XS_CENTER, YS_TOP);
		mVAni[type].push_back(idleImg);

		//trans
		ImageGp* toTrans = new ImageGp;
		toTrans->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(TREE_IMG_WIDTH, TREE_IMG_HEIGHT));
		treeTop->toAlpha();
		treeTop->rebuildChachedBitmap();
		toTrans->overlayImageGp(treeStump, XS_CENTER, YS_BOTTOM);
		toTrans->overlayImageGp(treeTop, XS_CENTER, YS_TOP, false);

		mVAni[type].push_back(toTrans);

		for (int i = 0; i < 4; i++) {
			ImageGp* tt = new ImageGp;
			tt->init(getMemDc(),
				mBaseSprite->getFrameBitmapToIndex(
					frameX,
					frameY,
					TREE_X_COUNT,
					TREE_Y_COUNT,
					TREE_IMG_TOP_WIDTH, TREE_IMG_TOP_HEIGHT)
			);
			ImageGp* hitImg = new ImageGp;
			hitImg->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(TREE_IMG_WIDTH, TREE_IMG_HEIGHT));
			tt->move(3.0f * (i % 2 == 0 ? 1 : -1));
			hitImg->overlayImageGp(treeStump, XS_CENTER, YS_BOTTOM);
			hitImg->overlayImageGp(tt, XS_CENTER, YS_TOP, false);

			mVAni[type].push_back(hitImg);
		}
		for (int i = 0; i < 6; i++) {
			ImageGp* tt = new ImageGp;
			tt->init(getMemDc(),
				mBaseSprite->getFrameBitmapToIndex(
					frameX,
					frameY,
					TREE_X_COUNT,
					TREE_Y_COUNT,
					TREE_IMG_TOP_WIDTH, TREE_IMG_TOP_HEIGHT)
			);

			ImageGp* crashImg = new ImageGp;
			crashImg->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(TREE_IMG_TOP_HEIGHT * 2.0f, TREE_IMG_HEIGHT));
			tt->rotate(i * 20.0f, XS_CENTER, YS_BOTTOM, TREE_IMG_TOP_HEIGHT * 2.0f, TREE_IMG_TOP_HEIGHT);
			tt->rebuildChachedBitmap();
			crashImg->overlayImageGp(treeStump, XS_CENTER, YS_BOTTOM);
			crashImg->overlayImageGp(tt, XS_CENTER, YS_TOP, false);
			mVAni[type].push_back(crashImg);
		}
		
		ImageGp* stumpIdle = new ImageGp;
		stumpIdle->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(TREE_IMG_WIDTH, TREE_IMG_HEIGHT));
		stumpIdle->overlayImageGp(treeStump, XS_CENTER, YS_BOTTOM);
		mVAni[type].push_back(stumpIdle);
	}


	return S_OK;
}

void TreeSprite::release(void)
{
}
