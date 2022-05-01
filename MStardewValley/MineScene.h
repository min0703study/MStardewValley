#pragma once

#include "GameScene.h"
#include "Player.h"
#include "Map.h"

class MineScene: public GameScene
{
public:
	HRESULT init(void) override;
	void update(void) override;
	void release(void) override;
	void render(void) override;
	void pause(void) override;
	HRESULT resume(void) override;

private:
	MineMap* mMineMap;
};

