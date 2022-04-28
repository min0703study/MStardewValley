#include "Stdafx.h"
#include "MenuScene.h"

#define MENU_BTN_WIDTH 222.0f
#define MENU_BTN_SPACE 20.0f
#define MENU_BTN_HEIGHT 174.0f
#define MENU_BTN_X	WIN_CENTER_X
#define MENU_BTN_Y WINSIZE_Y - 320.0f
#define MENU_LOGO_X		WIN_CENTER_X
#define MENU_LOG_Y		WIN_CENTER_Y - 100.0f

HRESULT MenuScene::init(void)
{
	mMenuLogo = new UIComponent;
	mMenuLogo->init("메뉴 로고", MENU_LOGO_X, MENU_LOG_Y, GDIPLUSMANAGER->clone(IMGCLASS->MenuBackLogo), XS_CENTER, YS_CENTER);

	mMenuBg = new UIComponent;
	mMenuBg->init("메뉴 배경 하늘", 0, 0, IMAGEMANAGER->findImage(IMGCLASS->MenuBack), XS_LEFT, YS_TOP);

	mMenuBgCloud = new UIComponent;
	mMenuBgCloud->init("메뉴 배경 구름", 0, 0, GDIPLUSMANAGER->findOriginalImage(IMGCLASS->MenuBackCloud), XS_LEFT, YS_TOP);
	mMenuBgCloud->toLoopX(30);

	RectF mBtnsArea = RectFMakeCenter(MENU_BTN_X, MENU_BTN_Y, (MENU_BTN_WIDTH * 3) + (MENU_BTN_SPACE * 2), MENU_BTN_HEIGHT);

	mBtns[0] = new SButton;
	mBtns[0]->init("게임 시작 버튼", mBtnsArea.GetLeft(), mBtnsArea.GetBottom(), GDIPLUSMANAGER->clone(IMGCLASS->MenuBtnStart));
	mBtns[0]->setClickDownEvent([this](UIComponent* ui) {
		bReqChangeScene = true;
		mChangeScene = "start";
	});

	mBtns[1] = new SButton;
	mBtns[1]->init("맵툴 버튼", mBtnsArea.GetLeft() + MENU_BTN_WIDTH + MENU_BTN_SPACE, mBtnsArea.GetBottom(), GDIPLUSMANAGER->clone(IMGCLASS->MenuBtnMaptool));
	mBtns[1]->setClickDownEvent([this](UIComponent* ui) {
		bReqChangeScene = true;
		mChangeScene = "maptool";
	});

	mBtns[2] = new SButton;
	mBtns[2]->init("나가기 버튼", mBtnsArea.GetLeft() + (MENU_BTN_WIDTH * 2) + (MENU_BTN_SPACE * 2), mBtnsArea.GetBottom(), GDIPLUSMANAGER->clone(IMGCLASS->MenuBtnExit));
	mBtns[2]->setClickDownEvent([this](UIComponent* ui) {
		exit(0);
	});

	UIMANAGER->addUi(mMenuBg);
	UIMANAGER->addUi(mMenuBgCloud);
	UIMANAGER->addUi(mMenuLogo);
	UIMANAGER->addUiList((UIComponent**)mBtns, 3);

	bReqChangeScene = false;

	SOUNDMANAGER->play(SOUNDCLASS->MenuBackBgm, 0.1f);

	return S_OK;
}

void MenuScene::update(void)
{
	if (!bReqChangeScene) {
		UIMANAGER->update();
	}
	else {
		SCENEMANAGER->changeScene(mChangeScene);
		bReqChangeScene = false;
	}
}

void MenuScene::release(void)
{

	UIMANAGER->release();

	mMenuLogo->release();
	SAFE_DELETE(mMenuLogo);

	mMenuBgCloud->release();
	SAFE_DELETE(mMenuBgCloud);

	mBtns[0]->release();
	SAFE_DELETE(mBtns[0]);
	
	mBtns[1]->release();
	SAFE_DELETE(mBtns[1]);
	
	mBtns[2]->release();
	SAFE_DELETE(mBtns[2]);
}

void MenuScene::render(void)
{
	if (!bReqChangeScene) {
		UIMANAGER->render();
	}
}