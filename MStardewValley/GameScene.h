#pragma once

#include "GameNode.h"
#include "GameUI.h"

class GameScene: public GameNode
{
public:
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void release(void);
	virtual void render(void);

	GameScene() {};
	virtual ~GameScene() {};
protected:
	string mSceneId;

	static Toolbar* mToolbar;
	static GameUI* mClock;
	static GameUI* mEnergyProgressBar;

};
