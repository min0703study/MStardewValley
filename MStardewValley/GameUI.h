#pragma once
#include "GameNode.h"
#include "GdiPlusFunction.h"

#define SHOW_EVENT_TIME		15.0f

class UIComponent: public GameNode
{
public:
	enum class eAniStat
	{
		NONE,
		SIZE_TO_BIG,
		SIZE_BIG,
		SIZE_TO_ORIGINAL,
		LOOP_X,
		MOVE_TO,
		FADE_IN,	
		FADE_OUT
	};

	enum class eResType
	{
		RT_BLANK,
		RT_GDI_PLUS,
		RT_IMAGE_BASE,
	};

	HRESULT init(const char* id, float x, float y, float width, float height, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP);
	HRESULT init(const char* id, float x, float y, ImageBase* img, eXStandard xPos = XS_LEFT, eYStandard yPos = YS_TOP);
	HRESULT init(const char* id, float x, float y, float width, float height, ImageBase* img, eXStandard xPos = XS_LEFT, eYStandard yPos = YS_TOP);
	HRESULT init(const char* id, float x, float y, ImageGp* img, eXStandard xPos = XS_LEFT, eYStandard yPos = YS_TOP);
	HRESULT init(const char* id, float x, float y, float width, float height, ImageGp* img, eXStandard xPos = XS_LEFT, eYStandard yPos = YS_TOP);
	
	virtual void update() override;
	virtual void render() override;
	void release() override;
	virtual void render(float x, float y);

	inline eAniStat getCurAniStat() { return mAniStat; };

	void sizeToBig(float toSizeRatio, float speed);
	void sizeToOriginal(float speed);
	void fadeIn(float speed);
	void fadeOut(float speed);
	void moveTo(eUIDirection moveDirection, float speed);
	void toLoopX(int loopFrameCount, float speed);

	virtual void updateUI();

	inline float getX() const { return mCenterX;	};
	inline float getY() const { return mCenterY;};
	inline RectF getRectF() const { return mRectF;};
	inline float getHeight() const { return mHeight; };
	inline float getWidth() const { return mWidth; };
	inline ImageGp* getImgGp() const { return mImgGp; }
	inline eUIEventType getLastEvent() const { return mLastEvent; };

	void offsetX(float x) {
		mCenterX += x;
		mRectF.Offset(x, 0);
	};

	void offsetY(float y) {
		mCenterY += y;
		mRectF.Offset(0, y);
	};

	void setX(float x, eXStandard xStandard = XS_LEFT);
	void setY(float y, eYStandard yStandard = YS_TOP);

	void setWidth(float width);
	void setHeight(float height);

	void setActiveStat(bool isActive) { bIsActive = isActive; }
	void setShowing(bool isShowing) { bIsShowing = isShowing; }

	bool isActive() { return bIsActive; }
	bool isShowing() { return bIsShowing; }

	inline string getId() { return mId; }

	function<void(UIComponent* ui)> mClickDownEvent;
	function<void(UIComponent* ui)> mClickUpEvent;
	function<void(UIComponent* ui)> mMouseOverEvent;
	function<void(UIComponent* ui)> mMouseOffEvent;
	function<void(UIComponent* ui)> mDragEvent;

	void setClickDownEvent(function<void (UIComponent* ui)> clickDownEvent) { mClickDownEvent = clickDownEvent; };
	void setClickUpEvent(function<void (UIComponent* ui)> clickUpEvent) { mClickUpEvent = clickUpEvent; };
	void setMouseOverEvent(function<void(UIComponent* ui)> mouseOver) { mMouseOverEvent = mouseOver; };
	void setMouseOffEvent(function<void(UIComponent* ui)> mouseOff) { mMouseOffEvent = mouseOff; };
	void setDragEvent(function<void(UIComponent* ui)> drageEvent) { mDragEvent = drageEvent; };

	void onClickDown() { mClickDownEvent(this); };

