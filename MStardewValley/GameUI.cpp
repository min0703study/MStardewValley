#include "Stdafx.h"
#include "GameUI.h"
#include "GameScene.h"

//private init (common)
HRESULT UIComponent::init(const char * id, float x, float y, eXStandard xStandard, eYStandard yStandard)
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

	mAniStat = eAniStat::NONE;

	mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);

	bIsMouseOver = false;
	bIsMouseClick = false;
	bIsSelected = false;

	bInitSuccess = true;
	bIsMoveMode = false;
	bIsActive = true;
	bIsShowing = true;

	mId = id;
	
	mClickDownEvent = NULL;
	mClickUpEvent = NULL;
	mMouseOverEvent = NULL;
	mMouseOffEvent = NULL;
	mDragEvent = NULL;

	return S_OK;
}

//public init
HRESULT UIComponent::init(const char * id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	LOG::d((string)id + "");
	mResType = eResType::RT_BLANK;

	mImgGp = new ImageGp();
	mImgGp->init(getMemDc(), width, height);

	mWidth = width;
	mHeight = height;

	return init(id, x, y, xStandard, yStandard);
}

HRESULT UIComponent::init(const char* id, float centerX, float centerY, float width, float height, ImageBase * img, eXStandard xStandard, eYStandard yStandard)
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

HRESULT UIComponent::init(const char* id, float x, float y, ImageBase * img, eXStandard xStandard, eYStandard yStandard)
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

HRESULT UIComponent::init(const char* id, float x, float y, float width, float height, ImageGp * img, eXStandard xStandard, eYStandard yStandard)
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

	return init(id, x, y, xStandard, yStandard);
}

HRESULT UIComponent::init(const char* id, float x, float y, ImageGp * img, eXStandard xStandard, eYStandard yStandard)
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

void UIComponent::sizeToBig(float toSizeRatio, float speed)
{
	if (mAniStat != eAniStat::SIZE_TO_BIG && mAniStat != eAniStat::SIZE_BIG) {
		changeUIStat(eAniStat::SIZE_TO_BIG);

		mToSizeRatio = toSizeRatio;

		mSizeChangeWidth = mWidth;
		mSizeChangeHeight = mHeight;
		mSizeChangeRatio = mSizeChangeWidth / mSizeChangeHeight;
		mSizeChangeSpeed = speed;
	};
}

void UIComponent::fadeIn(float speed)
{
	changeUIStat(eAniStat::FADE_IN);
	mCurAlpha = 0;
	mFadeEffectSpeed = speed;
}

void UIComponent::fadeOut(float speed)
{
	changeUIStat(eAniStat::FADE_OUT);
	mCurAlpha = 255;
	mFadeEffectSpeed = speed;
}

void UIComponent::sizeToOriginal(float speed)
{
	if (mAniStat != eAniStat::SIZE_TO_ORIGINAL && mAniStat != eAniStat::NONE) {
		changeUIStat(eAniStat::SIZE_TO_ORIGINAL);
		mSizeChangeSpeed = speed;
	}
}

void UIComponent::toLoopX(int loopFrameCount, float speed)
{
	switch (mResType) {
	case eResType::RT_GDI_PLUS:
		if (mAniStat != eAniStat::LOOP_X) {
			mAniStat = eAniStat::LOOP_X;
			mCurLoopX = 0;
			mLoopFrameCount = loopFrameCount;
			mImgGp->startLoopX(loopFrameCount);
			mLoopSpeed = speed;
		}
		break;
	case eResType::RT_BLANK:
		break;
	case eResType::RT_IMAGE_BASE:
		if (mAniStat != eAniStat::LOOP_X) {
			mAniStat = eAniStat::LOOP_X;
			mCurLoopX = 0;
			mLoopFrameCount = loopFrameCount;
			mLoopSpeed = speed;
		}
		break;
	default:
		break;

	}

}

void UIComponent::moveTo(eUIDirection moveDirection, float speed)
{
	mAniStat = eAniStat::MOVE_TO;
	mMoveSpeed = speed;
	mMoveDirection = moveDirection;
}

void UIComponent::update()
{
}

void UIComponent::updateUI()
{
	if (!bInitSuccess) return;

	switch (mAniStat) {
	case eAniStat::MOVE_TO:
		switch (mMoveDirection)
		{
		case UI_RIGHT:
			offsetX(mMoveSpeed);
			break;
		case UI_LEFT:
			offsetX(-mMoveSpeed);
			break;
		case UI_UP:
			offsetY(-mMoveSpeed);
			break;
		case UI_DOWN:
			offsetY(mMoveSpeed);
			break;
		default:
			break;
		}
		break;
	case eAniStat::SIZE_TO_BIG:
		if (mSizeChangeWidth > mWidth * mToSizeRatio) {
			changeUIStat(eAniStat::SIZE_BIG);
		}
		else {
			mSizeChangeWidth = mSizeChangeWidth + mSizeChangeSpeed;
			mSizeChangeHeight = mSizeChangeHeight + (mSizeChangeSpeed / mSizeChangeRatio);
			mSizeChangeRectF = RectFMakeCenter(mCenterX, mCenterY, mSizeChangeWidth, mSizeChangeHeight);
		}
		break;
	case  eAniStat::SIZE_TO_ORIGINAL:
		if (mSizeChangeWidth < mWidth) {
			changeUIStat(eAniStat::NONE);
		}
		else {
			mSizeChangeWidth = mSizeChangeWidth - mSizeChangeSpeed;
			mSizeChangeHeight = mSizeChangeHeight - (mSizeChangeSpeed / mSizeChangeRatio);
			mSizeChangeRectF = RectFMakeCenter(mCenterX, mCenterY, mSizeChangeWidth, mSizeChangeHeight);
		}
		break;
	case eAniStat::LOOP_X:
		mCurLoopX += mLoopSpeed;
		if (mCurLoopX >= mLoopFrameCount) mCurLoopX = 0;
		break;

	case eAniStat::FADE_IN:
		mCurAlpha += mFadeEffectSpeed;
		break;
	case eAniStat::FADE_OUT:
		mCurAlpha -= mFadeEffectSpeed;
		mCurAlpha -= mFadeEffectSpeed;
		break;
	default:
		//!DO NOTHING
		break;
	}
}

