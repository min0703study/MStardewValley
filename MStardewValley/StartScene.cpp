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
		PLAYER->setToLoaction(eLocation::L_SHOP);
		SCENEMANAGER->changeScene("shop");
		bIsInitOver = false;
	}
}

void StartScene::release(void)
{
}

void StartScene::render(void)
{

}
