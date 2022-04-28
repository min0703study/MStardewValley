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

	mInfoImg = new ImageGp;
	mInfoImg->init(getMemDc(), 200.0f, 500.0f);

	mPriceInfoImg = new ImageGp;
	mPriceInfoImg->init(getMemDc(), 200.0f, 500.0f);

	ImageGp* title = GDIPLUSMANAGER->clone(IMGCLASS->ItemInfoName);
	ImageGp* content = GDIPLUSMANAGER->clone(IMGCLASS->ItemInfoContent);
	ImageGp* priceArea = GDIPLUSMANAGER->clone(IMGCLASS->ItemInfoContent);
	ImageGp* end = GDIPLUSMANAGER->clone(IMGCLASS->ItemInfoEnd);

	title->setSize(200, 100);
	content->setSize(200, 200);
	end->setSize(200, 10);
	GDIPLUSMANAGER->drawTextToBitmap(title->getBitmap(), itemName,RectFMake(20.0f, 20.0f, 500.0f, 50.0f), 45.0f, CR_BLACK, CR_NONE, XS_LEFT, FontStyleRegular, 2);
	GDIPLUSMANAGER->drawTextToBitmap(title->getBitmap(), L"档备", RectFMake(20.0f, 70.0f, 500.0f, 50.0f), 35.0f, CR_BLACK, CR_NONE, XS_LEFT, FontStyleRegular, 2);
	GDIPLUSMANAGER->drawTextToBitmap(priceArea->getBitmap(), to_wstring(price), RectFMake(20.0f, 70.0f, 500.0f, 50.0f), 35.0f, CR_BLACK, CR_NONE, XS_LEFT, FontStyleRegular, 2);
	GDIPLUSMANAGER->drawTextToBitmap(content->getBitmap(), L"档备\n档备\n档备", RectFMake(20.0f, 70.0f, 500.0f, 50.0f), 35.0f, CR_BLACK, CR_NONE, XS_LEFT, FontStyleRegular, 2);
	mInfoImg->overlayBitmap(0,0, title->getBitmap());
	mInfoImg->overlayBitmap(0,100, content->getBitmap());
	mInfoImg->overlayBitmap(0,300, end->getBitmap());

	mPriceInfoImg->overlayBitmap(0, 0, title->getBitmap());
	mPriceInfoImg->overlayBitmap(0, 100, priceArea->getBitmap());
	mPriceInfoImg->overlayBitmap(0, 300, end->getBitmap());

	mInfoImg->rebuildChachedBitmap();
	mPriceInfoImg->rebuildChachedBitmap();

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

void Item::renderInfo(float x, float y) const
{
	mInfoImg->render(getMemDc(), x + 30.0f, y + 30.0f, XS_LEFT, YS_TOP);
}

void Item::renderPriceInfo(float x, float y) const
{
	mPriceInfoImg->render(getMemDc(), x + 30.0f, y + 30.0f, XS_LEFT, YS_TOP);
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
