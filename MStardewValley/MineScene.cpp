#include "Stdafx.h"
#include "MineScene.h"

HRESULT MineScene::init(void)
{
	mPlayer = Player::getSingleton();
	mPlayer->Init("�÷��̾�", CAMERA_X / 2.0f, CAMERA_Y/2.0f, 36.0f, 72.0f);

	mMap = new Map;
	mMap->Init("���� ��", IMGCLASS->MapMines1To30);
	return S_OK;
}

void MineScene::update(void)
{
	mPlayer->update();
}

void MineScene::release(void)
{
}

void MineScene::render(void)
{
	mMap->render();
	mPlayer->render();
}
