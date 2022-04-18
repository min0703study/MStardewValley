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
	mMenuLogo = new GameUI;
	mMenuLogo->init("�޴� �ΰ�", MENU_LOGO_X, MENU_LOG_Y, GDIPLUSMANAGER->clone(IMGCLASS->MenuBackLogo), XS_CENTER, YS_CENTER);

	mMenuBg = new GameUI;
	mMenuBg->init("�޴� ��� �ϴ�", 0, 0, IMAGEMANAGER->findImage(IMGCLASS->MenuBack), XS_LEFT, YS_TOP);

	mMenuBgCloud = new GameUI;
	mMenuBgCloud->init("�޴� ��� ����", 0, 0, GDIPLUSMANAGER->findOriginalImage(IMGCLASS->MenuBackCloud), XS_LEFT, YS_TOP);
	mMenuBgCloud->toLoopX(30);

	//Button
	RectF mBtnsArea = RectFMakeCenter(MENU_BTN_X, MENU_BTN_Y, (MENU_BTN_WIDTH * 3) + (MENU_BTN_SPACE * 2), MENU_BTN_HEIGHT);
	mBtns[0] = new SButton;
	mBtns[0]->init("���� ���� ��ư", mBtnsArea.GetLeft(), mBtnsArea.GetBottom(), GDIPLUSMANAGER->clone(IMGCLASS->MenuBtnStart));
	mBtns[0]->setClickDownEvent([this](GameUI* ui) {
		bChangeScene = true;
		mChangeScene = "start";
	});

	mBtns[1] = new SButton;
	mBtns[1]->init("���� ��ư", mBtnsArea.GetLeft() + MENU_BTN_WIDTH + MENU_BTN_SPACE, mBtnsArea.GetBottom(), GDIPLUSMANAGER->clone(IMGCLASS->MenuBtnMaptool));
	mBtns[1]->setClickDownEvent([this](GameUI* ui) {
		bChangeScene = true;
		mChangeScene = "maptool";
	});

	mBtns[2] = new SButton;
	mBtns[2]->init("������ ��ư", mBtnsArea.GetLeft() + (MENU_BTN_WIDTH * 2) + (MENU_BTN_SPACE * 2), mBtnsArea.GetBottom(), GDIPLUSMANAGER->clone(IMGCLASS->MenuBtnExit));
	mBtns[2]->setClickDownEvent([this](GameUI* ui) {
		exit(0);
	});

	UIMANAGER->addUi(mMenuBg);
	UIMANAGER->addUi(mMenuBgCloud);
	UIMANAGER->addUi(mMenuLogo);
	UIMANAGER->addUiList((GameUI**)mBtns, 3);

	bChangeScene = false;

	SOUNDMANAGER->play(SOUNDCLASS->MenuBackBgm, 0.1f);

	return S_OK;
}

void MenuScene::update(void)
{
	if (!bChangeScene) {
		UIMANAGER->update();
	}
	else {
		SCENEMANAGER->changeScene(mChangeScene);
		bChangeScene = false;
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
	if (!bChangeScene) {
		UIMANAGER->render();
	}
}