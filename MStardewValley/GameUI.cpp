#include "Stdafx.h"
#include "GameUI.h"

//private
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

	isInitSuccess = true;

	mId = id;

	return S_OK;
}

HRESULT GameUI::init(const char * id, float x, float y, float width, float height)
{
	mResType = eResType::RT_NONE;
	
	mImgGp = new ImageGp();
	mImgGp->init(getMemDc(), width, height);

	mWidth = width;
	mHeight = height;

	return init(id, x, y, XS_LEFT, YS_TOP);
}

HRESULT GameUI::init(const char* id, float centerX, float centerY, float width, float height, ImageBase * img, eXStandard xStandard, eYStandard yStandard)
{
	if (img == nullptr) {
		isInitSuccess = false;
		MY_UTIL::log(DEBUG_GAME_UI_TAG, (string)id + " - (init 실패) 이미지 null");
		return E_FAIL;
	}

	mResType = eResType::RT_IMAGE_BASE;

	mImgBase = img;

	mWidth = mImgBase->getWidth();
	mHeight = mImgBase->getHeight();

	 return init(id, centerX, centerY, xStandard, yStandard);
}

HRESULT GameUI::init(const char* id, float centerX, float centerY, ImageBase * img, eXStandard xStandard, eYStandard yStandard)
{
	if (img == nullptr) {
		isInitSuccess = false;
		MY_UTIL::log(DEBUG_GAME_UI_TAG, (string)id + " - (init 실패) 이미지 null");
		return E_FAIL;
	}

	mResType = eResType::RT_IMAGE_BASE;

	mImgBase = img;

	mWidth = img->getWidth();
	mHeight = img->getHeight();

	return init(id, centerX, centerY, xStandard, yStandard);
}

