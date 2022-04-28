#include "Stdafx.h"
#include "MenuScene.h"

#define MENU_BTN_WIDTH 222.0f
#define MENU_BTN_SPACE 20.0f
#define MENU_BTN_HEIGHT 174.0f
#define MENU_BTN_X	WIN_CENTER_X
#define MENU_BTN_Y WINSIZE_Y - 340.0f
#define MENU_LOGO_X		WIN_CENTER_X
#define MENU_LOG_Y		WIN_CENTER_Y - 120.0f

HRESULT MenuScene::init(void)
{
	mMenuLogo = new UIComponent;
	mMenuLogo->init("메뉴 로고", MENU_LOGO_X, MENU_LOG_Y, GDIPLUSMANAGER->clone(IMGCLASS->MenuBackLogo), XS_CENTER, YS_CENTER);

	mMenuBg = new UIComponent;
	mMenuBg->init("메뉴 배경 하늘", 0, 0, IMAGEMANAGER->findImage(IMGCLASS->MenuBack), XS_LEFT, YS_TOP);

	mMenuBgCloud = new UIComponent;
	mMenuBgCloud->init("메뉴 배경 구름", 0, 0, IMAGEMANAGER->findImage(IMGCLASS->MenuBackCloud), XS_LEFT, YS_TOP);

	RectF mBtnsArea = RectFMakeCenter(MENU_BTN_X, MENU_BTN_Y, (MENU_BTN_WIDTH * 3) + (MENU_BTN_SPACE * 2), MENU_BTN_HEIGHT);

	mBtns[0] = new SButton;
	mBtns[0]->init("게임 시작 버튼", mBtnsArea.GetLeft(), mBtnsArea.GetBottom(), GDIPLUSMANAGER->clone(IMGCLASS->MenuBtnStart));
	mBtns[0]->setClickDownEvent([this](UIComponent* ui) {
		bReqChangeScene = true;
		mChangeScene = SCENECLASS->START;
	});

	mBtns[1] = new SButton;
	mBtns[1]->init("맵툴 버튼", mBtnsArea.GetLeft() + MENU_BTN_WIDTH + MENU_BTN_SPACE, mBtnsArea.GetBottom(), GDIPLUSMANAGER->clone(IMGCLASS->MenuBtnMaptool));
	mBtns[1]->setClickDownEvent([this](UIComponent* ui) {
		bReqChangeScene = true;
		mChangeScene = SCENECLASS->MAPTOOL;
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
	bStartChangeSceneAni = false;
	bEndChangeSceneAni = false;

	SOUNDMANAGER->play(SOUNDCLASS->MenuBackBgm, 0.1f);

	mMenuLogo->sizeToBig(1.03f, 3.0f);
	mMenuBgCloud->toLoopX(100, 0.1f);

	return S_OK;
}

void MenuScene::update(void)
{
	UIMANAGER->update();

	if (bReqChangeScene) {
		bReqChangeScene = false;
		bStartChangeSceneAni = true;
	}

	if (bStartChangeSceneAni) {
		mMenuLogo->moveTo(eUIDirection::UI_RIGHT, 15.0f);
		for (int i = 0; i < 3; i++) {
			mBtns[i]->moveTo(eUIDirection::UI_RIGHT, 15.0f);
		}
		mMenuBgCloud->fadeOut(1);
		bStartChangeSceneAni = false;

		mChangeSceneTimer = 0.8f;
		UIMANAGER->setEventCheck(false);
	}

	if (mChangeSceneTimer > 0.0f) {
		mChangeSceneTimer -= 0.01f;
		if (mChangeSceneTimer <= 0.0f) bEndChangeSceneAni = true;
	}

	if (bEndChangeSceneAni) {
		UIMANAGER->setEventCheck(true);
		SCENEMANAGER->changeScene(mChangeScene);
	}

	if (mMenuLogo->getCurAniStat() == UIComponent::eAniStat::SIZE_BIG) {
		mMenuLogo->sizeToOriginal(3.0f);
	}
}

void MenuScene::render(void)
{
	UIMANAGER->render();
}

void MenuScene::release(void)
{
	UIMANAGER->release();

	//mMenuLogo->release();
	//SAFE_DELETE(mMenuLogo);

	//mMenuBgCloud->release();
	//SAFE_DELETE(mMenuBgCloud);

	mBtns[0]->release();
	SAFE_DELETE(mBtns[0]);
	
	mBtns[1]->release();
	SAFE_DELETE(mBtns[1]);
	
	mBtns[2]->release();
	SAFE_DELETE(mBtns[2]);
}
