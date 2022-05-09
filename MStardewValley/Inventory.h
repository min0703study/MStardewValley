#pragma once
typedef struct tagInventoryOneBox {
	bool IsEmpty;
	int Count;
	const Item* Item;
	ImageGp* CountImg;
} OneBox;

class Inventory : public GameObject {
public:
	HRESULT init(int size) {
		mSize = size;
		mCurItemCount = 0;
		mItems = new OneBox[mSize];
		for (int i = 0; i < mSize; i++) {
			mItems[i].Count = 0;
			mItems[i].IsEmpty = true;
			mItems[i].CountImg = new ImageGp;
			mItems[i].CountImg->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(INVENTORY_BOX_WIDTH, INVENTORY_BOX_WIDTH * 0.4));
		}

		return S_OK;
	}

	const void render(RectF rcF, int index) const {
		if (!mItems[index].IsEmpty) {
			mItems[index].Item->renderIdle(rcF.GetLeft(), rcF.GetTop());

			if (mItems[index].Item->getItemType() != eItemType::ITP_TOOL && mItems[index].Item->getItemType() != eItemType::ITP_WEAPON) {
				mItems[index].CountImg->render(rcF.GetRight(), rcF.GetBottom(), XS_RIGHT, YS_BOTTOM);
			}
		}
	}
	const void render(float x, float y, int index, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP) const {
		if (!mItems[index].IsEmpty) {
			mItems[index].Item->getInventoryImg()->render(x, y, xStandard, yStandard);
		}
	}
	const void renderInfo(float x, float y, int index, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP) const {
		if (!mItems[index].IsEmpty) {
			if (mItems[index].Item == NULL) {
				LOG::d("?");
			}
			else {
				mItems[index].Item->getDescriptionImg()->render(x, y, xStandard, yStandard);
			}
		}
	}
	const void renderPriceInfo(float x, float y, int index) const {
		if (!mItems[index].IsEmpty) {
			mItems[index].Item->renderPriceInfo(x, y);
		}
	}

	string getItemId(int index) {
		return mItems[index].Item->getItemId();
	};

	inline const Item* getItem(int index) {
		if (mItems[index].IsEmpty) { return nullptr; }
		else { return mItems[index].Item; }
	};
	inline const int getCount(int index) {
		if (mItems[index].IsEmpty) { return -1; }
		else { return mItems[index].Count; }
	};

	eItemType getItemType(int index) {
		if (mItems[index].IsEmpty) {
			return eItemType::ITP_END;
		}
		return mItems[index].Item->getItemType();
	};
	int getIndexToId(string itemId) {
		for (int i = 0; i < mSize; i++) {
			if (mItems[i].IsEmpty) continue;
			if (mItems[i].Item->getItemId() == itemId) {
				return i;
			};
		}

		return -1;
	}
	bool isEmpty(int index) const {
		return mItems[index].IsEmpty;
	};
	int addItem(const Item* item, int count = 1) {
		for (int i = 0; i < mSize; i++) {
			if (!mItems[i].IsEmpty) continue;
			mItems[i].Item = item;
			mItems[i].IsEmpty = false;
			mItems[i].Count = count;
			mItems[i].CountImg->clear();
			mCurItemCount += 1;
			GDIPLUSMANAGER->drawTextToBitmap(mItems[i].CountImg->getBitmap(), to_wstring(mItems[i].Count), 15.0f, Color(255, 255, 255), Color(0, 0, 0), XS_RIGHT, FontStyleBold, 1);
			mItems[i].CountImg->rebuildChachedBitmap();
			return i;
		}
		return -1;
	};
	void addCount(int index, int count) {
		mItems[index].Count += count;
		mItems[index].CountImg->clear();
		GDIPLUSMANAGER->drawTextToBitmap(mItems[index].CountImg->getBitmap(), to_wstring(mItems[index].Count), 15.0f, Color(255, 255, 255), Color(0, 0, 0), XS_RIGHT, FontStyleBold, 1);
		mItems[index].CountImg->rebuildChachedBitmap();
		mCurItemCount += count;
	};

	void swap(int index1, int index2) const {
		OneBox tempBox;
		tempBox = mItems[index1];
		mItems[index1] = mItems[index2];
		mItems[index2] = tempBox;
	};

	void deleteItem(int index) {
		mItems[index].IsEmpty = true;
		mItems[index].Item = nullptr;
		mItems[index].Count = -1;
		mCurItemCount -= 1;
	};

	void useItem(int index, int count) {
		mItems[index].Count -= count;
		mItems[index].CountImg->clear();
		GDIPLUSMANAGER->drawTextToBitmap(mItems[index].CountImg->getBitmap(), to_wstring(mItems[index].Count), 15.0f, Color(255, 255, 255), Color(0, 0, 0), XS_RIGHT, FontStyleBold, 1);
		mItems[index].CountImg->rebuildChachedBitmap();
	};

	bool findItem(string itemId, OUT int& index, OUT int& count) const {
		for (int i = 0; i < mSize; i++) {
			if (mItems[i].IsEmpty) continue;
			if (mItems[i].Item->getItemId() == itemId) {
				index = i;
				count = mItems[i].Count;
				return true;
			}
		}
		return false;
	};
private:
	int mSize;
	int mCurItemCount;

	OneBox* mItems;
};
