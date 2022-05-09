#include "Stdafx.h"
#include "GameScene.h"

Toolbar* GameScene::sToolbar = nullptr;
AccessMenu* GameScene::sAccessMenu = nullptr;
MoneyBoard* GameScene::mMoneyBoard = nullptr;
EnergePGBar* GameScene::mEnergePGBar = nullptr;
HPPGBar* GameScene::mHPPGBar = nullptr;
Clock* GameScene::mClock = nullptr;
QuestionBox* GameScene::mQuestionBox = nullptr;
EventBox* GameScene::sShowItemBox = nullptr;
ImageGp* GameScene::sBrightnessImg = nullptr;

HRESULT GameScene::init(void)
{
	mSceneId = "";

	sToolbar = new Toolbar();
	sToolbar->init();

	sAccessMenu = new AccessMenu;
	sAccessMenu->init();

	mEnergePGBar = new EnergePGBar;
	mEnergePGBar->init();

	mHPPGBar = new HPPGBar;
	mHPPGBar->init();

	mClock = new Clock;
	mClock->init();

	mMoneyBoard = new MoneyBoard;
	mMoneyBoard->init("돈 계기판", WIN_DETAIL_SIZE_X, mClock->getHeight(), 260, 76, XS_RIGHT, YS_TOP);
	mMoneyBoard->setActiveStat(false);

	sShowItemBox = new EventBox;
	sShowItemBox->init("아이템 표시", 0, WINSIZE_Y - 400.0f, 213, 93, XS_LEFT, YS_TOP);

	mQuestionBox = new QuestionBox;
	mQuestionBox->init();

	sBrightnessImg = new ImageGp;
	sBrightnessImg->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(WINSIZE_X, WINSIZE_Y, Color(0, 0, 0)));
	sBrightnessImg->setRenderBitBlt();
	sBrightnessImg->setRenderAlpha();
	sBrightnessImg->setAlpha((BYTE)0);

	ImageGp* mFocusModeBG = new ImageGp;
	mFocusModeBG->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(WINSIZE_X, WINSIZE_Y, Color(0,0,0)));
	mFocusModeBG->setRenderBitBlt();
	mFocusModeBG->setRenderAlpha();
	mFocusModeBG->setAlpha((BYTE)150);

	UIMANAGER->addFocusModeBg(mFocusModeBG);

	UIMANAGER->addComponent(mMoneyBoard);

	UIMANAGER->addGameUI(sToolbar);
	UIMANAGER->addGameUI(mHPPGBar);
	UIMANAGER->addGameUI(mEnergePGBar);
	UIMANAGER->addGameUI(mClock);
	TIMEMANAGER->startGameTime();
	SOUNDMANAGER->play(SOUNDCLASS->GameBackBgm, 0.1f);

	return S_OK;
}

void GameScene::update(void)
{
	UIMANAGER->update();
	PLAYER->update();

	sShowItemBox->update();
	
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

	if (KEYMANAGER->isOnceKeyDown('L')) {
		if (bActiveEatMenu) {
			SOUNDMANAGER->play(SOUNDCLASS->ACCESS_MENU_ON);
			UIMANAGER->oneUIFocusMode(mQuestionBox);
		}
		else {
			UIMANAGER->oneUIFocusModeOff();
			SOUNDMANAGER->play(SOUNDCLASS->ACCESS_MENU_OFF);
			Fruit* fruit = (Fruit*)PLAYER->getHoldItem();
			sShowItemBox->addHpUpEvent(fruit->getHp(), fruit->getEnergy());
			PLAYER->eat();
			
		}

		bActiveEatMenu = !bActiveEatMenu;
	}

	if (KEYMANAGER->isOnceKeyDown('K')) {
		if (mSceneId == "home") {
			sBrightnessImg->setAlpha(0);
		}
		else {
			sBrightnessImg->offsetAlpha(10);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) {
		if (bActiveAccessMenu) {
			UIMANAGER->oneUIFocusMode(sAccessMenu);
			SOUNDMANAGER->play(SOUNDCLASS->ACCESS_MENU_ON);
		}
		else {
			UIMANAGER->oneUIFocusModeOff();
			SOUNDMANAGER->play(SOUNDCLASS->ACCESS_MENU_OFF);
		}

		bActiveAccessMenu = !bActiveAccessMenu;
	}
}

void GameScene::release(void)
{
	UIMANAGER->deleteObject(PLAYER);
}

void GameScene::render(void)
{
	UIMANAGER->render();
	sShowItemBox->render();
	//sBrightnessImg->render(0.0f, 0.0f);
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
