#include "Stdafx.h"
#include "WeaponSprite.h"

HRESULT WeaponSprite::init(void)
{
	mBaseSprite = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->WeaponSprite);

	mWeaponIndexX[eWeaponType::WT_NORMAL] = 0;
	mWeaponIndexY[eWeaponType::WT_NORMAL] = 0;

	for (int i = eWeaponType::WT_NORMAL; i < eWeaponType::WT_END; i++) {
		ImageGp* tempImageGp = new ImageGp;
		tempImageGp->init(getMemDc(),
			mBaseSprite->getFrameBitmap(
				mWeaponIndexX[i],
				mWeaponIndexY[i],
				INVENTORY_BOX_WIDTH,
				INVENTORY_BOX_HEIGHT),
			INVENTORY_BOX_WIDTH,
			INVENTORY_BOX_HEIGHT);
		mVOriginalImgTool[i] = tempImageGp;

		vector<ImageGp*> tempVImageGp;
		for (int direction = eGameDirection::GD_UP; direction <= eGameDirection::GD_DOWN; direction++) {
			if (direction == GD_LEFT || direction == GD_RIGHT) {
				for (int x = 0; x < 4; x++) {
					ImageGp* tempImageGp = new ImageGp;
					tempImageGp->init(getMemDc(),
						mBaseSprite->getFrameBitmap(
							mWeaponIndexX[i],
							mWeaponIndexY[i],
							PLAYER_HEIGHT,
							PLAYER_HEIGHT),
					PLAYER_HEIGHT, PLAYER_HEIGHT);
					tempImageGp->rotate(x * 35.0f);
					if (direction == GD_LEFT) {
						tempImageGp->flipX();
					}
					tempVImageGp.push_back(tempImageGp);
				}
			}

			if (direction == GD_UP || direction == GD_DOWN) {
				for (int x = 0; x < 4; x++) {
					ImageGp* tempImageGp = new ImageGp;
					tempImageGp->init(getMemDc(),
						mBaseSprite->getFrameBitmap(
							mWeaponIndexX[i],
							mWeaponIndexY[i],
							PLAYER_HEIGHT,
							PLAYER_HEIGHT),
						PLAYER_HEIGHT, PLAYER_HEIGHT);
					tempImageGp->rotate(x * 35.0f);
					if (direction == GD_UP) {
						tempImageGp->flipX();
					}
					tempVImageGp.push_back(tempImageGp);
				}
			}
		}

		mVWeapon[i] = tempVImageGp;
	}

	return S_OK;
}

vector<ImageGp*> WeaponSprite::getVAni(eWeaponType type)
{
	return mVWeapon[type];
}

ImageGp* WeaponSprite::getImgGp(eWeaponType type)
{
	return mVOriginalImgTool[type];
}
