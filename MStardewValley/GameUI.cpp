#include "Stdafx.h"
#include "GameUI.h"

HRESULT GameUI::init(const char* id, float x, float y, float width, float height, ImageBase * img)
{
	if (img == nullptr) {
		isInitSuccess = false;
		MY_UTIL::log(DEBUG_GAME_UI_TAG, (string)id + " - (init 실패) 이미지 null");
		return E_FAIL;
	}

	isGdiPlus = false;


	mImgBase = img;

	mWidth = mImgBase->getWidth();
	mHeight = mImgBase->getHeight();

	mX = x;
	mY = y;

	mStat = eStat::NONE;

	mRECT = RECT_MAKE_FUNCTION;

	isMouseOver = false;
	isMouseClick = false;
	isInitSuccess = true;

	mId = id;

	return S_OK;
}

HRESULT GameUI::init(const char* id, float x, float y, ImageBase * img)
{
	if (img == nullptr) {
		isInitSuccess = false;
		MY_UTIL::log(DEBUG_GAME_UI_TAG, (string)id + " - (init 실패) 이미지 null");
		return E_FAIL;
	}

	isGdiPlus = false;
	mStat = eStat::NONE;

	mImgBase = img;

	mWidth = img->getWidth();
	mHeight = img->getHeight();

	mX = x;
	mY = y;

	mRECT = RECT_MAKE_FUNCTION;

	isMouseOver = false;
	isMouseClick = false;
	isInitSuccess = true;

	mId = id;

	return S_OK;
}

HRESULT GameUI::init(const char* id, float x, float y, float width, float height, ImageGp * img)
{
	if (img == nullptr) {
		isInitSuccess = false;
		MY_UTIL::log(DEBUG_GAME_UI_TAG, (string)id + " - (init 실패) 이미지 null");
		return E_FAIL;
	}

	isGdiPlus = true;
	mStat = eStat::NONE;

	mImgGp = img;

	if (img->getWidth() != width || img->getHeight() != height) {
		img->setSize(width, height);
	}

	mWidth = width;
	mHeight = height;

	mX = x;
	mY = y;
	
	mRECT = RECT_MAKE_FUNCTION;

	isMouseOver = false;
	isMouseClick = false;
	isInitSuccess = true;

	mId = id;

	return S_OK;
}

