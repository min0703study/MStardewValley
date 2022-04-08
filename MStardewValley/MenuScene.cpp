#include "Stdafx.h"
#include "MenuScene.h"

#define MENU_BTN_WIDTH 222.0f
#define MENU_BTN_SPACE 20.0f
#define MENU_BTN_HEIGHT 174.0f
#define MENU_BTN_X	WIN_CENTER_X
#define MENU_BTN_Y WINSIZE_Y - 300.0f

HRESULT MenuScene::init(void)
{
	mMenuLogo = new GameUI;
	mMenuLogo->init("메뉴 로고", POS::MENU::LOGO::x, POS::MENU::LOGO::y, GDIPLUSMANAGER->cloneImage(IMGCLASS->MenuBackLogo));

	mMenuBg = new GameUI;
	mMenuBg->init("메뉴 배경 하늘", 0, 0, IMAGEMANAGER->findImage(IMGCLASS->MenuBack));

	mMenuBgCloud = new GameUI;
	mMenuBgCloud->init("메뉴 배경 구름", 0, 0, GDIPLUSMANAGER->findOriginalImage(IMGCLASS->MenuBackCloud), XS_LEFT, YS_TOP);
	mMenuBgCloud->toLoopX(30);

	//Button
	RectF mBtnsArea = RectFMakeCenter(MENU_BTN_X, MENU_BTN_Y, (MENU_BTN_WIDTH * 3) + (MENU_BTN_SPACE * 2), MENU_BTN_HEIGHT);
	mBtns[0] = new SButton;
	mBtns[0]->init("게임 시작 버튼", mBtnsArea.GetLeft(), mBtnsArea.GetBottom(), GDIPLUSMANAGER->cloneImage(IMGCLASS->MenuBtnStart));
	mBtns[0]->setClickDownEvent([this](GameUI* ui) {
		SCENEMANAGER->changeScene("start");
	});

	mBtns[1] = new SButton;
	mBtns[1]->init("맵툴 버튼", mBtnsArea.GetLeft() + MENU_BTN_WIDTH + MENU_BTN_SPACE, mBtnsArea.GetBottom(), GDIPLUSMANAGER->cloneImage(IMGCLASS->MenuBtnMaptool));
	mBtns[1]->setClickDownEvent([this](GameUI* ui) {
		SCENEMANAGER->changeScene("maptool");
	});

	mBtns[2] = new SButton;
	mBtns[2]->init("맵툴 버튼", mBtnsArea.GetLeft() + (MENU_BTN_WIDTH * 2) + (MENU_BTN_SPACE * 2), mBtnsArea.GetBottom(), GDIPLUSMANAGER->cloneImage(IMGCLASS->MenuBtnExit));
	mBtns[2]->setClickDownEvent([this](GameUI* ui) {
		exit(0);
	});

	UIMANAGER->addUi(mMenuBg);
	UIMANAGER->addUi(mMenuBgCloud);
	UIMANAGER->addUi(mMenuLogo);
	UIMANAGER->addUiList((GameUI**)mBtns, 3);

	SOUNDMANAGER->play(SOUNDCLASS->MenuBackBgm, 0.1f);

	return S_OK;
}

void MenuScene::update(void)
{
	UIMANAGER->update();
}

void MenuScene::release(void)
{
	UIMANAGER->release();

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
	UIMANAGER->render();
}