void UIComponent::render()
{
	if (!bInitSuccess) return;
	switch (mResType) {
	case eResType::RT_GDI_PLUS:
		switch (mAniStat) {
		case eAniStat::SIZE_TO_BIG: case eAniStat::SIZE_BIG: case eAniStat::SIZE_TO_ORIGINAL:
			mImgGp->render(mSizeChangeRectF);
			break;
		case eAniStat::NONE: case eAniStat::MOVE_TO:
			mImgGp->render(mRectF.GetLeft(), mRectF.GetTop());
			break;
		case eAniStat::LOOP_X:
			mImgGp->loopRender(getMemDc(), mRectF.GetLeft(), mRectF.GetTop(), static_cast<int>(mCurLoopX));
			break;
		default:
			//!DO NOTHING
			break;
		}
		break;
	case eResType::RT_IMAGE_BASE:
		switch (mAniStat) {
		case eAniStat::NONE:case eAniStat::MOVE_TO:
			mImgBase->render(getMemDc(), static_cast<int>(mRectF.GetLeft()), static_cast<int>(mRectF.GetTop()));
			break;
		case eAniStat::LOOP_X:
			mImgBase->loopRender(getMemDc(), &RectMake(0, 0, WINSIZE_INT_X, WINSIZE_INT_Y), mCurLoopX, 0);
			break;
		case eAniStat::FADE_IN: case eAniStat::FADE_OUT:
			mImgBase->alphaRender(getMemDc(), (BYTE)mCurAlpha);
			break;
		default:
			//!DO NOTHING
			break;
		}
		break;
	case eResType::RT_BLANK:
		break;
	default:
		break;

	}
}

void UIComponent::render(float x, float y)
{
	if (!bInitSuccess) return;
	switch (mResType) {
	case eResType::RT_GDI_PLUS:
		mImgGp->render(x, y);
		break;
	case eResType::RT_BLANK:
		mImgGp->render(x, y);
		break;
	case eResType::RT_IMAGE_BASE:
		mImgBase->render(getMemDc(), static_cast<int>(x), static_cast<int>(y));
		break;
	default:
		break;

	}
}

void UIComponent::release()
{
	if (!bInitSuccess) return;
	mImgGp->release();
	SAFE_DELETE(mImgGp);
}

void UIComponent::setX(float x, eXStandard xStandard)
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
	mRectF.X = x - (mWidth * 0.5f);
}

void UIComponent::setY(float y, eYStandard yStandard)
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
	mRectF.Y = y - (mHeight * 0.5f);
}

void UIComponent::setWidth(float width)
{
	if (mResType == eResType::RT_GDI_PLUS) {
		mWidth = width;
		mRectF.Width = width;
		mImgGp->setWidth(width);
	}
}

void UIComponent::setHeight(float height)
{
	if (mResType == eResType::RT_GDI_PLUS) {
		mHeight = height;
		mRectF.Height = height;
		mImgGp->setHeight(height);
	}
}

void UIComponent::clickDownEvent()
{
	mLastEvent = eUIEventStat::ES_CLICK_DOWN;
	if (mClickDownEvent != NULL) {
		mClickDownEvent(this);
	}
}

void UIComponent::clickUpEvent()
{
	mLastEvent = eUIEventStat::ES_CLICK_UP;
	if (mClickUpEvent != NULL) {
		mClickUpEvent(this);
	}
}

void UIComponent::mouseOverEvent()
{
	mLastEvent = eUIEventStat::ES_MOUSE_OVER;
	if (mMouseOverEvent != NULL) {
		mMouseOverEvent(this);
	}
}

void UIComponent::mouseOffEvent()
{
	mLastEvent = eUIEventStat::ES_MOUSE_OFF;
	if (mMouseOffEvent != NULL) {
		mMouseOffEvent(this);
	}
}

void UIComponent::dragEvent() {
	mLastEvent = eUIEventStat::ES_DRAG;
	if (mDragEvent != NULL) {
		mDragEvent(this);
	}
}

void UIComponent::changeUIStat(eAniStat changeStat)
{
	if (mAniStat == changeStat) {
		return;
	}
	
	mAniStat = changeStat;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT ScrollBox::init(const char* id, float x, float y, float width, float height, ImageGp* contentImg, eXStandard xStandard, eYStandard yStandard, bool useVScroll, bool useHScroll)
{
	UIComponent::init(id, x, y, width, height, GDIPLUSMANAGER->clone(IMGCLASS->UISetupBox), xStandard, yStandard);

	getImgGp()->setRenderBitBlt();

	bUseVScroll = useVScroll;
	bUseHScroll = useHScroll;
	
	bShowingSubImg = false;

	mContentImg = contentImg;
	mSubImg = new ImageGp;
	mSubImg->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(mContentImg->getWidth(), mContentImg->getHeight()));

	mFrameBorderH = 15.0f * (height / (WINSIZE_Y * 0.5f));
	mFrameBorderW = 10.0f * (width / (WINSIZE_X * 0.25f));

	if (bUseVScroll) {
		mScrollRatioH = mContentImg->getHeight() / height;
		mVScrollWidth = 30.0f;
	}
	else {
		mVScrollWidth = 0.0f;
		mScrollRatioH = 0;
	}

	if (bUseHScroll) {
		mHScrollHeight = 30.0f;
		mScrollRatioW = mContentImg->getWidth() / width;
	}
	else {
		mHScrollHeight = 0;
		mScrollRatioW = 0;
	}

	//콘텐츠 영역 설정
	float contentAreaX = mRectF.GetLeft() + mFrameBorderW;
	float contentAreaY = mRectF.GetTop() + mFrameBorderH;
	float contentAreaWidth = mWidth - mVScrollWidth - (mFrameBorderW * 2.0f);
	float contentAreaHeight = mHeight - mHScrollHeight - (mFrameBorderH * 2.0f);

	mAbsContentArea = RectFMake(contentAreaX, contentAreaY, contentAreaWidth, contentAreaHeight);
	mRelContentArea = RectFMake(0.0f, 0.0f, contentAreaWidth, contentAreaHeight);

	if (bUseVScroll) {
		//vertical 스크롤바 설정
		mVScrollMoveDistance = 0.0f;

		mVScrollHeight = height - (mFrameBorderH * 2.0f) - mVScrollWidth;
		mVScrollStartX = mRectF.GetRight() - mVScrollWidth - mFrameBorderW;
		mVScrollStartY = mRectF.GetTop() + mFrameBorderH;

		mVScrollBar = GDIPLUSMANAGER->clone(IMGCLASS->UIVScrollBar);
		mVScrollBar->setSize(mVScrollWidth, mVScrollHeight);

		float vScrollBtnW = mVScrollWidth;
		float vScrollBtnH = contentAreaHeight - ((mContentImg->getHeight() - contentAreaHeight) / mScrollRatioH);

		if (vScrollBtnH <= 0 || vScrollBtnH == INFINITY) {
			bUseVScroll = false;
		} else {
			mVScrollBtn = new UIComponent;
			mVScrollBtn->init("수직 스크롤 버튼", mVScrollStartX, mVScrollStartY, vScrollBtnW, vScrollBtnH, GDIPLUSMANAGER->clone(IMGCLASS->UIVScrollBtn), XS_LEFT, YS_TOP);
			mVScrollBtn->setClickDownEvent([this](UIComponent* ui) {
				mVScrollPtDistance = _ptMouse.y - mVScrollBtn->getRectF().GetTop();
			});
			mVScrollBtn->setDragEvent([this](UIComponent* ui) {
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
					mRelContentArea.Y = mAbsContentArea.GetTop() + (mVScrollMoveDistance * mScrollRatioH);
					clipingContentArea();
				}
			});
		}
	}
	if (bUseHScroll) {
		//horizantal 스크롤바 설정
		mHScrollMoveDistance = 0.0f;
		mHScrollWidth = width - (mFrameBorderW * 2.0f) - mHScrollHeight;
		mHScrollStartX = mRectF.GetLeft() + mFrameBorderW;
		mHScrollStartY = mRectF.GetBottom() - mHScrollHeight - mFrameBorderH;

		mHScrollBar = GDIPLUSMANAGER->clone(IMGCLASS->UIHScrollBar);
		mHScrollBar->setSize(mHScrollWidth, mHScrollHeight);

		float hScrollBtnW = contentAreaWidth - ((mContentImg->getWidth() - contentAreaWidth) / mScrollRatioW);
		float hScrollBtnH = mHScrollHeight;

		mHScrollBtn = new UIComponent;
		mHScrollBtn->init("수평 스크롤 버튼", mHScrollStartX, mHScrollStartY, hScrollBtnW, hScrollBtnH, GDIPLUSMANAGER->clone(IMGCLASS->UIHScrollBtn), XS_LEFT, YS_TOP);
		mHScrollBtn->setClickDownEvent([this](UIComponent* ui) {
			mHScrollPtDistance = _ptfMouse.X - ui->getRectF().GetLeft();
		});
		mHScrollBtn->setDragEvent([this](UIComponent* ui) {
			Gdiplus::RectF tempMoveRectF = RectFMake(_ptfMouse.X - mHScrollPtDistance, mHScrollBtn->getRectF().GetTop(), mHScrollBtn->getRectF().Width, mHScrollBtn->getRectF().Height);
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
				mRelContentArea.X = mAbsContentArea.GetLeft() + (mHScrollMoveDistance * mScrollRatioW);
				clipingContentArea();
			}
		});
	}

	mContentImg->startClipping(contentAreaWidth, contentAreaHeight);
	mSubImg->startClipping(contentAreaWidth, contentAreaHeight);
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
	mImgGp->render(mRectF.X, mRectF.Y);
	mContentImg->render(mAbsContentArea.GetLeft(), mAbsContentArea.GetTop());

	if (bShowingSubImg) {
		mSubImg->render(mAbsContentArea.GetLeft(), mAbsContentArea.GetTop());
	}

	if (bUseVScroll) {
		mVScrollBar->render(mVScrollStartX, mVScrollStartY);
		mVScrollBtn->render();
	}

	if (bUseHScroll) {
		mHScrollBar->render(mHScrollStartX, mHScrollStartY);
		mHScrollBtn->render();
	}
}

