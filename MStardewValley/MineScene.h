#pragma once

#include "GameScene.h"
#include "Player.h"
#include "Map.h"

class MineScene: public GameScene
{
public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

private:
	MineMap* mMap;
	ImageGp* imageGp;
};

