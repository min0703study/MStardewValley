#include "Stdafx.h"
#include "MainGame.h"
#include "MenuScene.h"
#include "MapToolScene.h"
#include "MineScene.h"
#include "StartScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	ShowCursor(false);

	mCursor = new GameUI;
	mCursor->init("메인 커서", _ptfMouse.X, _ptfMouse.Y, IMAGEMANAGER->findImage(IMGCLASS->Cursor));

	SCENEMANAGER->addScene("menu", new MenuScene);
	SCENEMANAGER->addScene("maptool", new MapToolScene);
	SCENEMANAGER->addScene("start", new StartScene);
	SCENEMANAGER->addScene("mine", new MineScene);

	SCENEMANAGER->changeScene("menu");

	return S_OK;
}

void MainGame::update(void)
{
	KEYMANAGER->update();

	mCursor->setX(_ptfMouse.X);
	mCursor->setY(_ptfMouse.Y);

	SCENEMANAGER->update();
}

void MainGame::release(void)
{
	mCursor->release();

	SAFE_DELETE(mCursor);
	SCENEMANAGER->release();
}

void MainGame::render(void)
{
	PatBlt(getMemDc(), 0, 0, WINSIZE_INT_X, WINSIZE_INT_Y, BLACKNESS);

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDc());

	mCursor->render();

	IMAGEMANAGER->render(getBackBufferKey(), getHdc());
}