void ScrollBox::update()
{
	UIComponent::update();
}

void ScrollBox::clickDownEvent()
{
	UIComponent::clickDownEvent();
	
	if (mAbsContentArea.Contains(_ptfMouse)) {
		if (mContentClickDownFunc != NULL) {
			mContentClickDownFunc(this);
			mCurActiveUI = "content";
		}
	}
	else if (bUseVScroll && mVScrollBtn->getRectF().Contains(_ptfMouse)) {
		mVScrollBtn->clickDownEvent();
		mCurActiveUI = "vScrollBtn";
	}
	else if (bUseHScroll &&mHScrollBtn->getRectF().Contains(_ptfMouse)) {
		mHScrollBtn->clickDownEvent();
		mCurActiveUI = "hScrollBtn";
	}
}

void ScrollBox::clickUpEvent()
{
	UIComponent::clickUpEvent();

	if (mAbsContentArea.Contains(_ptfMouse)) {
		if (mContentClickUpEvent != NULL) {
			mContentClickUpEvent(this);
		}
	}
	else if (bUseVScroll && mVScrollBtn->getRectF().Contains(_ptfMouse)) {
		mVScrollBtn->clickUpEvent();
	}
	else if (bUseHScroll && mHScrollBtn->getRectF().Contains(_ptfMouse)) {
		mHScrollBtn->clickUpEvent();
	}
}

void ScrollBox::dragEvent()
{
	UIComponent::dragEvent();

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
	UIComponent::mouseOverEvent();

	if (mAbsContentArea.Contains(_ptfMouse)) {
		if (mContentMouseOverEvent != NULL) {
			mContentMouseOverEvent(this);
		}
	}
	else if (bUseVScroll &&mVScrollBtn->getRectF().Contains(_ptfMouse)) {
		mVScrollBtn->mouseOverEvent();
	}
	else if (bUseHScroll &&mHScrollBtn->getRectF().Contains(_ptfMouse)) {
		mHScrollBtn->mouseOverEvent();
	}
}

void ScrollBox::mouseOffEvent()
{
	UIComponent::mouseOffEvent();
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
	mSubImg->clipping(0, 0, mHScrollMoveDistance * mScrollRatioW, mVScrollMoveDistance * mScrollRatioH, mAbsContentArea.Width, mAbsContentArea.Height);
}

void ScrollBox::scrollToCenter()
{
	if (bUseVScroll) {
		mVScrollBtn->setY(mVScrollStartY + (mVScrollHeight * 0.5f), YS_CENTER);
		mVScrollMoveDistance = mVScrollBtn->getRectF().GetTop() - mVScrollStartY;
	}
	if(bUseHScroll) {
		mHScrollBtn->setX(mHScrollStartX + (mHScrollWidth * 0.5f), XS_CENTER);
		mHScrollMoveDistance = mHScrollBtn->getRectF().GetLeft() - mHScrollStartX;

	}
	clipingContentArea();
}

void ScrollBox::moveVScroll(float moveValue)
{
	if (bUseVScroll) {
		Gdiplus::RectF tempMoveRectF;
		mVScrollBtn->getRectF().GetBounds(&tempMoveRectF);
		tempMoveRectF.Offset(0, moveValue);
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
			mRelContentArea.Y = mAbsContentArea.GetTop() + (mVScrollMoveDistance * mScrollRatioH);
			clipingContentArea();
		}
	}
}

void ScrollBox::moveHScroll(float moveValue)
{
	if (bUseVScroll) {
		Gdiplus::RectF tempMoveRectF;
		mHScrollBtn->getRectF().GetBounds(&tempMoveRectF);
		tempMoveRectF.Offset(moveValue, 0);
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
			mRelContentArea.X = mAbsContentArea.GetLeft() + (mHScrollMoveDistance * mScrollRatioW);
			clipingContentArea();
		}
	}

}

