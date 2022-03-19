#include "Stdafx.h"
#include "UIManager.h"

HRESULT UIManager::init(void)
{
	return S_OK;
}

void UIManager::update(void)
{
	for (mViGameUi = mVGameUi.begin(); mViGameUi != mVGameUi.end(); mViGameUi++) {
		(*mViGameUi)->update();
	}

	for (mViGameObject = mVGameObject.begin(); mViGameObject != mVGameObject.end(); mViGameObject++) {
		(*mViGameObject)->update();
	}
}

void UIManager::release(void)
{
}

void UIManager::render(void)
{
	for (mViGameUi = mVGameUi.begin(); mViGameUi != mVGameUi.end(); mViGameUi++) {
		(*mViGameUi)->render();
	}

	for (mViGameObject = mVGameObject.begin(); mViGameObject != mVGameObject.end(); mViGameObject++) {
		(*mViGameObject)->render();
	}
}

void UIManager::addUi(GameUI * ui)
{
	mVGameUi.push_back(ui);
}

void UIManager::addUi(GameObject * ui)
{
	mVGameObject.push_back(ui);
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

void UIManager::deleteUI(GameObject * ui)
{
	for (mViGameObject = mVGameObject.begin(); mViGameObject != mVGameObject.end(); mViGameObject++) {
		if (*mViGameObject == ui) {
			mVGameObject.erase(mViGameObject);
			break;
		}
	}
}
