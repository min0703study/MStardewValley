#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{
	GameScene::init();
	bIsInitOver = true;
	return S_OK;
}

void StartScene::update(void)
{
	if (bIsInitOver)
	{
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
