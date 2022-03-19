#pragma once
#include "SingletonBase.h"

#include "GameUI.h"
#include "GameObject.h"

class UIManager: public SingletonBase<UIManager>
{
public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	void addUi(GameUI* ui);
	void addUi(GameObject* ui);

	void deleteUI(GameUI* ui);
	void deleteUI(GameObject* ui);
private:
	vector<GameUI*> mVGameUi;
	vector<GameUI*>::iterator mViGameUi;

	vector<GameObject*> mVGameObject;
	vector<GameObject*>::iterator mViGameObject;
};

