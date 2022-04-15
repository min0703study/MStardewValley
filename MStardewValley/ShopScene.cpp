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
	
	string itemId[4] = { ITEMCLASS->PARSNIP_SEED, ITEMCLASS->POTATO_SEED, ITEMCLASS->CAULIFLOWER_SEED,  ITEMCLASS->BEEN_SEED };

	ImageGp* imgGp = new ImageGp[4];

	for (int i = 0; i < 4; i++) {
		imgGp[i] = *GDIPLUSMANAGER->cloneImage(IMGCLASS->ShopMenuItem);
		imgGp[i].overlayBitmap(40, 40, ITEMMANAGER->findItem(itemId[i])->getInventoryImg()->getBitmap());
		imgGp[i].rebuildChachedBitmap();
		imgGp[i].setSize(1000,100);
	}

	mListBox = new ListBox;
	mListBox->init("아이템 메뉴", WIN_CENTER_X, WIN_CENTER_Y, 1000.0f, 500.0f, imgGp, 4, XS_CENTER, YS_CENTER);
	mListBox->setContentClickDownEvent([this](GameUI* ui) {
		int clickIndex = ((ListBox*)ui)->getIndexToXY(_ptfMouse.X, _ptfMouse.Y);
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
