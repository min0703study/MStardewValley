#pragma once
#include "GameNode.h"
#include "GdiPlusFunction.h"
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

	enum class eResType
	{
		RT_NONE,
		RT_GDI_PLUS,
		RT_IMAGE_BASE,
	};

	HRESULT init(const char* id, float x, float y, float width, float height);
	HRESULT init(const char* id, float x, float y, float width, float height, ImageBase* img, eXStandard xPos = XS_CENTER, eYStandard yPos = YS_CENTER);
	HRESULT init(const char* id, float x, float y, ImageBase* img, eXStandard xPos = XS_CENTER, eYStandard yPos = YS_CENTER);
	HRESULT init(const char* id, float x, float y, float width, float height, ImageGp* img, eXStandard xPos = XS_CENTER, eYStandard yPos = YS_CENTER);
	HRESULT init(const char* id, float x, float y, ImageGp* img, eXStandard xPos = XS_CENTER, eYStandard yPos = YS_CENTER);

	void sizeToBig(float toSizeRatio);
	void sizeToOriginal();

	virtual void update();
	virtual void render();

	void render(float x, float y, float width, float height);
	void render(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);
	
	void release() override;


	float getX() {
		return mCenterX;
	};
	float getY() {
		return mCenterY;
	};

	void offsetX(float x) {
		mCenterX += x;
		mRECT = RECT_MAKE_FUNCTION;
		mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
	};

	void setX(float x) {
		mCenterX = x;
		mRECT = RECT_MAKE_FUNCTION;
		mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
	};
	void setY(float y) {
		mCenterY = y;
		mRECT = RECT_MAKE_FUNCTION;
		mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
	};

	void setWidth(float width);
	void setHeight(float height);

	RECT getRECT() {
		return mRECT;
	};

	RectF getRectF() {
		return mRectF;
	};

	float getHeight() {
		return mHeight;
	};

	float getWidth() {
		return mWidth;
	};

	ImageGp* getImgGp() {
		return mImgGp;
	}

	GameUI() {};
	virtual ~GameUI() {};

protected:
	const char* mId;

	float mCenterX;
	float mCenterY;

	float mWidth;
	float mHeight;

	RECT mRECT;
	RectF mRectF;

	eStat mStat;

	float mToSizeRatio;
	float mSizeChangeWidth;
	float mSizeChangeHeight;
	float mSizeChangeRatio;

	RectF mSizeChangeRectF;

	ImageGp* mImgGp;
	ImageBase* mImgBase;

	eResType mResType;

	bool bIsMouseOver;
	bool bIsMouseClick;
	bool bIsSelected;

	bool isInitSuccess;
private:
	HRESULT init(const char* id, float x, float y, eXStandard xStandard = XS_CENTER, eYStandard yStandard = YS_CENTER);
};

class SButton : public GameUI
{
public:
	bool isSelected() { return bIsSelected; }
	
	void clickDownEvent();
	void clickUpEvent();

	void update();
	void render();
protected:
	ImageGp* mSelectedImg;
};

class ScrollBox : public GameUI
{
public:
	HRESULT init(const char* id, float x, float y, float width, float height, GameUI* gameUI, eXStandard xStandard = XS_CENTER, eYStandard yStandard = YS_CENTER);

	void render();
	void update();

	void clickDownEvent();
	void clickUpEvent();

	void mouseOverEvent();
	void mouseOffEvent();

	RECT getValueRECT() {
		return mValueRECT;
	};

	float getValueRelXToX(float x) {
		return x - mContentArea.GetLeft();
	}

	float getValueRelYToY(float y) {
		return (mHScrollBtn->getRectF().GetTop() - mFrameBorderH) + y - mContentArea.GetTop();
	}

	ScrollBox() {};
	~ScrollBox() {};
private:
	RECT mVScroll;
	RECT mValueRECT;

	GameUI* mHScrollBar;
	GameUI* mHScrollBtn;
	GameUI* mContent;

	RectF mContentArea;

	float mFrameBorderH;
	float mFrameBorderW;

	bool isDrag;
	float mHpt;
};

class MapWork : public GameUI
{
public:
	HRESULT init(const char * id, float x, float y, int xCount, int yCount, int tileSize, eXStandard xStandard, eYStandard yStandard);
	
	vector<RECT> mVTileRECT;
	vector<RECT>::iterator miVTileRECT;

	void render();
	void update();

	MapWork() {};
	~MapWork() {};
private:


};