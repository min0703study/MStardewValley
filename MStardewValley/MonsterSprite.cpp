#include "Stdafx.h"
#include "MonsterSprite.h"

HRESULT MonsterSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MonsterSprite);

	mMonsterX[eMonsterType::MST_GRUB] = 735;
	mMonsterY[eMonsterType::MST_GRUB] = 12;
	mMonsterXCount[eMonsterType::MST_GRUB] = 4;
	mMonsterYCount[eMonsterType::MST_GRUB] = 4;
	mMonsterWidth[eMonsterType::MST_GRUB] = 16.0f;
	mMonsterHeight[eMonsterType::MST_GRUB] = 22.5f;

	for (int i = eMonsterType::MST_GRUB; i <= eMonsterType::MST_GRUB; i++) {
		vector<ImageGp*> tempVImageGp;
		for (int y = 0; y < mMonsterYCount[i]; y++) {
			for (int x = 0; x < mMonsterXCount[i]; x++) {
				ImageGp* idleImg = new ImageGp;
				idleImg->initCenter(getMemDc(),
					mBaseSprite->getPartBitmap(
						mMonsterX[i] + (x * mMonsterWidth[i]),
						mMonsterY[i] + (y * mMonsterHeight[i]),
						TILE_SIZE * 0.8,
						TILE_SIZE,
						mMonsterWidth[i],
						mMonsterHeight[i]),
					TILE_SIZE,
					TILE_SIZE);
				tempVImageGp.push_back(idleImg);
			}
		}

		mVMonster[i] = tempVImageGp;
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
