#include "Stdafx.h"
#include "MainGame.h"

#include "MenuScene.h"
#include "MapToolScene.h"
#include "MineScene.h"
#include "StartScene.h"
#include "FarmScene.h"
#include "ShopScene.h"
#include "HomeScene.h"
#include "LoadScene.h"
#include "TownScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);

	ShowCursor(false);
	mCustomCursor = IMAGEMANAGER->findImage(IMGCLASS->Cursor);

	SCENEMANAGER->addScene("menu", new MenuScene);
	SCENEMANAGER->addScene("mine", new MineScene);
	SCENEMANAGER->addScene("farm", new FarmScene);
	SCENEMANAGER->addScene("shop", new ShopScene);
	SCENEMANAGER->addScene("home", new HomeScene);
	SCENEMANAGER->addScene("maptool", new MapToolScene);
	SCENEMANAGER->addScene("town", new TownScene);
	SCENEMANAGER->addScene("load", new LoadScene);
	SCENEMANAGER->addScene("start", new StartScene);

	SCENEMANAGER->initScene("start");

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
