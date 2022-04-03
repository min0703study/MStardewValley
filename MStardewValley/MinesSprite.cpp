#include "Stdafx.h"
#include "MinesSprite.h"

HRESULT MinesSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MineRockSprite);

	mMineTypeIndexX[eMineStoneType::MT_NORMAL_1] =	0;
	mMineTypeIndexX[eMineStoneType::MT_NORMAL_2] =	2;
	mMineTypeIndexX[eMineStoneType::MT_NORMAL_3] =	4;
	mMineTypeIndexX[eMineStoneType::MT_NORMAL_4] =	6;
	mMineTypeIndexX[eMineStoneType::MT_NORMAL_5] =	8;
	mMineTypeIndexX[eMineStoneType::MT_COPPER] =	0;
	mMineTypeIndexX[eMineStoneType::MT_IRON] =		2;
	mMineTypeIndexX[eMineStoneType::MT_GOLD] =		4;

	mMineTypeIndexY[eMineStoneType::MT_NORMAL_1] =	0;
	mMineTypeIndexY[eMineStoneType::MT_NORMAL_2] =	0;
	mMineTypeIndexY[eMineStoneType::MT_NORMAL_3] =	0;
	mMineTypeIndexY[eMineStoneType::MT_NORMAL_4] =	0;
	mMineTypeIndexY[eMineStoneType::MT_NORMAL_5] =	0;
	mMineTypeIndexY[eMineStoneType::MT_COPPER] =	1;
	mMineTypeIndexY[eMineStoneType::MT_IRON] =		1;
	mMineTypeIndexY[eMineStoneType::MT_GOLD] =		1;

	for (int i = eMineStoneType::MT_NORMAL_1; i < eMineStoneType::MT_END; i++) {
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
	for (int i = eMineStoneType::MT_NORMAL_1; i < eMineStoneType::MT_END; i++) {
		for (vector<ImageGp*>::iterator mVIMines = mVMines[i].begin(); mVIMines != mVMines[i].end(); mVIMines++) {
			(*mVIMines)->release();
			SAFE_DELETE(*mVIMines);
		}
	}
}

vector<ImageGp*> MinesSprite::getVAni(eMineStoneType stoneType)
{
	return mVMines[stoneType];
}
