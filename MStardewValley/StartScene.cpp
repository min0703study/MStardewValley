#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{
	GameScene::init();
	bIsInitOver = true;

	PLAYER->init("플레이어", 0.0f, 0.0f, PLAYER_WIDTH, PLAYER_WIDTH, XS_CENTER, YS_CENTER);

	return S_OK;
}

void StartScene::update(void)
{
	if (bIsInitOver)
	{
		PLAYER->setToLoaction(eLocation::L_FARM);
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
