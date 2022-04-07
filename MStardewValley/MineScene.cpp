#include "Stdafx.h"
#include "MineScene.h"

HRESULT MineScene::init(void)
{
	//�� ����
	mMineMap = new MineMap;
	mMineMap->init("�����", PLAYER->getToLoaction());

	mMap = mMineMap;
	
	UIMANAGER->addMap(mMineMap);

	PLAYER->setCurLoaction(PLAYER->getToLoaction());
	PLAYER->setToLoaction(eLocation::L_NONE);

	PLAYER->changePos(mMineMap->getEntranceAbsX(), mMineMap->getEntranceAbsY(), XS_CENTER, YS_CENTER);

	return S_OK;
}

void MineScene::update(void)
{
	GameScene::update();
	mMap->update();
}

void MineScene::release(void)
{
	//�� ����
	UIMANAGER->deleteMap(mMap);

	mMap->release();
	SAFE_DELETE(mMap);
}

void MineScene::render(void)
{
	GameScene::render();

}
