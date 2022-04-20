#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{
	PLAYER->init("플레이어", 0.0f, 0.0f, PLAYER_WIDTH, PLAYER_WIDTH, XS_CENTER, YS_CENTER);

	GameScene::init();
	bIsInitOver = true;

	return S_OK;
}

void StartScene::update(void)
{
	if (bIsInitOver)
	{
		PLAYER->setToMapKey(MAPCLASS->MINE_1);
		PLAYER->setToPortalKey(0);
		SCENEMANAGER->changeScene("mine");
		bIsInitOver = false;
	}
}

void StartScene::release(void)
{
}

void StartScene::render(void)
{

}
