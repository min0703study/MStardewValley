#pragma once
#include "GameNode.h"

class GameUI: public GameNode
{
enum class eStat
{
	NONE,
	SIZE_TO_BIG,
	SIZE_BIG,
	SIZE_TO_ORIGINAL
};

public:
	virtual HRESULT init(string id, const char * imgKey, float x, float y, bool isGdiPlus);
	void update() override;
	void render() override;
	void render(float x, float y, float width, float height);
	void render(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);
	void release() override;
	
	void sizeToBig();
	void sizeToOriginal();

	void mouseOverEvent();
	void mouseOutEvent();

	void mouseClickDownEvent();
	void mouseClickUpEvent();

	void setX(float x) {
		mX = x;
		mRc = RECT_MAKE_FUNCTION;
	};
	void setY(float y) {
		mY = y;
		mRc = RECT_MAKE_FUNCTION;
	};

	void setWidth(float width);
	void setHeight(float height);

	RECT getRECT() {
		return mRc;
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

	RECT mRc;

	float mX;
	float mY;

	float mSizeChangeWidth;
	float mSizeChangeHeight;
	float mSizeChangeRatio;

	RectF mSizeChangeRectF;

	eStat mStat;

	ImageGp* mImg;
	ImageBase* mImgB;

	bool isGdiPlus;

	string mImgKey;

	bool isMouseOver;
	bool isMouseClick;
};

class ScrollBox : public GameUI
{
public:
	HRESULT init(string id, const char * imgKey, float x, float y, bool isGdiPlus, float width, float height, GameUI* gameUI);
	void render() override;
	void update() override;

	ScrollBox() {};
	~ScrollBox() {};

private:
	RECT mVScroll;

	GameUI* mHScrollBtn;
	GameUI* mValueGameUi;

	float mFrameBorder;
};
