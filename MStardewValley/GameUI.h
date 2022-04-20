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

	enum class eEventStat
	{
		ES_NONE,
		ES_CLICK_DOWN,
		ES_CLICK_UP,
		ES_DRAG,
		ES_MOUSE_OVER,
		ES_MOUSE_OFF
	};

	HRESULT init(const char* id, float x, float y, float width, float height, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP);
	HRESULT init(const char* id, float x, float y, ImageBase* img, eXStandard xPos = XS_LEFT, eYStandard yPos = YS_TOP);
	HRESULT init(const char* id, float x, float y, float width, float height, ImageBase* img, eXStandard xPos = XS_LEFT, eYStandard yPos = YS_TOP);
	HRESULT init(const char* id, float x, float y, ImageGp* img, eXStandard xPos = XS_LEFT, eYStandard yPos = YS_TOP);
	HRESULT init(const char* id, float x, float y, float width, float height, ImageGp* img, eXStandard xPos = XS_LEFT, eYStandard yPos = YS_TOP);

	void sizeToBig(float toSizeRatio);
	void sizeToOriginal();
	void toLoopX(int loopFrameCount);

	virtual void update();
	virtual void updateUI();

	virtual void render();
	virtual void render(float x, float y);
	void release() override;

	float getX() {
		return mCenterX;
	};

	float getY() {
		return mCenterY;
	};

	inline eEventStat getLastEvent() { return mLastEvent; };

	void offsetX(float x) {
		mCenterX += x;
		mRECT = RECT_MAKE_FUNCTION;
		mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
	};

	void offsetY(float y) {
		mCenterY += y;
		mRECT = RECT_MAKE_FUNCTION;
		mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
	};

	void setX(float x, eXStandard xStandard = XS_LEFT);
	void setY(float y, eYStandard yStandard = YS_TOP);

	void setWidth(float width);
	void setHeight(float height);

	void setActiveStat(bool isActive) { bIsActive = isActive; }
	bool isActive() { return bIsActive; }

	function<void(GameUI* ui)> mClickDownEvent;
	function<void(GameUI* ui)> mClickUpEvent;
	function<void(GameUI* ui)> mMouseOverEvent;
	function<void(GameUI* ui)> mMouseOffEvent;
	function<void(GameUI* ui)> mDragEvent;

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

	void setClickDownEvent(function<void (GameUI* ui)> clickDownEvent) { mClickDownEvent = clickDownEvent; };
	void setClickUpEvent(function<void (GameUI* ui)> clickUpEvent) { mClickUpEvent = clickUpEvent; };
	void setMouseOverEvent(function<void(GameUI* ui)> clickMouseOver) { mMouseOverEvent = clickMouseOver; };
	void setMouseOffEvent(function<void(GameUI* ui)> clickMouseOff) { mMouseOffEvent = clickMouseOff; };
	void setDragEvent(function<void(GameUI* ui)> drageEvent) { mDragEvent = drageEvent; };

	virtual void clickDownEvent();
	virtual void clickUpEvent();
	virtual void mouseOverEvent();
	virtual void mouseOffEvent();
	virtual void dragEvent();

	virtual void changeUIStat(eStat changeStat);
	
	eEventStat mLastEvent;

	
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

	bool bIsActive;
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
	void clickDownEvent();
	void clickUpEvent();
	void mouseOverEvent();
	void mouseOffEvent();

	void changeUIStat(eStat changeStat) override;

	SButton() {};
	~SButton() {};
protected:
};

class RadioButton : public GameUI
{
public:
	HRESULT init(float x, float y, float btnWidth, float btnHeight, ImageGp** btnList, int btnCount, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP);

	int mCurSelectIndex;
	bool bSelectNothing;

	ImageGp** mBtnList;
	int mBtnCount;

	float mOneBtnWidth;
	float mOneBtnHeight;

	void render(void) override;

	int changeSelectIndex();

	RadioButton() {};
	~RadioButton() {};
protected:

};

class EditText : public GameUI
{
public:
	HRESULT init(const char* id, float x, float y, float width, float height, eXStandard xPos = XS_LEFT, eYStandard yPos = YS_TOP);

	void update();
	void render();

	bool bIsActiveEditMode;
	string mCurInputText;

	RectF mTextArea;
	
	float mFrameBorderW;
	float mFrameBorderH;

	string getInputText() { return mCurInputText; }
	void changeEditMode(bool isOn) { bIsActiveEditMode = isOn; }

	EditText() {};
	~EditText() {};
protected:
	ImageGp* mSelectedImg;
};

class ScrollBox : public GameUI
{
public:
	HRESULT init(const char* id, float x, float y, float width, float height, ImageGp* contentImg, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP, bool useVScroll = true, bool useHScroll = true);

	virtual void render();
	void update();

	void clickDownEvent() override;
	void clickUpEvent() override;
	void dragEvent() override;
	void mouseOverEvent() override;
	void mouseOffEvent() override;

	void setContentClickDownEvent(function<void(GameUI* ui)> clickDownEvent) { mContentClickDownFunc = clickDownEvent; };
	void setContentClickUpEvent(function<void(GameUI* ui)> clickUpEvent) { mContentClickUpEvent = clickUpEvent; };
	void setContentMouseOverEvent(function<void(GameUI* ui)> clickMouseOver) { mContentMouseOverEvent = clickMouseOver; };
	void setContentMouseOffEvent(function<void(GameUI* ui)> clickMouseOff) { mContentMouseOffEvent = clickMouseOff; };
	void setContentDragEvent(function<void(GameUI* ui)> drageEvent) { mContentDragEvent = drageEvent; };

