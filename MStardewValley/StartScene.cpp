#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{
	PLAYER->init("플레이어", 0.0f, 0.0f, PLAYER_WIDTH, PLAYER_WIDTH, XS_CENTER, YS_CENTER);
	UIMANAGER->addObject(PLAYER);

	//debug
	PLAYER->addItem(ITEMCLASS->HOE);
	PLAYER->addItem(ITEMCLASS->WATERING_CAN);
	PLAYER->addItem(ITEMCLASS->PICK);
	PLAYER->addItem(ITEMCLASS->AXE);
	PLAYER->addItem(ITEMCLASS->WEAPON);
	PLAYER->addItem(ITEMCLASS->SICKLE);
	PLAYER->addItem(ITEMCLASS->FURNACE);
	PLAYER->addItem(ITEMCLASS->BEEN_SEED, 3);

	PLAYER->changeHoldingItem(0);

	GameScene::init();

	SCENEMANAGER->initScene(SCENECLASS->HOME);
	SCENEMANAGER->initScene(SCENECLASS->MINE);
	SCENEMANAGER->initScene(SCENECLASS->FARM);
	SCENEMANAGER->initScene(SCENECLASS->SHOP);
	SCENEMANAGER->initScene(SCENECLASS->TOWN);
	SCENEMANAGER->initScene(SCENECLASS->LOAD);

	bIsInitOver = true;

	return S_OK;
}

void StartScene::update(void)
{
	if (bIsInitOver)
	{
		PLAYER->setToPortal(MapPortal(-1));
		SCENEMANAGER->changeGameScene(SCENECLASS->HOME);
		bIsInitOver = false;
	}
}

void StartScene::release(void)
{
}

void StartScene::render(void)
{

}
