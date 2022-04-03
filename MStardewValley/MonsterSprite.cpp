#include "Stdafx.h"
#include "MonsterSprite.h"

HRESULT MonsterSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MonsterSprite);

	mMonsterX[eMonsterType::MST_BUG_CATERFILLER] = 735;
	mMonsterY[eMonsterType::MST_BUG_CATERFILLER] = 12;
	mMonsterXCount[eMonsterType::MST_BUG_CATERFILLER] = 4;
	mMonsterYCount[eMonsterType::MST_BUG_CATERFILLER] = 4;
	mMonsterWidth[eMonsterType::MST_BUG_CATERFILLER] = 16.0f;
	mMonsterHeight[eMonsterType::MST_BUG_CATERFILLER] = 22.5f;

	for (int i = eMonsterType::MST_BUG_CATERFILLER; i <= eMonsterType::MST_BUG_CATERFILLER; i++) {
		vector<ImageGp*> tempVImageGp;
		for (int y = 0; y < mMonsterYCount[i]; y++) {
			for (int x = 0; x < mMonsterXCount[i]; x++) {
				//idle
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