	void clipingContentArea();
	void scrollToCenter();
	ImageGp* getSubImgGp() { return mSubImg; }
	bool bUseVScroll;
	bool bUseHScroll;

	void toggleShowingSubImg() { bShowingSubImg = !bShowingSubImg; }

	int tempX() {
		return (int)(mHScrollMoveDistance) % 70;
	}
	int tempY() {
		return (int)(mVScrollMoveDistance) % 70;
	}

	float getContentAreaRelX() {
		return mHScrollMoveDistance * mScrollRatioW;
	}

	float getContentAreaRelY() {
		return mVScrollMoveDistance * mScrollRatioH;
	}

	float getContentAreaRelXToX(float x) {
		return (mHScrollMoveDistance * mScrollRatioW) + x - mAbsContentArea.GetLeft();
	}

	float getContentAreaRelYToY(float y) {
		return (mVScrollMoveDistance * mScrollRatioH) + y - mAbsContentArea.GetTop();
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

	RectF getContentAreaRelRectF() {
		return mRelContentArea;
	};

	inline ImageGp* getContent() { return mContentImg; }
	
	void changeContent(ImageGp* changeImg);

	ScrollBox() {};
	~ScrollBox() {};
private:
	ImageGp* mVScrollBar;
	GameUI* mVScrollBtn;

	ImageGp* mHScrollBar;
	GameUI* mHScrollBtn;

	ImageGp* mContentImg;
	ImageGp* mSubImg;

	RectF mAbsContentArea;
	RectF mRelContentArea;

	float mFrameBorderH;
	float mFrameBorderW;

	float mVScrollMoveDistance;
	float mHScrollMoveDistance;

	float mVScrollPtDistance;
	float mHScrollPtDistance;

	int mScrollRatioW;
	int mScrollRatioH;

	float mVScrollStartX;
	float mVScrollStartY;
	float mVScrollWidth;
	float mVScrollHeight;

	float mHScrollStartX;
	float mHScrollStartY;
	float mHScrollWidth;
	float mHScrollHeight;

	string mCurActiveUI;
	bool bShowingSubImg;

	function<void(GameUI* ui)> mContentClickDownFunc;
	function<void(GameUI* ui)> mContentClickUpEvent;
	function<void(GameUI* ui)> mContentMouseOverEvent;
	function<void(GameUI* ui)> mContentMouseOffEvent;
	function<void(GameUI* ui)> mContentDragEvent;
};

class Toolbar : public GameUI {
public:
	HRESULT init(const char* id, float x, float y, float width, float height, ImageGp* imgGp);
	void render(void) override;
	int changeSelectItem(int index);

	bool isCollisionContentBox(PointF ptF);
	int getIndexToPtF(PointF ptF);

	Toolbar() {};
	~Toolbar() {};
private:
	GameUI* mSelectBox;
	RectF mAbsContentArea;

	int mCurSelectIndex;
	int mMaxIndex;

	float mFrameBorderH;
	float mFrameBorderW;

	RectF mItemRectF[MAX_TOOLBAR_INDEX];
};

class ListBox : public ScrollBox
{
public:
	HRESULT init(const char * id, float x, float y, float width, float height, vector<ImageGp*> vItemImg, eXStandard xStandard, eYStandard yStandard);
	void render() override;
	
	int getIndexToXY (float x, float y) {
		return getContentAreaRelYToY(y) / mOneItemHeight;
	}

	ListBox() {};
	~ListBox() {};
private:
	vector<ImageGp*> mVItem;
	int mItemCount;

	float mOneItemWidth;
	float mOneItemHeight;

	int mListItemCount;
	float tempY;
};

class GridList : public GameUI
{
public:
	HRESULT init(const char * id, float x, float y, float width, float height, int xCount, int yCount, ImageGp * imgGp, eXStandard xStandard, eYStandard yStandard);
	void render() override;
	void render(float x, float y) override;

	function<void(int index, RectF& rcF)> mRenderIndexFunc;
	void setRenderIndexFunc(function<void(int index, RectF& rcF)> renderIndexFunction) { mRenderIndexFunc = renderIndexFunction;  };
	int getIndexToPtF(PointF ptF);
	GridList() {};
	~GridList() {};
private:
	float mFrameBorderH;
	float mFrameBorderW;

	int mXCount;
	int mYCount;

	RectF mAbsContentArea;
	RectF** mItemRectF;

};

///////////////////////////

class AccessMenu: public GameUI {
public:
	HRESULT init(const char* id, float x, float y, float width, float height);
	void update() override;
	void render() override;
	void release() override;

	int getIndexToPtF(PointF ptF);

	AccessMenu() {};
	~AccessMenu() {};
private:
	RadioButton* mRadioButton;
	GameUI* mMenuGroup[eAccessMenu::AM_END];
};

class MoneyBoard : public GameUI {
public:
	HRESULT init(const char* id, float x, float y, float width, float height);
	void update() override;
	void updateUI() override;
	void render() override;
	void release() override;

	MoneyBoard() {};
	~MoneyBoard() {};
private:
	int mCurMoeny;
	ImageGp* mMoneyImgGp;

	float mFrameBorderT;
	float mFrameBorderL;
	float mFrameBorderR;
	float mFrameBorderB;

	RectF mAbsContentArea;
};