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

	PLAYER->changePos(9 * TILE_SIZE, 9 * TILE_SIZE, XS_LEFT, YS_BOTTOM);

	return S_OK;
}

void HomeScene::update(void)
{
	GameScene::update();
	mMap->update();
}

void HomeScene::release(void)
{
	mHomeMap->release();
	UIMANAGER->deleteMap(mHomeMap);
}

void HomeScene::render(void)
{
	GameScene::render();
}
