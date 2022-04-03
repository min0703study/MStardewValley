#include "Stdafx.h"
#include "GameScene.h"

HRESULT GameScene::init(void)
{
	//common ui
	mToolbar = new GameUI();
	mToolbar->init("하단 툴바",  WIN_CENTER_X, WINSIZE_Y - 100, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->Toolbar));

	return S_OK;
}

void GameScene::update(void)
{
}

void GameScene::release(void)
{
}

void GameScene::render(void)
{
	mToolbar->render();
}
