#include "Stdafx.h"
#include "HomeScene.h"

HRESULT HomeScene::init(void)
{
	mHomeMap = new HomeMap;
	mHomeMap->init();

	mMap = mHomeMap;

	UIMANAGER->addMap(mHomeMap);

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
