#include "Stdafx.h"
#include "Item.h"
#include "ItemAnimation.h"

HRESULT Item::init(string itemId, eItemType type, wstring itemName, int price)
{
	TileObject::init(1,1,0,0);

	mItemId = itemId;
	mItemName = itemName;
	mItemType = type;

	mPrice = price;

	return S_OK;
}

void Item::render(float startX, float startY) const
{
	mInventoryImg->render(startX, startY);
}

void Item::render(eItemStat itemStat, float playerCenterX, float playerCenterY, float playerHalfHeight) const
{
	mInventoryImg->render(getMemDc(), playerCenterX, playerCenterY - playerHalfHeight, XS_CENTER, YS_CENTER);
}

void Item::renderIdle(float x, float y) const
{
	mInventoryImg->render(getMemDc(), x, y, XS_LEFT, YS_TOP);
}

void Item::update(void) const
{
}

void Item::setInventoryImg(Bitmap* idleBitmap)
{
	mInventoryImg = new ImageGp;
	if (mItemId == ITEMCLASS->WATERING_CAN) {
		mInventoryImg->initCenter(getMemDc(), GDIPLUSMANAGER->bitmapSizeChangeToWidth(idleBitmap, INVENTORY_BOX_WIDTH * 0.9), INVENTORY_BOX_WIDTH, INVENTORY_BOX_WIDTH);
	}
	else {
		mInventoryImg->initCenter(getMemDc(), GDIPLUSMANAGER->bitmapSizeChangeToHeight(idleBitmap, INVENTORY_BOX_WIDTH * 0.9), INVENTORY_BOX_WIDTH, INVENTORY_BOX_WIDTH);
	}
}

void Item::playUsingAni() const
{
}

/////////////////////////////////////////////////////////////////////////////////////
HRESULT Weapon::init(string itemId, eWeaponType weaponType, wstring itemName, int minDamage, int maxDamage ,int price)
{
	Item::init(itemId, ITP_WEAPON, itemName, price);

	mWeaponType = weaponType;
	setInventoryImg(WEAPONSPRITE->getIdleBitmap(mWeaponType));

	mAni = new ItemAnimation;
	mAni->initWeapon(mWeaponType);

	mMInDamage = minDamage;
	mMaxDamage = maxDamage;

	return S_OK;
}
void Weapon::update() const
{
	Item::update();
	if (mAni->isPlaying()) {
		mAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	}
}
void Weapon::playUsingAni() const
{
	mAni->playAniOneTime();
}
void Weapon::render(eItemStat itemStat, float playerCenterX, float playerCenterY, float playerHalfHeight) const
{
	if (itemStat == eItemStat::IS_USE) {
		if (mAni->isPlaying()) {
			mAni->render(getMemDc(), playerCenterX, playerCenterY);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////
HRESULT Tool::init(string itemId, eToolType toolType, wstring itemName, int price)
{
	Item::init(itemId, ITP_TOOL, itemName, price);

	mToolType = toolType;
	mToolLevel = TL_NORMAL;

	mAni = new ItemAnimation;
	mAni->initTool(toolType, mToolLevel);

	setInventoryImg(TOOLSPRITE->getIdleBitmap(mToolType, mToolLevel));

	return S_OK;
}
void Tool::playUsingAni() const
{
	mAni->playAniOneTime();
}

void Tool::update() const
{
	if (mAni->isPlaying()) {
		mAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	}
}

void Tool::render(eItemStat itemStat, float playerCenterX, float playerCenterY, float playerHalfHeight) const
{
	if (itemStat == eItemStat::IS_USE) {
		if (mAni->isPlaying()) {
			if (mToolType == eToolType::TT_WATERING_CAN) {
				switch (PLAYER->getDirection()) {
					case GD_RIGHT:
						mAni->render(getMemDc(), playerCenterX + 45.0f, playerCenterY);
						break;
					case GD_LEFT:
						mAni->render(getMemDc(), playerCenterX - 45.0f, playerCenterY);
						break;
					case GD_DOWN: case GD_UP:
						mAni->render(getMemDc(), playerCenterX, playerCenterY + 25.0f);
						break;
				}
			}
			else {
				mAni->render(getMemDc(), playerCenterX, playerCenterY);
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////
HRESULT Seed::init(string itemId, eCropType cropType, wstring itemName, int price)
{
	Item::init(itemId, ITP_SEED,itemName, price);

	mCropType = cropType;
	setInventoryImg(CROPSPRITE->getIdleSeedBitmap (cropType));
	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////////////
HRESULT Fruit::init(string itemId, eCropType cropType, wstring itemName, int price, int eneregy)
{
	Item::init(itemId, ITP_FRUIT,itemName, price);

	mCropType = cropType;
	setInventoryImg(CROPSPRITE->getIdleBitmap(cropType));
	mEnergy = eneregy;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////////////
HRESULT Stone::init(string itemId, eStoneType stoneType, wstring itemName, int price)
{
	Item::init(itemId, ITP_STONE, itemName, price);

	mStoneType = stoneType;
	setInventoryImg(MINESSPRITE->getStoneImg(stoneType)->getBitmap());
	return S_OK;
}

HRESULT Forage::init(string itemId, eForageType forageType, wstring itemName, int price)
{
	Item::init(itemId, ITP_FORAGE, itemName, price);

	mForagetype = forageType;
	setInventoryImg(FORAGESPRITE->getIdleBitmap(forageType));
	return S_OK;
}
