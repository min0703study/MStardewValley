#include "Stdafx.h"
#include "MineScene.h"

HRESULT MineScene::init(void)
{
	//¸Ê »ý¼º
	mMineMap = new MineMap;
	mMineMap->init(1);

	mMap = mMineMap;
	
	UIMANAGER->addMap(mMineMap);

	return S_OK;
}

void MineScene::update(void)
{
	GameScene::update();

	if (mMineMap != nullptr) {
		if (mMineMap->getRebuildRequest()) {
			mMineMap->setRebuildRequest(false);
			mMineMap->rebuild(mMineMap->getRequestFloor());
		}
	}
}

void MineScene::render(void)
{
	GameScene::render();
}

void MineScene::release(void)
{
	//¸Ê »èÁ¦
	UIMANAGER->deleteMap(mMineMap);
	mMineMap->release();
	SAFE_DELETE(mMineMap);
}