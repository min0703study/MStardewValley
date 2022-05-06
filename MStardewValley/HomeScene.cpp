#include "Stdafx.h"
#include "HomeScene.h"

HRESULT HomeScene::init(void)
{
	mHomeMap = new HomeMap;
	mHomeMap->init(MAPCLASS->HOME);

	mMap = mHomeMap;

	return S_OK;
}

void HomeScene::pause(void)
{
	UIMANAGER->deleteMap(mHomeMap);
}

HRESULT HomeScene::resume(void)
{
	if (PLAYER->getToPortal().ToPortal == -1) {
		UIMANAGER->addMap(mMap);
		mMap->inToPlayer(mHomeMap->getBedIndex());
	}
	else {
		GameScene::resume();
	}

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