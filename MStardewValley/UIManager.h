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

	void addMap(Map * map);

	bool isActiveUI() { return bActiveGameUI; };

	void deleteUI(GameUI* ui);
	void deleteObject(GameObject* ui);
	void deleteMap(Map * map);

	void activeGameUI(GameUI* ui);
	void disableGameUI(GameUI * ui);
private:
	vector<GameUI*> mVGameUi;
	vector<GameUI*>::iterator mViGameUi;

	vector<GameUI*> mVActiveUiList;
	vector<GameUI*>::iterator mViActiveUiList;
	GameUI* mCurActiveUI;

	vector<GameObject*> mVGameObject;
	vector<GameObject*>::iterator mViGameObject;

	Map* mMap;

	bool bActiveGameUI;
};

