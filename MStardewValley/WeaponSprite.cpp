#include "Stdafx.h"
#include "WeaponSprite.h"

#define WEAPON_FRAME_COUNT	6

HRESULT WeaponSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->clone(IMGCLASS->WeaponSprite);

	//스프라이트 정보 INIT
	mVSpriteInfo[eItemStat::IS_GRAP].StartIndex = 0;
	mVSpriteInfo[eItemStat::IS_GRAP].EndIndex = 0;
	mVSpriteInfo[eItemStat::IS_GRAP].IsNone = true;

	mVSpriteInfo[eItemStat::IS_USE_UP].StartIndex = 0;
	mVSpriteInfo[eItemStat::IS_USE_UP].EndIndex = 3;
	mVSpriteInfo[eItemStat::IS_USE_UP].IsNone = false;

	mVSpriteInfo[eItemStat::IS_USE_DOWN].StartIndex = 4;
	mVSpriteInfo[eItemStat::IS_USE_DOWN].EndIndex = 7;
	mVSpriteInfo[eItemStat::IS_USE_DOWN].IsNone = false;

	mVSpriteInfo[eItemStat::IS_USE_LEFT].StartIndex = 8;
	mVSpriteInfo[eItemStat::IS_USE_LEFT].EndIndex = 11;
	mVSpriteInfo[eItemStat::IS_USE_LEFT].IsNone = false;

	mVSpriteInfo[eItemStat::IS_USE_RIGHT].StartIndex = 12;
	mVSpriteInfo[eItemStat::IS_USE_RIGHT].EndIndex = 15;
	mVSpriteInfo[eItemStat::IS_USE_RIGHT].IsNone = false;

	//무기 실제 index 위치 설정
	mWeaponIndexX[eWeaponType::WT_NORMAL] = 0;
	mWeaponIndexY[eWeaponType::WT_NORMAL] = 0;

	mWeaponIndexX[eWeaponType::WT_WOODEN_BLADE] = 4;
	mWeaponIndexY[eWeaponType::WT_WOODEN_BLADE] = 1;

	mWeaponIndexX[eWeaponType::WT_IRON_DIRCT] = 2;
	mWeaponIndexY[eWeaponType::WT_IRON_DIRCT] = 1;

	mWeaponIndexX[eWeaponType::WT_PIRATES_SWORD] = 3;
	mWeaponIndexY[eWeaponType::WT_PIRATES_SWORD] = 5;

	mWeaponIndexX[eWeaponType::WT_WOOD_MALLET] = 3;
	mWeaponIndexY[eWeaponType::WT_WOOD_MALLET] = 3;

	mWeaponIndexX[eWeaponType::WT_BONE_SWORD] = 0;
	mWeaponIndexY[eWeaponType::WT_BONE_SWORD] = 5;

	mWeaponIndexX[eWeaponType::WT_INSECT_HEAD] = 1;
	mWeaponIndexY[eWeaponType::WT_INSECT_HEAD] = 5;

	//이미지 생성
	int directionInt = 0;
	for (int i = eWeaponType::WT_NORMAL; i < eWeaponType::WT_END; i++) {
		for (int direction = eGameDirection::GD_UP; direction <= eGameDirection::GD_DOWN; direction++) {
			for (int x = 0; x < WEAPON_FRAME_COUNT; x++) {
				ImageGp* tempImageGp = new ImageGp;
				tempImageGp->initCenter(getMemDc(),
					mBaseSprite->getFrameBitmap(
						mWeaponIndexX[i],
						mWeaponIndexY[i],
						WEAPON_IMG_SIZE_HEIGHT,
						WEAPON_IMG_SIZE_HEIGHT), 
					PLAYER_HEIGHT, PLAYER_HEIGHT);
				tempImageGp->rotateSample(x * 30.0f - 45.0f);

				switch (direction)
				{
				case eGameDirection::GD_UP:
					tempImageGp->flip90(3);
					break;
				case eGameDirection::GD_LEFT:
					tempImageGp->flipX();
					break;
				case eGameDirection::GD_DOWN:
					tempImageGp->flip90(3);
					tempImageGp->flipY();
					break;
				default:
					//tempImageGp->flip90(1);
					break;
				}

				mVWeapon[i].push_back(tempImageGp);
			}
			directionInt++;
		}

		mIdleBitmapList[i] = mBaseSprite->getFrameBitmap(
			mWeaponIndexX[i],
			mWeaponIndexY[i]);
	}

	return S_OK;
}

vector<ImageGp*> WeaponSprite::getVAni(eWeaponType type)
{
	return mVWeapon[type];
}

Bitmap * WeaponSprite::getIdleBitmap(eWeaponType type)
{
	return mIdleBitmapList[type];
}