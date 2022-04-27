#pragma once
#include "SingletonBase.h"

#include "GameUI.h"
#include "GameObject.h"
#include "Map.h"

class UIManager: public SingletonBase<UIManager>
{
public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	void addUi(GameUI* ui);
	void addUiList(GameUI ** ui, int count);
	void addObject(GameObject* ui);
	void addFocusModeBg(ImageGp* ui);

	void addMap(Map * map);

	bool isActiveUI() { return bActiveGameUI; };

	void deleteUI(GameUI* ui);
	void deleteObject(GameObject* ui);
	void deleteMap(Map * map);

	void activeGameUI(GameUI* ui);
	void disableGameUI(GameUI * ui);
	void oneUIFocusMode(GameUI * ui);
	void oneUIFocusModeOff();
private:
	vector<GameUI*> mVGameUi;
	vector<GameUI*>::iterator mViGameUi;

	vector<GameUI*> mVActiveUiList;
	vector<GameUI*>::iterator mViActiveUiList;
	
	ImageGp* mFocusBg;

	GameUI* mFocusUi;
	GameUI* mCurActiveUI;

	vector<GameObject*> mVGameObject;
	vector<GameObject*>::iterator mViGameObject;


	Map* mMap;

	bool bActiveGameUI;
	bool bOneUiFocusMode;
	bool bOneUiClick;
};

