#include "Stdafx.h"
#include "MineScene.h"

HRESULT MineScene::init(void)
{
	mPlayer = Player::getSingleton();
	mPlayer->Init("ÇÃ·¹ÀÌ¾î", CAMERA_X / 2.0f, CAMERA_Y/2.0f, PLAYER_WIDTH, PLAYER_HEIGHT, XS_CENTER, YS_CENTER);

	mMap = new MineMap;
	mMap->init("±¤»ê¸Ê", 1, ML_ONE);

	return S_OK;
}

void MineScene::update(void)
{
	mPlayer->update();
	mMap->update();

	if (KEYMANAGER->isStayTempKeyDown(LEFT_KEY)) {
		if (KEYMANAGER->isOnceTempKeyDown(LEFT_KEY)) {
			mPlayer->changeDirection(GD_LEFT);
			mPlayer->changeActionStat(PS_WALK);
		}
		if (!mMap->isCollisionWall(mPlayer->getTempMoveBoxRectF(GD_LEFT))) {
			mPlayer->move(GD_LEFT);
		}
	}

	if (KEYMANAGER->isStayTempKeyDown(RIGHT_KEY)) {
		if (KEYMANAGER->isOnceTempKeyDown(RIGHT_KEY)) {
			mPlayer->changeDirection(GD_RIGHT);
			mPlayer->changeActionStat(PS_WALK);
		}
		if (!mMap->isCollisionWall(mPlayer->getTempMoveBoxRectF(GD_RIGHT))) {
			mPlayer->move(GD_RIGHT);
		}
	}

	if (KEYMANAGER->isStayTempKeyDown(UP_KEY)) {
		if (KEYMANAGER->isOnceTempKeyDown(UP_KEY)) {
			mPlayer->changeDirection(GD_UP);
			mPlayer->changeActionStat(PS_WALK);
		}
		if (!mMap->isCollisionWall(mPlayer->getTempMoveBoxRectF(GD_UP))) {
			mPlayer->move(GD_UP);
		}
	}

	if (KEYMANAGER->isStayTempKeyDown(DOWN_KEY)) {
		if (KEYMANAGER->isOnceTempKeyDown(DOWN_KEY)) {
			mPlayer->changeDirection(GD_DOWN);
			mPlayer->changeActionStat(PS_WALK);
		}
		if (!mMap->isCollisionWall(mPlayer->getTempMoveBoxRectF(GD_DOWN))) {
			mPlayer->move(GD_DOWN);
		}
	}

	if (KEYMANAGER->isOnceTempKeyUp(LEFT_KEY)) {
		mPlayer->changeActionStat(PS_IDLE);
	}


	if (KEYMANAGER->isOnceTempKeyUp(RIGHT_KEY)) {
		mPlayer->changeActionStat(PS_IDLE);
	}


	if (KEYMANAGER->isOnceTempKeyUp(DOWN_KEY)) {
		mPlayer->changeActionStat(PS_IDLE);
	}


	if (KEYMANAGER->isOnceTempKeyUp(UP_KEY)) {
		mPlayer->changeActionStat(PS_IDLE);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		mPlayer->changeActionStat(PS_ATTACK_1);
	}

}

void MineScene::release(void)
{
	mMap->release();
	//mPlayer->release();
}

void MineScene::render(void)
{
	mMap->render();
	mPlayer->render();
}