HRESULT GameUI::init(const char* id, float x, float y, ImageGp * img)
{
	if (img == nullptr) {
		isInitSuccess = false;
		MY_UTIL::log(DEBUG_GAME_UI_TAG, (string)id + " - (init 실패) 이미지 null");
		return E_FAIL;
	}

	isGdiPlus = true;
	mStat = eStat::NONE;

	mImgGp = img;

	mWidth = img->getWidth();
	mHeight = img->getHeight();

	mX = x;
	mY = y;

	mRECT = RECT_MAKE_FUNCTION;

	isMouseOver = false;
	isMouseClick = false;
	isInitSuccess = true;
	mId = id;

	return S_OK;
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
	if (PtInRect(&mRECT, _ptMouse)) {
		if (!isMouseOver) {
			isMouseOver = true;
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			if (!isMouseClick) {
				isMouseClick = true;
			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			if (!isMouseClick) {
				isMouseClick = false;
			}
		}
	}

	switch (mStat) {
	case eStat::SIZE_TO_BIG:
		if (mSizeChangeWidth > mWidth * mToSizeRatio) {
			mStat = eStat::SIZE_BIG;
		}
		else {
			mSizeChangeWidth = mSizeChangeWidth + SIZE_CHANGE_SPEED;
			mSizeChangeHeight = mSizeChangeHeight + (SIZE_CHANGE_SPEED / mSizeChangeRatio);
			mSizeChangeRectF = RectFMakeCenter(mX, mY, mSizeChangeWidth, mSizeChangeHeight);
		}
		break;
	case  eStat::SIZE_TO_ORIGINAL:
		if (mSizeChangeWidth < mWidth) {
			mStat = eStat::NONE;
		}
		else {
			mSizeChangeWidth = mSizeChangeWidth - SIZE_CHANGE_SPEED;
			mSizeChangeHeight = mSizeChangeHeight - (SIZE_CHANGE_SPEED / mSizeChangeRatio);
			mSizeChangeRectF = RectFMakeCenter(mX, mY, mSizeChangeWidth, mSizeChangeHeight);
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
	if (isGdiPlus) {
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
	}
	else {
		mImgBase->render(getMemDc(), mX, mY);
	}
}

void GameUI::render(float x, float y, float width, float height)
{
	if (!isInitSuccess) return;
	if (isGdiPlus) {
		mImgGp->render(getMemDc(), x, y, width, height);
	}
	else {
		mImgBase->render(getMemDc(), mX, mY);
	}
}

void GameUI::render(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	if (!isInitSuccess) return;
	if (isGdiPlus) {
		mImgGp->render(getMemDc(), destX, destY, sourX, sourY, sourWidth, sourHeight);
	}
}

void GameUI::release()
{
	if (!isInitSuccess) return;
	mImgGp->release();
	SAFE_DELETE(mImgGp);
}

void GameUI::setWidth(float width)
{
	if (isGdiPlus) {
		mWidth = width;
		mRECT = RECT_MAKE_FUNCTION;
		mImgGp->setWidth(width);
	}
}

void GameUI::setHeight(float height)
{
	if (isGdiPlus) {
		mHeight = height;
		mRECT = RECT_MAKE_FUNCTION;
		mImgGp->setHeight(height);
	}
}

HRESULT ScrollBox::init(const char* id, float x, float y, float width, float height, GameUI* gameUI)
{
	GameUI::init(id, x, y, width, height, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->UISetupBox));
	
	isDrag = false;

	mValueGameUi = gameUI;
	
	//스크롤바 상자 설정
	mFrameBorderW = 10.0f;
	mFrameBorderH = 15.0f;
	
	mValueX = mX + mFrameBorderW;
	mValueY = mY + mFrameBorderH;

	mValueWidth = mWidth * 0.9f - (mFrameBorderW * 2.0f);
	mValueHeight = mHeight - (mFrameBorderH * 2.0f);

	mValueRECT = RectMakeCenter(mValueX, mValueY, mValueWidth, mValueHeight);

	mHScrollBarW = mWidth * 0.1f - (mFrameBorderW * 2.0f);
	mHScrollBarH = mHeight - (mFrameBorderH * 2.0f);

	mHScrollBarX = mWidth - mHScrollBarW - mFrameBorderW;
	mHScrollBarY = mY + mFrameBorderH;

	mHScrollBtnW = mHScrollBarW;
	mHScrollBtnH = mHScrollBarH * 0.2f;

	mHScrollBtnX = mHScrollBarX;
	mHScrollBtnY = mHScrollBarY;

	PointF mHScrolBarPt = GetCenterPtF(mHScrollBarX, mHScrollBarY, mHScrollBarW, mHScrollBarH);
	mHScrollBar = new GameUI;
	mHScrollBar->init("샘플 위아래 스크롤", mHScrolBarPt.X, mHScrolBarPt.Y, mHScrollBarW, mHScrollBarH, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->UIScrollBar));

	PointF mHScrollBtnPt = GetCenterPtF(mHScrollBtnX, mHScrollBtnY, mHScrollBtnW, mHScrollBtnH);
	mHScrollBtn = new GameUI;
	mHScrollBtn->init("샘플 위아래 스크롤", mHScrollBtnPt.X, mHScrollBtnPt.Y, mHScrollBtnW, mHScrollBtnH, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->UIScrollBtn));

	return S_OK;
}

