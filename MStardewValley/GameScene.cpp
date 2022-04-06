#include "Stdafx.h"
#include "GameScene.h"

Toolbar* GameScene::mToolbar = nullptr;
GameUI* GameScene::mClock = nullptr;
GameUI* GameScene::mEnergyProgressBar = nullptr;

HRESULT GameScene::init(void)
{
	PLAYER->init("플레이어", 0.0f, 0.0f, PLAYER_WIDTH, PLAYER_HEIGHT, XS_CENTER, YS_CENTER);

	mToolbar = new Toolbar();
	mToolbar->init("하단 툴바",  WIN_CENTER_X, WINSIZE_Y - 100, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->Toolbar), XS_CENTER, YS_CENTER);

	UIMANAGER->addUi(mToolbar);
	UIMANAGER->addObject(PLAYER);

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
