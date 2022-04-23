#include "Stdafx.h"
#include "FarmScene.h"

HRESULT FarmScene::init(void)
{
	mFarmMap = new FarmMap;
	mFarmMap->init();

	mMap = mFarmMap;

	UIMANAGER->addMap(mFarmMap);

	return S_OK;
}

void FarmScene::update(void)
{
	GameScene::update();
	mMap->update();
}

void FarmScene::release(void)
{
	mFarmMap->release();
	UIMANAGER->deleteObject(mFarmMap);
}

void FarmScene::render(void)
{
	GameScene::render();
}
