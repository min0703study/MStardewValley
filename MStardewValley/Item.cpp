#include "Stdafx.h"
#include "Item.h"
#include "ItemAnimation.h"

HRESULT Item::init(string itemId, eItemType type, wstring itemName, int price, wstring description, int xCount, int yCount)
{
	TileObject::init(1, 1, xCount, yCount);

	mItemId = itemId;
	mItemName = itemName;
	mItemType = type;

	switch (mItemType) {
	case eItemType::ITP_TOOL:
		mItemTypeText = L"도구";
		break;
	case eItemType::ITP_WEAPON:
		mItemTypeText = L"무기";
		break;
	case eItemType::ITP_SEED:
		mItemTypeText = L"씨앗";
		break;
	case eItemType::ITP_FRUIT:
		mItemTypeText = L"과일";
		break;
	case eItemType::ITP_ORE:
		mItemTypeText = L"자원";
		break;
	}

	mPrice = price;
	mDescription = description;

	return S_OK;
}

void Item::render(float startX, float startY) const
{
	mInventoryImg->render(startX, startY);
}

void Item::renderHold(eItemState itemStat, float playerCenterX, float playerBottom, float playerAniHeight) const
{
	mHoldingImg->render(playerCenterX, playerBottom - playerAniHeight + 10.0f, XS_CENTER, YS_BOTTOM);
}

void Item::renderIdle(float x, float y) const
{
	mInventoryImg->render(x, y, XS_LEFT, YS_TOP);
}

void Item::renderInfo(float x, float y) const
{
	mInfoImg->render(x + 30.0f, y + 30.0f, XS_LEFT, YS_TOP);
}

void Item::renderPriceInfo(float x, float y) const
{
	mPriceInfoImg->render(x + 30.0f, y + 30.0f, XS_LEFT, YS_TOP);
}

void Item::update(void) const
{
}

