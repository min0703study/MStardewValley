#include "Stdafx.h"
#include "MinesSprite.h"

HRESULT MinesSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->cloneImage(IMGCLASS->MineRockSprite);

	mMineTypeIndexX[eRockType::RT_NORMAL_1] =	0;
	mMineTypeIndexX[eRockType::RT_NORMAL_2] =	2;
	mMineTypeIndexX[eRockType::RT_NORMAL_3] =	4;
	mMineTypeIndexX[eRockType::RT_NORMAL_4] =	6;
	mMineTypeIndexX[eRockType::RT_NORMAL_5] =	8;
	mMineTypeIndexX[eRockType::RT_COPPER] =	0;
	mMineTypeIndexX[eRockType::RT_IRON] =		2;
	mMineTypeIndexX[eRockType::RT_GOLD] =		4;

	mMineTypeIndexY[eRockType::RT_NORMAL_1] =	0;
	mMineTypeIndexY[eRockType::RT_NORMAL_2] =	0;
	mMineTypeIndexY[eRockType::RT_NORMAL_3] =	0;
	mMineTypeIndexY[eRockType::RT_NORMAL_4] =	0;
	mMineTypeIndexY[eRockType::RT_NORMAL_5] =	0;
	mMineTypeIndexY[eRockType::RT_COPPER] =	1;
	mMineTypeIndexY[eRockType::RT_IRON] =		1;
	mMineTypeIndexY[eRockType::RT_GOLD] =		1;

	for (int i = eRockType::RT_NORMAL_1; i < eRockType::RT_END; i++) {
		vector<ImageGp*> tempVImageGp;
		//idle
		ImageGp* idleImg = new ImageGp;
		idleImg->initCenter(getMemDc(),
			mBaseSprite->getFrameBitmap(
				mMineTypeIndexX[i],
				mMineTypeIndexY[i], 
				ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
			ROCK_WIDTH, ROCK_WIDTH);
		tempVImageGp.push_back(idleImg);
		//attack
		ImageGp* attackImg = new ImageGp;
		attackImg->init(getMemDc(),
			mBaseSprite->getFrameBitmap(
				mMineTypeIndexX[i],
				mMineTypeIndexY[i],
				ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
			10, 0, ROCK_WIDTH, ROCK_WIDTH);
		tempVImageGp.push_back(attackImg);

		attackImg = new ImageGp;
		attackImg->init(getMemDc(),
			mBaseSprite->getFrameBitmap(
				mMineTypeIndexX[i],
				mMineTypeIndexY[i],
				ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
			5, 0, ROCK_WIDTH, ROCK_WIDTH);
		tempVImageGp.push_back(attackImg);

		attackImg = new ImageGp;
		attackImg->init(getMemDc(),
			mBaseSprite->getFrameBitmap(
				mMineTypeIndexX[i],
				mMineTypeIndexY[i],
				ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
			10, 0, ROCK_WIDTH, ROCK_WIDTH);
		tempVImageGp.push_back(attackImg);

		attackImg = new ImageGp;
		attackImg->init(getMemDc(),
			mBaseSprite->getFrameBitmap(
				mMineTypeIndexX[i],
				mMineTypeIndexY[i],
				ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
			5, 0, ROCK_WIDTH, ROCK_WIDTH);
		tempVImageGp.push_back(attackImg);
		//crash
		mVMines[i] = tempVImageGp;

		ImageGp* crashImg = new ImageGp;
		crashImg->init(getMemDc(),
			mBaseSprite->getFrameBitmap(
				mMineTypeIndexX[i] + 1,
				mMineTypeIndexY[i],
				ROCK_IMG_WIDTH, ROCK_IMG_HEIGHT),
			5, 0, ROCK_WIDTH, ROCK_WIDTH);
		tempVImageGp.push_back(crashImg);
		mVMines[i] = tempVImageGp;
	}

	return S_OK;
}

void MinesSprite::release(void)
{
	for (int i = eRockType::RT_NORMAL_1; i < eRockType::RT_END; i++) {
		for (vector<ImageGp*>::iterator mVIMines = mVMines[i].begin(); mVIMines != mVMines[i].end(); mVIMines++) {
			(*mVIMines)->release();
			SAFE_DELETE(*mVIMines);
		}
	}
}

vector<ImageGp*> MinesSprite::getVAni(eRockType stoneType)
{
	return mVMines[stoneType];
}
