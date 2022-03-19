#include "Stdafx.h"
#include "MainGame.h"
#include "MenuScene.h"
#include "MapToolScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(true);
	ShowCursor(false);

	mCursor = new GameUI;
	mCursor->init("메인 커서", IMGCLASS->Cursor, _ptMouse.x, _ptMouse.y, false);

	//SCENEMANAGER->addScene("menu", new MenuScene);
	SCENEMANAGER->addScene("maptool", new MapToolScene);

	SCENEMANAGER->changeScene("maptool");

	return S_OK;
}

void MainGame::update(void)
{
	GameNode::update();

	mCursor->setX(_ptMouse.x);
	mCursor->setY(_ptMouse.y);

	SCENEMANAGER->update();
}

void MainGame::release(void)
{
	GameNode::release();
	SCENEMANAGER->release();
}

void MainGame::render(void)
{
	PatBlt(getMemDc(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDc());
	
	mCursor->render();
	
	IMAGEMANAGER->render(getBackBufferKey(), getHdc());
}