HRESULT GameUI::init(const char* id, float centerX, float centerY, float width, float height, ImageGp * img, eXStandard xStandard, eYStandard yStandard)
{
	if (img == nullptr) {
		isInitSuccess = false;
		MY_UTIL::log(DEBUG_GAME_UI_TAG, (string)id + " - (init 실패) 이미지 null");
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

HRESULT GameUI::init(const char* id, float centerX, float centerY, ImageGp * img, eXStandard xStandard, eYStandard yStandard)
{
	if (img == nullptr) {
		isInitSuccess = false;
		MY_UTIL::log(DEBUG_GAME_UI_TAG, (string)id + " - (init 실패) 이미지 null");
		return E_FAIL;
	}

	mResType = eResType::RT_GDI_PLUS;

	mImgGp = img;

	mWidth = img->getWidth();
	mHeight = img->getHeight();

	return init(id, centerX, centerY, xStandard, yStandard);
}

void GameUI::sizeToBig(float toSizeRatio)
{
	if (mStat != eStat::SIZE_TO_BIG && mStat != eStat::SIZE_BIG) {
		mToSizeRatio = toSizeRatio;

		mStat = eStat::SIZE_TO_BIG;

		mSizeChangeWidth = mWidth;
		mSizeChangeHeight = mHeight;
		mSizeChangeRatio = mSizeChangeWidth / mSizeChangeHeight;
	};

}

void GameUI::sizeToOriginal()
{
	if (mStat != eStat::SIZE_TO_ORIGINAL && mStat != eStat::NONE) {
		mStat = eStat::SIZE_TO_ORIGINAL;
	}
}

void GameUI::update()
{
	if (!isInitSuccess) return;

	switch (mStat) {
	case eStat::SIZE_TO_BIG:
		if (mSizeChangeWidth > mWidth * mToSizeRatio) {
			mStat = eStat::SIZE_BIG;
		}
		else {
			mSizeChangeWidth = mSizeChangeWidth + SIZE_CHANGE_SPEED;
			mSizeChangeHeight = mSizeChangeHeight + (SIZE_CHANGE_SPEED / mSizeChangeRatio);
			mSizeChangeRectF = RectFMakeCenter(mCenterX, mCenterY, mSizeChangeWidth, mSizeChangeHeight);
		}
		break;
	case  eStat::SIZE_TO_ORIGINAL:
		if (mSizeChangeWidth < mWidth) {
			mStat = eStat::NONE;
		}
		else {
			mSizeChangeWidth = mSizeChangeWidth - SIZE_CHANGE_SPEED;
			mSizeChangeHeight = mSizeChangeHeight - (SIZE_CHANGE_SPEED / mSizeChangeRatio);
			mSizeChangeRectF = RectFMakeCenter(mCenterX, mCenterY, mSizeChangeWidth, mSizeChangeHeight);
		}
		break;
	default:
		//!DO NOTHING
		break;
	}
}

void GameUI::render()
{
	if (!isInitSuccess) return;
	switch (mResType) {
	case eResType::RT_GDI_PLUS:
		switch (mStat) {
		case eStat::SIZE_TO_BIG: case eStat::SIZE_BIG: case eStat::SIZE_TO_ORIGINAL:
			mImgGp->render(getMemDc(), mSizeChangeRectF);
			break;
		case eStat::NONE:
			mImgGp->render(getMemDc(), mRECT.left, mRECT.top);
			break;
		default:
			//!DO NOTHING
			break;
		}
		break;
	case eResType::RT_IMAGE_BASE:
		mImgBase->render(getMemDc(), mCenterX, mCenterY);
		break;
	case eResType::RT_NONE:
		break;
	default:
		break;

	}
}

void GameUI::render(float x, float y)
{
	if (!isInitSuccess) return;
	switch (mResType) {
	case eResType::RT_GDI_PLUS:
		mImgGp->render(getMemDc(), x, y);
		break;
	case eResType::RT_IMAGE_BASE:
		mImgBase->render(getMemDc(), x, y);
		break;
	case eResType::RT_NONE:
		mImgGp->render(getMemDc(), x, y);
		break;
	default:
		break;

	}
}

void GameUI::render(float x, float y, float width, float height)
{
	if (!isInitSuccess) return;
	switch (mResType) {
		case eResType::RT_GDI_PLUS:
			mImgGp->render(getMemDc(), x, y, width, height);
			break;
		case eResType::RT_IMAGE_BASE:
			mImgBase->render(getMemDc(), mCenterX, mCenterY);
			break;
		case eResType::RT_NONE:
			break;
		default:
			break;
	}
}

void GameUI::render(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	if (!isInitSuccess) return;
	switch (mResType) {
	case eResType::RT_GDI_PLUS:
		mImgGp->render(getMemDc(), destX, destY, sourX, sourY, sourWidth, sourHeight);
		break;
	case eResType::RT_IMAGE_BASE:
		mImgBase->render(getMemDc(), mCenterX, mCenterY);
		break;
	case eResType::RT_NONE:
		mImgGp->render(getMemDc(), destX, destY, sourX, sourY, sourWidth, sourHeight);
		break;
	default:
		break;
	}
}

void GameUI::release()
{
	if (!isInitSuccess) return;
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
	}
}

void GameUI::setHeight(float height)
{
	if (mResType == eResType::RT_GDI_PLUS) {
		mHeight = height;
		mRECT = RECT_MAKE_FUNCTION;
		mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
		mImgGp->setHeight(height);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT ScrollBox::init(const char* id, float x, float y, float width, float height, GameUI* gameUI, eXStandard xStandard, eYStandard yStandard)
{
	GameUI::init(id, x, y, width, height, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->UISetupBox), xStandard, yStandard);
	
	mContent = gameUI;

	isVScrollDrag = false;
	isHScrollDrag = false;

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
	float vScrollBarW = 30.0f;
	float vScrollBarH = height - (mFrameBorderH * 2.0f) - vScrollBarW;

	float vScrollBarX = mRectF.GetRight() - vScrollBarW - mFrameBorderW;
	float vScrollBarY = mRectF.GetTop() + mFrameBorderH;

	float vScrollBtnW = vScrollBarW;
	float vScrollBtnH = height - (mFrameBorderH * 2.0f) - (gameUI->getHeight() - contentAreaHeight);

	float vScrollBtnX = vScrollBarX;
	float vScrollBtnY = vScrollBarY;

	mVScrollBar = new GameUI;
	mVScrollBar->init("수직 스크롤 바", vScrollBarX, vScrollBarY, vScrollBarW, vScrollBarH, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->UIVScrollBar), XS_LEFT, YS_TOP);

	mVScrollBtn = new GameUI;
	mVScrollBtn->init("수직 스크롤 버튼", vScrollBtnX, vScrollBarY, vScrollBtnW, vScrollBtnH, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->UIVScrollBtn), XS_LEFT, YS_TOP);

	mVScrollMoveDistance = 0.0f;

	//horizantal 스크롤바 설정
	float hScrollBarH = 30.0f;
	float hScrollBarW = width - (mFrameBorderW * 2.0f) - hScrollBarH;

	float hScrollBarX = mRectF.GetLeft() + mFrameBorderW;
	float hScrollBarY = mRectF.GetBottom() - hScrollBarH - mFrameBorderH;

	float hScrollBtnW = hScrollBarW * 0.2f;
	float hScrollBtnH = hScrollBarH;

	float hScrollBtnX = hScrollBarX;
	float hScrollBtnY = hScrollBarY;

	mHScrollBar = new GameUI;
	mHScrollBar->init("수평 스크롤 바", hScrollBarX, hScrollBarY, hScrollBarW, hScrollBarH, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->UIHScrollBar), XS_LEFT, YS_TOP);

	mHScrollBtn = new GameUI;
	mHScrollBtn->init("수평 스크롤 버튼", hScrollBtnX, hScrollBarY, hScrollBtnW, hScrollBtnH, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->UIHScrollBtn), XS_LEFT, YS_TOP);

	mHScrollMoveDistance = 0.0f;

	clipingContentArea();
	return S_OK;
}

