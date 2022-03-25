#include "Stdafx.h"
#include "MenuScene.h"

HRESULT MenuScene::init(void)
{
	GameScene::init();

	mMenuLogo = new GameUI;
	mMenuLogo->init("메뉴 로고", POS::MENU::LOGO::x, POS::MENU::LOGO::y, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MenuBackLogo));

	mMenuBg = new GameUI;
	mMenuBg->init("메뉴 배경 하늘", 0, 0, IMAGEMANAGER->findImage(IMGCLASS->MenuBack));

	mMenuBgCloud = new GameUI;
	mMenuBgCloud->init("메뉴 배경 구름", 0, 0, GDIPLUSMANAGER->findImage(IMGCLASS->MenuBackCloud));

	//Button Create and Init
	float btnAllWidth = UI_SIZE::MENU::BTN::width * 3 + UI_SIZE::MENU::BTN::spaceWidth * 2;
	float btnStartX = ((WINSIZE_X + 100.0f) / 2.0f) - btnAllWidth / 2.0f;

	mBtnStart = new SButton;
	mBtnStart->init("게임 시작 버튼", btnStartX, POS::MENU::BTN::y, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MenuBtnStart));
	mBtns[0] = mBtnStart;

	mBtnMaptool = new SButton;
	mBtnMaptool->init("맵툴 버튼", btnStartX + UI_SIZE::MENU::BTN::width + UI_SIZE::MENU::BTN::spaceWidth, POS::MENU::BTN::y, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MenuBtnMaptool));
	mBtns[1] = mBtnMaptool;

	mBtnExit = new SButton;
	mBtnExit->init("나가기 버튼", btnStartX + (UI_SIZE::MENU::BTN::width + UI_SIZE::MENU::BTN::spaceWidth) * 2.0f, POS::MENU::BTN::y, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MenuBtnExit));
	mBtns[2] = mBtnExit;
	
	SOUNDMANAGER->play(SOUNDCLASS->MenuBackBgm, 0.1f);

	return S_OK;
}

void MenuScene::update(void)
{
	GameScene::update();

	mBtnExit->update();
	mBtnStart->update();
	mBtnMaptool->update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		mBtnExit->clickDownEvent();
		mBtnStart->clickDownEvent();
		mBtnMaptool->clickDownEvent();
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		mBtnExit->clickUpEvent();
		mBtnStart->clickUpEvent();
		mBtnMaptool->clickUpEvent();
	}

	if (mBtnMaptool->isSelected()) {
		SOUNDMANAGER->stop(SOUNDCLASS->MenuBackBgm);
		SCENEMANAGER->changeScene("maptool");
	}

	if (mBtnExit->isSelected()) {
		SOUNDMANAGER->stop(SOUNDCLASS->MenuBackBgm);
		exit(0);
	}
}

void MenuScene::release(void)
{
	mMenuLogo->release();
	SAFE_DELETE(mMenuLogo);
	
	mBtnStart->release();
	SAFE_DELETE(mBtnStart);
	
	mBtnMaptool->release();
	SAFE_DELETE(mBtnMaptool);
	
	mBtnExit->release();
	SAFE_DELETE(mBtnExit);

}

void MenuScene::render(void)
{
	GameScene::render();

	mMenuBg->render();
	mMenuBgCloud->render();
	mMenuLogo->render();

	mBtnStart->render();
	mBtnMaptool->render();
	mBtnExit->render();
}