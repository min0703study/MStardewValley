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
	void addUi(GameUI* ui, eGameFixedUI fiedKind);
	void addUiList(GameUI ** ui, int count);
	void addObject(GameObject* ui);

	void addMap(Map * map);

	bool isClickUI() { return bIsClickUI; };

	void deleteUI(GameUI* ui);
	void deleteObject(GameObject* ui);
	void deleteMap(Map * map);
	GameUI * getFixedUI(eGameFixedUI fixedKind);
private:
	vector<GameUI*> mVGameUi;
	vector<GameUI*>::iterator mViGameUi;

	vector<GameObject*> mVGameObject;
	vector<GameObject*>::iterator mViGameObject;
	
	GameUI* mGameUIList[eGameFixedUI::GFU_END];

	Map* mMap;

	bool bIsClickUI;
};

