#include "Stdafx.h"
#include "TownScene.h"

HRESULT TownScene::init(void)
{
	mTownMap = new TownMap;
	mTownMap->init();

	mMap = mTownMap;

	UIMANAGER->addMap(mTownMap);

	PLAYER->setCurMapKey(PLAYER->getToLoaction());
	PLAYER->setToMapKey("");

	return S_OK;
}

void TownScene::update(void)
{
	GameScene::update();
	mMap->update();
}

void TownScene::release(void)
{
}

void TownScene::render(void)
{
	GameScene::render();
}
