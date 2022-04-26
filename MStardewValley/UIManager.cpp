#include "Stdafx.h"
#include "UIManager.h"

HRESULT UIManager::init(void)
{
	mMap = nullptr;
	bActiveGameUI = false;
	return S_OK;
}

void UIManager::update(void)
{
	bOneUiActive = false;

	for (mViActiveUiList = mVActiveUiList.begin(); mViActiveUiList != mVActiveUiList.end(); mViActiveUiList++) {
		if ((*mViActiveUiList)->getLastEvent() == GameUI::eEventStat::ES_CLICK_DOWN || (*mViActiveUiList)->getLastEvent() == GameUI::eEventStat::ES_DRAG) {
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
				(*mViActiveUiList)->clickUpEvent();
			}

			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
				(*mViActiveUiList)->dragEvent();
			}
		}
		else {
			if ((*mViActiveUiList)->getRectF().Contains(_ptfMouse)) {
				if ((*mViActiveUiList)->getLastEvent() != GameUI::eEventStat::ES_DRAG) {
					(*mViActiveUiList)->mouseOverEvent();
				}

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					(*mViActiveUiList)->clickDownEvent();
					bOneUiActive = true;
				}
			} else {
				if ((*mViActiveUiList)->getLastEvent() == GameUI::eEventStat::ES_MOUSE_OVER) {
					(*mViActiveUiList)->mouseOffEvent();
				}
			}

			(*mViActiveUiList)->updateUI();
		}
	}

	if (!bOneUiActive && mMap != nullptr) {
		mMap->update();
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
		//(*mViGameObject)->render();
	}

	for (mViActiveUiList = mVActiveUiList.begin(); mViActiveUiList != mVActiveUiList.end(); mViActiveUiList++) {
		(*mViActiveUiList)->render();
	}

}

void UIManager::addUi(GameUI * ui)
{
	mVGameUi.push_back(ui);
	mVActiveUiList.push_back(ui);
}

void UIManager::addUiList(GameUI** ui, int count)
{
	for (int i = 0; i < count; i++) {
		mVGameUi.push_back(ui[i]);
		mVActiveUiList.push_back(ui[i]);
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

void UIManager::activeGameUI(GameUI * ui)
{
	mVActiveUiList.push_back(ui);
}

void UIManager::disableGameUI(GameUI * ui)
{
	for (mViActiveUiList = mVActiveUiList.begin(); mViActiveUiList != mVActiveUiList.end(); mViActiveUiList++) {
		if (*mViActiveUiList == ui) {
			mVActiveUiList.erase(mViActiveUiList);
			break;
		}
	}
}
