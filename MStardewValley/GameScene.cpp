#include "Stdafx.h"
#include "GameScene.h"

Toolbar* GameScene::mToolbar = nullptr;
GameUI* GameScene::mClock = nullptr;
GameUI* GameScene::mEnergyProgressBar = nullptr;

HRESULT GameScene::init(void)
{
	mToolbar = new Toolbar();
	mToolbar->init("하단 툴바",  WIN_CENTER_X, WINSIZE_Y - 100, TOOLBAR_WIDTH, TOOLBAR_HEIGHT,GDIPLUSMANAGER->cloneImage(IMGCLASS->Toolbar), XS_CENTER, YS_CENTER);
	mToolbar->setClickDownEvent([this](GameUI* ui) {
		int index = mToolbar->changeSelectItem(mToolbar->getIndexToPtF(_ptfMouse));
		if (index != -1) {
			PLAYER->changeHoldingItem(index);
		}
	});

	UIMANAGER->addUi(mToolbar);
	UIMANAGER->addObject(PLAYER);
	
	//debug
	PLAYER->addItem(ITEMCLASS->HOE);
	PLAYER->addItem(ITEMCLASS->WATERING_CAN);
	PLAYER->addItem(ITEMCLASS->PICK);
	PLAYER->addItem(ITEMCLASS->HOE);

	return S_OK;
}

void GameScene::update(void)
{
	UIMANAGER->update();
	PLAYER->update();
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
