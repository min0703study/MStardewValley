#include "Stdafx.h"
#include "FarmScene.h"

HRESULT FarmScene::init(void)
{
	mFarmMap = new FarmMap;
	mFarmMap->init(MAPCLASS->FARM);

	mMap = mFarmMap;
	return S_OK;
}

void FarmScene::update(void)
{
	GameScene::update();
}

void FarmScene::render(void)
{
	GameScene::render();
}

void FarmScene::pause(void)
{
	GameScene::pause();
}

HRESULT FarmScene::resume(void)
{
	GameScene::resume();
	return S_OK;
}

void FarmScene::release(void)
{
	mFarmMap->release();
	UIMANAGER->deleteObject(mFarmMap);
}