void ScrollBox::render()
{
	//debug
	mImgGp->render(getMemDc(), mRectF.X, mRectF.Y);
	mVScrollBar->render();
	mVScrollBtn->render();
	mHScrollBar->render();
	mHScrollBtn->render();
	mContent->render(mAbsContentArea.GetLeft(), mAbsContentArea.GetTop());
}

void ScrollBox::update()
{
	GameUI::update();

	if (isVScrollDrag) {
		Gdiplus::RectF tempMoveRectF = RectFMake(mVScrollBtn->getRectF().GetLeft(), _ptMouse.y - mVScrollPtDistance, mVScrollBtn->getRectF().Width, mVScrollBtn->getRectF().Height);
		float tempVScrollDistance = tempMoveRectF.GetTop() - mVScrollBar->getRectF().GetTop();

		if (mVScrollMoveDistance != tempVScrollDistance) {
			if (mVScrollBar->getRectF().GetTop() > tempMoveRectF.GetTop()) {
				mVScrollBtn->setY(mVScrollBar->getRectF().GetTop(), YS_TOP);
			}
			else if (mVScrollBar->getRectF().GetBottom() < tempMoveRectF.GetBottom())
			{
				mVScrollBtn->setY(mVScrollBar->getRectF().GetBottom(), YS_BOTTOM);
			}
			else {
				mVScrollBtn->setY(tempMoveRectF.GetTop(), YS_TOP);
			}

			mVScrollMoveDistance = mVScrollBtn->getRectF().GetTop() - mVScrollBar->getRectF().GetTop();
			clipingContentArea();
		}
	}

	if (isHScrollDrag) {
		Gdiplus::RectF tempMoveRectF = RectFMake(_ptMouse.x - mHScrollPtDistance, mHScrollBtn->getRectF().GetTop(), mHScrollBtn->getRectF().Width, mHScrollBtn->getRectF().Height);
		float tempHScrollDistance = tempMoveRectF.GetLeft() - mHScrollBar->getRectF().GetLeft();

		if (mHScrollMoveDistance != tempHScrollDistance) {
			if (mHScrollBar->getRectF().GetLeft() > tempMoveRectF.GetLeft()) {
				mHScrollBtn->setX(mHScrollBar->getRectF().GetLeft(), XS_LEFT);
			}
			else if (mHScrollBar->getRectF().GetRight() < tempMoveRectF.GetRight())
			{
				mHScrollBtn->setX(mHScrollBar->getRectF().GetRight(), XS_RIGHT);
			}
			else {
				mHScrollBtn->setX(tempMoveRectF.GetLeft(), XS_LEFT);
			}

			mHScrollMoveDistance = mHScrollBtn->getRectF().GetLeft() - mHScrollBar->getRectF().GetLeft();
			clipingContentArea();
		}
	}
}

