#include "Stdafx.h"
#include "MonsterSprite.h"

HRESULT MonsterSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->clone(IMGCLASS->MonsterSprite);

	SpriteInfo* curInfo = &mSpriteInfoList[eMonsterType::MST_GRUB];
	curInfo->StatCount = 2;
	curInfo->StartIndex = new int[curInfo->StatCount];
	curInfo->DirectionInterval = new int[curInfo->StatCount];
	curInfo->MaxFrameCount = new int[curInfo->StatCount];

	curInfo->StartIndex[0] = 0;
	curInfo->DirectionInterval[0] = 4;
	curInfo->MaxFrameCount[0] = 4;

	curInfo->StartIndex[1] = 16;
	curInfo->DirectionInterval[1] = 4;
	curInfo->MaxFrameCount[1] = 4;


	curInfo = &mSpriteInfoList[eMonsterType::MST_SLIME];
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

	mMonsterX[eMonsterType::MST_SLIME] = 663;
	mMonsterY[eMonsterType::MST_SLIME] = 443;
	mMonsterXCount[eMonsterType::MST_SLIME] = 4;
	mMonsterYCount[eMonsterType::MST_SLIME] = 4;
	mMonsterWidth[eMonsterType::MST_SLIME] = 16.0f;
	mMonsterHeight[eMonsterType::MST_SLIME] = 22.5f;

	int directionRank[4] = {2, 1, 3, 0};

	for (int type = eMonsterType::MST_GRUB; type < eMonsterType::MST_END; type++) {
		for (int dir = 0; dir < eGameDirection::GD_END; dir++) {
			for (int i = 0; i < 4; i++) {
				ImageGp* tempImg = new ImageGp;
				tempImg->initCenter(getMemDc(),
					mBaseSprite->getPartBitmap(
						mMonsterX[type] + (mMonsterWidth[type] * i),
						mMonsterY[type] + (mMonsterHeight[type] * directionRank[dir]),
						TILE_SIZE * 0.8,
						TILE_SIZE,
						mMonsterWidth[type],
						mMonsterHeight[type]),
					TILE_SIZE,
					TILE_SIZE);
				mVMonster[type].push_back(tempImg);
			}
		}

		for (int dir = 0; dir < eGameDirection::GD_END; dir++) {
			for (int i = 0; i < 4; i++) {
				ImageGp* tempImg = new ImageGp;
				tempImg->initCenter(getMemDc(),
					mBaseSprite->getPartBitmap(
						mMonsterX[type] + (mMonsterWidth[type] * i),
						mMonsterY[type] + (mMonsterHeight[type] * directionRank[dir]),
						TILE_SIZE * 0.8,
						TILE_SIZE,
						mMonsterWidth[type],
						mMonsterHeight[type]),
					TILE_SIZE,
					TILE_SIZE);
				if(i % 2 == 0) tempImg->setSizeRatio(1.2f);
				mVMonster[type].push_back(tempImg);
			}
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