void ScrollBox::changeContent(ImageGp * changeImg)
{
	mContentImg = changeImg;
	mContentImg->startClipping(mAbsContentArea.Width, mAbsContentArea.Height);

	mSubImg = new ImageGp;
	mSubImg->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(mContentImg->getWidth(), mContentImg->getHeight()));
	mSubImg->startClipping(mAbsContentArea.Width, mAbsContentArea.Height);

	if (bUseVScroll) {
		mScrollRatioH = (changeImg->getHeight() / mHeight);
		mVScrollMoveDistance = 0.0f;

		float vScrollBtnH = mAbsContentArea.Height - ((changeImg->getHeight() - mAbsContentArea.Height) / mScrollRatioH);
		while (vScrollBtnH < 30.0f) {
			mScrollRatioH++;
			vScrollBtnH = mAbsContentArea.Height - ((changeImg->getHeight() - mAbsContentArea.Height) / mScrollRatioH);
		}
		mVScrollBtn->setHeight(vScrollBtnH);
		mVScrollBtn->setY(mVScrollStartY);

	}
	if (bUseHScroll) {
		mScrollRatioW = (changeImg->getWidth() / mWidth);
		mHScrollMoveDistance = 0.0f;

		float hScrollBtnW = mAbsContentArea.Width - ((changeImg->getWidth() - mAbsContentArea.Width) / mScrollRatioW);
		while (hScrollBtnW < 30.0f) {
			mScrollRatioW++;
			hScrollBtnW = mAbsContentArea.Width - ((changeImg->getWidth() - mAbsContentArea.Width) / mScrollRatioW);
		}
		mHScrollBtn->setWidth(hScrollBtnW);
		mHScrollBtn->setX(mHScrollStartX);
	}

	clipingContentArea();
}

///////////////////////////////////////start Button/////////////////////////////////////////////////////

void SButton::clickDownEvent()
{
	UIComponent::clickDownEvent();
	
	if (bIsMouseClick) {
		bIsMouseClick = true;
	}

	if (!SOUNDMANAGER->isPlaySound(SOUNDCLASS->MenuBtnClickEffect)) {
		SOUNDMANAGER->play(SOUNDCLASS->MenuBtnClickEffect);
	}
}

void SButton::clickUpEvent()
{
	UIComponent::clickUpEvent();

	if (bIsMouseClick) {
		bIsMouseClick = false;
	}
}

void SButton::mouseOverEvent()
{
	UIComponent::mouseOverEvent();

	if (!bIsMouseOver) {
		bIsMouseOver = true;

		if (!SOUNDMANAGER->isPlaySound(SOUNDCLASS->MenuBtnMouseOverEffect)) {
			SOUNDMANAGER->play(SOUNDCLASS->MenuBtnMouseOverEffect, 1.0f);
		}

		this->sizeToBig(1.2f, 2.0f);
	}
}

void SButton::mouseOffEvent()
{
	UIComponent::mouseOffEvent();

	if (bIsMouseOver) {
		bIsMouseOver = false;

		if (SOUNDMANAGER->isPlaySound(SOUNDCLASS->MenuBtnMouseOverEffect)) {
			SOUNDMANAGER->stop(SOUNDCLASS->MenuBtnMouseOverEffect);
		}

		this->sizeToOriginal(2.0f);
	}
}

