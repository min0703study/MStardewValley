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

	void addUi(UIComponent* ui);
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
	vector<UIComponent*> mVGameUi;
	vector<UIComponent*>::iterator mViGameUi;

	vector<UIComponent*> mVActiveUiList;
	vector<UIComponent*>::iterator mViActiveUiList;
	
	ImageGp* mFocusBg;

	UIComponent* mFocusUi;
	UIComponent* mCurActiveUI;

	vector<GameObject*> mVGameObject;
	vector<GameObject*>::iterator mViGameObject;



	bool bEventCheck;

	Map* mMap;

	bool bActiveGameUI;
	bool bOneUiFocusMode;
	bool bOneUiClick;
};

