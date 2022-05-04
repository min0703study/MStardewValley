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

	void addComponent(UIComponent* ui);
	void addGameUI(GameUI * ui);
	void addUiList(UIComponent ** ui, int count);
	void addObject(GameObject* ui);
	void addFocusModeBg(ImageGp* ui);

	void addMap(Map * map);

	bool isActiveUI() { return bActiveGameUI; };

	void deleteUI(UIComponent* ui);
	void deleteObject(GameObject* ui);
	void deleteMap(Map * map);

	void activeGameUI(UIComponent* ui);
	void disableGameUI(UIComponent * ui);
	void oneUIFocusMode(UIComponent * ui);
	void oneUIFocusModeOff();

	void setEventCheck(bool flag) { bEventCheck = flag; }
private:
	vector<UIComponent*> mVGameComponent;
	vector<UIComponent*>::iterator mViComponent;

	vector<UIComponent*> mVActiveUiList;
	vector<UIComponent*>::iterator mViActiveUiList;
	
	ImageGp* mFocusBg;

	UIComponent* mFocustComponent;
	UIComponent* mCurActiveUI;

	vector<GameUI*> mVGameUI;
	vector<GameUI*>::iterator mViGameUI;

	GameUI* mFocusUI;

	vector<GameObject*> mVGameObject;
	vector<GameObject*>::iterator mViGameObject;

	bool bEventCheck;

	Map* mMap;

	bool bActiveGameUI;
	bool bOneUiFocusMode;
	bool bOneUiClick;
};

