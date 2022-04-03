#pragma once

#include "GameScene.h"
#include "Player.h"
#include "Map.h"
#include "EnvironmentManager.h"

class MineScene: public GameScene
{
public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

private:
	Player* mPlayer;
	MineMap* mMap;
	ImageGp* imageGp;
	EnvironmentManager* mEnvironmentManager;
};

