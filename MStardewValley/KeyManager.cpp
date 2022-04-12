#include "Stdafx.h"
#include "KeyManager.h"

HRESULT KeyManager::init(void)
{
	for (int i = 0; i < KEY_MAX; i++)
	{
		this->setKeyDown(i, false);
		this->setKeyUp(i, false);
		this->setKeyStat(i, false);
		this->setTetmpKeyDown(i, false);
		this->setTetmpKeyUp(i, false);
	}

	return S_OK;
}

void KeyManager::update()
{
	for (int i = 0; i < KEY_MAX; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000) {
			if (!getKeyStat()[i]) {
				setKeyStat(i, true);
				_keyOnceDown[i] = true;
			}
			else {
				if (_keyOnceDown[i]) {
					_keyOnceDown[i] = false;
					LOG::d(LOG_KEYMNG_TAG, "======= one down =========");
					LOG::d(LOG_KEYMNG_TAG, "one down : " + char(i));
				}
				else {
					LOG::d(LOG_KEYMNG_TAG, "stay down : " + char(i));
				}
			}
		}
		else {
			if (getKeyStat()[i]) {
				setKeyStat(i, false); 
				_keyOnceUp[i] = true;
				if (_keyOnceDown[i]) {
					_keyOnceDown[i] = false;
				}
			} else {
				if (_keyOnceUp[i]) {
					_keyOnceUp[i] = false;
					LOG::d(LOG_KEYMNG_TAG, "stay up : " + char(i));
					LOG::d(LOG_KEYMNG_TAG, "======= one up =========");
				}
			}
		}
	}
}

bool KeyManager::isToggleKey(int key)
{
	return (GetKeyState(key) & 0x0001);
}

bool KeyManager::isOnceKeyUp(int key)
{
	return this->_keyOnceUp[key];
}

bool KeyManager::isOnceKeyDown(int key)
{
	return this->_keyOnceDown[key];
}

bool KeyManager::isStayKeyDown(int key)
{
	return this->_keyStat[key];
}

bool KeyManager::isStatKeysUp(int count, ...)
{
	va_list VA_LIST;
	va_start(VA_LIST, count);

	for (int i = 0; i < count; i++)
	{
		int key = va_arg(VA_LIST, int);
		if (this->_keyStat[key]) {
			return false;
		}
	}

	va_end(VA_LIST);

	return true;
}


bool KeyManager::isAllKeysUp(int count, ...)
{
	va_list VA_LIST;
	va_start(VA_LIST, count);

	for (int i = 0; i < count; i++)
	{
		int key = va_arg(VA_LIST, int);
		if (this->_keyStat[key]) {
			return false;
		}
	}

	va_end(VA_LIST);

	return true;
}

int KeyManager::getCurKeyDown() {
	for (int i = 0; i < KEY_MAX; i++)
	{
		if (_keyOnceDown[i]) {
			return i;
		}
	}

	return -1;
}
/*

bool KeyManager::isOnceKeysUp(int count, ...)
{
	bool resultFlag = false;

	va_list VA_LIST;
	va_start(VA_LIST, count);

	for (int i = 0; i < count; i++)
	{
		int key = va_arg(VA_LIST, int);
		if (GetAsyncKeyState(key) & 0x8000)
		{
			this->setKeyUp(key, true);
		}
		else
		{
			if (this->getKeyUp()[key])
			{
				this->setKeyUp(key, false);
				resultFlag = true;
			}
		}
	}

	va_end(VA_LIST);

	return resultFlag;
}


bool KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		this->setKeyUp(key, true);
	}
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}

	return false;
}

bool KeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			//키 다운을 true로 만들고 true 를 return
			this->setKeyDown(key, true);
			return true;
		}
	} else {
		this->setKeyDown(key, false);
	};

	return false;
}
bool KeyManager::isStayKeyDown(int key)
{
	return (GetAsyncKeyState(key) & 0x8000);
}

*/
