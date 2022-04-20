#include "Stdafx.h"
#include "MonsterSprite.h"

HRESULT MonsterSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->clone(IMGCLASS->MonsterSprite);

	SpriteInfo* curInfo = &mSpriteInfoList[eMonsterType::MST_GRUB];
	curInfo->StatCount = 1;
	curInfo->StartIndex = new int[curInfo->StatCount];
	curInfo->DirectionInterval = new int[curInfo->StatCount];
	curInfo->MaxFrameCount = new int[curInfo->StatCount];
	curInfo->StartIndex[0] = 0;
	curInfo->DirectionInterval[0] = 4;
	curInfo->MaxFrameCount[0] = 4;

	mMonsterX[eMonsterType::MST_GRUB] = 735;
	mMonsterY[eMonsterType::MST_GRUB] = 12;
	mMonsterXCount[eMonsterType::MST_GRUB] = 4;
	mMonsterYCount[eMonsterType::MST_GRUB] = 4;
	mMonsterWidth[eMonsterType::MST_GRUB] = 16.0f;
	mMonsterHeight[eMonsterType::MST_GRUB] = 22.5f;

	for (int type = eMonsterType::MST_GRUB; type <= eMonsterType::MST_GRUB; type++) {
		for (int i = 0; i < 4; i++) {
			ImageGp* tempImg = new ImageGp;
			tempImg->initCenter(getMemDc(),
				mBaseSprite->getPartBitmap(
					mMonsterX[type] + (mMonsterWidth[type] * i),
					mMonsterY[type] + (mMonsterHeight[type] * 2),
					TILE_SIZE * 0.8,
					TILE_SIZE,
					mMonsterWidth[type],
					mMonsterHeight[type]),
				TILE_SIZE,
				TILE_SIZE);
			mVMonster[type].push_back(tempImg);
		}
		for (int i = 0; i < 4; i++) {
			ImageGp* tempImg = new ImageGp;
			tempImg->initCenter(getMemDc(),
				mBaseSprite->getPartBitmap(
					mMonsterX[type] + (mMonsterWidth[type] * i),
					mMonsterY[type] + (mMonsterHeight[type] * 1),
					TILE_SIZE * 0.8,
					TILE_SIZE,
					mMonsterWidth[type],
					mMonsterHeight[type]),
				TILE_SIZE,
				TILE_SIZE);
			mVMonster[type].push_back(tempImg);
		}
		for (int i = 0; i < 4; i++) {
			ImageGp* tempImg = new ImageGp;
			tempImg->initCenter(getMemDc(),
				mBaseSprite->getPartBitmap(
					mMonsterX[type] + (mMonsterWidth[type] * i),
					mMonsterY[type] + (mMonsterHeight[type] * 3),
					TILE_SIZE * 0.8,
					TILE_SIZE,
					mMonsterWidth[type],
					mMonsterHeight[type]),
				TILE_SIZE,
				TILE_SIZE);
			mVMonster[type].push_back(tempImg);
		}
		for (int i = 0; i < 4; i++) {
			ImageGp* tempImg = new ImageGp;
			tempImg->initCenter(getMemDc(),
				mBaseSprite->getPartBitmap(
					mMonsterX[type] + (mMonsterWidth[type] * i),
					mMonsterY[type] + (mMonsterHeight[type] * 0),
					TILE_SIZE * 0.8,
					TILE_SIZE,
					mMonsterWidth[type],
					mMonsterHeight[type]),
				TILE_SIZE,
				TILE_SIZE);
			mVMonster[type].push_back(tempImg);
		}
	}

	return S_OK;
}

void MonsterSprite::release(void)
{
}

vector<ImageGp*> MonsterSprite::getVAni(eMonsterType type)
{
	return mVMonster[type];
}
