#include "Stdafx.h"
#include "GameScene.h"

Toolbar* GameScene::mToolbar = nullptr;
GameUI* GameScene::mClock = nullptr;
GameUI* GameScene::mEnergyProgressBar = nullptr;

HRESULT GameScene::init(void)
{
	mToolbar = new Toolbar();
	mToolbar->init("하단 툴바",  WIN_CENTER_X, WINSIZE_Y - 100, GDIPLUSMANAGER->cloneImage(IMGCLASS->Toolbar), XS_CENTER, YS_CENTER);

	UIMANAGER->addUi(mToolbar);
	UIMANAGER->addObject(PLAYER);
	
	//debug
	mToolbar->addItem(ITEMCLASS->WEAPON, PLAYER->addItem(ITEMCLASS->WEAPON));
	mToolbar->addItem(ITEMCLASS->PICK, PLAYER->addItem(ITEMCLASS->PICK));

	return S_OK;
}

void GameScene::update(void)
{
	PLAYER->update();
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		if (mToolbar->isCollisionContentBox(_ptfMouse)) {
			int index = mToolbar->changeSelectItem(mToolbar->getIndexToPtF(_ptfMouse));
			if (index != -1) {
				PLAYER->changeHoldingItem(index);
			}
		}
		else {
			PLAYER->attack();
		}
	}
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
