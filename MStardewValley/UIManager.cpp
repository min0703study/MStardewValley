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
		if (mFocusUI->getRectF().Contains(_ptfMouse)) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				mFocusUI->clickDownEvent();
			}
			else {
				if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
					mFocusUI->dragEvent();
				}
				else {
					mFocusUI->mouseOverEvent();
				}
			}
		}
		else {
			if (mFocusUI->getLastEvent() != eUIEventType::ES_MOUSE_OFF) {
				mFocusUI->mouseOffEvent();
			}
		};

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			if (mFocusUI->getLastEvent() != eUIEventType::ES_CLICK_UP) {
				mFocusUI->clickUpEvent();
			}
		}

		mFocusUI->update();
	} 
	else {
		bOneUiClick = false;
		for (mViActiveUiList = mVActiveUiList.begin(); mViActiveUiList != mVActiveUiList.end(); mViActiveUiList++) {
			if (bEventCheck) {
				if ((*mViActiveUiList)->getLastEvent() == eUIEventType::ES_CLICK_DOWN || (*mViActiveUiList)->getLastEvent() == eUIEventType::ES_DRAG) {
					if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
						LOG::d(to_string(_ptfMouse.X) + " / " + to_string(_ptfMouse.Y));
						(*mViActiveUiList)->clickUpEvent();
					}

					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
						(*mViActiveUiList)->dragEvent();
					}
				}
				else {
					if ((*mViActiveUiList)->getRectF().Contains(_ptfMouse)) {
						if ((*mViActiveUiList)->getLastEvent() != eUIEventType::ES_DRAG) {
							(*mViActiveUiList)->mouseOverEvent();
						}

						if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
							(*mViActiveUiList)->clickDownEvent();
							bOneUiClick = true;
						}
					}
					else {
						if ((*mViActiveUiList)->getLastEvent() == eUIEventType::ES_MOUSE_OVER) {
							(*mViActiveUiList)->mouseOffEvent();
						}
					}
				}
			}

			(*mViActiveUiList)->updateUI();
		}

		for (mViGameUI = mVGameUI.begin(); mViGameUI != mVGameUI.end(); mViGameUI++) {
			if ((*mViGameUI)->getRectF().Contains(_ptfMouse)) {
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
					bOneUiClick = true;
					(*mViGameUI)->clickDownEvent();
				}
				else {
					if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
						(*mViGameUI)->dragEvent();
					}
					else {
						(*mViGameUI)->mouseOverEvent();
					}
				}
			}
			else {
				if ((*mViGameUI)->getLastEvent() != eUIEventType::ES_MOUSE_OFF) {
					(*mViGameUI)->mouseOffEvent();
				}
			};

			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
				if ((*mViGameUI)->getLastEvent() != eUIEventType::ES_CLICK_UP) {
					(*mViGameUI)->clickUpEvent();
				}
			}

			(*mViGameUI)->update();
		}

		if (!bOneUiClick && mMap != nullptr) {
			mMap->update();
		}
		EFFECTMANAGER->update();
	}

}

void UIManager::release(void)
{
	mVGameComponent.clear();
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

	for (mViGameUI = mVGameUI.begin(); mViGameUI != mVGameUI.end(); mViGameUI++) {
		(*mViGameUI)->render();
	}

	if (bOneUiFocusMode) {
		mFocusBg->render(0,0);
		mFocusUI->render();
	}
}

void UIManager::addComponent(UIComponent * ui)
{
	mVGameComponent.push_back(ui);
	mVActiveUiList.push_back(ui);
}

void UIManager::addGameUI(GameUI * ui)
{
	mVGameUI.push_back(ui);
}

void UIManager::addUiList(UIComponent** ui, int count)
{
	for (int i = 0; i < count; i++) {
		mVGameComponent.push_back(ui[i]);
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

////////////////////////////////////////////
void UIManager::addMap(Map* map)
{
	mMap = map;
}

void UIManager::deleteMap(Map* map)
{
	mMap = nullptr;
}
///////////////////////////////////////////

void UIManager::deleteUI(UIComponent * ui)
{
	for (mViComponent = mVGameComponent.begin(); mViComponent != mVGameComponent.end(); mViComponent++) {
		if (*mViComponent == ui) {
			mVGameComponent.erase(mViComponent);
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
	mFocustComponent = ui;
};

void UIManager::oneUIFocusModeOff() {
	bOneUiFocusMode = false;
	mFocustComponent = nullptr;
	mFocusUI = nullptr;
};

void UIManager::oneUIFocusMode(GameUI* ui) {
	bOneUiFocusMode = true;
	mFocusUI = ui;
};