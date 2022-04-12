#include "Stdafx.h"
#include "FarmScene.h"

HRESULT FarmScene::init(void)
{
	mFarmMap = new FarmMap;
	mFarmMap->init();

	mMap = mFarmMap;

	UIMANAGER->addMap(mFarmMap);

	PLAYER->setCurLoaction(PLAYER->getToLoaction());
	PLAYER->setToLoaction(eLocation::L_NONE);

	PLAYER->changePos(10 * TILE_SIZE, 10 * TILE_SIZE , XS_CENTER, YS_CENTER);

	return S_OK;
}

void FarmScene::update(void)
{
	GameScene::update();
	mMap->update();
}

void FarmScene::release(void)
{
}

void FarmScene::render(void)
{
	GameScene::render();
}
