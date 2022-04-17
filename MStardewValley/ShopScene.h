#pragma once
#include "GameScene.h"

class ShopMap;
class ListBox;

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

	vector<const Item*> mVSaleItem;
	vector<ImageGp*> vSaleItemImg;
};
