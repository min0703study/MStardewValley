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

	mBlackSmithShopMap = new ShopMap;
	mBlackSmithShopMap->init(MAPCLASS->SHOP_BLACKSMITH, eShopType::SPT_CLINT_SHOP);

	mSeedSaleItemBox = new SaleItemBox();
	mSeedSaleItemBox->init("씨앗 판매 리스트", mSeedShopMap->getSaleItemIdList(), mSeedShopMap->getSaleNpcPortraitImg());

	mWeaponSaleItemBox = new SaleItemBox();
	mWeaponSaleItemBox->init("무기 판매 리스트", mWeaponShopMap->getSaleItemIdList(), mWeaponShopMap->getSaleNpcPortraitImg());

	mToolUpgradeItemBox = new SaleItemBox();
	mToolUpgradeItemBox->init("도구 업그레이드 리스트", mBlackSmithShopMap->getSaleItemIdList(), mBlackSmithShopMap->getSaleNpcPortraitImg());

	vector<string> saleList;
	saleList.push_back(ITEMCLASS->IRON_PICK);
	saleList.push_back(ITEMCLASS->IRON_AXE);
	saleList.push_back(ITEMCLASS->IRON_HOE);
	saleList.push_back(ITEMCLASS->FURNACE);
	saleList.push_back(ITEMCLASS->COAL);
	saleList.push_back(ITEMCLASS->STONE_NORMAL);
	saleList.push_back(ITEMCLASS->COPPER);
	saleList.push_back(ITEMCLASS->IRON);
	saleList.push_back(ITEMCLASS->GOLD);

	mToolUpgradeItemBox2 = new SaleItemBox();
	mToolUpgradeItemBox2->init("도구1 업그레이드 리스트", saleList, mBlackSmithShopMap->getSaleNpcPortraitImg());

	vector<string> saleList2;
	saleList2.push_back(ITEMCLASS->COPPER_PICK);
	saleList2.push_back(ITEMCLASS->COPPER_AXE);
	saleList2.push_back(ITEMCLASS->COPPER_HOE);
	saleList2.push_back(ITEMCLASS->FURNACE);
	saleList2.push_back(ITEMCLASS->COAL);
	saleList2.push_back(ITEMCLASS->STONE_NORMAL);
	saleList2.push_back(ITEMCLASS->COPPER);
	saleList2.push_back(ITEMCLASS->IRON);
	saleList2.push_back(ITEMCLASS->GOLD);
	mToolUpgradeItemBox3 = new SaleItemBox();
	mToolUpgradeItemBox3->init("도구1 업그레이드 리스트", saleList2, mBlackSmithShopMap->getSaleNpcPortraitImg());


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
	}
	else if (playerPortal.ToMapKey == MAPCLASS->SHOP_BLACKSMITH) {
		mCurShopMap = mBlackSmithShopMap;

		int index = -1; 
		int count = -1;
		PLAYER->getInventory()->findItem(ITEMCLASS->IRON_BAR, index, count);
		if (index != -1) {
			mCurItemList = mToolUpgradeItemBox2;
		}
		else {
			PLAYER->getInventory()->findItem(ITEMCLASS->COPPER_BAR, index, count);
			if (index != -1) {
				mCurItemList = mToolUpgradeItemBox3;
			}
			else {
				mCurItemList = mToolUpgradeItemBox;
			}
		}
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
