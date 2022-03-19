#include "Stdafx.h"
#include "MenuScene.h"

HRESULT MenuScene::init(void)
{
	GameScene::init();

	mMenuLogo = new GameUI;
	mMenuLogo->init("메뉴 로고", IMGCLASS->MenuBackLogo, WINSIZE_X / 2.0f, WINSIZE_Y / 2.0f - 200, true);
	UIMANAGER->addUi(mMenuLogo);

	mBtnStart = new GameUI;
	mBtnStart->init("게임 시작 버튼", IMGCLASS->MenuBtnStart, mMenuLogo->getRECT().left, mMenuLogo->getRECT().bottom + 200, true);
	UIMANAGER->addUi(mBtnStart);

	mBtnMaptool = new GameUI;
	mBtnMaptool->init("맵툴 버튼", IMGCLASS->MenuBtnMaptool, mMenuLogo->getRECT().left + 300 , mMenuLogo->getRECT().bottom + 200, true);
	UIMANAGER->addUi(mBtnMaptool);

	mBtnExit = new GameUI;
	mBtnExit->init("나가기 버튼", IMGCLASS->MenuBtnExit, mMenuLogo->getRECT().left + 600, mMenuLogo->getRECT().bottom + 200, true);
	UIMANAGER->addUi(mBtnExit);

	SOUNDMANAGER->play(SOUNDCLASS->MenuBackBgm, 1.0f);
	
	return S_OK;
}

void MenuScene::update(void)
{
	GameScene::update();

	if (PtInRect(&mBtnStart->getRECT(), _ptMouse)) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			mBtnExit->mouseClickDownEvent();
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			mBtnExit->mouseClickUpEvent();
		}
		mBtnStart->mouseOverEvent();
	}
	else {
		mBtnStart->mouseOutEvent();
	}

	if (PtInRect(&mBtnMaptool->getRECT(), _ptMouse)) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			mBtnExit->mouseClickDownEvent();
			SCENEMANAGER->changeScene("maptool");

		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			mBtnExit->mouseClickUpEvent();
		}
		mBtnMaptool->mouseOverEvent();
	}
	else {
		mBtnMaptool->mouseOutEvent();
	}

	if (PtInRect(&mBtnExit->getRECT(), _ptMouse)) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			mBtnExit->mouseClickDownEvent();
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			mBtnExit->mouseClickUpEvent();
		}
		mBtnExit->mouseOverEvent();
	}
	else {
		mBtnExit->mouseOutEvent();
	}
}

void MenuScene::release(void)
{
}

void MenuScene::render(void)
{
	IMAGEMANAGER->render(IMGCLASS->MenuBack, getMemDc(), 0, 0);
	GDIPLUSMANAGER->render(IMGCLASS->MenuBackCloud, getMemDc(), 0, 0);
	UIMANAGER->render();
	GameScene::render();

}