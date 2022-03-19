#include "Stdafx.h"
#include "GameUI.h"

HRESULT GameUI::init(string id, const char* imgKey, float x, float y, bool isGdiPlus)
{
	this->isGdiPlus = isGdiPlus;
	
	mStat = eStat::NONE;

	if (isGdiPlus) {
		mImg = GDIPLUSMANAGER->findAndCloneImage(imgKey);
		mImgKey = imgKey;

		mWidth = mImg->getWidth();
		mHeight = mImg->getHeight();

		mX = x;
		mY = y;

		mRc = RECT_MAKE_FUNCTION;
	}
	else {
		mImgB = IMAGEMANAGER->findImage(imgKey);
		mImgKey = imgKey;

		mWidth = mImgB->getWidth();
		mHeight = mImgB->getHeight();

		mX = x;
		mY = y;

		mRc = RECT_MAKE_FUNCTION;
	}

	isMouseOver = false;
	isMouseClick = false;

	return S_OK;
}

void GameUI::sizeToBig()
{
	if (mStat == eStat::SIZE_TO_BIG || mStat == eStat::SIZE_BIG) return;
	
	mStat = eStat::SIZE_TO_BIG;

	mSizeChangeWidth = mWidth;
	mSizeChangeHeight = mHeight;
	mSizeChangeRatio = mSizeChangeWidth / mSizeChangeHeight;

	cout << endl;
}

void GameUI::sizeToOriginal()
{
	if (mStat == eStat::SIZE_TO_ORIGINAL || mStat == eStat::NONE) return;
	mStat = eStat::SIZE_TO_ORIGINAL;
}

void GameUI::update()
{
	if (mStat == eStat::SIZE_TO_BIG) {
		if (mSizeChangeWidth > mWidth * 1.3) {
			mStat = eStat::SIZE_BIG;
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
		}
		else {
			mSizeChangeWidth = mSizeChangeWidth - 2;
			mSizeChangeHeight = mSizeChangeHeight - (2.0f / mSizeChangeRatio);
			mSizeChangeRectF = RectFMakeCenter(mX, mY, mSizeChangeWidth, mSizeChangeHeight);
		}
	}
}

void GameUI::render()
{
	if (isGdiPlus) {
		switch (mStat) {
		case eStat::SIZE_TO_BIG: case eStat::SIZE_BIG: case eStat::SIZE_TO_ORIGINAL:
			mImg->render(getMemDc(), mSizeChangeRectF);
			break;
		case eStat::NONE:
			mImg->render(getMemDc(), mRc.left, mRc.top);
			//RectangleMake(getMemDc(), mRc);
			break;
		default:
			//!DO NOTHING
			break;
		}
	}
	else {
		mImgB->render(getMemDc(), mX, mY);
	}
}

void GameUI::render(float x, float y, float width, float height)
{
	if (isGdiPlus) {
		mImg->render(getMemDc(), x, y, width, height);
	}
	else {
		IMAGEMANAGER->render(mImgKey, getMemDc(), mX, mY);
	}
}

void GameUI::render(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	if (isGdiPlus) {
		mImg->render(getMemDc(), destX, destY, sourX, sourY, sourWidth, sourHeight);
	}
}

void GameUI::release()
{
}

void GameUI::mouseOverEvent()
{
	if (!isMouseOver) {
		isMouseOver = true;
		if (!SOUNDMANAGER->isPlaySound(SOUNDCLASS->MenuBtnMouseOverEffect)) {
			SOUNDMANAGER->play(SOUNDCLASS->MenuBtnMouseOverEffect, 1.0f);
		}
		this->sizeToBig();
	}
}

void GameUI::mouseOutEvent()
{
	if (isMouseOver) {
		isMouseOver = false;
		if (SOUNDMANAGER->isPlaySound(SOUNDCLASS->MenuBtnMouseOverEffect)) {
			SOUNDMANAGER->stop(SOUNDCLASS->MenuBtnMouseOverEffect);
		}
		if (SOUNDMANAGER->isPlaySound(SOUNDCLASS->MenuBtnClickEffect)) {
			SOUNDMANAGER->stop(SOUNDCLASS->MenuBtnClickEffect);
		}
		this->sizeToOriginal();
	}
}

void GameUI::mouseClickDownEvent()
{
	if (!isMouseClick) {
		isMouseClick = true;
		if (!SOUNDMANAGER->isPlaySound(SOUNDCLASS->MenuBtnClickEffect)) {
			SOUNDMANAGER->play(SOUNDCLASS->MenuBtnClickEffect);
		}
	}
}

void GameUI::mouseClickUpEvent()
{
	if (isMouseClick) {
		isMouseClick = false;
	}
}

void GameUI::setWidth(float width)
{
	if (isGdiPlus) {
		mWidth = width;
		mRc = RECT_MAKE_FUNCTION;
		mImg->setWidth(width);
	}
}

void GameUI::setHeight(float height)
{
	if (isGdiPlus) {
		mHeight = height;
		mRc = RECT_MAKE_FUNCTION;
		mImg->setHeight(height);
	}
}

HRESULT ScrollBox::init(string id, const char * imgKey, float x, float y, bool isGdiPlus, float width, float height, GameUI * gameUI)
{
	mImg = GDIPLUSMANAGER->findAndCloneImage(imgKey);
	mImgKey = imgKey;

	mWidth = width;
	mHeight = height;

	mX = x;
	mY = y;

	mFrameBorder = 10.0f;
	mRc = RECT_MAKE_FUNCTION;

	mValueGameUi = gameUI;

	mImg->setSize(mWidth, mHeight);
	
	float b =  mHeight/ mValueGameUi->getHeight();
	

	mHScrollBtn = new GameUI;
	mHScrollBtn->init("샘플 위아래 스크롤 : " + string(imgKey), IMGCLASS->UIScrollBtn, mX - 20, mY, true);
	float c = mHeight * b;
	mHScrollBtn->setHeight(mHeight * b);

	return S_OK;
}

void ScrollBox::render()
{
	mImg->render(getMemDc(), mX, mY);
	mValueGameUi->render(mX + mFrameBorder, mY + mFrameBorder, mX, mY, mWidth - mFrameBorder, mHeight - mFrameBorder);
	mHScrollBtn->render();
}

void ScrollBox::update()
{
	GameUI::update();
}
