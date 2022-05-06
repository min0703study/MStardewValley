#pragma once
#include "GameScene.h"

class ShopMap;
class ListBox;

class ShopScene : public GameScene {
public:
	HRESULT init(void) override;
	void update(void) override;
	void render(void) override;
	void pause(void) override;
	HRESULT resume(void) override;
	void release(void) override;

	ShopScene() {};
	~ShopScene() {};
private:
	ShopMap* mSeedShopMap;
	ShopMap* mWeaponShopMap;
	ShopMap* mBlackSmithShopMap;

	SaleItemBox* mSeedSaleItemBox;
	SaleItemBox* mWeaponSaleItemBox;
	SaleItemBox* mToolUpgradeItemBox;

	ShopMap* mCurShopMap;
	SaleItemBox* mCurItemList;

	bool bShowingSaleList;
};
