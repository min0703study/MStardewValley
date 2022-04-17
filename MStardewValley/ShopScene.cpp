#include "Stdafx.h"
#include "ShopScene.h"

#include "Map.h"
#include "GameUI.h"
#include "Item.h"

#define MENU_ITEM_WIDTH 940.0f
#define MENU_ITEM_HEIGHT 100.0f

HRESULT ShopScene::init(void)
{
	mShopMap = new ShopMap;
	mShopMap->init();

	mMap = mShopMap;

	UIMANAGER->addMap(mShopMap);

	PLAYER->setCurMapKey(PLAYER->getToLoaction());
	PLAYER->setToMapKey("");

	PLAYER->changePos(10 * TILE_SIZE, 10 * TILE_SIZE, XS_CENTER, YS_CENTER);

	mVSaleItem.push_back(ITEMMANAGER->findItemReadOnly(ITEMCLASS->PARSNIP_SEED));
	mVSaleItem.push_back(ITEMMANAGER->findItemReadOnly(ITEMCLASS->POTATO_SEED));
	mVSaleItem.push_back(ITEMMANAGER->findItemReadOnly(ITEMCLASS->CAULIFLOWER_SEED));
	mVSaleItem.push_back(ITEMMANAGER->findItemReadOnly(ITEMCLASS->BEEN_SEED));

	RectF itemRcF = RectFMake(0.0f, 0.0f, 940.0f, 100.0f);

	for (auto iter = mVSaleItem.begin(); iter != mVSaleItem.end(); iter++) {		
		ImageGp* saleItemImg = new ImageGp;
		RectF contentArea = RectFMake(itemRcF.GetLeft() + 50.0f, itemRcF.GetTop() + 30.0f, itemRcF.Width - (50.0f * 2.0f), itemRcF.Height - (30.0f * 2.0f));

		saleItemImg = GDIPLUSMANAGER->clone(IMGCLASS->ShopMenuItem);
		saleItemImg->setSize(itemRcF.Width, itemRcF.Height);
		saleItemImg->overlayBitmap(contentArea.GetLeft() - 30.0f, contentArea.GetTop() - 15.0f, (*iter)->getInventoryImg()->getBitmap());

		GDIPLUSMANAGER->drawTextToBitmap(
			saleItemImg->getBitmap(), 
			to_wstring((*iter)->getPrice()),
			contentArea,
			40.0f,
			Color(86,22,12), 
			Color(0, 0, 0, 0), 
			XS_RIGHT,
			FontStyle::FontStyleBold, 
			2);

		contentArea.Offset(40.0f, 0.0f);
		GDIPLUSMANAGER->drawTextToBitmap(
			saleItemImg->getBitmap(),
			(*iter)->getItemName(),
			contentArea,
			40.0f,
			Color(86, 22, 12),
			Color(0, 0, 0, 0),
			XS_LEFT,
			FontStyle::FontStyleBold,
			2);

		saleItemImg->rebuildChachedBitmap();
		vSaleItemImg.push_back(saleItemImg);
	}

	mListBox = new ListBox;
	mListBox->init("아이템 메뉴", WIN_CENTER_X, WIN_CENTER_Y, 1000.0f, 500.0f, vSaleItemImg, XS_CENTER, YS_CENTER);
	mListBox->setContentClickDownEvent([this](GameUI* ui) {
		int clickIndex = ((ListBox*)ui)->getIndexToXY(_ptfMouse.X, _ptfMouse.Y);
		int price = mVSaleItem[clickIndex]->getPrice();

		if (price < PLAYER->getMoeny()) {
			PLAYER->saleItem(mVSaleItem[clickIndex]->getItemId(), 1);
		}
	});
	mListBox->setActiveStat(false);
	
	UIMANAGER->addUi(mListBox);

	return S_OK;
}

void ShopScene::update(void)
{
	GameScene::update();
	mMap->update();
	if (mShopMap->isOpenUi()) {
		if (!mListBox->isActive()) {
			mListBox->setActiveStat(true);
		}
	};

	if (KEYMANAGER->isOnceKeyDown('Y')) {
		if (mListBox->isActive()) {
			mListBox->setActiveStat(false);
			mShopMap->openUI = false;
		}
	};

}

void ShopScene::release(void)
{
}

void ShopScene::render(void)
{
	GameScene::render();
	NPCSPRITE->getPortraits(eNpcs::NPC_PIERRE)[0]->render(0, 0);
}
