#include "Stdafx.h"
#include "MineScene.h"

HRESULT MineScene::init(void)
{
	//�� ����
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
			
			bool isToOneFloor = mMineMap->getRequestFloor() == 1;

			mMineMap->release();
			UIMANAGER->deleteMap(mMineMap);
			SAFE_DELETE(mMineMap);

			mMineMap = new MineMap;
			mMap = mMineMap;
			if (isToOneFloor) {
				mMineMap->init(1);
				mMineMap->down();
			}
			else {
				mMineMap->init(RND->getFlag() ? 2 : 3);
				mMineMap->down();
			}

			UIMANAGER->addMap(mMap);

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
	//�� ����
	UIMANAGER->deleteMap(mMineMap);
	mMineMap->release();
	SAFE_DELETE(mMineMap);
}