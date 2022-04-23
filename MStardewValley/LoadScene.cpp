#include "Stdafx.h"
#include "LoadScene.h"

HRESULT LoadScene::init(void)
{
	mLoadMap = new LoadMap;
	mLoadMap->init();

	mMap = mLoadMap;

	UIMANAGER->addMap(mLoadMap);

	return S_OK;
}

void LoadScene::update(void)
{
	GameScene::update();
	mMap->update();

	if (mMap->getReqSceneChange()) {
		mMap->setReqSceneChange(true);
		PLAYER->setToPortal(mMap->getReqSceneChangePortal());
		SCENEMANAGER->changeScene(mMap->getReqSceneChangePortal().ToSceneName);
	}
}

void LoadScene::release(void)
{
	UIMANAGER->deleteMap(mMap);
	mMap->release();
	SAFE_DELETE(mMap);
}

void LoadScene::render(void)
{
	GameScene::render();
}
