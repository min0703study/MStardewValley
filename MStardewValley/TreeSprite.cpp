#include "Stdafx.h"
#include "TreeSprite.h"

HRESULT TreeSprite::init(void)
{
	MAPPALETTEMANAGER->findBaseSprite(MAPCLASS->OUTDOOR_P);

	mSpriteInfoList[TTP_NORMAL].FrameX = 0;
	mSpriteInfoList[TTP_NORMAL].FrameY = 0;
	mSpriteInfoList[TTP_NORMAL].FrameToXCount = 3;
	mSpriteInfoList[TTP_NORMAL].FrameToYCount = 6;
	mSpriteInfoList[TTP_NORMAL].HitStartIndexX = 1;
	mSpriteInfoList[TTP_NORMAL].HitFrameCount = 4;

	for (int type = TTP_NORMAL; type < TTP_END; type++) {
		mSpriteInfoList[type].HitStartIndexX = 1;
		mSpriteInfoList[type].HitFrameCount = 4;
		mSpriteInfoList[type].CrashStartIndexX = 5;
		mSpriteInfoList[type].CrashFrameCount = 2;
	}

	for (int type = eTreeType::TTP_NORMAL; type < eTreeType::TTP_END; type++) {
		SpriteInfo& info = mSpriteInfoList[type];

		//idle
		ImageGp* idleImg = new ImageGp;
		idleImg->initCenter(getMemDc(),
			MAPPALETTEMANAGER->findBaseSprite(MAPCLASS->OUTDOOR_P)->getFrameBitmapToIndex(
				info.FrameX,
				info.FrameY,
				info.FrameToXCount,
				info.FrameToYCount,
				TREE_IMG_WIDTH, TREE_IMG_HEIGHT),
			TREE_IMG_WIDTH, TREE_IMG_HEIGHT);
		mVAni[type].push_back(idleImg);
		//attack
		ImageGp* attackImg = new ImageGp;
		attackImg->init(getMemDc(),
			MAPPALETTEMANAGER->findBaseSprite(MAPCLASS->OUTDOOR_P)->getFrameBitmapToIndex(
				info.FrameX,
				info.FrameY,
				info.FrameToXCount,
				info.FrameToYCount,
				TREE_IMG_WIDTH, TREE_IMG_HEIGHT),
			TREE_IMG_WIDTH, TREE_IMG_HEIGHT);
		mVAni[type].push_back(attackImg);

		attackImg = new ImageGp;
		attackImg->init(getMemDc(),
			MAPPALETTEMANAGER->findBaseSprite(MAPCLASS->OUTDOOR_P)->getFrameBitmapToIndex(
				info.FrameX,
				info.FrameY,
				info.FrameToXCount,
				info.FrameToYCount,
				TREE_IMG_WIDTH, TREE_IMG_HEIGHT),
			TREE_IMG_WIDTH, TREE_IMG_HEIGHT);
		mVAni[type].push_back(attackImg);

		attackImg = new ImageGp;
		attackImg->init(getMemDc(),
			MAPPALETTEMANAGER->findBaseSprite(MAPCLASS->OUTDOOR_P)->getFrameBitmapToIndex(
				info.FrameX,
				info.FrameY,
				info.FrameToXCount,
				info.FrameToYCount,
				TREE_IMG_WIDTH, TREE_IMG_HEIGHT),
			TREE_IMG_WIDTH, TREE_IMG_HEIGHT);
		mVAni[type].push_back(attackImg);

		attackImg = new ImageGp;
		attackImg->init(getMemDc(),
			MAPPALETTEMANAGER->findBaseSprite(MAPCLASS->OUTDOOR_P)->getFrameBitmapToIndex(
				info.FrameX,
				info.FrameY,
				info.FrameToXCount,
				info.FrameToYCount,
				TREE_IMG_WIDTH, TREE_IMG_HEIGHT),
			TREE_IMG_WIDTH, TREE_IMG_HEIGHT);
		mVAni[type].push_back(attackImg);

		//crash
		ImageGp* crashImg = new ImageGp;
		crashImg->init(getMemDc(),
			MAPPALETTEMANAGER->findBaseSprite(MAPCLASS->OUTDOOR_P)->getFrameBitmapToIndex(
				info.FrameX,
				info.FrameY,
				info.FrameToXCount,
				info.FrameToYCount,
				TREE_IMG_WIDTH, TREE_IMG_HEIGHT),
			TREE_IMG_WIDTH, TREE_IMG_HEIGHT);
		mVAni[type].push_back(crashImg);

		crashImg = new ImageGp;
		crashImg->init(getMemDc(),
			MAPPALETTEMANAGER->findBaseSprite(MAPCLASS->OUTDOOR_P)->getFrameBitmapToIndex(
				info.FrameX,
				info.FrameY,
				info.FrameToXCount,
				info.FrameToYCount,
				TREE_IMG_WIDTH, TREE_IMG_HEIGHT),
			TREE_IMG_WIDTH, TREE_IMG_HEIGHT);
		mVAni[type].push_back(crashImg);
	}

	return S_OK;
}

void TreeSprite::release(void)
{
}
