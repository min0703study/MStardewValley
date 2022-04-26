#include "Stdafx.h"
#include "ShopScene.h"

#include "Map.h"
#include "GameUI.h"
#include "Item.h"

#define MENU_ITEM_WIDTH		940.0f
#define MENU_ITEM_HEIGHT	100.0f

HRESULT ShopScene::init(void)
{
	const MapPortal playerPortal = PLAYER->getToPortal();

	bShowingSaleList = false;

	mShopMap = new ShopMap;
	mShopMap->init(playerPortal.ToMapKey, playerPortal.ToPortal);

	mMap = mShopMap;
	UIMANAGER->addMap(mShopMap);

	mSaleItemBox = new SaleItemBox();
	mSaleItemBox->init("판매 리스트", mShopMap->getSaleItemIdList(), mShopMap->getSaleNpcPortraitImg());

	UIMANAGER->addUi(mSaleItemBox);
	UIMANAGER->disableGameUI(mSaleItemBox);

	return S_OK;
}

void ShopScene::update(void)
{
	GameScene::update();
	if (mShopMap->getReqSaleListUI()) {
		mShopMap->setReqShopListUI(false);
		UIMANAGER->activeGameUI(mSaleItemBox);
		bShowingSaleList = true;
	}

	if (bShowingSaleList) {
		if (KEYMANAGER->isOnceKeyDown('O')) {
			bShowingSaleList = false;
			UIMANAGER->disableGameUI(mSaleItemBox);
		}
	}
}

void ShopScene::release(void)
{
	mShopMap->release();

	UIMANAGER->deleteObject(mShopMap);
	UIMANAGER->deleteUI(mSaleItemBox);
}

void ShopScene::render(void)
{
	GameScene::render();
}
