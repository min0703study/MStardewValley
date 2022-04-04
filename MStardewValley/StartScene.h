#pragma once
#include "GameScene.h"

class StartScene: public GameScene
{
public:
	HRESULT init(void) override;
	void update(void) override;
	void release(void) override;
	void render(void) override;

private:
	bool bIsInitOver;
};

