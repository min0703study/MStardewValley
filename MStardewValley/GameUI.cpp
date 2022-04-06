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

	bInitSuccess = true;

	mId = id;

	return S_OK;
}

HRESULT GameUI::init(const char * id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard)
{
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

HRESULT GameUI::init(const char* id, float centerX, float centerY, ImageBase * img, eXStandard xStandard, eYStandard yStandard)
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
		mStat = eStat::SIZE_TO_BIG;

		mToSizeRatio = toSizeRatio;

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
	if (!bInitSuccess) return;

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
	float vScrollBtnH = contentAreaHeight - (gameUI->getHeight() - contentAreaHeight);

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

	float hScrollBtnW = contentAreaWidth - (gameUI->getWidth() - contentAreaWidth);
	float hScrollBtnH = hScrollBarH;

	float hScrollBtnX = hScrollBarX;
	float hScrollBtnY = hScrollBarY;

	mHScrollBar = new GameUI;
	mHScrollBar->init("수평 스크롤 바", hScrollBarX, hScrollBarY, hScrollBarW, hScrollBarH, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->UIHScrollBar), XS_LEFT, YS_TOP);

	mHScrollBtn = new GameUI;
	mHScrollBtn->init("수평 스크롤 버튼", hScrollBtnX, hScrollBarY, hScrollBtnW, hScrollBtnH, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->UIHScrollBtn), XS_LEFT, YS_TOP);

	mHScrollMoveDistance = 0.0f;

	mContent->getImgGp()->startClipping(contentAreaWidth, contentAreaHeight);
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
			if (mAbsContentArea.Contains(_ptfMouse)) {

			} else if(mVScrollBtn->getRectF().Contains(_ptfMouse)) {
				isVScrollDrag = true;
				mVScrollPtDistance = _ptMouse.y - mVScrollBtn->getRectF().GetTop();
			} else if (mHScrollBtn->getRectF().Contains(_ptfMouse)) {
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

bool ScrollBox::isCollisionScrollBar(PointF ptF)
{
	return mVScrollBar->getRectF().Contains(ptF) || mHScrollBar->getRectF().Contains(ptF);
}

bool ScrollBox::isCollisionContentBox(PointF ptF)
{
	return mAbsContentArea.Contains(ptF);
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
	if (!bInitSuccess) return;

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

////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT Toolbar::init(const char * id, float x, float y, float width, float height, ImageGp * imgGp, eXStandard xStandard, eYStandard yStandard)
{
	GameUI::init(id, x, y, width, height, imgGp, xStandard, yStandard);

	for (int i = 0; i < MAX_TOOLBAR_INDEX; i++) {
		mItems[i].IsNone = true;
	}

	return S_OK;
}

HRESULT Toolbar::init(const char * id, float x, float y, ImageGp * img, eXStandard xPos, eYStandard yPos)
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