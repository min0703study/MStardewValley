#include "Stdafx.h"
#include "MineScene.h"

HRESULT MineScene::init(void)
{
	//¸Ê »ý¼º
	mMap = new MineMap;
	mMap->init("±¤»ê¸Ê", 1, ML_ONE);
	UIMANAGER->addMap(mMap);
	
	//ÇÃ·¹ÀÌ¾î À§Ä¡ º¯°æ
	PLAYER->changeLocation(mMap->getEntranceAbsX(), mMap->getEntranceAbsY(), eLocation::L_MINE, XS_CENTER, YS_CENTER);

	mToolbar->addItem(0, 1, 2);

	return S_OK;
}

void MineScene::update(void)
{
	GameScene::update();

	mMap->update();

	if (KEYMANAGER->isStayTempKeyDown(LEFT_KEY)) {
		if (KEYMANAGER->isOnceTempKeyDown(LEFT_KEY)) {
			PLAYER->changeDirection(GD_LEFT);
			PLAYER->changeActionStat(PS_WALK);
		}
		if (!mMap->isCollisionWall(PLAYER->getTempMoveBoxRectF(GD_LEFT))) {
			PLAYER->move(GD_LEFT);
		}
	}

	if (KEYMANAGER->isStayTempKeyDown(RIGHT_KEY)) {
		if (KEYMANAGER->isOnceTempKeyDown(RIGHT_KEY)) {
			PLAYER->changeDirection(GD_RIGHT);
			PLAYER->changeActionStat(PS_WALK);
		}
		if (!mMap->isCollisionWall(PLAYER->getTempMoveBoxRectF(GD_RIGHT))) {
			PLAYER->move(GD_RIGHT);
		}
	}

	if (KEYMANAGER->isStayTempKeyDown(UP_KEY)) {
		if (KEYMANAGER->isOnceTempKeyDown(UP_KEY)) {
			PLAYER->changeDirection(GD_UP);
			PLAYER->changeActionStat(PS_WALK);
		}
		if (!mMap->isCollisionWall(PLAYER->getTempMoveBoxRectF(GD_UP))) {
			PLAYER->move(GD_UP);
		}
	}

	if (KEYMANAGER->isStayTempKeyDown(DOWN_KEY)) {
		if (KEYMANAGER->isOnceTempKeyDown(DOWN_KEY)) {
			PLAYER->changeDirection(GD_DOWN);
			PLAYER->changeActionStat(PS_WALK);
		}
		if (!mMap->isCollisionWall(PLAYER->getTempMoveBoxRectF(GD_DOWN))) {
			PLAYER->move(GD_DOWN);
		}
	}

	if (KEYMANAGER->isOnceTempKeyUp(LEFT_KEY)) {
		PLAYER->changeActionStat(PS_IDLE);
	}

	if (KEYMANAGER->isOnceTempKeyUp(RIGHT_KEY)) {
		PLAYER->changeActionStat(PS_IDLE);
	}

	if (KEYMANAGER->isOnceTempKeyUp(DOWN_KEY)) {
		PLAYER->changeActionStat(PS_IDLE);
	}

	if (KEYMANAGER->isOnceTempKeyUp(UP_KEY)) {
		PLAYER->changeActionStat(PS_IDLE);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		if (mToolbar->isCollisionContentBox(_ptfMouse)) {
			int itemId = mToolbar->changeSelectItem(mToolbar->getIndexToPtF(_ptfMouse));
			if (itemId != -1) {
				PLAYER->changeSelectItem(itemId);
			}
		}
	}


}

void MineScene::release(void)
{
	//¸Ê »èÁ¦
	UIMANAGER->deleteMap(mMap);
	mMap->release();
	SAFE_DELETE(mMap);
}

void MineScene::render(void)
{
	GameScene::render();
}
