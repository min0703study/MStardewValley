#include "Stdafx.h"
#include "HomeScene.h"

HRESULT HomeScene::init(void)
{
	mHomeMap = new HomeMap;
	mHomeMap->init(MAPCLASS->HOME, -1);

	mMap = mHomeMap;

	UIMANAGER->addMap(mHomeMap);

	return S_OK;
}

void HomeScene::update(void)
{
	GameScene::update();
}

void HomeScene::release(void)
{
	mMap = nullptr;
	UIMANAGER->deleteMap(mHomeMap);
	mHomeMap->release();
	SAFE_DELETE(mHomeMap);
}

void HomeScene::render(void)
{
	GameScene::render();

}
