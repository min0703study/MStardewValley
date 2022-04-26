#include "Stdafx.h"
#include "LoadScene.h"

HRESULT LoadScene::init(void)
{
	mLoadMap = new LoadMap;
	mLoadMap->init(MAPCLASS->LOAD, PLAYER->getToPortal().ToPortal);

	mMap = mLoadMap;

	UIMANAGER->addMap(mLoadMap);

	return S_OK;
}

void LoadScene::update(void)
{
	GameScene::update();
}

void LoadScene::release(void)
{
	mMap = nullptr;
	UIMANAGER->deleteMap(mLoadMap);
	mLoadMap->release();
	SAFE_DELETE(mLoadMap);
}

void LoadScene::render(void)
{
	GameScene::render();
}
