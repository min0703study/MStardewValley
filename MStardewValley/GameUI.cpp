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

	isDrag = false;

	//스크롤바 상자 설정
	mFrameBorderW = 10.0f * (width / (WINSIZE_X * 0.25f));
	mFrameBorderH = 15.0f * (height / (WINSIZE_Y * 0.5f));

	//스크롤바 설정
	float hScrollBarW = 30.0f;
	float hScrollBarH = height - (mFrameBorderH * 2.0f);

	float hScrollBarX = mRectF.GetRight() - hScrollBarW - mFrameBorderW;
	float hScrollBarY = mRectF.GetTop() + mFrameBorderH;

	mHScrollBar = new GameUI;
	mHScrollBar->init("샘플 위아래 스크롤", hScrollBarX, hScrollBarY, hScrollBarW, hScrollBarH, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->UIScrollBar), XS_LEFT, YS_TOP);

	//스크롤바 컨트롤 버튼 설정
	float hScrollBtnW = hScrollBarW;
	float hScrollBtnH = hScrollBarH * 0.2f;

	float hScrollBtnX = hScrollBarX;
	float hScrollBtnY = hScrollBarY;

	mHScrollBtn = new GameUI;
	mHScrollBtn->init("샘플 위아래 스크롤", hScrollBtnX, hScrollBarY, hScrollBtnW, hScrollBtnH, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->UIScrollBtn), XS_LEFT, YS_TOP);

	//콘텐츠 영역 설정
	float contentAreaX = mRectF.GetLeft() + mFrameBorderW;
	float contentAreaY = mRectF.GetTop() + mFrameBorderH;

	float contentAreaWidth = mWidth - hScrollBarW - (mFrameBorderW * 2.0f);
	float contentAreaHeight = mHeight - (mFrameBorderH * 2.0f);

	mContentArea = RectFMake(contentAreaX, contentAreaY, contentAreaWidth, contentAreaHeight);
	mValueRECT = RectMake(contentAreaX, contentAreaY, contentAreaWidth, contentAreaHeight);

	return S_OK;
}

void ScrollBox::render()
{
	mImgGp->render(getMemDc(), mRectF.X, mRectF.Y);
	mHScrollBar->render();
	mHScrollBtn->render();
	mContent->render(mContentArea.GetLeft(), mContentArea.GetTop(), 0, mHScrollBtn->getRectF().GetTop(), mContentArea.Width, mContentArea.Height);
}

void ScrollBox::update()
{
	GameUI::update();

	if (isDrag) {
		Gdiplus::RectF tempMoveRectF = RectFMake(mHScrollBtn->getRectF().GetLeft(), _ptMouse.y - mHpt, mHScrollBtn->getRectF().Width, mHScrollBtn->getRectF().Height);

		if (mHScrollBar->getRectF().GetTop() > tempMoveRectF.GetTop()) {

			mHScrollBtn->setY(mHScrollBar->getRectF().GetTop() + tempMoveRectF.Height / 2.0f);
		}
		else if (mHScrollBar->getRectF().GetBottom() < tempMoveRectF.GetBottom())
		{
			mHScrollBtn->setY(mHScrollBar->getRectF().GetBottom() - tempMoveRectF.Height / 2.0f);
		}
		else {
			mHScrollBtn->setY(tempMoveRectF.GetTop() + tempMoveRectF.Height / 2.0f);
		}
	}
}

void ScrollBox::clickDownEvent()
{
	if (bIsMouseOver) {
		if (!bIsMouseClick) {
			bIsMouseClick = true;

			if (mContentArea.Contains(Gdiplus::PointF(_ptMouse.x, _ptMouse.y))) {

			} else if(mHScrollBtn->getRectF().Contains(Gdiplus::PointF(_ptMouse.x, _ptMouse.y))) {
				isDrag = true;
				mHpt = _ptMouse.y - mHScrollBtn->getRectF().GetTop();
			}
		}
	}
}

void ScrollBox::clickUpEvent()
{
	if (bIsMouseClick) {
		bIsMouseClick = false;
		isDrag = false;
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
		}
		else {
			mSizeChangeWidth = mSizeChangeWidth + 2;
			mSizeChangeHeight = mSizeChangeHeight + (2.0f / mSizeChangeRatio);
			mSizeChangeRectF = RectFMakeCenter(mCenterX, mCenterY, mSizeChangeWidth, mSizeChangeHeight);
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
			mSizeChangeRectF = RectFMakeCenter(mCenterX, mCenterY, mSizeChangeWidth, mSizeChangeHeight);
		}
	}
}

void SButton::render()
{
	GameUI::render();
}

HRESULT MapWork::init(const char * id, float x, float y, int xCount, int yCount, int tileSize, eXStandard xStandard, eYStandard yStandard)
{

	for (int x = 0; x < xCount; x++)
	{
		for (int y = 0; y < yCount; y++) {
			mVTileRECT.push_back(RectMake(x + (x * tileSize), y + (y * tileSize), tileSize, tileSize));
		}
	}

	return S_OK;
}

void MapWork::render()
{
	for (miVTileRECT = mVTileRECT.begin(); miVTileRECT != mVTileRECT.end(); miVTileRECT++) {
		RectangleMake(getMemDc(), *miVTileRECT);
	}
}

void MapWork::update()
{

}
