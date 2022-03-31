#include "Stdafx.h"
#include "MineScene.h"

HRESULT MineScene::init(void)
{
	mPlayer = Player::getSingleton();
	mPlayer->Init("ÇÃ·¹ÀÌ¾î", CAMERA_X / 2.0f, CAMERA_Y/2.0f, PLAYER_WIDTH, PLAYER_HEIGHT, XS_CENTER, YS_CENTER);

	mMap = new Map;
	mMap->Init("±¤»ê ¸Ê", IMGCLASS->MapMines1To30);

	return S_OK;
}

void MineScene::update(void)
{
	mPlayer->update();

	if (KEYMANAGER->isStayTempKeyDown(VK_LEFT)) {
		if (!mMap->isCollisionWall(mPlayer->getTempMoveBoxRectF(GD_LEFT))) {
			mPlayer->move(GD_LEFT);
		}
	}

	if (KEYMANAGER->isStayTempKeyDown(VK_RIGHT)) {
		if (!mMap->isCollisionWall(mPlayer->getTempMoveBoxRectF(GD_RIGHT))) {
			mPlayer->move(GD_RIGHT);
		}
	}

	if (KEYMANAGER->isStayTempKeyDown(VK_UP)) {
		if (!mMap->isCollisionWall(mPlayer->getTempMoveBoxRectF(GD_UP))) {
			mPlayer->move(GD_UP);
		}
	}

	if (KEYMANAGER->isStayTempKeyDown(VK_DOWN)) {
		if (!mMap->isCollisionWall(mPlayer->getTempMoveBoxRectF(GD_DOWN))) {
			mPlayer->move(GD_DOWN);
		}
	}

}

void MineScene::release(void)
{
	
}

void MineScene::render(void)
{
	mMap->render();
	mPlayer->render();
}
