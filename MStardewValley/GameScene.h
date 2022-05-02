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

	virtual HRESULT resume(void);
	virtual void pause(void);

	const inline string getSceneId() { return mSceneId; };

	GameScene() {};
	virtual ~GameScene() {};
protected:
	Map* mMap;

	string mSceneId;

	static Toolbar* sToolbar;
	static AccessMenu* sAccessMenu;
	static Clock* mClock;
	static EnergePGBar* mEnergePGBar;
	static MoneyBoard* mMoneyBoard;
	static QuestionBox* mQuestionBox;
	static EventBox* sShowItemBox;

	static ImageGp* sBrightnessImg;
	bool bActiveAccessMenu;
};
