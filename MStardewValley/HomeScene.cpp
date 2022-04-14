#include "Stdafx.h"
#include "HomeScene.h"

HRESULT HomeScene::init(void)
{
	mHomeMap = new HomeMap;
	mHomeMap->init();

	mMap = mHomeMap;

	UIMANAGER->addMap(mHomeMap);

	PLAYER->setCurMapKey(PLAYER->getToLoaction());
	PLAYER->setToMapKey("");

	PLAYER->changePos(10 * TILE_SIZE, 10 * TILE_SIZE, XS_CENTER, YS_CENTER);

	return S_OK;
}

void HomeScene::update(void)
{
	GameScene::update();
	mMap->update();
}

void HomeScene::release(void)
{
}

void HomeScene::render(void)
{
	GameScene::render();
}
