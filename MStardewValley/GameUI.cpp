#include "Stdafx.h"
#include "GameUI.h"

//private init (common)
HRESULT GameUI::init(const char * id, float x, float y, eXStandard xStandard, eYStandard yStandard)
{
	switch (xStandard) {
	case XS_LEFT:
		x = x + (mWidth / 2.0f);
		break;
	case XS_RIGHT:
		x = x - (mWidth / 2.0f);
		break;
	case XS_CENTER:
		break;
	}

	switch (yStandard) {
	case YS_TOP:
		y = y + (mHeight / 2.0f);
		break;
	case YS_BOTTOM:
		y = y - (mHeight / 2.0f);
		break;
	case YS_CENTER:
		break;
	}

	mCenterX = x;
	mCenterY = y;

	mStat = eStat::NONE;

	mRECT = RectMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
	mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);

	bIsMouseOver = false;
	bIsMouseClick = false;
	bIsSelected = false;

	bInitSuccess = true;
	bIsMoveMode = false;

	mId = id;
	
	mClickDownEvent = NULL;
	mClickUpEvent = NULL;
	mMouseOverEvent = NULL;
	mMouseOffEvent = NULL;
	mDragEvent = NULL;

	return S_OK;
}

//public init
HRESULT GameUI::init(const char * id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	LOG::d((string)id + " : init 생성");
	mResType = eResType::RT_BLANK;
	
	mImgGp = new ImageGp();
	mImgGp->init(getMemDc(), width, height);

	mWidth = width;
	mHeight = height;

	return init(id, x, y, xStandard, yStandard);
}

HRESULT GameUI::init(const char* id, float centerX, float centerY, float width, float height, ImageBase * img, eXStandard xStandard, eYStandard yStandard)
{
	if (img == nullptr) {
		bInitSuccess = false;
		LOG::d(LOG_GAME_UI_TAG, (string)id + " - (init 실패) 이미지 null");
		return E_FAIL;
	}

	mResType = eResType::RT_IMAGE_BASE;

	mImgBase = img;

	mWidth = mImgBase->getFloatWidth();
	mHeight = mImgBase->getFloatHeight();

	 return init(id, centerX, centerY, xStandard, yStandard);
}

HRESULT GameUI::init(const char* id, float x, float y, ImageBase * img, eXStandard xStandard, eYStandard yStandard)
{
	if (img == nullptr) {
		bInitSuccess = false;
		LOG::d(LOG_GAME_UI_TAG, (string)id + " - (init 실패) 이미지 null");
		return E_FAIL;
	}

	mResType = eResType::RT_IMAGE_BASE;

	mImgBase = img;

	mWidth = mImgBase->getFloatWidth();
	mHeight = mImgBase->getFloatHeight();

	return init(id, x, y, xStandard, yStandard);
}

HRESULT GameUI::init(const char* id, float centerX, float centerY, float width, float height, ImageGp * img, eXStandard xStandard, eYStandard yStandard)
{
	if (img == nullptr) {
		bInitSuccess = false;
		LOG::d(LOG_GAME_UI_TAG, (string)id + " - (init 실패) 이미지 null");
		return E_FAIL;
	}

	mResType = eResType::RT_GDI_PLUS;

	mImgGp = img;

	if (img->getWidth() != width || img->getHeight() != height) {
		img->setSize(width, height);
	}

	mWidth = width;
	mHeight = height;

	return init(id, centerX, centerY, xStandard, yStandard);
}

HRESULT GameUI::init(const char* id, float x, float y, ImageGp * img, eXStandard xStandard, eYStandard yStandard)
{
	if (img == nullptr) {
		bInitSuccess = false;
		LOG::d(LOG_GAME_UI_TAG, (string)id + " - (init 실패) 이미지 null");
		return E_FAIL;
	}

	mResType = eResType::RT_GDI_PLUS;

	mImgGp = img;

	mWidth = img->getWidth();
	mHeight = img->getHeight();

	return init(id, x, y, xStandard, yStandard);
}

