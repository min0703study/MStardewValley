#pragma once
#include "Map.h"
#include "GameScene.h"

class LoadScene: public GameScene
{
public:
	HRESULT init(void) override;
	void update(void) override;
	void release(void) override;
	void render(void) override;

	void pause(void) override;
	HRESULT resume(void) override;
private:
	LoadMap* mLoadMap;
};

