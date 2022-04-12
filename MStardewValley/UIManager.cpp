#include "Stdafx.h"
#include "UIManager.h"

HRESULT UIManager::init(void)
{
	mMap = nullptr;
	return S_OK;
}

void UIManager::update(void)
{
	bool isClickUI = false;
	for (mViGameUi = mVGameUi.begin(); mViGameUi != mVGameUi.end(); mViGameUi++) {
		if ((*mViGameUi)->getLastEvent() == GameUI::eEventStat::ES_CLICK_DOWN || (*mViGameUi)->getLastEvent() == GameUI::eEventStat::ES_DRAG) {
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
				(*mViGameUi)->clickUpEvent();
			}

			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
				(*mViGameUi)->dragEvent();
			}
		}
		else {
			if ((*mViGameUi)->getRectF().Contains(_ptfMouse)) {
				if ((*mViGameUi)->getLastEvent() != GameUI::eEventStat::ES_DRAG) {
					(*mViGameUi)->mouseOverEvent();
				}

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					isClickUI = true;
					(*mViGameUi)->clickDownEvent();
				}
			}
			else {
				if ((*mViGameUi)->getLastEvent() == GameUI::eEventStat::ES_MOUSE_OVER) {
					(*mViGameUi)->mouseOffEvent();
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !isClickUI) {
		mMap->clickDownEvent();
	}
}

void UIManager::release(void)
{
	//mVGameUi.clear();
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