void GameUI::sizeToBig(float toSizeRatio)
{
	if (mStat != eStat::SIZE_TO_BIG && mStat != eStat::SIZE_BIG) {
		changeUIStat(eStat::SIZE_TO_BIG);

		mToSizeRatio = toSizeRatio;

		mSizeChangeWidth = mWidth;
		mSizeChangeHeight = mHeight;
		mSizeChangeRatio = mSizeChangeWidth / mSizeChangeHeight;
	};
}

void GameUI::sizeToOriginal()
{
	if (mStat != eStat::SIZE_TO_ORIGINAL && mStat != eStat::NONE) {
		changeUIStat(eStat::SIZE_TO_ORIGINAL);
	}
}

void GameUI::toLoopX(int loopFrameCount)
{
	if (mStat != eStat::LOOP_X) {
		mStat = eStat::LOOP_X;
		mCurLoopX = 0;
		mLoopFrameCount = loopFrameCount;
		mImgGp->startLoopX(loopFrameCount);
	}
}

void GameUI::update()
{
}

void GameUI::updateUI()
{
	if (!bInitSuccess) return;

	switch (mStat) {
	case eStat::SIZE_TO_BIG:
		if (mSizeChangeWidth > mWidth * mToSizeRatio) {
			changeUIStat(eStat::SIZE_BIG);
		}
		else {
			mSizeChangeWidth = mSizeChangeWidth + SIZE_CHANGE_SPEED;
			mSizeChangeHeight = mSizeChangeHeight + (SIZE_CHANGE_SPEED / mSizeChangeRatio);
			mSizeChangeRectF = RectFMakeCenter(mCenterX, mCenterY, mSizeChangeWidth, mSizeChangeHeight);
		}
		break;
	case  eStat::SIZE_TO_ORIGINAL:
		if (mSizeChangeWidth < mWidth) {
			changeUIStat(eStat::NONE);
		}
		else {
			mSizeChangeWidth = mSizeChangeWidth - SIZE_CHANGE_SPEED;
			mSizeChangeHeight = mSizeChangeHeight - (SIZE_CHANGE_SPEED / mSizeChangeRatio);
			mSizeChangeRectF = RectFMakeCenter(mCenterX, mCenterY, mSizeChangeWidth, mSizeChangeHeight);
		}
		break;
	case eStat::LOOP_X:
		mCurLoopX += LOOP_X_SPEED;
		if (mCurLoopX >= mLoopFrameCount) mCurLoopX = 0;
		break;
	default:
		//!DO NOTHING
		break;
	}
}

void GameUI::render()
{
	if (!bInitSuccess) return;
	switch (mResType) {
	case eResType::RT_GDI_PLUS:
		switch (mStat) {
		case eStat::SIZE_TO_BIG: case eStat::SIZE_BIG: case eStat::SIZE_TO_ORIGINAL:
			mImgGp->render(getMemDc(), mSizeChangeRectF);
			break;
		case eStat::NONE:
			mImgGp->render(getMemDc(), mRectF.GetLeft(), mRectF.GetTop());
			break;
		case eStat::LOOP_X:
			mImgGp->loopRender(getMemDc(), mRectF.GetLeft(), mRectF.GetTop(), static_cast<int>(mCurLoopX));
			break;
		default:
			//!DO NOTHING
			break;
		}
		break;
	case eResType::RT_IMAGE_BASE:
		mImgBase->render(getMemDc(), static_cast<int>(mCenterX), static_cast<int>(mCenterY));
		break;
	case eResType::RT_BLANK:
		break;
	default:
		break;

	}
}

