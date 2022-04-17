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

	static Toolbar* sToolbar;
	static AccessMenu* sAccessMenu;
	static GameUI* mClock;
	static GameUI* mEnergyProgressBar;
	static MoneyBoard* mMoneyBoard;

	Map* mMap;
};