void SButton::changeUIStat(eAniStat changeStat)
{
	UIComponent::changeUIStat(changeStat);

	if (mAniStat == eAniStat::SIZE_BIG) {
		mImgGp->changeColor();
	}

	if (mAniStat == eAniStat::NONE) {
		mAniStat = eAniStat::NONE;
		mImgGp->backOriginalColor();
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT Toolbar::init(const char * id, float x, float y, float width, float height, ImageGp * imgGp)
{
	UIComponent::init(id, x, y, imgGp, XS_CENTER, YS_CENTER);

	mCurSelectIndex = 0;

	mFrameBorderH = 16.0f;
	mFrameBorderW = 16.0f;

	mAbsContentArea = RectFMake(mRectF.GetLeft() + mFrameBorderW, mRectF.GetTop() + mFrameBorderH, mWidth - (mFrameBorderW * 2.0f), mHeight - (mFrameBorderH * 2.0f));

	float toolbarBoxW = mAbsContentArea.Width / MAX_TOOLBAR_INDEX;
	for (int i = 0; i < MAX_TOOLBAR_INDEX; i++) {
		mItemRectF[i] = RectFMake(mAbsContentArea.GetLeft() + (i * toolbarBoxW), mAbsContentArea.GetTop(), toolbarBoxW, mAbsContentArea.Height);
	}

	setClickDownEvent([this](UIComponent* ui) {

	});

	return S_OK;
}

void Toolbar::render(void)
{
	UIComponent::render();
	for (int i = 0; i < MAX_TOOLBAR_INDEX; i++) {
		PLAYER->getInventory()->render(mItemRectF[i], i);
	}

	GDIPLUSMANAGER->drawRectFLine(getMemDc(), mItemRectF[mCurSelectIndex], Color(255, 0, 0), 4.0f);
}

int Toolbar::changeSelectItem(int index) {
	SOUNDMANAGER->play(SOUNDCLASS->SelectToolbar);
	int itemIndex = -1;
	if (mCurSelectIndex != index) {
		mCurSelectIndex = index;
		if (!PLAYER->getInventory()->isEmpty(index)) {
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
	UIComponent::init(id, x, y, width, height, GDIPLUSMANAGER->clone(IMGCLASS->UISetupBox), xStandard, yStandard);

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
	mImgGp->render(mRectF.X, mRectF.Y);
	GDIPLUSMANAGER->drawText(mCurInputText, mTextArea, 45.0f, CR_BLACK);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT RadioButton::init(float x, float y, float btnWidth, float btnHeight, ImageGp ** btnList, int btnCount, eXStandard xStandard, eYStandard yStandard)
{
	UIComponent::init("라디오 버튼 리스트", x, y, btnWidth * btnCount, btnHeight, xStandard, yStandard);

	this->mBtnList = btnList;
	this->mBtnCount = btnCount;
	this->mOneBtnWidth = btnWidth;
	this->mOneBtnHeight = btnHeight;

	for (int i = 0; i < mBtnCount; i++) {
		mBtnList[i]->setSize(btnWidth, btnHeight);
	}

	bSelectNothing = true;

	return S_OK;
}

void RadioButton::render(void)
{
	for(int i = 0; i < mBtnCount; i++) {
		if (!bSelectNothing && mCurSelectIndex == i) {
			mBtnList[i]->render(getRectF().GetLeft() + (i * mOneBtnWidth), getRectF().GetTop() + 10.0f);
		}
		else {
			mBtnList[i]->render(getRectF().GetLeft() + (i * mOneBtnWidth), getRectF().GetTop());
		}
	}
}

int RadioButton::changeSelectIndex()
{
	bSelectNothing = false;
	mCurSelectIndex = (_ptfMouse.X - mRectF.GetLeft()) / mOneBtnWidth;
	return mCurSelectIndex;
}

int RadioButton::changeSelectIndex(int index)
{
	bSelectNothing = false;
	mCurSelectIndex = index;
	return mCurSelectIndex;
}

void RadioButton::clickDownEvent()
{
	changeSelectIndex();
	UIComponent::clickDownEvent();
}



///////////////////////////////////////////////

HRESULT ListBox::init(const char * id, float x, float y, float width, float height, vector<ImageGp*> vItemImg, eXStandard xStandard, eYStandard yStandard)
{
	mVItem = vItemImg;
	mItemCount = vItemImg.size();

	mCurSelectIndex = -1;

	mOneItemHeight = vItemImg[0]->getHeight();
	int allItemHeight = mOneItemHeight * mItemCount;

	Bitmap* allImage = GDIPLUSMANAGER->getBlankBitmap(width, allItemHeight);

	for (int i = 0; i < mItemCount; i++) {
		GDIPLUSMANAGER->combindBitmap(allImage, mVItem[i]->getBitmap(), 0, i * mOneItemHeight);
		mVRectF.push_back(RectFMake(0, i * mOneItemHeight, mVItem[i]->getBitmap()->GetWidth(), mOneItemHeight));
	}

	ImageGp* menuList = new ImageGp;
	menuList->init(getMemDc(), allImage);

	ScrollBox::init(id, x, y, width, height, menuList, xStandard, yStandard, true, false);
	toggleShowingSubImg();

	setContentMouseOverEvent([this](UIComponent* ui) {
		int tempIndex = getIndexToXY(_ptfMouse.X, _ptfMouse.Y);
		if (mCurSelectIndex != tempIndex) {
			if (mCurSelectIndex != -1) {
				getSubImgGp()->toTransparent(mVRectF[mCurSelectIndex]);
			}
			mCurSelectIndex = tempIndex;
			GDIPLUSMANAGER->drawRectFToBitmap(getSubImgGp()->getBitmap(), mVRectF[mCurSelectIndex], CR_A_SALE_CHANGE);
			clipingContentArea();
		}
	});

	setContentMouseOffEvent([this](UIComponent* ui) {
		mCurSelectIndex = -1;
	});

	return S_OK;
}

void ListBox::render()
{
	if (bIsActive) {
		ScrollBox::render();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT AccessMenu::init()
{
	GameUI::init("사용자 컨트롤 메뉴", WIN_CENTER_X, WIN_CENTER_Y, ACCESS_MENU_WIDTH, ACCESS_MENU_HEIGHT, XS_CENTER, YS_CENTER);

	mInvenSelectIndex = -1;
	mInvenClickIndex = -1;

	mRadioButton = new RadioButton;
	mRadioButton->init(
		getRectF().GetLeft() + RADIO_BTN_WIDTH,
		getRectF().GetTop(), 
		RADIO_BTN_WIDTH, 
		RADIO_BTN_HEIGHT, 
		new ImageGp*[2] {
		GDIPLUSMANAGER->clone(IMGCLASS->InventoryRadioBtn),
		GDIPLUSMANAGER->clone(IMGCLASS->CraftRadioBtn)}, 
		2, 
		XS_LEFT, YS_TOP);

	mRadioButton->setClickDownEvent([this](UIComponent* ui) {
		RadioButton* castUi = (RadioButton*)ui;
		mCurActiveMenu = (eAccessMenu)castUi->getCurSelectIndex();
	});

	mInventory = new GridList;
	mInventory->init("", 
		getRectF().GetLeft(),
		mRadioButton->getRectF().GetBottom(),
		INVENTORY_WIDTH,
		INVENTORY_HEIGHT,
		12, 3, 
		GDIPLUSMANAGER->clone(IMGCLASS->InventoryBox), XS_LEFT, YS_TOP);

	mInventory->setMouseOverEvent([this](UIComponent* ui) {
		GridList* convertUi = (GridList*)ui;
		int tempIndex = convertUi->getIndexToXY(_ptfMouse.X, _ptfMouse.Y);
		if (mInvenSelectIndex != tempIndex) {
			mInvenSelectIndex = tempIndex;
		}
	});
	mInventory->setMouseOffEvent([this](UIComponent* ui) {
		mInvenSelectIndex = -1;
	});
	mInventory->setClickDownEvent([this](UIComponent* ui) {
		if (mInvenClickIndex != -1) {
			if (mInvenClickIndex == mInvenSelectIndex) {
				mInvenClickIndex = -1;
			} else {
				PLAYER->getInventory()->swap(mInvenClickIndex, mInvenSelectIndex);
			}
		} else {
			mInvenClickIndex = mInvenSelectIndex;
		}
	});
	mInventory->setRenderIndexFunc([this](int index, RectF rcF) {
		if (index != mInvenClickIndex) {
			PLAYER->getInventory()->render(rcF, index);
		}
	});

	addComponent(mInventory);
	addComponent(mRadioButton);

	return S_OK;
}

void AccessMenu::update()
{
	GameUI::update();
}

void AccessMenu::render()
{
	GameUI::render();

	if (mInvenClickIndex != -1) {
		PLAYER->getInventory()->render(_ptfMouse.X, _ptfMouse.Y, mInvenClickIndex);
	}

	if (mInvenSelectIndex != -1) {
		PLAYER->getInventory()->renderInfo(_ptfMouse.X, _ptfMouse.Y, mInvenSelectIndex);
	}
}

void AccessMenu::release()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT GridList::init(const char * id, float x, float y, float width, float height, int xCount, int yCount, ImageGp * imgGp, eXStandard xStandard, eYStandard yStandard)
{
	UIComponent::init(id, x, y, width, height, imgGp, xStandard, yStandard);

	mFrameBorderH = 39.0f;
	mFrameBorderW = 39.0f;

	mXCount = xCount;
	mYCount = yCount;

	mAbsContentArea = RectFMake(mRectF.GetLeft() + mFrameBorderW, mRectF.GetTop() + mFrameBorderH, mWidth - (mFrameBorderW * 2.0f), mHeight - (mFrameBorderH * 2.0f));

	mOneBoxWidth = mAbsContentArea.Width / xCount;
	mOneBoxHeight = mAbsContentArea.Height / yCount;

	mRenderIndexFunc = [](int index, RectF& rcF) {};

	return S_OK;
}

void GridList::render()
{
	UIComponent::render();
	mAbsContentArea = RectFMake(mRectF.GetLeft() + mFrameBorderW, mRectF.GetTop() + mFrameBorderH, mWidth - (mFrameBorderW * 2.0f), mHeight - (mFrameBorderH * 2.0f));

	float toolbarBoxW = mAbsContentArea.Width / mXCount;
	float toolbarBoxH = mAbsContentArea.Height / mYCount;

	for (int y = 0, i = 0; y < mYCount; y++) {
		for (int x = 0; x < mXCount; x++, i++) {
			mRenderIndexFunc(i, RectFMake(mAbsContentArea.GetLeft() + (x * toolbarBoxW), mAbsContentArea.GetTop() + (y * toolbarBoxH), toolbarBoxW, toolbarBoxH));
		}
	}

}

void GridList::render(float pX, float pY)
{
	UIComponent::render(pX, pY);
	mAbsContentArea = RectFMake(pX + mFrameBorderW, pY + mFrameBorderH, mWidth - (mFrameBorderW * 2.0f), mHeight - (mFrameBorderH * 2.0f));

	float toolbarBoxW = mAbsContentArea.Width / mXCount;
	float toolbarBoxH = mAbsContentArea.Height / mYCount;

	for (int y = 0, i = 0; y < mYCount; y++) {
		for (int x = 0; x < mXCount; x++, i++) {
			mRenderIndexFunc(i, RectFMake(mAbsContentArea.GetLeft() + (x * toolbarBoxW), mAbsContentArea.GetTop() + (y * toolbarBoxH), toolbarBoxW, toolbarBoxH));
		}
	}
}

int GridList::getIndexToXY(float x, float y)
{
	float relX = x - mAbsContentArea.GetLeft();
	float relY = y - mAbsContentArea.GetTop();

	int indexX = relX / mOneBoxWidth;
	int indexY = relY / mOneBoxHeight;

	return indexX + (indexY * mXCount);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT MoneyBoard::init(const char * id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	UIComponent::init(id, x, y, width, height, GDIPLUSMANAGER->clone(IMGCLASS->MoneyBoard), xStandard, yStandard);

	mFrameBorderT = 28.0f;
	mFrameBorderL = 28.0f;
	mFrameBorderR = 25.0f;
	mFrameBorderB = 13.0f;

	mFontSize = 31.0f;

	mAbsContentArea = RectFMake(mRectF.GetLeft() + mFrameBorderL, mRectF.GetTop() + mFrameBorderT, mWidth - (mFrameBorderL + mFrameBorderR), mHeight - (mFrameBorderT + mFrameBorderB));

	mCurMoeny = PLAYER->getMoeny();

	mMoneyImgGp = new ImageGp;
	mMoneyImgGp->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(mAbsContentArea.Width, mAbsContentArea.Height));
	GDIPLUSMANAGER->drawTextToBitmap(mMoneyImgGp->getBitmap(), to_wstring(PLAYER->getMoeny()), mFontSize, Color(128,0,0),Color(0,0,0,0) ,XS_RIGHT, FontStyleBold, 1);
	mMoneyImgGp->rebuildChachedBitmap();
	return S_OK;
}

void MoneyBoard::update()
{

}

void MoneyBoard::updateUI()
{
	if (mCurMoeny != PLAYER->getMoeny()) {
		mCurMoeny = PLAYER->getMoeny();
		mMoneyImgGp->clear();
		GDIPLUSMANAGER->drawTextToBitmap(mMoneyImgGp->getBitmap(), to_wstring(PLAYER->getMoeny()), mFontSize, Color(128, 0, 0), Color(0, 0, 0, 0), XS_RIGHT, FontStyleBold, 1);
		mMoneyImgGp->rebuildChachedBitmap();
	}
}

void MoneyBoard::render()
{
	UIComponent::render();
	mMoneyImgGp->render(mAbsContentArea.GetLeft(), mAbsContentArea.GetTop());
}

void MoneyBoard::release()
{
}

///////////////////////////////////////////////////////////////////////////////////

#define SALE_ITEM_BOX_W			1300.0f
#define SALE_ITEM_BOX_H			720.0f

#define SALE_LIST_W				1000.0f
#define SALE_LIST_H				500.0f

#define SALE_INVEN_W				830.0f
#define SALE_INVEN_H				250.0f

#define SALE_MONEY_BOARD_W			220.0f
#define SALE_MONEY_BOARD_H			55.0f

HRESULT SaleItemBox::init(const char * id, vector<string> itemIdList, ImageGp* npcPortrait)
{
	UIComponent::init(id, WIN_CENTER_X, WIN_CENTER_Y, SALE_ITEM_BOX_W, SALE_ITEM_BOX_H, XS_CENTER, YS_CENTER);
	
	mSelectInvenIndex = -1;

	mNpcPortrait = npcPortrait;

	mSaleListRectF = RectFMake(getRectF().GetRight() - SALE_LIST_W, getRectF().GetTop(), SALE_LIST_W, SALE_LIST_H);
	mNpcPortraitRectF = RectFMake(getRectF().GetLeft(), getRectF().GetTop(), NPC_P_W_SIZE , NPC_P_H_SIZE);
	mSaleMoneyBoardRectF = RectFMake(getRectF().GetLeft(), mNpcPortraitRectF.GetBottom(), SALE_MONEY_BOARD_W, SALE_MONEY_BOARD_H);

	mItemBox = RectFMake(0.0f, 0.0f, 940.0f, 100.0f);
	mItemImgPos = RectFMake(17.0f, 17.0f, 60.0f, 60.0f);
	mItemNamePos = RectFMake(90.0f, 30.0f, 150.0f, 40.0f);
	mItemPricePos = RectFMake(710.0f, 30.0f, 150.0f, 40.0f);

	mFontSize = 50.0f;

	for (auto iterId = itemIdList.begin(); iterId != itemIdList.end(); iterId++) {
		mVSaleItem.push_back(ITEMMANAGER->findItemReadOnly(*iterId));
	}

	for (auto iter = mVSaleItem.begin(); iter != mVSaleItem.end(); iter++) {
		ImageGp* saleItemImg = new ImageGp;
		saleItemImg = GDIPLUSMANAGER->clone(IMGCLASS->ShopMenuItem);
		saleItemImg->setSize(mItemBox.Width, mItemBox.Height);

		saleItemImg->overlayBitmap(mItemImgPos.GetLeft(), mItemImgPos.GetTop(), (*iter)->getInventoryImg()->getBitmap());

		GDIPLUSMANAGER->drawTextToBitmap(
			saleItemImg->getBitmap(),
			(*iter)->getItemName(),
			mItemNamePos,
			mFontSize,
			Color(86, 22, 12),
			Color(0, 0, 0, 0),
			XS_LEFT,
			FontStyle::FontStyleBold,
			2);

		GDIPLUSMANAGER->drawTextToBitmap(
			saleItemImg->getBitmap(),
			to_wstring((*iter)->getPrice()),
			mItemPricePos,
			mFontSize,
			Color(86, 22, 12),
			Color(0, 0, 0, 0),
			XS_RIGHT,
			FontStyle::FontStyleBold,
			2);

		saleItemImg->rebuildChachedBitmap();
		vSaleItemImg.push_back(saleItemImg);
	}

	mListBox = new ListBox;
	mListBox->init("아이템 메뉴", mSaleListRectF.X, mSaleListRectF.Y, mSaleListRectF.Width, mSaleListRectF.Height, vSaleItemImg);
	mListBox->setContentClickDownEvent([this](UIComponent* ui) {
		ListBox* convertUI = (ListBox*)ui;
		int clickIndex = convertUI->getCurSelectIndex();
		if (clickIndex != -1) {
			int price = mVSaleItem[clickIndex]->getPrice();

			if (price < PLAYER->getMoeny()) {
				PLAYER->buyItem(mVSaleItem[clickIndex]->getItemId(), 1);
			}
		}
	});

	mSaleMoneyBoard = new MoneyBoard;
	mSaleMoneyBoard->init("상점 돈 계기판", mListBox->getRectF().GetLeft(), mListBox->getRectF().GetBottom(), SALE_MONEY_BOARD_W, SALE_MONEY_BOARD_H, XS_LEFT, YS_TOP);

	//판매 인벤토리 화면
	mSaleInventory = new GridList;
	mSaleInventory->init("", mSaleMoneyBoard->getRectF().GetRight(), mListBox->getRectF().GetBottom(), SALE_INVEN_W, SALE_INVEN_H, 12, 3, GDIPLUSMANAGER->clone(IMGCLASS->InventoryBox), XS_LEFT, YS_TOP);
	mSaleInventory->setRenderIndexFunc([this](int index, RectF rcF) { PLAYER->getInventory()->render(rcF, index);});
	mSaleInventory->setMouseOverEvent([this](UIComponent* ui) {
		GridList* convertUi = (GridList*)ui;
		int tempIndex = convertUi->getIndexToXY(_ptfMouse.X, _ptfMouse.Y);
		if (mSelectInvenIndex != tempIndex) {
			mSelectInvenIndex = tempIndex;
		}
	});
	mSaleInventory->setClickDownEvent([this](UIComponent* ui) {
		if (mSelectInvenIndex != -1) {
			PLAYER->saleItem(mSelectInvenIndex, 1);
		}
	});

	return S_OK;
}

void SaleItemBox::mouseOverEvent()
{
	UIComponent::mouseOverEvent();
	if (mSaleListRectF.Contains(_ptfMouse)) {
		mListBox->mouseOverEvent();
	}

	if (mSaleInventory->getRectF().Contains(_ptfMouse)) {
		mSaleInventory->mouseOverEvent();
	}
}

void SaleItemBox::mouseOffEvent()
{
	if (mSaleListRectF.Contains(_ptfMouse)) {
		mListBox->mouseOffEvent();
	}

	if (mSaleInventory->getRectF().Contains(_ptfMouse)) {
		mSaleInventory->mouseOffEvent();
	}
}

void SaleItemBox::clickDownEvent()
{
	UIComponent::clickDownEvent();
	if (mListBox->getRectF().Contains(_ptfMouse)) {
		mListBox->clickDownEvent();
	}

	if (mSaleInventory->getRectF().Contains(_ptfMouse)) {
		mSaleInventory->clickDownEvent();
	}
}

void SaleItemBox::clickUpEvent()
{
	UIComponent::clickUpEvent();
	if (mListBox->getRectF().Contains(_ptfMouse)) {
		mListBox->clickUpEvent();
	}

	if (mSaleInventory->getRectF().Contains(_ptfMouse)) {
		mSaleInventory->clickUpEvent();
	}
}

void SaleItemBox::dragEvent()
{
	UIComponent::dragEvent();
	if (mListBox->getRectF().Contains(_ptfMouse)) {
		mListBox->dragEvent();
	}

	if (mSaleInventory->getRectF().Contains(_ptfMouse)) {
		mSaleInventory->dragEvent();
	}
}

void SaleItemBox::update()
{
}

void SaleItemBox::updateUI()
{
}

void SaleItemBox::render()
{
	mListBox->render();
	mSaleMoneyBoard->render();
	mSaleInventory->render();
	mNpcPortrait->render(mNpcPortraitRectF.GetLeft(), mNpcPortraitRectF.GetTop());
}

void SaleItemBox::release()
{
}

///////////////////////////////////////////////////////

HRESULT Clock::init(const char * id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	UIComponent::init(id, x, y, width, height, GDIPLUSMANAGER->clone(IMGCLASS->Clock), xStandard, yStandard);
	return S_OK;
}

void Clock::update()
{
	UIComponent::update();
}

void Clock::updateUI()
{
	UIComponent::updateUI();
}

void Clock::render()
{
	UIComponent::render();

	FONTMANAGER->drawText(getMemDc(), to_string(TIMEMANAGER->getGameTime()), getRectF().GetLeft(), getRectF().GetTop(), 0, RGB(255,255,0));
}

void Clock::release()
{
}

////////////////////////////////////////////////////////////////////////////////////////

HRESULT EnergePGBar::init(const char * id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	UIComponent::init(id, x, y, width, height, GDIPLUSMANAGER->clone(IMGCLASS->EnergePGBarB), xStandard, yStandard);

	mPGBarFront = GDIPLUSMANAGER->clone(IMGCLASS->EnergePGBarF);

	mFrameBorderT = 52.0f;
	mFrameBorderB = 8.0f;
	mFrameBorderW = 10.0f;

	mRectFValueArea = 
		RectFMake(getRectF().GetLeft() + mFrameBorderW,
			getRectF().GetTop() + mFrameBorderT,
			width - (mFrameBorderW * 2.0f),
			height - (mFrameBorderB + mFrameBorderT));

	mValueRECT = RectMake(
		static_cast<int>(mRectFValueArea.GetLeft()), 
		static_cast<int>(mRectFValueArea.GetTop()), 
		static_cast<int>(mRectFValueArea.Width), 
		static_cast<int>(mRectFValueArea.Height));

	mCurPlayerEnergy = PLAYER->getEnergy();

	mSufficeColor = mCurValueColor = RGB(127, 255, 0);
	mNormalColor = RGB(255, 255, 0);
	mLakeColor = RGB(255, 92, 0);

	
	return S_OK;
}

void EnergePGBar::update()
{
	UIComponent::update();

}

void EnergePGBar::updateUI()
{
	if (mCurPlayerEnergy != PLAYER->getEnergy()) { 
		mCurPlayerEnergy = PLAYER->getEnergy();
		float persent = (PLAYER->getEnergy() / PLAYER->getMaxEnergy());

		if (persent < 0.3) {
			mCurValueColor = mLakeColor;
		} else if (persent < 0.5) {
			mCurValueColor = mNormalColor;
		} else {
			mCurValueColor = mSufficeColor;
		}

		mValueHeight = mRectFValueArea.Height * persent;
		mValueRECT = RectMakeBottom(
			static_cast<int>(mRectFValueArea.GetLeft()),
			static_cast<int>(mRectFValueArea.GetBottom()),
			static_cast<int>(mRectFValueArea.Width),
			static_cast<int>(mValueHeight));
	}
}

void EnergePGBar::render()
{
	UIComponent::render();

	HBRUSH hTBrush = CreateSolidBrush(mCurValueColor);
	RectangleMake(getMemDc(), mValueRECT);
	FillRect(getMemDc(), &mValueRECT, hTBrush);
	DeleteObject(hTBrush);
	
	mPGBarFront->render(mRectF.GetLeft(), mRectF.GetTop());
}

void EnergePGBar::release()
{
}

////////////////////////////////////////////////////////////////
HRESULT GameUI::init(const char * id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	switch (xStandard) {
	case XS_LEFT:
		x = x + (width / 2.0f);
		break;
	case XS_RIGHT:
		x = x - (width / 2.0f);
		break;
	case XS_CENTER:
		break;
	}

	switch (yStandard) {
	case YS_TOP:
		y = y + (height / 2.0f);
		break;
	case YS_BOTTOM:
		y = y - (height / 2.0f);
		break;
	case YS_CENTER:
		break;
	}

	mId = id;

	mWidth = width;
	mHeight = height;

	mCenterX = x;
	mCenterY = y;

	mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
	mFocusComponent = nullptr;

	return S_OK;
}

void GameUI::update()
{
	for (mViComponent = mVComponent.begin(); mViComponent != mVComponent.end(); ++mViComponent) {
		if ((*mViComponent)->isActive()) {
			(*mViComponent)->update();
		}
	}
}

void GameUI::render()
{
	for (mViComponent = mVComponent.begin(); mViComponent != mVComponent.end(); ++mViComponent) {
		if ((*mViComponent)->isShowing()) {
			(*mViComponent)->render();
		}
	}
}

void GameUI::release()
{
}

bool GameUI::addComponent(UIComponent * component)
{
	if (mRectF.Contains(component->getRectF())) {
		mVComponent.push_back(component);
		return true;
	}

	LOG::e(component->getId() + " 추가 실패");
	return false;
}

void GameUI::mouseOverEvent()
{
	mLastEventStat = eUIEventStat::ES_MOUSE_OVER;
	for (mViComponent = mVComponent.begin(); mViComponent != mVComponent.end(); ++mViComponent) {
		if ((*mViComponent)->getRectF().Contains(_ptfMouse)) {
			if (mFocusComponent != (*mViComponent)) {
				if (mFocusComponent != nullptr) {
					mFocusComponent->mouseOffEvent();
				}
				mFocusComponent = *mViComponent;
				LOG::d(mFocusComponent->getId() + " : change focus");
			}
			mFocusComponent->mouseOverEvent();
		}
	}
}

void GameUI::mouseOffEvent()
{
	mLastEventStat = eUIEventStat::ES_MOUSE_OFF;
	if(mFocusComponent != nullptr) mFocusComponent->mouseOverEvent();
}

void GameUI::clickDownEvent()
{
	mLastEventStat = eUIEventStat::ES_CLICK_DOWN;
	if (mFocusComponent != nullptr) mFocusComponent->clickDownEvent();
}

void GameUI::clickUpEvent()
{
	mLastEventStat = eUIEventStat::ES_CLICK_UP;
	if (mFocusComponent != nullptr) mFocusComponent->clickUpEvent();
}

void GameUI::dragEvent()
{
	mLastEventStat = eUIEventStat::ES_DRAG;
	if (mFocusComponent != nullptr) mFocusComponent->dragEvent();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT QuestionBox::init()
{
	GameUI::init("질문 상자", 0,0, WINSIZE_X, WINSIZE_Y);
	
	mQuestion = new RadioList;
	vector<string> temp;
	temp.push_back("");
	temp.push_back("");
	mQuestion->init("",WIN_CENTER_X, WIN_DETAIL_SIZE_Y - 30.0f, 1277, 357, "셰먼베리 먹?", temp, XS_CENTER, YS_BOTTOM);

	addComponent(mQuestion);

	return S_OK;
}

void QuestionBox::update()
{
	GameUI::update();
}

void QuestionBox::render()
{
	GameUI::render();
}

void QuestionBox::release()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT EventBox::init(const char * id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
	GameUI::init(id, x, y, width, height, xStandard, yStandard);
	
	mOneEventHegith = 96.0f;
	
	for (int i = 0; i < 3; i++) {
		ImageGp* tempImage = GDIPLUSMANAGER->clone(IMGCLASS->EventBox);
		tempImage->setRenderBitBlt();
		tempImage->setRenderAlpha();
		mEventStack.push(tagOneEvent(tempImage));
	}

	return S_OK;
}

void EventBox::update()
{
	GameUI::update();

	if (!mEventQueue.empty()) {
		int eventSize = mEventQueue.size();
		for (int i = 0; i < eventSize; i++) {
			OneEvent* oneEvent = &(mEventQueue.front());
			oneEvent->CurEventCount -= 0.1f;
			if (oneEvent->CurEventCount <= 0.0f) {
				mEventStack.push(mEventQueue.front());
				mEventQueue.pop();
			}

			oneEvent->EventImg->offsetAlpha(-1);
		}
	}
}

void EventBox::render()
{
	//UIComponent::render();
	if (!mEventQueue.empty()) {
		queue<OneEvent> tempQueue = mEventQueue;
		int eventSize = tempQueue.size();
		for (int i = 0;i < eventSize; i++) {
			OneEvent oneEvent = tempQueue.front();
			oneEvent.EventImg->render(getRectF().GetLeft(), getRectF().GetTop() + (i * mOneEventHegith));
			tempQueue.pop();
		}
	}
}

void EventBox::release()
{
	GameUI::release();
	
}

void EventBox::addPickUpItemEvent(string itemId)
{
	if (!mEventStack.empty()) {
		OneEvent& newEvent = mEventStack.top();
		newEvent.EventImg->overlayImageGp(ITEMMANAGER->findItemReadOnly(itemId)->getInventoryImg());
		newEvent.EventImg->setAlpha((BYTE)254);
		newEvent.CurEventCount = SHOW_EVENT_TIME;
		mEventStack.pop();
		mEventQueue.push(newEvent);
	}
}

void EventBox::addHpUpEvent(string itemId)
{
}

//////////////////////////////////
HRESULT MapTool::init()
{
	GameUI::init("맵툴", 0, 0, WINSIZE_X, WINSIZE_Y);
	return S_OK;
}

void MapTool::update(void)
{
	GameUI::update();
}

void MapTool::render(void)
{
	GameUI::render();
}

void MapTool::release(void)
{
	GameUI::release();
}

////////////////

HRESULT RadioList::init(const char * id, float x, float y, float width, float height, string question, vector<string> answerList, eXStandard xStandard, eYStandard yStandard)
{
	UIComponent::init(id, x, y, width, height, GDIPLUSMANAGER->clone(IMGCLASS->QuestionBox), xStandard, yStandard);
	
	mFrameBorderH = 30.0f;
	mFrameBorderW = 38.0f;

	mAbsContentArea = RectFMake(mRectF.GetLeft() + mFrameBorderW, mRectF.GetTop() + mFrameBorderH, mWidth - (mFrameBorderW * 2.0f), mHeight - (mFrameBorderH * 2.0f));

	int allListCount = answerList.size();

	if (question != "") {
		allListCount += 1;
	}

	mOneAnswerHeight = mAbsContentArea.Height / allListCount;

	for (int i = 0; i < allListCount; i++) {
		mVRectF.push_back(RectFMake(mAbsContentArea.X, mAbsContentArea.Y + i * mOneAnswerHeight, mAbsContentArea.Width, mOneAnswerHeight));
	}


	setMouseOverEvent([this](UIComponent* ui) {
		int tempIndex = getIndexToXY(_ptfMouse.X, _ptfMouse.Y);
		if (mCurSelectIndex != tempIndex) {
			
			if (mCurSelectIndex != -1) {
			}
			mCurSelectIndex = tempIndex;
		}
	});

	setMouseOffEvent([this](UIComponent* ui) {
		mCurSelectIndex = -1;
	});



	return S_OK;
}

void RadioList::render()
{
	UIComponent::render();
	for (auto iter = mVRectF.begin(); iter != mVRectF.end(); ++iter) {
		FONTMANAGER->drawText(getMemDc(), "셰먹?", iter->X, iter->Y, 1, RGB(0,0,0));
		GDIPLUSMANAGER->drawRectF(*iter, CR_RED, CR_NONE);
	}
}