void GameUI::render(float x, float y)
{
	if (!bInitSuccess) return;
	switch (mResType) {
	case eResType::RT_GDI_PLUS:
		mImgGp->render(getMemDc(), x, y);
		break;
	case eResType::RT_BLANK:
		mImgGp->render(getMemDc(), x, y);
		break;
	case eResType::RT_IMAGE_BASE:
		mImgBase->render(getMemDc(), static_cast<int>(x), static_cast<int>(y));
		break;
	default:
		break;

	}
}

void GameUI::release()
{
	if (!bInitSuccess) return;
	mImgGp->release();
	SAFE_DELETE(mImgGp);
}

void GameUI::setX(float x, eXStandard xStandard)
{
	switch (xStandard) {
	case XS_LEFT:
		x = x + (mWidth / 2.0f);
		break;
	case XS_RIGHT:
		x = x - (mWidth / 2.0f);
		break;
	case XS_CENTER:
		break;
	}

	mCenterX = x;
	mRECT = RECT_MAKE_FUNCTION;
	mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
}

void GameUI::setY(float y, eYStandard yStandard)
{
	switch (yStandard) {
	case YS_TOP:
		y = y + (mHeight / 2.0f);
		break;
	case YS_BOTTOM:
		y = y - (mHeight / 2.0f);
		break;
	case YS_CENTER:
		break;
	}

	mCenterY = y;
	mRECT = RECT_MAKE_FUNCTION;
	mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
}

void GameUI::setWidth(float width)
{
	if (mResType == eResType::RT_GDI_PLUS) {
		mWidth = width;
		mRECT = RECT_MAKE_FUNCTION;
		mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
		mImgGp->setWidth(width);
		mImgGp->rebuildChachedBitmap();
	}
}

void GameUI::setHeight(float height)
{
	if (mResType == eResType::RT_GDI_PLUS) {
		mHeight = height;
		mRECT = RECT_MAKE_FUNCTION;
		mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
		mImgGp->setHeight(height);
		mImgGp->rebuildChachedBitmap();
	}
}

void GameUI::clickDownEvent()
{
	mLastEvent = eEventStat::ES_CLICK_DOWN;
	if (mClickDownEvent != NULL) {
		mClickDownEvent(this);
	}
}

void GameUI::clickUpEvent()
{
	mLastEvent = eEventStat::ES_CLICK_UP;
	if (mClickUpEvent != NULL) {
		mClickUpEvent(this);
	}
}

void GameUI::mouseOverEvent()
{
	mLastEvent = eEventStat::ES_MOUSE_OVER;
	if (mMouseOverEvent != NULL) {
		mMouseOverEvent(this);
	}
}

void GameUI::mouseOffEvent()
{
	mLastEvent = eEventStat::ES_MOUSE_OFF;
	if (mMouseOffEvent != NULL) {
		mMouseOffEvent(this);
	}
}

void GameUI::dragEvent() {
	mLastEvent = eEventStat::ES_DRAG;
	if (mDragEvent != NULL) {
		mDragEvent(this);
	}
}