void Item::setInfoImg()
{
	float infoWidth = 200.0f;
	float titleHeight = 100.0f;
	float oneLineHeight = 50.0f;
	float contentHeight = (mDescription.size() / 5) * oneLineHeight;
	float addDescriptionHeight = 0.0f;
	float endBoxHeight = 10.0f;

	if (mItemType == eItemType::ITP_WEAPON && mItemId != ITEMCLASS->SICKLE) {
		addDescriptionHeight = oneLineHeight;
	}
	else if (mItemType == eItemType::ITP_FRUIT) {
		addDescriptionHeight = oneLineHeight * 2.0f;
	}

	mInfoImg = new ImageGp;
	mInfoImg->init(getMemDc(), infoWidth, titleHeight + contentHeight + addDescriptionHeight + endBoxHeight);

	mPriceInfoImg = new ImageGp;
	mPriceInfoImg->init(getMemDc(), infoWidth, titleHeight + oneLineHeight);

	ImageGp* topTitle = GDIPLUSMANAGER->clone(IMGCLASS->ItemInfoName);
	ImageGp* description = GDIPLUSMANAGER->clone(IMGCLASS->ItemInfoContent);
	ImageGp* priceArea = GDIPLUSMANAGER->clone(IMGCLASS->ItemInfoContent);
	ImageGp* endBox = GDIPLUSMANAGER->clone(IMGCLASS->ItemInfoEnd);

	topTitle->setSize(infoWidth, titleHeight);
	description->setSize(infoWidth, contentHeight);
	priceArea->setSize(infoWidth, oneLineHeight);
	endBox->setSize(infoWidth, endBoxHeight);

	//title
	RectF titleArea = topTitle->getRectF(0, 0);
	titleArea.Inflate(-10, -10);
	GDIPLUSMANAGER->drawTextToBitmap(topTitle->getBitmap(), mItemName, titleArea, 40.0f, CR_BLACK, CR_NONE, XS_LEFT, FontStyleBold, 2);
	titleArea.Offset(0, 50.0f);
	GDIPLUSMANAGER->drawTextToBitmap(topTitle->getBitmap(), mItemTypeText, titleArea, 35.0f, CR_GREEN, CR_NONE, XS_LEFT, FontStyleRegular, 2);
	mInfoImg->overlayImageGp(topTitle, XS_LEFT, YS_TOP, false);

	//description
	RectF descriptionArea = description->getRectF(0, 0);
	descriptionArea.Inflate(-15, -10);
	GDIPLUSMANAGER->drawTextToBitmap(description->getBitmap(), mDescription, descriptionArea, 35.0f, CR_BLACK, CR_NONE, XS_LEFT, FontStyleRegular, 2);
	mInfoImg->overlayImageGp(description, 0, titleHeight, false);

	if (mItemType == eItemType::ITP_WEAPON&& mItemId != ITEMCLASS->SICKLE) {
		ImageGp* addDescription = GDIPLUSMANAGER->clone(IMGCLASS->ItemInfoContent);
		addDescription->setSize(infoWidth, addDescriptionHeight);
		addDescription->overlayImageGp(GDIPLUSMANAGER->findOriginalImage(IMGCLASS->WeaponIcon), 15.0f, 10.0f);
		GDIPLUSMANAGER->drawTextToBitmap(addDescription->getBitmap(), 
			to_string(((Weapon*)this)->getMinDamage()) + " - " + to_string(((Weapon*)this)->getMaxDamage()), 
			addDescription->getRectF(60,10),
			30.0f, CR_BLACK, CR_NONE, XS_LEFT, FontStyleRegular, 2);
		mInfoImg->overlayImageGp(addDescription, 0, titleHeight + contentHeight, false);
		addDescription->release();
		SAFE_DELETE(addDescription);
	}
	else if (mItemType == eItemType::ITP_FRUIT) {
		ImageGp* addDescription = GDIPLUSMANAGER->clone(IMGCLASS->ItemInfoContent);
		addDescription->setSize(infoWidth, addDescriptionHeight);
		addDescription->overlayImageGp(GDIPLUSMANAGER->findOriginalImage(IMGCLASS->HpIcon), 15.0f, 10.0f);
		GDIPLUSMANAGER->drawTextToBitmap(addDescription->getBitmap(),
			L"기력 + " + to_wstring(((Fruit*)this)->getEnergy()),
			addDescription->getRectF(60, 10),
			30.0f, CR_BLACK, CR_NONE, XS_LEFT, FontStyleRegular, 2);
		addDescription->overlayImageGp(GDIPLUSMANAGER->findOriginalImage(IMGCLASS->EnergyIcon), 15.0f, 60.0f);
		GDIPLUSMANAGER->drawTextToBitmap(addDescription->getBitmap(),
			L"체력 + " + to_wstring(((Fruit*)this)->getHp()),
			addDescription->getRectF(60, 60),
			30.0f, CR_BLACK, CR_NONE, XS_LEFT, FontStyleRegular, 2);

		mInfoImg->overlayImageGp(addDescription, 0, titleHeight + contentHeight, false);
		addDescription->release();
		SAFE_DELETE(addDescription);
	}


	//end
	mInfoImg->overlayImageGp(endBox, XS_LEFT, YS_BOTTOM, false);

	topTitle->release();
	SAFE_DELETE(topTitle);

	description->release();
	SAFE_DELETE(description);

	priceArea->release();
	SAFE_DELETE(priceArea);

	endBox->release();
	SAFE_DELETE(endBox);
}

