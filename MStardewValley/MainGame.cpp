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
	mCustomCursor = IMAGEMANAGER->findImage(IMGCLASS->Cursor);

	SCENEMANAGER->addScene("menu", new MenuScene);
	SCENEMANAGER->addScene("maptool", new MapToolScene);
	SCENEMANAGER->addScene("start", new StartScene);
	SCENEMANAGER->addScene("mine", new MineScene);

	SCENEMANAGER->initScene("maptool");

	return S_OK;
}

void MainGame::update(void)
{
	KEYMANAGER->update();
	SCENEMANAGER->update();
}

void MainGame::release(void)
{
	SCENEMANAGER->release();
}

void MainGame::render(void)
{
	PatBlt(getMemDc(), 0, 0, WINSIZE_INT_X, WINSIZE_INT_Y, BLACKNESS);

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDc());

	mCustomCursor->render(getMemDc(), _ptfMouse.X, _ptfMouse.Y);

	IMAGEMANAGER->render(getBackBufferKey(), getHdc());
}
