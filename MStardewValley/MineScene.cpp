#include "Stdafx.h"
#include "MineScene.h"

HRESULT MineScene::init(void)
{
	mPlayer = Player::getSingleton();
	mPlayer->Init("ÇÃ·¹ÀÌ¾î", CAMERA_X / 2.0f, CAMERA_Y/2.0f, 100.0f, 50.0f);

	mMap = new Map;
	mMap->Init("±¤»ê ¸Ê", IMGCLASS->MapMines1To30);
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
}