void GameUI::changeUIStat(eStat changeStat)
{
	if (mStat == changeStat) {
		return;
	}
	
	mStat = changeStat;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT ScrollBox::init(const char* id, float x, float y, float width, float height, ImageGp* contentImg, eXStandard xStandard, eYStandard yStandard)
{
	GameUI::init(id, x, y, width, height, GDIPLUSMANAGER->cloneImage(IMGCLASS->UISetupBox), xStandard, yStandard);

	mContentImg = contentImg;

	mScrollRatioW = contentImg->getWidth() / width;
	mScrollRatioH = contentImg->getHeight() / height;

	//상자 테두리 굵기 설정
	mFrameBorderW = 10.0f * (width / (WINSIZE_X * 0.25f));
	mFrameBorderH = 15.0f * (height / (WINSIZE_Y * 0.5f));

	//콘텐츠 영역 설정
	float contentAreaX = mRectF.GetLeft() + mFrameBorderW;
	float contentAreaY = mRectF.GetTop() + mFrameBorderH;
	float contentAreaWidth = mWidth - 30.0f - (mFrameBorderW * 2.0f);
	float contentAreaHeight = mHeight - 30.0f - (mFrameBorderH * 2.0f);

	mAbsContentArea = RectFMake(contentAreaX, contentAreaY, contentAreaWidth, contentAreaHeight);

	//vertical 스크롤바 설정
	mVScrollMoveDistance = 0.0f;

	mVScrollWidth = 30.0f;
	mVScrollHeight = height - (mFrameBorderH * 2.0f) - mVScrollWidth;
	mVScrollStartX = mRectF.GetRight() - mVScrollWidth - mFrameBorderW;
	mVScrollStartY = mRectF.GetTop() + mFrameBorderH;

	mVScrollBar = GDIPLUSMANAGER->cloneImage(IMGCLASS->UIVScrollBar);
	mVScrollBar->setSize(mVScrollWidth, mVScrollHeight);

	float vScrollBtnW = mVScrollWidth;
	float vScrollBtnH = contentAreaHeight - ((contentImg->getHeight() - contentAreaHeight) / mScrollRatioH);

	mVScrollBtn = new GameUI;
	mVScrollBtn->init("수직 스크롤 버튼", mVScrollStartX, mVScrollStartY, vScrollBtnW, vScrollBtnH, GDIPLUSMANAGER->cloneImage(IMGCLASS->UIVScrollBtn), XS_LEFT, YS_TOP);
	mVScrollBtn->setClickDownEvent([this](GameUI* ui) {
		mVScrollPtDistance = _ptMouse.y - mVScrollBtn->getRectF().GetTop();
	});
	mVScrollBtn->setDragEvent([this](GameUI* ui) {
		Gdiplus::RectF tempMoveRectF = RectFMake(mVScrollBtn->getRectF().GetLeft(), _ptMouse.y - mVScrollPtDistance, mVScrollBtn->getRectF().Width, mVScrollBtn->getRectF().Height);
		float tempVScrollDistance = tempMoveRectF.GetTop() - mVScrollStartX;
		if (mVScrollMoveDistance != tempVScrollDistance) {
			if (mVScrollStartY > tempMoveRectF.GetTop()) {
				mVScrollBtn->setY(mVScrollStartY, YS_TOP);
			}
			else if (mVScrollStartY + mVScrollHeight < tempMoveRectF.GetBottom())
			{
				mVScrollBtn->setY(mVScrollStartY + mVScrollHeight, YS_BOTTOM);
			}
			else {
				mVScrollBtn->setY(tempMoveRectF.GetTop(), YS_TOP);
			}

			mVScrollMoveDistance = mVScrollBtn->getRectF().GetTop() - mVScrollStartY;
			clipingContentArea();
		}
	});

	//horizantal 스크롤바 설정
	mHScrollMoveDistance = 0.0f;
	mHScrollHeight = 30.0f;
	mHScrollWidth = width - (mFrameBorderW * 2.0f) - mHScrollHeight;
	mHScrollStartX = mRectF.GetLeft() + mFrameBorderW;
	mHScrollStartY = mRectF.GetBottom() - mHScrollHeight - mFrameBorderH;

	mHScrollBar = GDIPLUSMANAGER->cloneImage(IMGCLASS->UIHScrollBar);
	mHScrollBar->setSize(mHScrollWidth, mHScrollHeight
	);
	float hScrollBtnW = contentAreaWidth - ((contentImg->getWidth() - contentAreaWidth) / mScrollRatioW);
	float hScrollBtnH = mHScrollHeight;

	mHScrollBtn = new GameUI;
	mHScrollBtn->init("수평 스크롤 버튼", mHScrollStartX, mHScrollStartY, hScrollBtnW, hScrollBtnH, GDIPLUSMANAGER->cloneImage(IMGCLASS->UIHScrollBtn), XS_LEFT, YS_TOP);
	mHScrollBtn->setClickDownEvent([this](GameUI* ui) {
		mHScrollPtDistance = _ptMouse.x - ui->getRectF().GetLeft();
	});
	mHScrollBtn->setDragEvent([this](GameUI* ui) {
		Gdiplus::RectF tempMoveRectF = RectFMake(_ptMouse.x - mHScrollPtDistance, mHScrollBtn->getRectF().GetTop(), mHScrollBtn->getRectF().Width, mHScrollBtn->getRectF().Height);
		float tempHScrollDistance = tempMoveRectF.GetLeft() - mHScrollStartX;

		if (mHScrollMoveDistance != tempHScrollDistance) {
			if (mHScrollStartX > tempMoveRectF.GetLeft()) {
				mHScrollBtn->setX(mHScrollStartX, XS_LEFT);
			}
			else if (mHScrollStartX + mHScrollWidth < tempMoveRectF.GetRight())
			{
				mHScrollBtn->setX(mHScrollStartX + mHScrollWidth, XS_RIGHT);
			}
			else {
				mHScrollBtn->setX(tempMoveRectF.GetLeft(), XS_LEFT);
			}

			mHScrollMoveDistance = mHScrollBtn->getRectF().GetLeft() - mHScrollStartX;
			clipingContentArea();
		}
	});

	mContentImg->startClipping(contentAreaWidth, contentAreaHeight);
	clipingContentArea();

	mContentClickDownFunc = NULL;
	mContentClickUpEvent = NULL;
	mContentMouseOverEvent = NULL;
	mContentMouseOffEvent = NULL;
	mContentDragEvent = NULL;

	return S_OK;
}

void ScrollBox::render()
{
	mImgGp->render(getMemDc(), mRectF.X, mRectF.Y);

	mContentImg->render(mAbsContentArea.GetLeft(), mAbsContentArea.GetTop());

	mVScrollBar->render(mVScrollStartX, mVScrollStartY);
	mVScrollBtn->render();
	mHScrollBar->render(mHScrollStartX, mHScrollStartY);
	mHScrollBtn->render();
}

void ScrollBox::update()
{
	GameUI::update();
}

void ScrollBox::clickDownEvent()
{
	GameUI::clickDownEvent();
	
	if (mAbsContentArea.Contains(_ptfMouse)) {
		if (mContentClickDownFunc != NULL) {
			mContentClickDownFunc(this);
			mCurActiveUI = "content";
		}
	}
	else if (mVScrollBtn->getRectF().Contains(_ptfMouse)) {
		mVScrollBtn->clickDownEvent();
		mCurActiveUI = "vScrollBtn";
	}
	else if (mHScrollBtn->getRectF().Contains(_ptfMouse)) {
		mHScrollBtn->clickDownEvent();
		mCurActiveUI = "hScrollBtn";
	}
}

void ScrollBox::clickUpEvent()
{
	GameUI::clickUpEvent();

	if (mAbsContentArea.Contains(_ptfMouse)) {
		if (mContentClickUpEvent != NULL) {
			mContentClickUpEvent(this);
		}
	}
	else if (mVScrollBtn->getRectF().Contains(_ptfMouse)) {
		mVScrollBtn->clickUpEvent();
	}
	else if (mHScrollBtn->getRectF().Contains(_ptfMouse)) {
		mHScrollBtn->clickUpEvent();
	}
}

void ScrollBox::dragEvent()
{
	GameUI::dragEvent();

	if (mCurActiveUI == "content") {
		if (mContentDragEvent != NULL) {
			mContentDragEvent(this);
		}
	} else if (mCurActiveUI == "vScrollBtn") {
		mVScrollBtn->dragEvent();
	} else if (mCurActiveUI == "hScrollBtn") {
		mHScrollBtn->dragEvent();
	}
}

void ScrollBox::mouseOverEvent()
{
	GameUI::mouseOverEvent();

	if (mAbsContentArea.Contains(_ptfMouse)) {
		if (mContentMouseOverEvent != NULL) {
			mContentMouseOverEvent(this);
		}
	}
	else if (mVScrollBtn->getRectF().Contains(_ptfMouse)) {
		mVScrollBtn->mouseOverEvent();
	}
	else if (mHScrollBtn->getRectF().Contains(_ptfMouse)) {
		mHScrollBtn->mouseOverEvent();
	}
}

void ScrollBox::mouseOffEvent()
{
	GameUI::mouseOffEvent();
	if (mCurActiveUI == "content") {
		if (mContentMouseOffEvent != NULL) {
			mContentMouseOffEvent(this);
		}
	}
	else if (mCurActiveUI == "vScrollBtn") {
		mVScrollBtn->mouseOffEvent();
	}
	else if (mCurActiveUI == "hScrollBtn") {
		mHScrollBtn->mouseOffEvent();
	}

	mCurActiveUI = "";
}

void ScrollBox::clipingContentArea()
{
	mContentImg->clipping(0, 0, mHScrollMoveDistance * mScrollRatioW, mVScrollMoveDistance * mScrollRatioH, mAbsContentArea.Width, mAbsContentArea.Height);
}

void ScrollBox::scrollToCenter()
{
	mHScrollBtn->setX(mHScrollStartX + (mHScrollWidth * 0.5f), XS_CENTER);
	mVScrollBtn->setY(mVScrollStartY + (mVScrollHeight * 0.5f), YS_CENTER);

	mHScrollMoveDistance = mHScrollBtn->getRectF().GetLeft() - mHScrollStartX;
	mVScrollMoveDistance = mVScrollBtn->getRectF().GetTop() - mVScrollStartY;

	clipingContentArea();
}

void ScrollBox::changeContent(ImageGp * changeImg)
{
	mContentImg = changeImg;
	mContentImg->startClipping(mAbsContentArea.Width, mAbsContentArea.Height);

	mScrollRatioW = (changeImg->getWidth() / mWidth);
	mScrollRatioH = (changeImg->getHeight() / mHeight);

	mVScrollMoveDistance = 0.0f;
	mHScrollMoveDistance = 0.0f;

	float vScrollBtnH = mAbsContentArea.Height - ((changeImg->getHeight() - mAbsContentArea.Height) / mScrollRatioH);
	while(vScrollBtnH < 30.0f) {
		mScrollRatioH++;
		vScrollBtnH = mAbsContentArea.Height - ((changeImg->getHeight() - mAbsContentArea.Height) / mScrollRatioH);
	}
	mVScrollBtn->setHeight(vScrollBtnH);
	mVScrollBtn->setY(mVScrollStartY);

	float hScrollBtnW = mAbsContentArea.Width - ((changeImg->getWidth() - mAbsContentArea.Width) / mScrollRatioW);
	while (hScrollBtnW < 30.0f) {
		mScrollRatioW++;
		hScrollBtnW = mAbsContentArea.Width - ((changeImg->getWidth() - mAbsContentArea.Width) / mScrollRatioW);
	}
	mHScrollBtn->setWidth(hScrollBtnW);
	mHScrollBtn->setX(mHScrollStartX);

	clipingContentArea();
}
///////////////////////////////////////start Button/////////////////////////////////////////////////////
void SButton::clickDownEvent()
{
	GameUI::clickDownEvent();
	
	if (bIsMouseClick) {
		bIsMouseClick = true;
	}

	if (!SOUNDMANAGER->isPlaySound(SOUNDCLASS->MenuBtnClickEffect)) {
		SOUNDMANAGER->play(SOUNDCLASS->MenuBtnClickEffect);
	}
}

void SButton::clickUpEvent()
{
	GameUI::clickUpEvent();

	if (bIsMouseClick) {
		bIsMouseClick = false;
	}
}

void SButton::mouseOverEvent()
{
	GameUI::mouseOverEvent();
	if (!bIsMouseOver) {
		bIsMouseOver = true;

		if (!SOUNDMANAGER->isPlaySound(SOUNDCLASS->MenuBtnMouseOverEffect)) {
			SOUNDMANAGER->play(SOUNDCLASS->MenuBtnMouseOverEffect, 1.0f);
		}

		this->sizeToBig(1.2f);
	}
}

void SButton::mouseOffEvent()
{
	GameUI::mouseOffEvent();

	if (bIsMouseOver) {
		bIsMouseOver = false;

		if (SOUNDMANAGER->isPlaySound(SOUNDCLASS->MenuBtnMouseOverEffect)) {
			SOUNDMANAGER->stop(SOUNDCLASS->MenuBtnMouseOverEffect);
		}

		this->sizeToOriginal();
	}
}

void SButton::changeUIStat(eStat changeStat)
{
	GameUI::changeUIStat(changeStat);

	if (mStat == eStat::SIZE_BIG) {
		mImgGp->changeColor();
	}

	if (mStat == eStat::NONE) {
		mStat = eStat::NONE;
		mImgGp->backOriginalColor();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT Toolbar::init(const char * id, float x, float y, float width, float height, ImageGp * imgGp, eXStandard xStandard, eYStandard yStandard)
{
	GameUI::init(id, x, y, width, height, imgGp, xStandard, yStandard);

	for (int i = 0; i < MAX_TOOLBAR_INDEX; i++) {
		mItems[i].IsNone = true;
	}

	return S_OK;
}

HRESULT Toolbar::init(const char * id, float x, float y, ImageGp* img, eXStandard xPos, eYStandard yPos)
{
	GameUI::init(id, x, y, img, xPos, yPos);
	
	mCurSelectIndex = 0;

	mFrameBorderH = 16.0f;
	mFrameBorderW = 16.0f;

	mAbsContentArea = RectFMake(mRectF.GetLeft() + mFrameBorderW, mRectF.GetTop() + mFrameBorderH, mWidth - (mFrameBorderW * 2.0f), mHeight - (mFrameBorderH * 2.0f));
	float toolbarBoxW = mAbsContentArea.Width / MAX_TOOLBAR_INDEX;
	for (int i = 0; i < MAX_TOOLBAR_INDEX; i++) {
		mItems[i].IsNone = true;
		mItems[i].ImgRectF = RectFMake(mAbsContentArea.GetLeft() + (i * toolbarBoxW), mAbsContentArea.GetTop(), toolbarBoxW, mAbsContentArea.Height);
	}

	return S_OK;
}

void Toolbar::render(void)
{
	GameUI::render();

	for (int i = 0; i < MAX_TOOLBAR_INDEX; i++) {
		if (!mItems[i].IsNone) {
			mItems[i].ItemImg->render(getMemDc(), mItems[i].ImgRectF.GetLeft(), mItems[i].ImgRectF.GetTop());
		}
	}

	GDIPLUSMANAGER->drawRectFLine(getMemDc(), mItems[mCurSelectIndex].ImgRectF, Color(255, 0, 0), 4.0f);
}

void Toolbar::addItem(string ItemId, int index, int count)
{
	mItems[index].IsNone = false;
	mItems[index].ItemId = 1;
	mItems[index].Count = count;
	mItems[index].ItemImg = ITEMMANAGER->findItem(ItemId)->getInventoryImg();
}

int Toolbar::changeSelectItem(int index) {
	int itemIndex = -1;
	if (mCurSelectIndex != index) {
		mCurSelectIndex = index;
		if (!mItems[index].IsNone) {
			itemIndex = index;
		}
	}

	return index;
}

bool Toolbar::isCollisionContentBox(PointF ptF)
{
	return mAbsContentArea.Contains(ptF);
}

int Toolbar::getIndexToPtF(PointF ptF) {
	float relX = ptF.X - mAbsContentArea.GetLeft();
	return relX / (mAbsContentArea.Width / MAX_TOOLBAR_INDEX);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT EditText::init(const char * id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameUI::init(id, x, y, width, height, GDIPLUSMANAGER->cloneImage(IMGCLASS->UISetupBox), xStandard, yStandard);

	mFrameBorderW = 10.0f * (width / (WINSIZE_X * 0.25f));
	mFrameBorderH = 15.0f * (height / (WINSIZE_Y * 0.5f));

	//콘텐츠 영역 설정
	float contentAreaX = mRectF.GetLeft() + mFrameBorderW;
	float contentAreaY = mRectF.GetTop() + mFrameBorderH;

	float contentAreaWidth = mWidth - (mFrameBorderW * 2.0f);
	float contentAreaHeight = mHeight- (mFrameBorderH * 2.0f);

	mTextArea = RectFMake(contentAreaX, contentAreaY, contentAreaWidth, contentAreaHeight);

	return S_OK;
}

void EditText::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		if (mRectF.Contains(_ptfMouse)) {
			bIsActiveEditMode = true;
		}
		else {
			bIsActiveEditMode = false;
		}

	}

	if (mRectF.Contains(_ptfMouse)) {
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('M')) {
			setX(_ptfMouse.X);
			setY(_ptfMouse.Y);
			return;
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && KEYMANAGER->isStayKeyDown('M')) {
			LOG::d(to_string(getRectF().GetLeft()) + " " + to_string(getRectF().GetTop()));
			LOG::d(to_string(getRectF().GetRight()) + " " + to_string(getRectF().GetBottom()));
			return;
		}
	}

	if (bIsActiveEditMode) {
		int curKey = KEYMANAGER->getCurKeyDown();
		if (curKey == -1) return;

		if (curKey >= 65 && curKey <= 90) {
			mCurInputText = mCurInputText + (char)tolower(curKey);
			return;
		}

		if (curKey >= 48 && curKey <= 57) {
			mCurInputText = mCurInputText + (char)curKey;
			return;
		}

		if (curKey == 190) {
			mCurInputText += '.';
		}

		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) && KEYMANAGER->isOnceKeyDown(189)) {
			mCurInputText += '_';
		}

		if (curKey == VK_BACK) {
			mCurInputText = mCurInputText.substr(0, mCurInputText.size() -1);
		}
	}
}

