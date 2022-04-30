#include "Stdafx.h"
#include "UIManager.h"

#define fade_in_time 5.0f

HRESULT UIManager::init(void)
{
	mMap = nullptr;
	bActiveGameUI = false;
	bOneUiClick = false;
	bOneUiFocusMode = false;
	bEventCheck = true;
	bOneUiFocusMode = false;

	return S_OK;
}

void UIManager::update(void)
{
	if (bOneUiFocusMode) {
		if (mFocusUi->getLastEvent() == UIComponent::eEventStat::ES_CLICK_DOWN || mFocusUi->getLastEvent() == UIComponent::eEventStat::ES_DRAG) {
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
				mFocusUi->clickUpEvent();
			}

			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
				mFocusUi->dragEvent();
			}
		} else {
			if (mFocusUi->getRectF().Contains(_ptfMouse)) {
				if (mFocusUi->getLastEvent() != UIComponent::eEventStat::ES_DRAG) {
					mFocusUi->mouseOverEvent();
				}

				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					mFocusUi->clickDownEvent();
					bOneUiClick = true;
				}
			}
			else {
				if (mFocusUi->getLastEvent() == UIComponent::eEventStat::ES_MOUSE_OVER) {
					mFocusUi->mouseOffEvent();
				}
			}

			mFocusUi->updateUI();
		}
	} else {
		bOneUiClick = false;
		for (mViActiveUiList = mVActiveUiList.begin(); mViActiveUiList != mVActiveUiList.end(); mViActiveUiList++) {
			if (bEventCheck) {
				if ((*mViActiveUiList)->getLastEvent() == UIComponent::eEventStat::ES_CLICK_DOWN || (*mViActiveUiList)->getLastEvent() == UIComponent::eEventStat::ES_DRAG) {
					if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
						LOG::d(to_string(_ptfMouse.X) + " / " + to_string(_ptfMouse.Y));
						(*mViActiveUiList)->clickUpEvent();
					}

					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
						//(*mViActiveUiList)->setX(_ptfMouse.X);
						//(*mViActiveUiList)->setY(_ptfMouse.Y);
						(*mViActiveUiList)->dragEvent();
					}
				}
				else {
					if ((*mViActiveUiList)->getRectF().Contains(_ptfMouse)) {
						if ((*mViActiveUiList)->getLastEvent() != UIComponent::eEventStat::ES_DRAG) {
							(*mViActiveUiList)->mouseOverEvent();
						}

						if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
							(*mViActiveUiList)->clickDownEvent();
							bOneUiClick = true;
						}
					}
					else {
						if ((*mViActiveUiList)->getLastEvent() == UIComponent::eEventStat::ES_MOUSE_OVER) {
							(*mViActiveUiList)->mouseOffEvent();
						}
					}
				}
			}

			(*mViActiveUiList)->updateUI();
		}

		if (!bOneUiClick && mMap != nullptr) {
			mMap->update();
		}
	}
}

void UIManager::release(void)
{
	mVGameUi.clear();
	mVActiveUiList.clear();
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

	if (bOneUiFocusMode) {
		mFocusBg->render(0,0);
		mFocusUi->render();
	}
}

void UIManager::addUi(UIComponent * ui)
{
	mVGameUi.push_back(ui);
	mVActiveUiList.push_back(ui);
}

void UIManager::addUiList(UIComponent** ui, int count)
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

void UIManager::addFocusModeBg(ImageGp * ui)
{
	mFocusBg = ui;
}

void UIManager::addMap(Map* map)
{
	mMap = map;
}

void UIManager::deleteUI(UIComponent * ui)
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

void UIManager::activeGameUI(UIComponent * ui)
{
	mVActiveUiList.push_back(ui);
}

void UIManager::disableGameUI(UIComponent * ui)
{
	for (mViActiveUiList = mVActiveUiList.begin(); mViActiveUiList != mVActiveUiList.end(); mViActiveUiList++) {
		if (*mViActiveUiList == ui) {
			mVActiveUiList.erase(mViActiveUiList);
			break;
		}
	}
}

void UIManager::oneUIFocusMode(UIComponent * ui) {
	bOneUiFocusMode = true;
	mFocusUi = ui;
};

void UIManager::oneUIFocusModeOff() {
	bOneUiFocusMode = false;
	mFocusUi = nullptr;
};

