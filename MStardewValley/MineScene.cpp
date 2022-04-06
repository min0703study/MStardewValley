#include "Stdafx.h"
#include "MineScene.h"

HRESULT MineScene::init(void)
{
	//¸Ê »ý¼º
	mMineMap = new MineMap;
	mMineMap->init("±¤»ê¸Ê", 1, ML_ONE);

	mMap = mMineMap;
	
	UIMANAGER->addMap(mMineMap);

	//ÇÃ·¹ÀÌ¾î À§Ä¡ º¯°æ
	PLAYER->changeLocation(mMineMap->getEntranceAbsX(), mMineMap->getEntranceAbsY(), eLocation::L_MINE, XS_CENTER, YS_CENTER);

	mToolbar->addItem(ITEMCLASS->WEAPON, PLAYER->addItem(ITEMCLASS->WEAPON));
	mToolbar->addItem(ITEMCLASS->PICK, PLAYER->addItem(ITEMCLASS->PICK));

	return S_OK;
}

void MineScene::update(void)
{
	GameScene::update();
	mMap->update();
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
