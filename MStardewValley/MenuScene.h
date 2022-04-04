#pragma once
#include "GameScene.h"
#include "GameUI.h"

#define MENU_BTN_COUNT		3

class MenuScene: public GameNode
{
public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	MenuScene() {};
	~MenuScene() {};
private:
	SButton* mBtns[MENU_BTN_COUNT];

	SButton* mBtnStart;
	SButton* mBtnMaptool;
	SButton* mBtnExit;

	GameUI* mMenuLogo;
	GameUI* mMenuBg;
	GameUI* mMenuBgCloud;

	float loop;

	bool mMousoverFlag;
};

