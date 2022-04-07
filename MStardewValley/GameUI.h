#pragma once
#include "GameNode.h"
#include "GdiPlusFunction.h"

#define SIZE_CHANGE_SPEED		2.0f
#define LOOP_X_SPEED			0.005f

class GameUI: public GameNode
{
public:
	enum class eStat
	{
		NONE,
		SIZE_TO_BIG,
		SIZE_BIG,
		SIZE_TO_ORIGINAL,
		LOOP_X
	};

	enum class eResType
	{
		RT_BLANK,
		RT_GDI_PLUS,
		RT_IMAGE_BASE,
	};

	HRESULT init(const char* id, float x, float y, float width, float height, eXStandard xPos = XS_CENTER, eYStandard yPos = YS_CENTER);
	HRESULT init(const char* id, float x, float y, ImageBase* img, eXStandard xPos = XS_CENTER, eYStandard yPos = YS_CENTER);
	HRESULT init(const char* id, float x, float y, float width, float height, ImageBase* img, eXStandard xPos = XS_CENTER, eYStandard yPos = YS_CENTER);
	HRESULT init(const char* id, float x, float y, ImageGp* img, eXStandard xPos = XS_CENTER, eYStandard yPos = YS_CENTER);
	HRESULT init(const char* id, float x, float y, float width, float height, ImageGp* img, eXStandard xPos = XS_CENTER, eYStandard yPos = YS_CENTER);

	void sizeToBig(float toSizeRatio);
	void sizeToOriginal();
	void toLoopX(int loopFrameCount);

	virtual void update();
	virtual void render();

	void render(float x, float y);
	
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

	void setX(float x, eXStandard xStandard = XS_CENTER);
	void setY(float y, eYStandard yStandard = YS_CENTER);

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

	float mCurLoopX;
	int mLoopFrameCount;

	RectF mSizeChangeRectF;

	ImageGp* mImgGp;
	ImageBase* mImgBase;

	eResType mResType;

	bool bIsMouseOver;
	bool bIsMouseClick;
	bool bIsSelected;

	bool bInitSuccess;

	bool bIsMoveMode;
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

	SButton() {};
	~SButton() {};
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

	void clipingContentArea();
	void scrollToCenter();

	int tempX() {
		return (int)(mHScrollMoveDistance ) % 70;
	}
	int tempY() {
		return (int)(mVScrollMoveDistance) % 70;
	}

	float getContentAreaRelXToX(float x) {
		return (mHScrollMoveDistance * mScrollRatio) + x - mAbsContentArea.GetLeft();
	}

	float getContentAreaRelYToY(float y) {
		return (mVScrollMoveDistance * mScrollRatio) + y - mAbsContentArea.GetTop();
	}

	float getContentAreaAbsXToX(float x) {
		return x - mAbsContentArea.GetLeft();
	}

	float getContentAreaAbsYToY(float y) {
		return y - mAbsContentArea.GetTop();
	}

	RectF getContentAreaRectF() {
		return mAbsContentArea;
	};

	bool isCollisionScrollBar(PointF ptF);
	bool isCollisionContentBox(PointF ptF);

	ScrollBox() {};
	~ScrollBox() {};
private:
	GameUI* mVScrollBar;
	GameUI* mVScrollBtn;
	
	GameUI* mHScrollBar;
	GameUI* mHScrollBtn;

	GameUI* mContent;
	RectF mAbsContentArea;

	float mFrameBorderH;
	float mFrameBorderW;

	bool isVScrollDrag;
	bool isHScrollDrag;

	float mVScrollMoveDistance;
	float mHScrollMoveDistance;

	float mVScrollPtDistance;
	float mHScrollPtDistance;

	int mScrollRatio;
};

class Toolbar : public GameUI {
public:
	typedef struct tagToolbarInfo {
		int ItemId;
		int Count;
		bool IsNone;

		ImageGp* ItemImg;
		ImageGp* ItemInfoImg;

		RectF ImgRectF;
	} ToolbarInfo;

	HRESULT init(const char* id, float x, float y, float width, float height, ImageGp* imgGp, eXStandard xStandard = XS_CENTER, eYStandard yStandard = YS_CENTER);
	HRESULT init(const char* id, float x, float y, ImageGp* img, eXStandard xPos = XS_CENTER, eYStandard yPos = YS_CENTER);
	
	void render(void) override;

	void addItem(string ItemId, int index, int count = 1);

	int changeSelectItem(int index);

	bool isCollisionContentBox(PointF ptF);

	int getIndexToPtF(PointF ptF);

	Toolbar() {};
	~Toolbar() {};
private:
	ToolbarInfo mItems[MAX_TOOLBAR_INDEX];

	GameUI* mSelectBox;
	RectF mAbsContentArea;

	int mCurSelectIndex;
	int mMaxIndex;

	float mFrameBorderH;
	float mFrameBorderW;

};