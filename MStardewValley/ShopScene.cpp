#include "Stdafx.h"
#include "ShopScene.h"

#include "Map.h"
#include "GameUI.h"
#include "Item.h"

#define MENU_ITEM_WIDTH		940.0f
#define MENU_ITEM_HEIGHT	100.0f

HRESULT ShopScene::init(void)
{
	bShowingSaleList = false;

	mSeedShopMap = new ShopMap;
	mSeedShopMap->init(MAPCLASS->SHOP_SEED, eShopType::SPT_PIERRE_SHOP);

	mWeaponShopMap = new ShopMap;
	mWeaponShopMap->init(MAPCLASS->SHOP_WEAPON, eShopType::SPT_GILL_SHOP);

	mSeedSaleItemBox = new SaleItemBox();
	mSeedSaleItemBox->init("씨앗 판매 리스트", mSeedShopMap->getSaleItemIdList(), mSeedShopMap->getSaleNpcPortraitImg());

	mWeaponSaleItemBox = new SaleItemBox();
	mWeaponSaleItemBox->init("무기 판매 리스트", mWeaponShopMap->getSaleItemIdList(), mWeaponShopMap->getSaleNpcPortraitImg());

	return S_OK;
}

void ShopScene::update(void)
{
	GameScene::update();

	if (mCurShopMap->getReqSaleListUI()) {
		mCurShopMap->setReqShopListUI(false);
		UIMANAGER->activeGameUI(mCurItemList);
		bShowingSaleList = true;
	}

	if (bShowingSaleList) {
		if (KEYMANAGER->isOnceKeyDown('O')) {
			bShowingSaleList = false;
			UIMANAGER->disableGameUI(mCurItemList);
		}
	}
}

void ShopScene::pause(void)
{
	GameScene::pause();
}

HRESULT ShopScene::resume(void)
{
	const MapPortal playerPortal = PLAYER->getToPortal();

	if (playerPortal.ToMapKey == MAPCLASS->SHOP_SEED) {
		mCurShopMap = mSeedShopMap;
		mCurItemList = mSeedSaleItemBox;
	}
	else if (playerPortal.ToMapKey == MAPCLASS->SHOP_WEAPON) {
		mCurShopMap = mWeaponShopMap;
		mCurItemList = mWeaponSaleItemBox;
	};

	mMap = mCurShopMap;
	GameScene::resume();
	return S_OK;
}

void ShopScene::release(void)
{
	mSeedShopMap->release();
	mWeaponShopMap->release();

	UIMANAGER->deleteObject(mSeedShopMap);
	UIMANAGER->deleteObject(mWeaponShopMap);

	UIMANAGER->deleteUI(mSeedSaleItemBox);
	UIMANAGER->deleteUI(mWeaponSaleItemBox);
}

void ShopScene::render(void)
{
	GameScene::render();
}