void ScrollBox::clickDownEvent()
{
	if (bIsMouseOver) {
		if (!bIsMouseClick) {
			bIsMouseClick = true;

			if (mAbsContentArea.Contains(Gdiplus::PointF(_ptMouse.x, _ptMouse.y))) {

			} else if(mVScrollBtn->getRectF().Contains(Gdiplus::PointF(_ptMouse.x, _ptMouse.y))) {
				isVScrollDrag = true;
				mVScrollPtDistance = _ptMouse.y - mVScrollBtn->getRectF().GetTop();
			} else if (mHScrollBtn->getRectF().Contains(Gdiplus::PointF(_ptMouse.x, _ptMouse.y))) {
				isHScrollDrag = true;
				mHScrollPtDistance = _ptMouse.x - mHScrollBtn->getRectF().GetLeft();
			}
		}
	}
}

void ScrollBox::clickUpEvent()
{
	if (bIsMouseClick) {
		bIsMouseClick = false;
		isVScrollDrag = false;
		isHScrollDrag = false;
	}
}

void ScrollBox::mouseOverEvent()
{
	if (!bIsMouseOver) {
		bIsMouseOver = true;
	}
}

void ScrollBox::mouseOffEvent()
{
	if (bIsMouseOver) {
		bIsMouseOver = false;
	}
}

void ScrollBox::clipingContentArea()
{
	mContent->getImgGp()->clipping(0, 0, mHScrollMoveDistance, mVScrollMoveDistance, mAbsContentArea.Width, mAbsContentArea.Height);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SButton::clickDownEvent()
{
	if (bIsMouseOver) {
		if (!bIsMouseClick) {
			bIsMouseClick = true;
			bIsSelected = true;

			if (!SOUNDMANAGER->isPlaySound(SOUNDCLASS->MenuBtnClickEffect)) {
				SOUNDMANAGER->play(SOUNDCLASS->MenuBtnClickEffect);
			}
		}
	}
}

void SButton::clickUpEvent()
{
	if (bIsMouseClick) {
		bIsMouseClick = false;
	}
}

void SButton::update()
{
	if (!isInitSuccess) return;
	if (PtInRect(&mRECT, _ptMouse)) {
		if (!bIsMouseOver) {
			bIsMouseOver = true;

			if (!SOUNDMANAGER->isPlaySound(SOUNDCLASS->MenuBtnMouseOverEffect)) {
				SOUNDMANAGER->play(SOUNDCLASS->MenuBtnMouseOverEffect, 1.0f);
			}

			this->sizeToBig(1.2f);
		}
	} else {
		if (bIsMouseOver) {
			bIsMouseOver = false;

			if (SOUNDMANAGER->isPlaySound(SOUNDCLASS->MenuBtnMouseOverEffect)) {
				SOUNDMANAGER->stop(SOUNDCLASS->MenuBtnMouseOverEffect);
			}

			this->sizeToOriginal();
		}
	}

	if (mStat == eStat::SIZE_TO_BIG) {
		if (mSizeChangeWidth > mWidth * 1.1) {
			mStat = eStat::SIZE_BIG;
			mImgGp->changeColor();
		} else {
			mSizeChangeWidth = mSizeChangeWidth + 2;
			mSizeChangeHeight = mSizeChangeHeight + (2.0f / mSizeChangeRatio);
			mSizeChangeRectF = RectFMakeCenter(mCenterX, mCenterY, mSizeChangeWidth, mSizeChangeHeight);
		}
	}
	else if (mStat == eStat::SIZE_TO_ORIGINAL) {
		if (mSizeChangeWidth < mWidth) {
			mStat = eStat::NONE;
			mImgGp->backOriginalColor();
		} else {
			mSizeChangeWidth = mSizeChangeWidth - 2;
			mSizeChangeHeight = mSizeChangeHeight - (2.0f / mSizeChangeRatio);
			mSizeChangeRectF = RectFMakeCenter(mCenterX, mCenterY, mSizeChangeWidth, mSizeChangeHeight);
		}
	}
}

void SButton::render()
{
	GameUI::render();
}