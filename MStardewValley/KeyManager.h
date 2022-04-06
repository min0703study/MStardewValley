#pragma once
#include "SingletonBase.h"

#define KEY_MAX 256

class KeyManager : public SingletonBase<KeyManager>
{
private:
	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;

	bitset<KEY_MAX> _keyStat;
	bitset<KEY_MAX> _keyOnceUp;
	bitset<KEY_MAX> _keyOnceDown;

	int tempCount;
public:
	HRESULT init(void);
	void update();

	//bool isOnceKeysUp(int count, ...);

	bitset<KEY_MAX> getKeyUp() {
		return _keyUp;
	}

	bitset<KEY_MAX> getKeyDown() {
		return _keyDown;
	}

	bitset<KEY_MAX> getKeyStat() {
		return _keyStat;
	}

	void setKeyUp(int key, bool state) {
		_keyUp.set(key, state);
	}

	void setKeyStat(int key, bool state) {
		_keyStat.set(key, state);
	}

	void setTetmpKeyDown(int key, bool state) {
		_keyOnceDown.set(key, state);
	}

	void setTetmpKeyUp(int key, bool state) {
		_keyOnceUp.set(key, state);
	}

	void setKeyDown(int key, bool state) {
		_keyDown.set(key, state);
	}

	//bool isOnceKeyUp(int key);
	//bool isOnceKeyDown(int key);

	bool isOnceKeyUp(int key);
	bool isOnceKeyDown(int key);
	bool isStayKeyDown(int key);

	bool isStatKeysUp(int count, ...);

	//bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	KeyManager() {};
	~KeyManager() {};
};

