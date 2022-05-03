#include "Stdafx.h"
#include "GameScene.h"

Toolbar* GameScene::sToolbar = nullptr;
AccessMenu* GameScene::sAccessMenu = nullptr;
MoneyBoard* GameScene::mMoneyBoard = nullptr;
EnergePGBar* GameScene::mEnergePGBar = nullptr;
Clock* GameScene::mClock = nullptr;
QuestionBox* GameScene::mQuestionBox = nullptr;
EventBox* GameScene::sShowItemBox = nullptr;
ImageGp* GameScene::sBrightnessImg = nullptr;

HRESULT GameScene::init(void)
{
	mSceneId = "";

	sToolbar = new Toolbar();
	sToolbar->init("하단 툴바",  WIN_CENTER_X, WINSIZE_Y - 100, TOOLBAR_WIDTH, TOOLBAR_HEIGHT,GDIPLUSMANAGER->clone(IMGCLASS->Toolbar));
	sToolbar->setClickDownEvent([this](UIComponent* ui) {
		int index = sToolbar->changeSelectItem(sToolbar->getIndexToPtF(_ptfMouse));
		if (index != -1) {
			PLAYER->changeHoldingItem(index);
		}
	});

	sAccessMenu = new AccessMenu;
	sAccessMenu->init();

	mEnergePGBar = new EnergePGBar;
	mEnergePGBar->init("플레이어 에너지바", WIN_DETAIL_SIZE_X, WIN_DETAIL_SIZE_Y, 48, 330, XS_RIGHT, YS_BOTTOM);

	mClock = new Clock;
	mClock->init("시계", WIN_DETAIL_SIZE_X, 0, 284, 160, XS_RIGHT, YS_TOP);

	mMoneyBoard = new MoneyBoard;
	mMoneyBoard->init("돈 계기판", WIN_DETAIL_SIZE_X, mClock->getHeight(), 260, 76, XS_RIGHT, YS_TOP);
	mMoneyBoard->setActiveStat(false);

	sShowItemBox = new EventBox;
	sShowItemBox->init("아이템 표시", 0, WINSIZE_Y - 300.0f, 213, 93, XS_LEFT, YS_TOP);

	vector<wstring> temp;
	temp.push_back(L"a");
	temp.push_back(L"b");
	mQuestionBox = new QuestionBox;
	mQuestionBox->init("질문 박스", 0, 0, 1000, 500, "", temp, XS_LEFT, YS_TOP);

	sBrightnessImg = new ImageGp;
	sBrightnessImg->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(WINSIZE_X, WINSIZE_Y, Color(0, 0, 0)));
	sBrightnessImg->setRenderBitBlt();
	sBrightnessImg->setRenderAlpha();
	sBrightnessImg->setAlpha((BYTE)100);

	ImageGp* mFocusModeBG = new ImageGp;
	mFocusModeBG->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(WINSIZE_X, WINSIZE_Y, Color(0,0,0)));
	mFocusModeBG->setRenderBitBlt();
	mFocusModeBG->setRenderAlpha();
	mFocusModeBG->setAlpha((BYTE)100);

	UIMANAGER->addFocusModeBg(mFocusModeBG);

	UIMANAGER->addComponent(sToolbar);
	//UIMANAGER->addUi(sShow);
	UIMANAGER->addComponent(mMoneyBoard);
	UIMANAGER->addComponent(mEnergePGBar);
	UIMANAGER->addComponent(mClock);
	UIMANAGER->addGameUI(sAccessMenu);

	//UIMANAGER->disableGameUI(sAccessMenu);

	TIMEMANAGER->startGameTime();
	SOUNDMANAGER->play(SOUNDCLASS->GameBackBgm, 0.1f);

	return S_OK;
}

void GameScene::update(void)
{
	UIMANAGER->update();
	EFFECTMANAGER->update();
	PLAYER->update();

	sShowItemBox->update();

	sBrightnessImg->setAlpha(static_cast<int>(TIMEMANAGER->getGameTime()) / 255);
	
	if (mMap->getReqSceneChange()) {
		mMap->setReqSceneChange(false);
		PLAYER->setToPortal(mMap->getReqSceneChangePortal());
		SCENEMANAGER->changeGameScene(mMap->getReqSceneChangePortal().ToSceneName);
		return;
	}

	if (mMap->getReqShowEventBox()) {
		mMap->setReqShowEventBox(false);
		sShowItemBox->addPickUpItemEvent(mMap->getReqShowEventBoxItemId());
	}

	if (KEYMANAGER->isStayKeyDown(VK_ESCAPE)) {
		if (bActiveAccessMenu) {

			//SOUNDMANAGER->play(SOUNDCLASS->ACCESS_MENU_ON);
			//UIMANAGER->oneUIFocusMode(sAccessMenu);
		}
		else {
			//SOUNDMANAGER->play(SOUNDCLASS->ACCESS_MENU_OFF);
			//UIMANAGER->oneUIFocusModeOff();
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
	EFFECTMANAGER->render();
	sShowItemBox->render();
	//sAccessMenu->render();
	//sBrightnessImg->render(0.0f,0.0f);
	//mQuestionBox->render();
}

void GameScene::pause(void)
{
	UIMANAGER->deleteObject(mMap);
}

HRESULT GameScene::resume(void)
{
	const MapPortal playerPortal = PLAYER->getToPortal();

	UIMANAGER->addMap(mMap);
	mMap->inToPlayer(playerPortal.ToPortal);

	return S_OK;
}
