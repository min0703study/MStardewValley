#include "Stdafx.h"
#include "MineScene.h"

HRESULT MineScene::init(void)
{
	//¸Ê »ý¼º
	mMineMap = new MineMap;
	mMineMap->init("±¤»ê¸Ê", PLAYER->getToLoaction());

	mMap = mMineMap;
	
	UIMANAGER->addMap(mMineMap);

	PLAYER->setCurLoaction(PLAYER->getToLoaction());
	PLAYER->setToLoaction(eLocation::L_NONE);

	PLAYER->changePos(mMineMap->getEntranceAbsX(), mMineMap->getEntranceAbsY(), XS_CENTER, YS_CENTER);

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
