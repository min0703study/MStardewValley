#pragma once
#include "GameScene.h"
#include "Map.h"
#include "GameUI.h"
class ShopScene : public GameScene {
public:
	HRESULT init(void) override;
	void update(void) override;
	void release(void) override;
	void render(void) override;

	ShopScene() {};
	~ShopScene() {};
private:
	ShopMap* mShopMap;
	ListBox* mListBox;
};