void EditText::render()
{
	mImgGp->render(getMemDc(), mRectF.X, mRectF.Y);
	GDIPLUSMANAGER->drawText(getMemDc(), mCurInputText, mTextArea.GetLeft(), mTextArea.GetTop(), 20, Color(0, 0, 0));
}

HRESULT RadioButton::init(float x, float y, float btnWidth, float btnHeight, ImageGp ** btnList, int btnCount)
{
	GameUI::init("라디오 버튼 리스트", x, y, btnWidth * btnCount, btnHeight, XS_LEFT, YS_TOP);

	this->mBtnList = btnList;
	this->mBtnCount = btnCount;
	this->mOneBtnWidth = btnWidth;
	this->mOneBtnHeight = btnHeight;

	bSelectNothing = true;

	return S_OK;
}

void RadioButton::render(void)
{
	for(int i = 0; i < mBtnCount; i++) {
		if (!bSelectNothing && mCurSelectIndex == i) {
			mBtnList[i]->render(getMemDc(), getRectF().GetLeft() + (i * mOneBtnWidth), getRectF().GetTop() + 10.0f);
		}
		else {
			mBtnList[i]->render(getMemDc(), getRectF().GetLeft() + (i * mOneBtnWidth), getRectF().GetTop());
		}
	}
}

int RadioButton::changeSelectIndex()
{
	bSelectNothing = false;
	mCurSelectIndex = (_ptfMouse.X - mRectF.GetLeft()) / mOneBtnWidth;
	return mCurSelectIndex;
}
