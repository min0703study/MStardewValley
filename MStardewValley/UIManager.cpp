#include "Stdafx.h"
#include "UIManager.h"

HRESULT UIManager::init(void)
{
	mMap = nullptr;
	return S_OK;
}

void UIManager::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		for (mViGameUi = mVGameUi.begin(); mViGameUi != mVGameUi.end(); mViGameUi++) {
			if ((*mViGameUi)->getRectF().Contains(_ptfMouse)) {
				(*mViGameUi)->clickDownEvent();
			}
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		for (mViGameUi = mVGameUi.begin(); mViGameUi != mVGameUi.end(); mViGameUi++) {
			if ((*mViGameUi)->getRectF().Contains(_ptfMouse)) {
				(*mViGameUi)->clickUpEvent();
			}
		}
	}

	for (mViGameUi = mVGameUi.begin(); mViGameUi != mVGameUi.end(); mViGameUi++) {
		if ((*mViGameUi)->getRectF().Contains(_ptfMouse)) {
			(*mViGameUi)->mouseOverEvent();
		}
		else {
			(*mViGameUi)->mouseOffEvent();
		}

		(*mViGameUi)->updateUI();
	}
}

void UIManager::release(void)
{
	mVGameUi.clear();
}

void UIManager::render(void)
{
	if (mMap != nullptr) {
		mMap->render();
	}

	for (mViGameObject = mVGameObject.begin(); mViGameObject != mVGameObject.end(); mViGameObject++) {
		(*mViGameObject)->render();
	}

	for (mViGameUi = mVGameUi.begin(); mViGameUi != mVGameUi.end(); mViGameUi++) {
		(*mViGameUi)->render();
	}

}

void UIManager::addUi(GameUI * ui)
{
	mVGameUi.push_back(ui);
}

void UIManager::addUiList(GameUI** ui, int count)
{
	for (int i = 0; i < count; i++) {
		mVGameUi.push_back(ui[i]);
	}
}

void UIManager::addObject(GameObject * object)
{
	mVGameObject.push_back(object);
}

void UIManager::addMap(Map* map)
{
	mMap = map;
}

void UIManager::deleteUI(GameUI * ui)
{
	for (mViGameUi = mVGameUi.begin(); mViGameUi != mVGameUi.end(); mViGameUi++) {
		if (*mViGameUi == ui) {
			mVGameUi.erase(mViGameUi);
			break;
		}
	}
}

void UIManager::deleteObject(GameObject * object)
{
	for (mViGameObject = mVGameObject.begin(); mViGameObject != mVGameObject.end(); mViGameObject++) {
		if (*mViGameObject == object) {
			mVGameObject.erase(mViGameObject);
			break;
		}
	}
}

void UIManager::deleteMap(Map* map)
{
	mMap = nullptr;
}
