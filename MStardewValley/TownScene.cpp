#include "Stdafx.h"
#include "TownScene.h"

HRESULT TownScene::init(void)
{
	mTownMap = new TownMap;
	mTownMap->init(MAPCLASS->TOWN, PLAYER->getToPortal().ToPortal);

	mMap = mTownMap;

	return S_OK;
}

void TownScene::update(void)
{
	GameScene::update();
}


HRESULT TownScene::resume(void)
{
	GameScene::resume();
	return S_OK;
}


void TownScene::pause(void)
{
	GameScene::pause();
}

void TownScene::render(void)
{
	GameScene::render();
}



void TownScene::release(void)
{
}
