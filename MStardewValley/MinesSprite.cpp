#include "Stdafx.h"
#include "MinesSprite.h"

HRESULT MinesSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->clone(IMGCLASS->MineRockSprite);

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
1;

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
		ImageGp* attackImg = new ImageGp;
		attackImg->init(getMemDc(),
			mBaseSprite->getFrameBitmap(
				info.FrameX,
				info.FrameY,
				ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
			10, 0, ROCK_WIDTH, ROCK_WIDTH);
		mVAni[type].push_back(attackImg);

		attackImg = new ImageGp;
		attackImg->init(getMemDc(),
			mBaseSprite->getFrameBitmap(
				info.FrameX,
				info.FrameY,
				ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
			5, 0, ROCK_WIDTH, ROCK_WIDTH);
		mVAni[type].push_back(attackImg);

		attackImg = new ImageGp;
		attackImg->init(getMemDc(),
			mBaseSprite->getFrameBitmap(
				info.FrameX,
				info.FrameY,
				ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
			10, 0, ROCK_WIDTH, ROCK_WIDTH);
		mVAni[type].push_back(attackImg);

		attackImg = new ImageGp;
		attackImg->init(getMemDc(),
			mBaseSprite->getFrameBitmap(
				info.FrameX,
				info.FrameY,
				ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
			5, 0, ROCK_WIDTH, ROCK_WIDTH);
		mVAni[type].push_back(attackImg);
		
		//crash
		ImageGp* crashImg = new ImageGp;
		crashImg->init(getMemDc(),
			mBaseSprite->getFrameBitmap(
				info.FrameX + 1,
				info.FrameY,
				ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
			5, 0, ROCK_WIDTH, ROCK_WIDTH);
		mVAni[type].push_back(crashImg);

		crashImg = new ImageGp; 
		crashImg->init(getMemDc(),
			mBaseSprite->getFrameBitmap(
				info.FrameX + 1,
				info.FrameY,
				ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
			5, 0, ROCK_WIDTH, ROCK_WIDTH);
		mVAni[type].push_back(crashImg);
	}

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