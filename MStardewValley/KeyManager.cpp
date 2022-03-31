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
	tempCount++;
	for (int i = 0; i < KEY_MAX; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000) {
			if (!getKeyStat()[i]) {
				setKeyStat(i, true);
				_keyTempDown[i] = true;
			}
			else {
				_keyTempDown[i] = false;
			}
		}
		else {
			if (getKeyStat()[i]) {
				setKeyStat(i, false);
				_keyTempUp[i] = true;
			}
			else {
				_keyTempUp[i] = false;
			}
		}
	}
}

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

bool KeyManager::isOnceTempKeyUp(int key)
{
	return this->_keyTempUp[key];
}

bool KeyManager::isOnceTempKeyDown(int key)
{
	return this->_keyTempDown[key];
}

bool KeyManager::isStayTempKeyDown(int key)
{
	return this->_keyStat[key];
}

bool KeyManager::isOnceTempKeysUp(int count, ...)
{
	va_list VA_LIST;
	va_start(VA_LIST, count);

	for (int i = 0; i < count; i++)
	{
		int key = va_arg(VA_LIST, int);
		if (this->_keyTempUp[key]) {
			return true;
		}
	}

	va_end(VA_LIST);

	return false;
}

bool KeyManager::isStayKeyDown(int key)
{
	return (GetAsyncKeyState(key) & 0x8000);
}

bool KeyManager::isToggleKey(int key)
{
	return (GetKeyState(key) & 0x0001);
}