	virtual void clickDownEvent();
	virtual void clickUpEvent();
	virtual void mouseOverEvent();
	virtual void mouseOffEvent();
	virtual void dragEvent();
	virtual void changeUIStat(eAniStat changeStat);

	UIComponent() {};
	virtual ~UIComponent() {};
protected:
	const char* mId;

	float mCenterX;
	float mCenterY;

	float mWidth;
	float mHeight;

	RectF mRectF;

	eAniStat mAniStat;
	eUIEventType mLastEvent;

	ImageGp* mImgGp;
	ImageBase* mImgBase;

	eResType mResType;

	//Size Change
	float mToSizeRatio;
	float mSizeChangeWidth;
	float mSizeChangeHeight;
	float mSizeChangeRatio;
	float mSizeChangeSpeed;
	RectF mSizeChangeRectF;

	//Loop
	float mCurLoopX;
	int mLoopFrameCount;
	float mLoopSpeed;

	//Fade In, Out
	float mCurAlpha;
	float mFadeEffectSpeed;

	eUIDirection mMoveDirection;
	float mMoveSpeed;

	bool bIsActive;
	bool bIsShowing;
	bool bIsMouseOver;
	bool bIsMouseClick;
	bool bIsSelected;

	bool bInitSuccess;
	bool bIsMoveMode;
private:
	HRESULT init(const char* id, float x, float y, eXStandard xStandard = XS_CENTER, eYStandard yStandard = YS_CENTER);
};

class SButton : public UIComponent
{
public:
	void clickDownEvent();
	void clickUpEvent();
	void mouseOverEvent();
	void mouseOffEvent();

	void changeUIStat(eAniStat changeStat) override;

	SButton() {};
	~SButton() {};
protected:
};

class RadioButton : public UIComponent
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
	int changeSelectIndex(int index);

	inline int getCurSelectIndex() const { return mCurSelectIndex; };

	void clickDownEvent() override;

	RadioButton() {};
	~RadioButton() {};
protected:

};

class EditText : public UIComponent
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

class ScrollBox : public UIComponent
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

	void setContentClickDownEvent(function<void(UIComponent* ui)> clickDownEvent) { mContentClickDownFunc = clickDownEvent; };
	void setContentClickUpEvent(function<void(UIComponent* ui)> clickUpEvent) { mContentClickUpEvent = clickUpEvent; };
	void setContentMouseOverEvent(function<void(UIComponent* ui)> clickMouseOver) { mContentMouseOverEvent = clickMouseOver; };
	void setContentMouseOffEvent(function<void(UIComponent* ui)> clickMouseOff) { mContentMouseOffEvent = clickMouseOff; };
	void setContentDragEvent(function<void(UIComponent* ui)> drageEvent) { mContentDragEvent = drageEvent; };

	void clipingContentArea();
	void scrollToCenter();
	ImageGp* getSubImgGp() { return mSubImg; }
	bool bUseVScroll;
	bool bUseHScroll;

	void toggleShowingSubImg() { bShowingSubImg = !bShowingSubImg; }
	void moveVScroll(float moveValue);
	void moveHScroll(float moveValue);
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
	UIComponent* mVScrollBtn;

	ImageGp* mHScrollBar;
	UIComponent* mHScrollBtn;

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

	function<void(UIComponent* ui)> mContentClickDownFunc;
	function<void(UIComponent* ui)> mContentClickUpEvent;
	function<void(UIComponent* ui)> mContentMouseOverEvent;
	function<void(UIComponent* ui)> mContentMouseOffEvent;
	function<void(UIComponent* ui)> mContentDragEvent;
};

class ListBox : public ScrollBox
{
public:
	HRESULT init(const char * id, float x, float y, float width, float height, vector<ImageGp*> vItemImg, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP);
	void render() override;

	inline int getCurSelectIndex() const { return mCurSelectIndex; };

	ListBox() {};
	~ListBox() {};
private:
	vector<ImageGp*> mVItem;
	vector<RectF> mVRectF;
	int mItemCount;

	float mOneItemWidth;
	float mOneItemHeight;

	int mListItemCount;
	float tempY;

