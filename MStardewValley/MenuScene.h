#pragma once
#include "GameScene.h"
#include "GameUI.h"

class MenuScene: public GameScene
{
public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	int offset = 0;

	MenuScene() {};
	~MenuScene() {};
private:
	GameUI* mBtnStart;
	GameUI* mBtnMaptool;
	GameUI* mBtnExit;

	GameUI* mMenuLogo;

	bool mMousoverFlag;
};

