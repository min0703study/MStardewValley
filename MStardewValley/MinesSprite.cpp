#include "Stdafx.h"
#include "MinesSprite.h"

HRESULT MinesSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->clone(IMGCLASS->MineRockSprite);
	mWeedSprite = GDIPLUSMANAGER->clone(IMGCLASS->WeedSprite);

	mSpriteInfoList[RT_NORMAL_1].FrameX =	0;
	mSpriteInfoList[RT_NORMAL_1].FrameY =	0;
	mSpriteInfoList[RT_NORMAL_1].HitStartIndexX =	1;
	mSpriteInfoList[RT_NORMAL_1].HitFrameCount =	4;

	mSpriteInfoList[RT_NORMAL_2].FrameX	=	2;
	mSpriteInfoList[RT_NORMAL_2].FrameY	=	0;
	mSpriteInfoList[RT_NORMAL_2].HitStartIndexX = 1;
	mSpriteInfoList[RT_NORMAL_2].HitFrameCount = 4;

	mSpriteInfoList[RT_NORMAL_3].FrameX	=	4;
	mSpriteInfoList[RT_NORMAL_3].FrameY	=	0;
	mSpriteInfoList[RT_NORMAL_3].HitStartIndexX = 1;
	mSpriteInfoList[RT_NORMAL_3].HitFrameCount = 4;

	mSpriteInfoList[RT_NORMAL_4].FrameX	=	6;
	mSpriteInfoList[RT_NORMAL_4].FrameY	=	0;
	mSpriteInfoList[RT_NORMAL_4].HitStartIndexX = 1;
	mSpriteInfoList[RT_NORMAL_4].HitFrameCount = 4;

	mSpriteInfoList[RT_NORMAL_5].FrameX	=	8;
	mSpriteInfoList[RT_NORMAL_5].FrameY	=	0;
	mSpriteInfoList[RT_NORMAL_5].HitStartIndexX = 1;
	mSpriteInfoList[RT_NORMAL_5].HitFrameCount = 4;

	mSpriteInfoList[RT_COPPER].FrameX	=	0;
	mSpriteInfoList[RT_COPPER].FrameY	=	1;
	mSpriteInfoList[RT_COPPER].HitStartIndexX = 1;
	mSpriteInfoList[RT_COPPER].HitFrameCount = 4;

	mSpriteInfoList[RT_IRON].FrameX		=	2;
	mSpriteInfoList[RT_IRON].FrameY		=	1;
	mSpriteInfoList[RT_IRON].HitStartIndexX = 1;
	mSpriteInfoList[RT_IRON].HitFrameCount = 4;

	mSpriteInfoList[RT_GOLD].FrameX		=	4;
	mSpriteInfoList[RT_GOLD].FrameY		=	1;
	mSpriteInfoList[RT_GOLD].HitStartIndexX = 1;
	mSpriteInfoList[RT_GOLD].HitFrameCount = 4;

	for (int type = 0; type < RT_END; type++) {
		mSpriteInfoList[type].HitStartIndexX = 1;
		mSpriteInfoList[type].HitFrameCount = 4;
		mSpriteInfoList[type].CrashStartIndexX = 5;
		mSpriteInfoList[type].CrashFrameCount = 2;
	}

	for (int type = eRockType::RT_NORMAL_1; type < eRockType::RT_END; type++) {
		SpriteInfo& info = mSpriteInfoList[type];

		//idle
		ImageGp* idleImg = new ImageGp;
		idleImg->initCenter(getMemDc(),
			mBaseSprite->getFrameBitmap(
				info.FrameX,
				info.FrameY,
				ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
			ROCK_WIDTH, ROCK_WIDTH);
		mVAni[type].push_back(idleImg);

		//attack
		for (int i = 0; i < 4; i++) {
			ImageGp* attackImg = new ImageGp;
			attackImg->initCenter(getMemDc(),
				mBaseSprite->getFrameBitmap(
					info.FrameX,
					info.FrameY,
					ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
				ROCK_WIDTH, ROCK_WIDTH, 2 * (i % 2 == 0 ? -1: 1), 0);
			mVAni[type].push_back(attackImg);
		}
	}

	ImageGp* idleImg = new ImageGp;
	idleImg->initCenter(getMemDc(),
		mWeedSprite->getFrameBitmap(
			0,
			0,
			ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
		ROCK_WIDTH, ROCK_WIDTH);
	mVWeedAni[eWeedType::WDT_NORMAL].push_back(idleImg);

	mStoneImg[ST_NORMAL] = new ImageGp;
	mStoneImg[ST_NORMAL]->initCenter(getMemDc(),
		mBaseSprite->getFrameBitmap(
			0,
			2,
			ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
		ROCK_WIDTH, ROCK_WIDTH);

	mStoneImg[ST_COPPER] = new ImageGp;
	mStoneImg[ST_COPPER]->initCenter(getMemDc(),
		mBaseSprite->getFrameBitmap(
			4,
			2,
			ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
		ROCK_WIDTH, ROCK_WIDTH);

	mStoneImg[ST_IRON] = new ImageGp;
	mStoneImg[ST_IRON]->initCenter(getMemDc(),
		mBaseSprite->getFrameBitmap(
			6,
			2,
			ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
		ROCK_WIDTH, ROCK_WIDTH);

	mStoneImg[ST_GOLD] = new ImageGp;
	mStoneImg[ST_GOLD]->initCenter(getMemDc(),
		mBaseSprite->getFrameBitmap(
			8,
			2,
			ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
		ROCK_WIDTH, ROCK_WIDTH);

	return S_OK;
}

void MinesSprite::release(void)
{
	for (int i = eRockType::RT_NORMAL_1; i < eRockType::RT_END; i++) {
		for (vector<ImageGp*>::iterator mVIMines = mVAni[i].begin(); mVIMines != mVAni[i].end(); mVIMines++) {
			(*mVIMines)->release();
			SAFE_DELETE(*mVIMines);
		}
	}
}