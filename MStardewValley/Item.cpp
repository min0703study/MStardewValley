#include "Stdafx.h"
#include "Item.h"

HRESULT Item::init(string id, string itemId, eItemType type, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameObject::Init(id, x, y, width, height, xStandard, yStandard);

	mItemId = itemId;
	mItemType = type;

	return S_OK;
}

void Item::render()
{

}

void Item::render(float x, float y, eXStandard xStandard, eYStandard yStandard)
{
	mAni->render(getMemDc(), x, y);
}

void Item::update(void)
{
	mAni->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void Item::changeStat(eItemStat changeStat)
{
	mAni->changeStatAni(changeStat);
	mCurItemStat = changeStat;
}

void Item::changeStat(eGameDirection direction)
{
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


HRESULT Weapon::init(string id, string itemId, eWeaponType weaponType, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	Item::init(id, itemId, ITP_WEAPON, x, y, width, height, xStandard, yStandard);

	mWeaponType = weaponType;
	mInventoryImg = WEAPONSPRITE->getInventoryImg(mWeaponType, INVENTORY_BOX_WIDTH, INVENTORY_BOX_HEIGHT);

	mAni = new ItemAnimation;
	mAni->initWeapon(mWeaponType);

	return S_OK;
}

HRESULT Tool::init(string id, string itemId, eToolType toolType, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	Item::init(id, itemId, ITP_TOOL, x, y, width, height, xStandard, yStandard);
	
	mToolType = toolType;
	mToolLevel = TL_GOLD;

	mAni = new ItemAnimation;
	mAni->initTool(toolType, mToolLevel);

	mInventoryImg = TOOLSPRITE->getImgGp(mToolType, mToolLevel);

	return S_OK;
}