void ScrollBox::render()
{
	mImgGp->render(getMemDc(), mX, mY);
	mHScrollBar->render();
	mHScrollBtn->render();
	mValueGameUi->render(mValueX, mValueY, 0, mHScrollBtnY, mValueWidth, mValueHeight);
	
	float relY = (mHScrollBtn->getRECT().top - mHScrollBarY) + mValueGameUi->getY();
	float relX = (mHScrollBtn->getRECT().left - mHScrollBarX) + mValueGameUi->getX();

	GDIPLUSMANAGER->drawRectF(getMemDc(), relX, relY, mValueWidth, mValueHeight);
}

void ScrollBox::update()
{
	GameUI::update();

	/*
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		if (PtInRect(&mHScrollBtn->getRECT(), _ptMouse)) {
			isDrag = true;
			mHpt = _ptMouse.y -  mHScrollBtn->getY();
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		isDrag = false;
	}
	*/

	if (isDrag) {
		float tempBtnY = _ptMouse.y - mHpt;
		RECT tempRECT = RectMakeCenter(mHScrollBtnX, tempBtnY, mHScrollBtnW, mHScrollBtnH);
		if (mHScrollBar->getRECT().top <= tempRECT.top && mHScrollBar->getRECT().bottom > tempRECT.bottom) {
			mHScrollBtn->setY(tempBtnY);
		}
	}
}

HRESULT SButton::init(const char* id, float x, float y, float width, float height, ImageBase * img)
{
	GameUI::init(id, x, y, width, height, img);
	mIsSelected = false;
	return S_OK;
}

HRESULT SButton::init(const char* id, float x, float y, ImageBase * img)
{
	GameUI::init(id, x, y, img);
	mIsSelected = false;
	return S_OK;
}

HRESULT SButton::init(const char* id, float x, float y, float width, float height, ImageGp * img)
{
	GameUI::init(id, x, y, width, height, img);
	mIsSelected = false;
	return S_OK;
}

HRESULT SButton::init(const char* id, float x, float y, ImageGp * img)
{
	GameUI::init(id, x, y, img);
	mIsSelected = false;
	return S_OK;
}

int counts = 0;

void SButton::clickDownEvent()
{
	if (isMouseOver) {
		if (!isMouseClick) {
			isMouseClick = true;
			mIsSelected = true;

			if (!SOUNDMANAGER->isPlaySound(SOUNDCLASS->MenuBtnClickEffect)) {
				SOUNDMANAGER->play(SOUNDCLASS->MenuBtnClickEffect);
			}
		}
	}
}

void SButton::clickUpEvent()
{
	if (isMouseClick) {
		isMouseClick = false;
	}
}

void SButton::update()
{
	if (!isInitSuccess) return;
	if (PtInRect(&mRECT, _ptMouse)) {
		if (!isMouseOver) {
			isMouseOver = true;

			if (!SOUNDMANAGER->isPlaySound(SOUNDCLASS->MenuBtnMouseOverEffect)) {
				SOUNDMANAGER->play(SOUNDCLASS->MenuBtnMouseOverEffect, 1.0f);
			}

			this->sizeToBig(1.2f);
		}
	} else {
		if (isMouseOver) {
			isMouseOver = false;

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
		}
		else {
			mSizeChangeWidth = mSizeChangeWidth + 2;
			mSizeChangeHeight = mSizeChangeHeight + (2.0f / mSizeChangeRatio);
			mSizeChangeRectF = RectFMakeCenter(mX, mY, mSizeChangeWidth, mSizeChangeHeight);
		}
	}
	else if (mStat == eStat::SIZE_TO_ORIGINAL) {
		if (mSizeChangeWidth < mWidth) {
			mStat = eStat::NONE;
			mImgGp->backOriginalColor();
		}
		else {
			mSizeChangeWidth = mSizeChangeWidth - 2;
			mSizeChangeHeight = mSizeChangeHeight - (2.0f / mSizeChangeRatio);
			mSizeChangeRectF = RectFMakeCenter(mX, mY, mSizeChangeWidth, mSizeChangeHeight);
		}
	}
}

void SButton::render()
{
	GameUI::render();
}
