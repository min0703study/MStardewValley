#pragma once
#include "GameScene.h"

class HomeMap;

class HomeScene : public GameScene {
public:
	HRESULT init(void) override;
	void update(void) override;
	void release(void) override;
	void render(void) override;

	HomeScene() {};
	~HomeScene() {};
private:
	HomeMap* mHomeMap;
};
