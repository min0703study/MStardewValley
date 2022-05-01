#include "Stdafx.h"
#include "MineScene.h"

HRESULT MineScene::init(void)
{
	//¸Ê »ý¼º
	mMineMap = new MineMap;
	mMineMap->init(1);

	mMap = mMineMap;

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

void MineScene::pause(void)
{
	GameScene::pause();
	SOUNDMANAGER->stop(SOUNDCLASS->MineBackBgm);
	SOUNDMANAGER->play(SOUNDCLASS->GameBackBgm);
}

HRESULT MineScene::resume(void)
{

	GameScene::resume();
	SOUNDMANAGER->stop(SOUNDCLASS->GameBackBgm);
	SOUNDMANAGER->play(SOUNDCLASS->MineBackBgm);
	return S_OK;
}

void MineScene::release(void)
{
	//¸Ê »èÁ¦
	UIMANAGER->deleteMap(mMineMap);
	mMineMap->release();
	SAFE_DELETE(mMineMap);
}