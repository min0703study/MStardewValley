#include "Stdafx.h"
#include "Item.h"
#include "ItemAnimation.h"

HRESULT Item::init(string itemId, eItemType type, string itemName, int price)
{
	TileObject::init(1,1,0,0);

	mItemId = itemId;
	mItemName = itemName;
	mItemType = type;
	mPrice = price;

	return S_OK;
}

void Item::render()
{

}

void Item::render(float centerX, float bottomY, float width, float height) const
{
	if (mItemType != ITP_TOOL && mItemType != ITP_WEAPON) {
		mInventoryImg->render(getMemDc(), centerX, bottomY - height + 20.0f, XS_CENTER, YS_BOTTOM);
	}
	else {
		mAni->render(getMemDc(), centerX, bottomY - height / 2.0f, XS_CENTER, YS_CENTER);
	}
}

void Item::update(void)
{
	if (mItemType != ITP_SEED) {
		mAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	}
;
}

void Item::setInventoryImg(Bitmap* idleBitmap)
{
	mInventoryImg = new ImageGp;
	if (mItemId == ITEMCLASS->WATERING_CAN) {
		mInventoryImg->initCenter(getMemDc(), GDIPLUSMANAGER->bitmapSizeChangeToWidth(idleBitmap, INVENTORY_BOX_SIZE * 0.9), INVENTORY_BOX_SIZE, INVENTORY_BOX_SIZE);
	}
	else {
		mInventoryImg->initCenter(getMemDc(), GDIPLUSMANAGER->bitmapSizeChangeToHeight(idleBitmap, INVENTORY_BOX_SIZE * 0.9), INVENTORY_BOX_SIZE, INVENTORY_BOX_SIZE);
	}

}

void Item::changeStat(eItemStat changeStat) const
{
	if (mItemType != ITP_SEED) {
		mAni->changeStatAni(changeStat);
	}
}

void Item::changeStat(eGameDirection direction) const
{
	if (mItemType != ITP_SEED) {
		switch (direction)
		{
		case eGameDirection::GD_LEFT:
			mAni->changeStatAni(eItemStat::IS_USE_LEFT);
			break;
		case eGameDirection::GD_RIGHT:
			mAni->changeStatAni(eItemStat::IS_USE_RIGHT);
			break;
		case eGameDirection::GD_UP:
			mAni->changeStatAni(eItemStat::IS_USE_UP);
			break;
		case eGameDirection::GD_DOWN:
			mAni->changeStatAni(eItemStat::IS_USE_DOWN);
			break;
		default:
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////
HRESULT Weapon::init(string itemId, eWeaponType weaponType, string itemName, int minDamage, int maxDamage ,int price)
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
///////////////////////////////////////////////////////////////////////////////////////
HRESULT Tool::init(string itemId, eToolType toolType, string itemName, int price)
{
	Item::init(itemId, ITP_TOOL, itemName, price);

	mToolType = toolType;
	mToolLevel = TL_NORMAL;

	mAni = new ItemAnimation;
	mAni->initTool(toolType, mToolLevel);

	setInventoryImg(TOOLSPRITE->getIdleBitmap(mToolType, mToolLevel));

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////////////
HRESULT Seed::init(string itemId, eCropType cropType, string itemName, int price)
{
	Item::init(itemId, ITP_SEED,itemName, price);

	mCropType = cropType;
	setInventoryImg(CROPSPRITE->getIdleSeedBitmap (cropType));

	return S_OK;
}
////////////////////////////////////////////////////////////////////////////////////////
HRESULT Fruit::init(string itemId, eCropType cropType,string itemName, int price, int eneregy)
{
	Item::init(itemId, ITP_FRUIT,itemName, price);

	mCropType = cropType;
	setInventoryImg(CROPSPRITE->getIdleBitmap(cropType));
	mEnergy = eneregy;
	return S_OK;
}
