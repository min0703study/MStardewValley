#include "Stdafx.h"
#include "Item.h"
#include "ItemAnimation.h"

HRESULT Item::init(string id, string itemId, eItemType type, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameObject::Init(id, x, y, width, height, xStandard, yStandard);

	setInventoryImg(CROPSPRITE->getIdleBitmap(CK_PARSNIP));

	mItemId = itemId;
	mItemType = type;

	return S_OK;
}

void Item::render()
{

}

void Item::render(float centerX, float bottomY, float width, float height)
{
	if (mItemType == ITP_SEED) {
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
	mInventoryImg->initCenter(getMemDc(), GDIPLUSMANAGER->bitmapSizeChangeToHeight(idleBitmap, INVENTORY_BOX_HEIGHT), INVENTORY_BOX_WIDTH, INVENTORY_BOX_HEIGHT);
}

void Item::changeStat(eItemStat changeStat)
{
	if (mItemType != ITP_SEED) {
		mAni->changeStatAni(changeStat);
	}

	mCurItemStat = changeStat;
}

void Item::changeStat(eGameDirection direction)
{
	if (mItemType != ITP_SEED) {
		switch (direction)
		{
		case eGameDirection::GD_LEFT:
			mAni->changeStatAni(eItemStat::IS_USE_LEFT);
			mCurItemStat = eItemStat::IS_USE_LEFT;
			break;
		case eGameDirection::GD_RIGHT:
			mAni->changeStatAni(eItemStat::IS_USE_RIGHT);
			mCurItemStat = eItemStat::IS_USE_RIGHT;
			break;
		case eGameDirection::GD_UP:
			mAni->changeStatAni(eItemStat::IS_USE_UP);
			mCurItemStat = eItemStat::IS_USE_UP;
			break;
		case eGameDirection::GD_DOWN:
			mAni->changeStatAni(eItemStat::IS_USE_DOWN);
			mCurItemStat = eItemStat::IS_USE_DOWN;
			break;
		default:
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////

HRESULT Weapon::init(string id, string itemId, eWeaponType weaponType, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	Item::init(id, itemId, ITP_WEAPON, x, y, width, height, xStandard, yStandard);

	mWeaponType = weaponType;
	setInventoryImg(WEAPONSPRITE->getIdleBitmap(mWeaponType));

	mAni = new ItemAnimation;
	mAni->initWeapon(mWeaponType);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT Tool::init(string id, string itemId, eToolType toolType, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	Item::init(id, itemId, ITP_TOOL, x, y, width, height, xStandard, yStandard);
	
	mToolType = toolType;
	mToolLevel = TL_GOLD;

	mAni = new ItemAnimation;
	mAni->initTool(toolType, mToolLevel);

	setInventoryImg(TOOLSPRITE->getIdleBitmap(mToolType, mToolLevel));

	return S_OK;
}
