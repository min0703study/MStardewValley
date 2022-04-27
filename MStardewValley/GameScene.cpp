#include "Stdafx.h"
#include "GameScene.h"

Toolbar* GameScene::sToolbar = nullptr;
AccessMenu* GameScene::sAccessMenu = nullptr;
MoneyBoard* GameScene::mMoneyBoard = nullptr;
EnergePGBar* GameScene::mEnergePGBar = nullptr;
Clock* GameScene::mClock = nullptr;

HRESULT GameScene::init(void)
{
	sToolbar = new Toolbar();
	sToolbar->init("하단 툴바",  WIN_CENTER_X, WINSIZE_Y - 100, TOOLBAR_WIDTH, TOOLBAR_HEIGHT,GDIPLUSMANAGER->clone(IMGCLASS->Toolbar));
	sToolbar->setClickDownEvent([this](GameUI* ui) {
		int index = sToolbar->changeSelectItem(sToolbar->getIndexToPtF(_ptfMouse));
		if (index != -1) {
			PLAYER->changeHoldingItem(index);
		}
	});

	sAccessMenu = new AccessMenu;
	sAccessMenu->init("사용자 컨트롤 메뉴", WIN_CENTER_X, WIN_CENTER_Y, ACCESS_MENU_WIDTH, ACCESS_MENU_HEIGHT);

	mEnergePGBar = new EnergePGBar;
	mEnergePGBar->init("플레이어 에너지바", WIN_DETAIL_SIZE_X, WIN_DETAIL_SIZE_Y, 48, 330, XS_RIGHT, YS_BOTTOM);

	mClock = new Clock;
	mClock->init("시계", WIN_DETAIL_SIZE_X, 0, 284, 160, XS_RIGHT, YS_TOP);

	mMoneyBoard = new MoneyBoard;
	mMoneyBoard->init("돈 계기판", WIN_DETAIL_SIZE_X, mClock->getHeight(), 260, 76, XS_RIGHT, YS_TOP);
	mMoneyBoard->setActiveStat(false);

	ImageGp* mFocusModeBG = new ImageGp;
	mFocusModeBG->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(WINSIZE_X, WINSIZE_Y, Color(100, 0,0,0)));

	UIMANAGER->addFocusModeBg(mFocusModeBG);
	UIMANAGER->addUi(sToolbar);
	UIMANAGER->addUi(sAccessMenu);
	UIMANAGER->addUi(mMoneyBoard);
	UIMANAGER->addUi(mEnergePGBar);
	UIMANAGER->addUi(mClock);

	UIMANAGER->disableGameUI(sAccessMenu);

	UIMANAGER->addObject(PLAYER);
	
	//debug
	PLAYER->addItem(ITEMCLASS->HOE);
	PLAYER->addItem(ITEMCLASS->WATERING_CAN);
	PLAYER->addItem(ITEMCLASS->PICK);
	PLAYER->addItem(ITEMCLASS->AXE);
	PLAYER->addItem(ITEMCLASS->WEAPON);
	PLAYER->addItem(ITEMCLASS->BEEN_SEED, 3);

	PLAYER->changeHoldingItem(0);

	SOUNDMANAGER->play(SOUNDCLASS->GameBackBgm, 0.1f);

	return S_OK;
}

void GameScene::update(void)
{
	UIMANAGER->update();
	PLAYER->update();

	if (mMap->getReqSceneChange()) {
		mMap->setReqSceneChange(false);
		PLAYER->setToPortal(mMap->getReqSceneChangePortal());
		SCENEMANAGER->changeScene(mMap->getReqSceneChangePortal().ToSceneName);
		return;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) {
		if (bActiveAccessMenu) {
			UIMANAGER->oneUIFocusMode(sAccessMenu);
		}
		else {
			UIMANAGER->oneUIFocusModeOff();
		}

		bActiveAccessMenu = !bActiveAccessMenu;
	}
}

void GameScene::release(void)
{
	UIMANAGER->deleteUI(sToolbar);
	UIMANAGER->deleteObject(PLAYER);
}

void GameScene::render(void)
{
	UIMANAGER->render();
}
