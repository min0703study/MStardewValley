#include "Stdafx.h"
#include "GameScene.h"

Toolbar* GameScene::mToolbar = nullptr;
GameUI* GameScene::mClock = nullptr;
GameUI* GameScene::mEnergyProgressBar = nullptr;

HRESULT GameScene::init(void)
{
	mToolbar = new Toolbar();
	mToolbar->init("하단 툴바",  WIN_CENTER_X, WINSIZE_Y - 100, GDIPLUSMANAGER->cloneImage(IMGCLASS->Toolbar), XS_CENTER, YS_CENTER);
	mToolbar->setClickDownEvent([this](GameUI* ui) {
		int index = mToolbar->changeSelectItem(mToolbar->getIndexToPtF(_ptfMouse));
		if (index != -1) {
			PLAYER->changeHoldingItem(index);
		}
	});

	UIMANAGER->addUi(mToolbar);
	UIMANAGER->addObject(PLAYER);
	
	//debug
	mToolbar->addItem(ITEMCLASS->WEAPON, PLAYER->addItem(ITEMCLASS->WEAPON));
	mToolbar->addItem(ITEMCLASS->PICK, PLAYER->addItem(ITEMCLASS->PICK));
	mToolbar->addItem(ITEMCLASS->HOE, PLAYER->addItem(ITEMCLASS->HOE));
	mToolbar->addItem(ITEMCLASS->PARSNIP_SEED, PLAYER->addItem(ITEMCLASS->PARSNIP_SEED));

	return S_OK;
}

void GameScene::update(void)
{
	PLAYER->update();
	UIMANAGER->update();
}

void GameScene::release(void)
{
	UIMANAGER->deleteUI(mToolbar);
	UIMANAGER->deleteObject(PLAYER);
}

void GameScene::render(void)
{
	UIMANAGER->render();
}
