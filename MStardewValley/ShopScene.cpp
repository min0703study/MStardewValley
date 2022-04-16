#include "Stdafx.h"
#include "ShopScene.h"

#include "Map.h"
#include "GameUI.h"
#include "Item.h"

HRESULT ShopScene::init(void)
{
	mShopMap = new ShopMap;
	mShopMap->init();

	mMap = mShopMap;

	UIMANAGER->addMap(mShopMap);

	PLAYER->setCurMapKey(PLAYER->getToLoaction());
	PLAYER->setToMapKey("");

	PLAYER->changePos(10 * TILE_SIZE, 10 * TILE_SIZE, XS_CENTER, YS_CENTER);

	ImageGp** imgGp = new ImageGp*[4];
	string itemId[4] = { ITEMCLASS->PARSNIP_SEED, ITEMCLASS->POTATO_SEED, ITEMCLASS->CAULIFLOWER_SEED,  ITEMCLASS->BEEN_SEED };
	vector<ImageGp*> vSaleItemImg;

	for (int i = 0; i < 4; i++) {
		const Item* saleItem = ITEMMANAGER->findItemReadOnly(itemId[i]);
		ImageGp* saleItemImg = new ImageGp;
		saleItemImg = GDIPLUSMANAGER->cloneImage(IMGCLASS->ShopMenuItem);
		saleItemImg->setSize(940.0f, 100.0f);
		saleItemImg->overlayBitmap(20.0f, 20.0f, saleItem->getInventoryImg()->getBitmap());
		GDIPLUSMANAGER->drawTextToBitmap(saleItemImg->getBitmap(), saleItem->getItemName(), 75,30, 55, Color(86,22,12), 2);
		GDIPLUSMANAGER->drawTextToBitmap(saleItemImg->getBitmap(), to_wstring(saleItem->getPrice()), 940.0f - 100,30, 55, Color(86, 22, 12), 2);
		saleItemImg->rebuildChachedBitmap();

		mVSaleItem.push_back(saleItem);
		vSaleItemImg.push_back(saleItemImg);
		
	}

	mListBox = new ListBox;
	mListBox->init("아이템 메뉴", WIN_CENTER_X, WIN_CENTER_Y, 1000.0f, 500.0f, vSaleItemImg, XS_CENTER, YS_CENTER);
	mListBox->setContentClickDownEvent([this](GameUI* ui) {
		int clickIndex = ((ListBox*)ui)->getIndexToXY(_ptfMouse.X, _ptfMouse.Y);
		PLAYER->addItem(mVSaleItem[clickIndex]->getItemId());
	});

	UIMANAGER->addUi(mListBox);
	return S_OK;
}

void ShopScene::update(void)
{
	GameScene::update();
	mMap->update();
}

void ShopScene::release(void)
{
}

void ShopScene::render(void)
{
	GameScene::render();
}