	int mCurSelectIndex;

	int getIndexToXY(float x, float y) {
		return getContentAreaRelYToY(y) / mOneItemHeight;
	}

};

class RadioList : public UIComponent
{
public:
	HRESULT init(const char * id, float x, float y, float width, float height, string question, vector<string> answerList, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP);
	void render() override;

	RectF mAbsContentArea;

	float mFrameBorderH;
	float mFrameBorderW;

	inline int getCurSelectIndex() const { return mCurSelectIndex; };

	float getContentAreaRelYToY(float y) {
		return  y - mAbsContentArea.GetTop();
	}
	int getIndexToXY(float x, float y) {
		return getContentAreaRelYToY(y) / mOneAnswerHeight;
	}

	RadioList() {};
	~RadioList() {};
private:
	vector<RectF> mVRectF;
	int mAnswerCount;
	vector<string> mVAnswerList;
	float mOneAnswerHeight;

	int mCurSelectIndex;
};

class GridList : public UIComponent
{
public:
	HRESULT init(const char * id, float x, float y, float width, float height, int xCount, int yCount, ImageGp * imgGp, float frameBorderH, float frameBorderW, eXStandard xStandard, eYStandard yStandard);
	void render() override;
	void render(float x, float y) override;
	void release() override;

	function<void(int index, RectF& rcF)> mRenderIndexFunc;
	void setRenderIndexFunc(function<void(int index, RectF& rcF)> renderIndexFunction) { mRenderIndexFunc = renderIndexFunction;  };
	int getIndexToXY(float x, float y);

	inline float getOneBoxWidth() const { return mOneBoxWidth; };
	inline const RectF& getAbsContentArea() const { return mAbsContentArea; };
	
	GridList() {};
	~GridList() {};
private:
	float mFrameBorderH;
	float mFrameBorderW;

	int mXCount;
	int mYCount;

	float mOneBoxWidth;
	float mOneBoxHeight;

	RectF mAbsContentArea;
};

///////////////////////////
class Item;

class GameUI : public GameNode
{
public:
	HRESULT init(const char* id, float x, float y, float width, float height, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP);
	virtual void update();
	virtual void render();
	virtual void release();

	bool addComponent(UIComponent * component);

	void mouseOverEvent();
	void mouseOffEvent();
	void clickDownEvent();
	void clickUpEvent();
	void dragEvent();

	inline const RectF getRectF() const { return mRectF; };
	inline const float getCenterX() const { return mCenterX; };
	inline const float getCenterY() const { return mCenterY; };
	inline const float getWidth() const { return mWidth; };
	inline const float getHeight() const { return mHeight; };

	inline eUIEventType getLastEvent() const { return mLastEventStat; };
private:
	const char* mId;

	vector<UIComponent*> mVComponent;
	vector<UIComponent*>::iterator mViComponent;

	UIComponent* mFocusComponent;

	RectF mRectF;

	float mCenterX;
	float mCenterY;

	float mWidth;
	float mHeight;

	eUIEventType mLastEventStat;
};

class Toolbar : public GameUI {
public:
	HRESULT init();
	void update(void) override;
	void render(void) override;
	void release(void) override;

	Toolbar() {};
	~Toolbar() {};
private:
	int mCurSelectIndex;
	int mCurClickIndex;
};

class AccessMenu: public GameUI {
public:
	HRESULT init();
	void update() override;
	void render() override;
	void release() override;

	AccessMenu() {};
	~AccessMenu() {};
private:
	eAccessMenu mCurActiveMenu;

	RadioButton* mRadioButton;

	//inventory
	GridList* mInventory;
	int mInvenClickIndex;
	int mInvenSelectIndex;
};

class MoneyBoard : public UIComponent {
public:
	HRESULT init(const char* id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);
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

	float mFontSize;

	RectF mAbsContentArea;
};

class SaleItemBox : public UIComponent {
public:
	HRESULT init(const char * id, vector<string> itemIdList, ImageGp * npcPortrait);