void Item::setInventoryImg(Bitmap* idleBitmap)
{
	mInventoryImg = new ImageGp;

	mHoldingImg = new ImageGp;
	mHoldingImg->init(getMemDc(), idleBitmap);

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
HRESULT Weapon::init(string itemId, eWeaponType weaponType, wstring itemName, int minDamage, int maxDamage, int price, wstring description)
{
	Item::init(itemId, ITP_WEAPON, itemName, price, description);

	mWeaponType = weaponType;

	mAni = new ItemAnimation;
	mAni->initWeapon(mWeaponType);

	mMInDamage = minDamage;
	mMaxDamage = maxDamage;

	setInventoryImg(WEAPONSPRITE->getIdleBitmap(mWeaponType));
	setInfoImg();

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
void Weapon::renderHold(eItemState itemStat, float playerCenterX, float playerBottom, float playerHalfHeight) const
{
	if (itemStat == eItemState::IS_USE) {
		if (mAni->isPlaying()) {
			mAni->render(getMemDc(), playerCenterX, playerBottom - PLAYER_HEIGHT * 0.5f);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////
HRESULT Tool::init(string itemId, eToolType toolType, eToolLevel toolLevel, wstring itemName, int price, wstring description)
{
	Item::init(itemId, ITP_TOOL, itemName, price, description);

	mToolType = toolType;
	mToolLevel = toolLevel;

	mAni = new ItemAnimation;
	mAni->initTool(toolType, mToolLevel);

	setInventoryImg(TOOLSPRITE->getIdleBitmap(mToolType, mToolLevel));
	setInfoImg();
	
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
void Tool::renderHold(eItemState itemStat, float playerCenterX, float playerBottom, float playerHalfHeight) const
{
	if (itemStat == eItemState::IS_USE) {
		if (mAni->isPlaying()) {
			if (mToolType == eToolType::TT_WATERING_CAN) {
				switch (PLAYER->getDirection()) {
				case GD_RIGHT:
					mAni->render(getMemDc(), playerCenterX + 45.0f, playerBottom - PLAYER_HEIGHT * 0.5f);
					break;
				case GD_LEFT:
					mAni->render(getMemDc(), playerCenterX - 45.0f, playerBottom - PLAYER_HEIGHT * 0.5f);
					break;
				case GD_DOWN: case GD_UP:
					mAni->render(getMemDc(), playerCenterX, (playerBottom - PLAYER_HEIGHT * 0.5f) + 25.0f);
					break;
				}
			}
			else {
				mAni->render(getMemDc(), playerCenterX, playerBottom - PLAYER_HEIGHT * 0.5f);
			}
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////
HRESULT Seed::init(string itemId, eCropType cropType, wstring itemName, int price, wstring description)
{
	Item::init(itemId, ITP_SEED, itemName, price, description);

	mCropType = cropType;

	setInventoryImg(CROPSPRITE->getIdleSeedBitmap(cropType));
	setInfoImg();

	return S_OK;
}
////////////////////////////////////////////////////////////////////////////////////////
HRESULT Fruit::init(string itemId, eCropType cropType, wstring itemName, int price, int eneregy, int hp ,wstring description)
{
	Item::init(itemId, ITP_FRUIT, itemName, price, description);

	mCropType = cropType;
	mEnergy = eneregy;
	mHp = hp;
	
	setInventoryImg(CROPSPRITE->getIdleBitmap(cropType));
	setInfoImg();
	
	return S_OK;
}
/////////////////////////////////////////////////////////////////////////////////////////
HRESULT Ore::init(string itemId, eOreType oreType, wstring itemName, int price, wstring description)
{
	Item::init(itemId, ITP_ORE, itemName, price, description);

	mOreType = oreType;

	setInventoryImg(MINESSPRITE->getStoneImg(oreType)->getBitmap());
	setInfoImg();
	return S_OK;
}
/////////////////////////////////////////////////////////////////////////////////////
HRESULT OreBar::init(string itemId, eOreType mOreType, wstring itemName, int price, wstring description)
{
	Item::init(itemId, ITP_ORE_BAR, itemName, 0, description);
	
	setInventoryImg(MINESSPRITE->getOreBarIdle(mOreType));
	setInfoImg();

	return S_OK;
}
/////////////////////////////////////////////////////////////////////////////////////
HRESULT Forage::init(string itemId, eForageType forageType, wstring itemName, int price, wstring description)
{
	Item::init(itemId, ITP_FORAGE, itemName, price, description);

	mForagetype = forageType;
	
	setInventoryImg(FORAGESPRITE->getIdleBitmap(forageType));
	setInfoImg();
	
	return S_OK;
}
/////////////////////////////////////////////////////////////////////////////////////
HRESULT Craftable::init(string itemId, eCraftablesType type, wstring itemName, wstring description)
{
	Item::init(itemId, ITP_CRAFTING, itemName, 0, description);

	mCraftablesType = type;
	
	setInventoryImg(CRAFTABLESSPRITE->getIdleBitmap(type));
	setInfoImg();
	
	return S_OK;
}
void Craftable::addIngredient(string itemId, int amount)
{
	mVIngredient.push_back(Ingredient(itemId, amount));
	setInfoImg();
}
