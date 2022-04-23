#include "Stdafx.h"
#include "MineScene.h"

HRESULT MineScene::init(void)
{
	//�� ����
	mMineMap = new MineMap;
	mMineMap->init(1);

	mMap = mMineMap;
	
	UIMANAGER->addMap(mMineMap);

	PLAYER->setCurMapKey(PLAYER->getToLoaction());
	PLAYER->setToMapKey("");

	return S_OK;
}

void MineScene::update(void)
{
	GameScene::update();
	mMineMap->update();
	if (mMineMap->getRebuildRequest()) {
		mMineMap->setRebuildRequest(false);
		mMineMap->rebuild(mMineMap->getRequestFloor());
	}
}

void MineScene::render(void)
{
	GameScene::render();
}

void MineScene::release(void)
{
	//�� ����
	UIMANAGER->deleteMap(mMap);

	mMap->release();
	SAFE_DELETE(mMap);
}