	void mouseOverEvent() override;
	void mouseOffEvent() override;
	void clickDownEvent() override;
	void clickUpEvent() override;
	void dragEvent() override;

	void update() override;
	void updateUI() override;
	void render() override;
	void release() override;

	SaleItemBox() {};
	~SaleItemBox() {};
private:
	ListBox* mListBox;

	vector<const Item*> mVSaleItem;
	vector<ImageGp*> vSaleItemImg;
	ImageGp* mNpcPortrait;
	MoneyBoard* mSaleMoneyBoard;
	GridList* mSaleInventory;

	RectF mSaleListRectF;
	RectF mNpcPortraitRectF;
	RectF mSaleMoneyBoardRectF;

	RectF mItemBox;
	RectF mItemNamePos;
	RectF mItemPricePos;
	RectF mItemImgPos;

	int mSelectInvenIndex;

	float mFontSize;
};

//확인
class Clock : public GameUI {
public:
	HRESULT init();
	void update() override;
	void render() override;
	void release() override;

	void startNewDay();
	inline int getCurPersent() { return mCurTimePersent; };

	Clock() {};
	~Clock() {};
private:
	ImageGp* mClockImg;
	ImageGp* mClockHandImg;

	vector<ImageGp*> mVClockHand;

	int mCurTimePersent;
	int mMaxTimePersent;

	int mHour;
	int mMinuate;
	int mDay;
	int mDayOfWeek;

	float mStartDayTime;
	float mElipseTime;

	string mDayOfWeekText;

	RectF mRectFTime;
	RectF mRectFDay;
	RectF mRectFHand;
};

//확인
class EnergePGBar : public GameUI {
public:
	HRESULT init();

	void update() override;
	void render() override;
	void release() override;

	EnergePGBar() {};
	~EnergePGBar() {};
private:
	ImageGp* mPGBarFront;
	ImageGp* mPGBarBack;

	RectF mRectFValueArea;

	float mFrameBorderT;
	float mFrameBorderB;
	float mFrameBorderW;

	float mCurPlayerEnergy;

	float mValueHeight;
	RECT mValueRECT;

	COLORREF mCurValueColor;

	COLORREF mSufficeColor;
	COLORREF mNormalColor;
	COLORREF mLakeColor;
};

//확인
class HPPGBar : public GameUI {
public:
	HRESULT init();
	void update() override;
	void render() override;
	void release() override;

	HPPGBar() {};
	~HPPGBar() {};
private:
	RectF mRectFValueArea;
	
	ImageGp* mPGBarFront;
	ImageGp* mPGBarBack;

	float mFrameBorderT;
	float mFrameBorderB;
	float mFrameBorderW;
	float mCurPlayerHP;
	
	float mValueHeight;
	RECT mValueRECT;

	COLORREF mCurValueColor;

	COLORREF mSufficeColor;
	COLORREF mNormalColor;
	COLORREF mLakeColor;
};


class QuestionBox : public GameUI {
public:
	HRESULT init();

	void update() override;
	void render() override;
	void release() override;

	RadioList* mQuestion;

	QuestionBox() {};
	~QuestionBox() {};
private:
};

class EventBox : public GameUI {
public:
	typedef struct tagOneEvent {
		ImageGp* EventBackImg;
		ImageGp* EventImg;
		BYTE Alpha;
		float CurEventCount;
		
		tagOneEvent() {};
		tagOneEvent(ImageGp* eventBackImg, ImageGp* eventImg): EventBackImg(eventBackImg), EventImg(eventImg){

		};
	} OneEvent;
public:
	HRESULT init(const char * id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);
	void update(void) override;
	void render(void) override;
	void release(void) override;

	void addPickUpItemEvent(string itemId);
	void addHpUpEvent(int hp, int energy);

	EventBox() {};
	~EventBox() {};
private:
	queue<tagOneEvent>		mEventQueue;
	stack<tagOneEvent>		mEventStack;
	
	RectF mImageArea;
	RectF mTextArea;

	float mOneEventHegith;
};