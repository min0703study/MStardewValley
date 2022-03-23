#pragma once
#include "GameNode.h"

#define SIZE_CHANGE_SPEED		2.0f

class GameUI: public GameNode
{
public:
	enum class eStat
	{
		NONE,
		SIZE_TO_BIG,
		SIZE_BIG,
		SIZE_TO_ORIGINAL
	};

	HRESULT init(const char* id, float x, float y, float width, float height, ImageBase* img);
	HRESULT init(const char* id, float x, float y, ImageBase* img);
	HRESULT init(const char* id, float x, float y, float width, float height, ImageGp* img);
	HRESULT init(const char* id, float x, float y, ImageGp* img);

	void sizeToBig(float toSizeRatio);
	void sizeToOriginal();

	virtual void update();
	virtual void render();

	void render(float x, float y, float width, float height);
	void render(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);
	
	void release() override;


	float getX() {
		return mX;
	};
	float getY() {
		return mY;
	};

	void offsetX(float x) {
		mX += x;
		mRECT = RECT_MAKE_FUNCTION;
	};

	void setX(float x) {
		mX = x;
		mRECT = RECT_MAKE_FUNCTION;
	};
	void setY(float y) {
		mY = y;
		mRECT = RECT_MAKE_FUNCTION;
	};

	void setWidth(float width);
	void setHeight(float height);

	RECT getRECT() {
		return mRECT;
	};

	float getHeight() {
		return mHeight;
	};

	float getWidth() {
		return mWidth;
	};

	GameUI() {};
	virtual ~GameUI() {};

protected:
	const char* mId;

	float mWidth;
	float mHeight;

	RECT mRECT;

	float mX;
	float mY;

	float mToSizeRatio;
	float mSizeChangeWidth;
	float mSizeChangeHeight;
	float mSizeChangeRatio;

	RectF mSizeChangeRectF;

	eStat mStat;

	ImageGp* mImgGp;
	ImageBase* mImgBase;

	bool isGdiPlus;

	bool isMouseOver;
	bool isMouseClick;

	bool isInitSuccess;
};

class SButton : public GameUI
{
public:
	HRESULT init(const char* id, float x, float y, float width, float height, ImageBase* img);
	HRESULT init(const char* id, float x, float y, ImageBase* img);
	HRESULT init(const char* id, float x, float y, float width, float height, ImageGp* img);
	HRESULT init(const char* id, float x, float y, ImageGp* img);

	bool isSelected() { return mIsSelected; }
	
	void clickDownEvent();
	void clickUpEvent();

	void update();
	void render();
protected:
	bool mIsSelected;
	ImageGp* mSelectedImg;
};

class ScrollBox : public GameUI
{
public:
	HRESULT init(const char* id, float x, float y, float width, float height, GameUI* gameUI);

	void render();
	void update();


	RECT getValueRECT() {
		return mValueRECT;
	};

	RECT getValueRelRECT() {
		float relY = (mHScrollBtnY - mHScrollBarY) + mValueGameUi->getY();
		float relX = (mHScrollBtnX - mHScrollBarX) + mValueGameUi->getX();

		return RectMake(relX, relY, mValueWidth, mValueHeight);
	};

	float getValueRelX() {
		return (mHScrollBtnX - mHScrollBarX) + mValueGameUi->getX();
	}

	float getValueRelY() {
		return (mHScrollBtnY - mHScrollBarY) + mValueGameUi->getY();
	}

	ScrollBox() {};
	~ScrollBox() {};
private:
	RECT mVScroll;
	RECT mValueRECT;

	GameUI* mHScrollBar;
	GameUI* mHScrollBtn;
	GameUI* mValueGameUi;

	float mFrameBorderH;
	float mFrameBorderW;

	float mValueX;
	float mValueY;

	float mValueWidth;
	float mValueHeight;

	float mHScrollBarX;
	float mHScrollBarY;

	float mHScrollBarW;
	float mHScrollBarH;

	float mHScrollBtnX;
	float mHScrollBtnY;

	float mHScrollBtnW;
	float mHScrollBtnH;

	bool isDrag;
	float mHpt;
};
