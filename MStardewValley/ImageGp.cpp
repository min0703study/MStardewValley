#include "Stdafx.h"
#include "ImageGp.h"

HRESULT ImageGp::init(HDC memDc, string fileName, float width, float height, int maxFrameX, int maxFrameY)
{
	if (mImageInfo != NULL) this->release();

	mImage = new Gdiplus::Image(wstring(fileName.begin(), fileName.end()).c_str());

	if (mImage->GetLastStatus() != Gdiplus::Status::Ok)
	{
		release();
		return E_FAIL;
	}

	mImageInfo = new IMAGE_INFO;
	mImageInfo->LoadType = LOAD_FILE;
	mImageInfo->Type = IT_FRAME;

	mImageInfo->CurrentFrameX = 0;
	mImageInfo->CurrentFrameY = 0;

	mImageInfo->MaxFrameX = maxFrameX - 1;
	mImageInfo->MaxFrameY = maxFrameY - 1;
	
	mImageInfo->FrameWidth = width / static_cast<float> (maxFrameX);
	mImageInfo->FrameHeight = height / static_cast<float>(maxFrameY);

	mImageInfo->Width = width;
	mImageInfo->Height = height;

	mFileName = fileName;

	mIndex = 0;

	mOriginalBitmap = new Bitmap(wstring(fileName.begin(), fileName.end()).c_str());

	this->initBitmap(memDc, width, height);

	return S_OK;
}

HRESULT ImageGp::init(HDC memDc, string fileName, float width, float height)
{
	mImage = new Gdiplus::Image(wstring(fileName.begin(), fileName.end()).c_str());

	if (mImage->GetLastStatus() != Gdiplus::Status::Ok)
	{
		release();
		return E_FAIL;
	}

	mImageInfo = new IMAGE_INFO;
	mImageInfo->LoadType = LOAD_FILE;

	mImageInfo->Width = width;
	mImageInfo->Height = height;

	mFileName = fileName;

	mIndex = 0;

	mOriginalBitmap = new Bitmap(wstring(fileName.begin(), fileName.end()).c_str());
	this->initBitmap(memDc, width, height);

	return S_OK;
}

HRESULT ImageGp::init(HDC memDc, float width, float height)
{
	mImageInfo = new IMAGE_INFO;

	mImageInfo->LoadType = LOAD_EMPTY;
	mImageInfo->Type = IT_EMPTY;

	mImageInfo->Width = width;
	mImageInfo->Height = height;

	mIndex = 0;

	mOriginalBitmap = new Bitmap(width, height);

	this->initBitmap(memDc, width, height);

	return S_OK;
}

HRESULT ImageGp::init(HDC memDc, Gdiplus::Bitmap* bitmap, float width, float height)
{
	mImage = bitmap;

	mImageInfo = new IMAGE_INFO;
	mImageInfo->LoadType = LOAD_FILE;

	mImageInfo->Width = width;
	mImageInfo->Height = height;

	mIndex = 0;

	mOriginalBitmap = bitmap;
	this->initBitmap(memDc, width, height);

	return S_OK;
}

HRESULT ImageGp::init(HDC memDc, Gdiplus::Bitmap* bitmap)
{
	mImage = bitmap;

	mImageInfo = new IMAGE_INFO;
	mImageInfo->LoadType = LOAD_FILE;

	mImageInfo->Width = static_cast<float>(bitmap->GetWidth());
	mImageInfo->Height = static_cast<float>(bitmap->GetHeight());

	mIndex = 0;

	mOriginalBitmap = bitmap;
	this->initBitmap(memDc, mImageInfo->Width, mImageInfo->Height);

	return S_OK;
}

HRESULT ImageGp::initCenter(HDC memDc, Gdiplus::Bitmap * bitmap, float width, float height)
{
	Bitmap* tempBitmap = GDIPLUSMANAGER->overlayBitmapCenter(memDc, bitmap, width, height);
	mImage = tempBitmap;

	mImageInfo = new IMAGE_INFO;
	mImageInfo->LoadType = LOAD_FILE;

	mImageInfo->Width = width;
	mImageInfo->Height = height;

	mIndex = 0;

	mOriginalBitmap = tempBitmap;
	this->initBitmap(memDc, width, height);

	return S_OK;
}

HRESULT ImageGp::init(HDC memDc, Gdiplus::Bitmap * bitmap, float x, float y, float width, float height)
{
	Bitmap* tempBitmap = GDIPLUSMANAGER->overlayBitmap(memDc, bitmap, x, y, width, height);
	mImage = tempBitmap;

	mImageInfo = new IMAGE_INFO;
	mImageInfo->LoadType = LOAD_FILE;

	mImageInfo->Width = width;
	mImageInfo->Height = height;

	mIndex = 0;

	mOriginalBitmap = tempBitmap;
	this->initBitmap(memDc, width, height);

	return S_OK;
}

HRESULT ImageGp::initBitmap(HDC memDc, float width, float height)
{
	if (mOriginalBitmap->GetWidth() != width || mOriginalBitmap->GetHeight() != height) {
		LOG::w(LOG_IMG_GP_TAG, "== 초기화 리사이징 : " + mFileName + " " + to_string(mIndex));
		LOG::w(LOG_IMG_GP_TAG, "== 원본 width : " + to_string(mOriginalBitmap->GetWidth()));
		LOG::w(LOG_IMG_GP_TAG, "== 원본 height : " + to_string(mOriginalBitmap->GetHeight()));

		mCurBitmap = new Bitmap(width, height);

		mCurBitmapGraphics = new Graphics(mCurBitmap);
		mCurBitmapGraphics->DrawImage(mOriginalBitmap, 0.0f, 0.0f, width, height);

		LOG::w(LOG_IMG_GP_TAG, "== 결과 width : " + to_string(mCurBitmap->GetWidth()));
		LOG::w(LOG_IMG_GP_TAG, "== 결과 height : " + to_string(mCurBitmap->GetHeight()));
		LOG::w(LOG_IMG_GP_TAG, "== 초기화 리사이징 종료 : " + mFileName + " " + to_string(mIndex));
	}
	else {
		mCurBitmap = mOriginalBitmap->Clone(0, 0, mOriginalBitmap->GetWidth(), mOriginalBitmap->GetHeight(), mOriginalBitmap->GetPixelFormat());
		mCurBitmapGraphics = new Graphics(mCurBitmap);
	}

	mGraphics = new Graphics(memDc);
	mCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);

	return S_OK;
}

void ImageGp::release()
{
	//SAFE_DELETE(_imageInfo);
	//SAFE_DELETE(_image);
}

void ImageGp::rebuildChachedBitmap(void)
{
	//mCurBitmap = mBitmap->Clone(0, 0, mBitmap->GetWidth(), mBitmap->GetHeight(), mBitmap->GetPixelFormat());
	mCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);
}

void ImageGp::changeOriginalToCurBitmap(void)
{
	//mCurBitmap = mBitmap->Clone(0, 0, mBitmap->GetWidth(), mBitmap->GetHeight(), mBitmap->GetPixelFormat());
}

void ImageGp::rotate(float angle)
{
	Bitmap* tempBitmap = new Bitmap(mImageInfo->Width, mImageInfo->Height);
	Gdiplus::Graphics gp(tempBitmap);

	Gdiplus::Matrix matrix;
	matrix.RotateAt(angle, { mImageInfo->Width / 2.0f, mImageInfo->Height - 30.0f });
	gp.SetTransform(&matrix);
	
	gp.DrawImage(mCurBitmap, 0.0f, 0.0f, mImageInfo->Width, mImageInfo->Height);

	mCurBitmap = tempBitmap;
	mCurBitmapGraphics = new Gdiplus::Graphics(mCurBitmap);
	mCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);
}


void ImageGp::rotate(float angle, float x, float y)
{
	Bitmap* tempBitmap = new Bitmap(mImageInfo->Width, mImageInfo->Height);
	Gdiplus::Graphics gp(tempBitmap);

	Gdiplus::Matrix matrix;
	matrix.RotateAt(angle, { mImageInfo->Width / 2.0f + x,  mImageInfo->Height / 2.0f + y });
	gp.SetTransform(&matrix);

	gp.DrawImage(mCurBitmap, 0.0f, 0.0f, mImageInfo->Width, mImageInfo->Height);

	mCurBitmap = tempBitmap;
	mCurBitmapGraphics = new Gdiplus::Graphics(mCurBitmap);
	mCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);
}

ImageGp* ImageGp::rotateAndClone(float angle)
{
	Bitmap* tempBitmap = new Bitmap(mImageInfo->Width, mImageInfo->Height);
	Gdiplus::Graphics gp(tempBitmap);

	Gdiplus::Matrix matrix;
	matrix.RotateAt(angle, { mImageInfo->Width / 2.0f, mImageInfo->Height / 2.0f});
	gp.SetTransform(&matrix);

	gp.DrawImage(mCurBitmap, 0.0f, 0.0f, mImageInfo->Width, mImageInfo->Height);

	ImageGp* cloneImg = new ImageGp();
	cloneImg->init(mGraphics->GetHDC(), tempBitmap);

	return cloneImg;
}

void ImageGp::setWidth(float width)
{
	mCurBitmapGraphics->DrawImage(mCurBitmap, 0.0f, 0.0f, width, mImageInfo->Height);

	if (mImageInfo->Type == IT_FRAME) {
		mImageInfo->FrameWidth = width / static_cast<float> (mImageInfo->MaxFrameX);
	}

	mImageInfo->Width = width;
}

void ImageGp::setHeight(float height)
{
	mCurBitmapGraphics->DrawImage(mCurBitmap, 0.0f, 0.0f, 0.0f, 0.0f, mImageInfo->Width, height, UnitPixel);

	if (mImageInfo->Type == IT_FRAME) {
		mImageInfo->FrameHeight = height / static_cast<float> (mImageInfo->MaxFrameY);
	}

	mImageInfo->Height = height;
}

void ImageGp::setSize(float width, float height)
{
	
	LOG::d(LOG_IMG_GP_TAG, "== 리사이징 : " + mFileName + " " + to_string(mIndex));
	LOG::d(LOG_IMG_GP_TAG, "== 원본 width : " + to_string(mCurBitmap->GetWidth()));
	LOG::d(LOG_IMG_GP_TAG, "== 원본 height : " + to_string(mCurBitmap->GetHeight()));
	
	Bitmap* tempBitmap = new Bitmap(width, height);
	Gdiplus::Graphics gp(tempBitmap);
	gp.DrawImage(mCurBitmap, 0.0f, 0.0f, width, height);
	
	/*
	delete mCacheBitmap;
	delete mCurBitmapGraphics;
	delete mGraphics;
	*/

	mCurBitmap = tempBitmap;
	mCurBitmapGraphics = new Gdiplus::Graphics(mCurBitmap);
	mCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);

	if (mImageInfo->Type == IT_FRAME) {
		mImageInfo->FrameWidth = width / static_cast<float> (mImageInfo->MaxFrameX + 1);
		mImageInfo->FrameHeight = height / static_cast<float> (mImageInfo->MaxFrameY + 1);
	}

	mImageInfo->Width = width;
	mImageInfo->Height = height;

	
	LOG::d(LOG_IMG_GP_TAG, "== 결과 width : " + to_string(mCurBitmap->GetWidth()));
	LOG::d(LOG_IMG_GP_TAG, "== 결과 height : " + to_string(mCurBitmap->GetHeight()));
	LOG::d(LOG_IMG_GP_TAG, "== 리사이징 종료 : " + mFileName + " " + to_string(mIndex));
	
}

void ImageGp::flipX()
{
	mCurBitmap->RotateFlip(RotateNoneFlipX);
	mCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);
}

void ImageGp::flip90(int count)
{

	if (count == 1) {
		mCurBitmap->RotateFlip(Rotate90FlipX);
	}
	else if (count == 2) {
		mCurBitmap->RotateFlip(Rotate180FlipX);
	}
	else if (count == 3) {
		mCurBitmap->RotateFlip(Rotate270FlipX);
	}

	mCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);
}

void ImageGp::setSizeRatio(float ratio)
{

	LOG::d(LOG_IMG_GP_TAG, "== 리사이징 : " + mFileName + " " + to_string(mIndex));
	LOG::d(LOG_IMG_GP_TAG, "== 원본 width : " + to_string(mCurBitmap->GetWidth()));
	LOG::d(LOG_IMG_GP_TAG, "== 원본 height : " + to_string(mCurBitmap->GetHeight()));
	
	//float mSizeChangeRatio = mSizeChangeWidth / mSizeChangeHeight;
	Bitmap* tempBitmap = new Bitmap(mImageInfo->Width * ratio, mImageInfo->Height * ratio);
	Gdiplus::Graphics gp(tempBitmap);
	gp.DrawImage(mCurBitmap, 0.0f, 0.0f, mImageInfo->Width * ratio, mImageInfo->Height * ratio);

	/*
	delete mCacheBitmap;
	delete mCurBitmapGraphics;
	delete mGraphics;
	*/

	mCurBitmap = tempBitmap;
	mCurBitmapGraphics = new Gdiplus::Graphics(mCurBitmap);
	mCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);

	mImageInfo->Width = mImageInfo->Width * ratio;
	mImageInfo->Height = mImageInfo->Height * ratio;

	if (mImageInfo->Type == IT_FRAME) {
		mImageInfo->FrameWidth = mImageInfo->Width / static_cast<float> (mImageInfo->MaxFrameX + 1);
		mImageInfo->FrameHeight = mImageInfo->Height / static_cast<float> (mImageInfo->MaxFrameY + 1);
	}
	LOG::d(LOG_IMG_GP_TAG, "== 결과 width : " + to_string(mCurBitmap->GetWidth()));
	LOG::d(LOG_IMG_GP_TAG, "== 결과 height : " + to_string(mCurBitmap->GetHeight()));
	LOG::d(LOG_IMG_GP_TAG, "== 리사이징 종료 ==");

}

void ImageGp::changeColor()
{
	LOG::d(LOG_IMG_GP_TAG, "컬러 변경 : " + mFileName + " " + to_string(mIndex));

	ImageAttributes  imageAttributes;

	ColorMatrix colorMatrix = {
	   1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	   0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	   0.2f, 0.2f, 0.2f, 0.0f, 1.0f };
	
	imageAttributes.SetColorMatrix(
		&colorMatrix,
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);
	
	Gdiplus::RectF rcf = Gdiplus::RectF(mImageInfo->X, mImageInfo->Y, mImageInfo->Width, mImageInfo->Height);

	mCurBitmapGraphics->DrawImage(
		mCurBitmap,
		rcf, 
		0, 0,
		mCurBitmap->GetWidth(),
		mCurBitmap->GetHeight(),
		UnitPixel,
		&imageAttributes);	
}

void ImageGp::backOriginalColor()
{
	LOG::d(LOG_IMG_GP_TAG, "컬러 변경 : " + mFileName + " " + to_string(mIndex));

	ImageAttributes  imageAttributes;
	ColorMatrix colorMatrix = {
	   1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	   0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	imageAttributes.SetColorMatrix(
		&colorMatrix,
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);

	Gdiplus::RectF rcf = Gdiplus::RectF(mImageInfo->X, mImageInfo->Y, mImageInfo->Width, mImageInfo->Height);

	mCurBitmapGraphics->DrawImage(
		mOriginalBitmap,
		rcf,
		0, 0,
		mCurBitmap->GetWidth(),
		mCurBitmap->GetHeight(),
		UnitPixel,
		&imageAttributes);
}

void ImageGp::clipping(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	mClippingBitmapGraphics->Clear(Color(0,0,0,0));
	mClippingBitmapGraphics->DrawImage(mCurBitmap,
		destX, destY,
		sourX, sourY,
		sourWidth,
		sourHeight,
		UnitPixel);

	mCacheBitmap = new CachedBitmap(mClippingBitmap, mGraphics);
}

void ImageGp::startLoopX(int loopFrameCount)
{
	mImageInfo->Type = IT_LOOP;
	mImageInfo->LoopWidth = mImageInfo->Width / loopFrameCount;
	mImageInfo->LoopFrameX = loopFrameCount;

	for (int i = 0; i < loopFrameCount; i++) {
		Bitmap* tempBitmap = getPartBitmap(i * mImageInfo->LoopWidth, 0, mImageInfo->LoopWidth, mImageInfo->Height);
		mVLoopCashBitmap.push_back(new CachedBitmap(tempBitmap, mGraphics));
	}

	for (int i = 0; i < loopFrameCount; i++) {
		Bitmap* tempBitmap = getPartBitmap(i * mImageInfo->LoopWidth, 0, mImageInfo->LoopWidth, mImageInfo->Height);
		mVLoopBitmap.push_back(tempBitmap);
	}
}


void ImageGp::startClipping(float sourWidth, float sourHeight)
{
	mImageInfo->Type = IT_CLIPPING;
	//delete mCacheBitmap;
	mClippingBitmap = new Bitmap(sourWidth, sourHeight);
	mClippingBitmapGraphics = new Graphics(mClippingBitmap);
	mCacheBitmap = new CachedBitmap(mClippingBitmap, mGraphics);
}

void ImageGp::render(HDC hdc, float x, float y, eXStandard xStandard, eYStandard yStandard)
{
	switch (xStandard) {
	case XS_LEFT:
		break;
	case XS_RIGHT:
		x = x  - mImageInfo->Width;
		break;
	case XS_CENTER:
		x = x - (mImageInfo->Width / 2.0f);
		break;
	}

	switch (yStandard) {
	case YS_TOP:
		break;
	case YS_BOTTOM:
		y = y - mImageInfo->Height;
		break;
	case YS_CENTER:
		y = y - (mImageInfo->Height / 2.0f);
		break;
	}

	mGraphics->DrawCachedBitmap(mCacheBitmap, x, y);
}

void ImageGp::render(float leftX, float topY)
{
	mGraphics->DrawCachedBitmap(mCacheBitmap, leftX, topY);
}

void ImageGp::loopRender(HDC hdc, float x, float y, int startIndex)
{
	int curIndex = 0;
	for (int i = 0; i < mVLoopCashBitmap.size(); i++) {
		curIndex = (i + startIndex) % (mImageInfo->LoopFrameX);
		mGraphics->DrawCachedBitmap(mVLoopCashBitmap[curIndex], i * mImageInfo->LoopWidth, y);
	}
}

void ImageGp::render(HDC hdc, float x, float y)
{
	mGraphics->DrawCachedBitmap(mCacheBitmap, x, y);
}

void ImageGp::render(HDC hdc, RectF rectF)
{
	mGraphics->DrawImage(mCurBitmap, rectF);
}

void ImageGp::frameRender(HDC hdc, float x, float y)
{
	mGraphics->DrawImage(
		mCurBitmap,
		x, y,
		mImageInfo->CurrentFrameX * mImageInfo->FrameWidth,
		mImageInfo->CurrentFrameY * mImageInfo->FrameHeight,
		mImageInfo->FrameWidth,
		mImageInfo->FrameHeight,
		UnitPixel);
}

void ImageGp::frameRender(HDC hdc, float x, float y, int currentFrameX, int currentFrameY)
{
	mImageInfo->CurrentFrameX = currentFrameX;
	mImageInfo->CurrentFrameY = currentFrameY;

	mGraphics->DrawImage(
		mCurBitmap,
		x, y,
		mImageInfo->CurrentFrameX * mImageInfo->FrameWidth,
		mImageInfo->CurrentFrameY * mImageInfo->FrameHeight,
		mImageInfo->FrameWidth,
		mImageInfo->FrameHeight,
		UnitPixel);
}

void ImageGp::coverBitmap(float x, float y, float width, float height, Gdiplus::Bitmap* bitmap)
{
	mCurBitmapGraphics->FillRectangle(&SolidBrush(Color(0, 0, 0, 0)), x, y, width, height);
	mCurBitmapGraphics->DrawImage(bitmap, x, y, bitmap->GetWidth(), bitmap->GetHeight());
}

void ImageGp::coverBitmap(float x, float y, Gdiplus::Bitmap* bitmap)
{
	mCurBitmapGraphics->FillRectangle(&SolidBrush(Color(0,0,0,0)),x, y, bitmap->GetWidth(), bitmap->GetHeight());
	mCurBitmapGraphics->DrawImage(bitmap, x, y, bitmap->GetWidth(), bitmap->GetHeight());
}

void ImageGp::coverBitmapCenter(Gdiplus::Bitmap* bitmap)
{
	float centerX = mCurBitmap->GetWidth() / 2.0f - bitmap->GetWidth() / 2.0f;
	float centerY = mCurBitmap->GetHeight() / 2.0f - bitmap->GetHeight() / 2.0f;

	mCurBitmapGraphics->Clear(Color(0,0,0,0));
	mCurBitmapGraphics->DrawImage(bitmap, centerX, centerY, bitmap->GetWidth(), bitmap->GetHeight());
}

void ImageGp::overlayBitmap(float x, float y, Gdiplus::Bitmap* bitmap)
{
	mCurBitmapGraphics->DrawImage(bitmap, x, y, bitmap->GetWidth(), bitmap->GetHeight());
}

void ImageGp::overlayBitmapCenter(Gdiplus::Bitmap* bitmap)
{
	float centerX = mCurBitmap->GetWidth() / 2.0f - bitmap->GetWidth() / 2.0f;
	float centerY = mCurBitmap->GetHeight() / 2.0f - bitmap->GetHeight() / 2.0f;
	
	mCurBitmapGraphics->DrawImage(bitmap, centerX, centerY, bitmap->GetWidth(), bitmap->GetHeight());
}

void ImageGp::overlayBitmapAdjustHeight(Gdiplus::Bitmap* bitmap)
{
	float centerX = mImageInfo->Width / 2.0f;
	float centerY = mImageInfo->Height / 2.0f;

	float a = bitmap->GetHeight();

	float mSizeChangeRatio = mImageInfo->Width / mImageInfo->Height;

	RectF rcF = RectFMakeCenter(centerX, centerY, mImageInfo->Height * mSizeChangeRatio, mImageInfo->Height);

	mCurBitmapGraphics->DrawImage(bitmap, 
		rcF,
		0.0f,
		0.0f,
		static_cast<float>(bitmap->GetWidth()), 
		static_cast<float>(bitmap->GetHeight()),
		UnitPixel);
}

RectF ImageGp::getRectF(float x, float y, eXStandard xStandard, eYStandard yStandard)
{
	switch (xStandard) {
	case XS_LEFT:
		break;
	case XS_RIGHT:
		x = x - mImageInfo->Width;
		break;
	case XS_CENTER:
		x = x - (mImageInfo->Width / 2.0f);
		break;
	}

	switch (yStandard) {
	case YS_TOP:
		break;
	case YS_BOTTOM:
		y = y - mImageInfo->Height;
		break;
	case YS_CENTER:
		y = y - (mImageInfo->Height / 2.0f);
		break;
	}

	return RectFMake(x, y, mCurBitmap->GetWidth(), mCurBitmap->GetHeight());
}

Gdiplus::Bitmap* ImageGp::getFrameBitmap(int currentFrameX, int currentFrameY)
{
	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(mImageInfo->FrameWidth, mImageInfo->FrameHeight);
	Gdiplus::Graphics graphics(pBitmap);

	graphics.DrawImage(
		mCurBitmap,
		0.0f, 0.0f,
		currentFrameX * mImageInfo->FrameWidth,
		currentFrameY * mImageInfo->FrameHeight,
		mImageInfo->FrameWidth,
		mImageInfo->FrameHeight,
		UnitPixel);

	return pBitmap;
}

Gdiplus::Bitmap* ImageGp::getFrameBitmap(int currentFrameX, int currentFrameY, float destWidth, float destHeight)
{
	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(destWidth, destHeight);
	Gdiplus::Graphics graphics(pBitmap);

	graphics.DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, destWidth, destHeight),
		currentFrameX * mImageInfo->FrameWidth,
		currentFrameY * mImageInfo->FrameHeight,
		mImageInfo->FrameWidth,
		mImageInfo->FrameHeight,
		UnitPixel);

	return pBitmap;
}

Gdiplus::Bitmap* ImageGp::getFrameBitmapRotate(int currentFrameX, int currentFrameY, float destWidth, float destHeight, float angle)
{
	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(destWidth, destHeight);
	Gdiplus::Graphics graphics(pBitmap);
	
	Gdiplus::Matrix matrix;
	matrix.RotateAt(angle, { mImageInfo->Width / 2.0f, mImageInfo->Height / 2.0f});
	graphics.SetTransform(&matrix);

	graphics.DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, destWidth, destHeight),
		currentFrameX * mImageInfo->FrameWidth,
		currentFrameY * mImageInfo->FrameHeight,
		mImageInfo->FrameWidth,
		mImageInfo->FrameHeight,
		UnitPixel);

	return pBitmap;
}

Gdiplus::Bitmap* ImageGp::getFrameBitmapAbjustHeight(int currentFrameX, int currentFrameY, float destHeight)
{
	float mSizeChangeRatio = mImageInfo->FrameWidth / mImageInfo->FrameHeight;
	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(mSizeChangeRatio * destHeight, destHeight);
	Gdiplus::Graphics graphics(pBitmap);

	graphics.DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, mSizeChangeRatio * destHeight, destHeight),
		currentFrameX * mImageInfo->FrameWidth,
		currentFrameY * mImageInfo->FrameHeight,
		mImageInfo->FrameWidth,
		mImageInfo->FrameHeight,
		UnitPixel);

	return pBitmap;
}

ImageGp* ImageGp::getFrameBitmapAbjustHeightAndClone(int currentFrameX, int currentFrameY, float destHeight)
{
	float mSizeChangeRatio = mImageInfo->FrameWidth / mImageInfo->FrameHeight;
	Gdiplus::Bitmap* tempBitmap = new Gdiplus::Bitmap(mSizeChangeRatio * destHeight, destHeight);
	Gdiplus::Graphics graphics(tempBitmap);

	graphics.DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, mSizeChangeRatio * destHeight, destHeight),
		currentFrameX * mImageInfo->FrameWidth,
		currentFrameY * mImageInfo->FrameHeight,
		mImageInfo->FrameWidth,
		mImageInfo->FrameHeight,
		UnitPixel);

	ImageGp* cloneImg = new ImageGp;
	cloneImg->init(mGraphics->GetHDC(), tempBitmap);

	return cloneImg;
}


Gdiplus::Bitmap* ImageGp::getFrameBitmapAbjustHeightToIndex(int currentFrameX, int currentFrameY, float destHeight, int toXIndex, int toYIndex)
{
	float mSizeChangeRatio = mImageInfo->FrameWidth * toXIndex / mImageInfo->FrameHeight * toYIndex;

	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(mSizeChangeRatio * destHeight, destHeight);
	Gdiplus::Graphics graphics(pBitmap);

	graphics.DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, mSizeChangeRatio * destHeight, destHeight),
		currentFrameX * mImageInfo->FrameWidth,
		currentFrameY * mImageInfo->FrameHeight,
		mImageInfo->FrameWidth * toYIndex,
		mImageInfo->FrameHeight * toYIndex,
		UnitPixel);

	return pBitmap;
}

Gdiplus::Bitmap* ImageGp::getFrameBitmapTemp(int currentFrameX, int currentFrameY, float destHeight, int toXIndex, int toYIndex)
{
	float mSizeChangeRatio = (mImageInfo->FrameWidth * toXIndex) / (mImageInfo->FrameHeight * toYIndex - 72);

	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(mSizeChangeRatio * destHeight, destHeight);
	Gdiplus::Graphics graphics(pBitmap);

	graphics.DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, mSizeChangeRatio * destHeight, destHeight),
		currentFrameX * mImageInfo->FrameWidth,
		currentFrameY * mImageInfo->FrameHeight + 50,
		mImageInfo->FrameWidth * toXIndex,
		mImageInfo->FrameHeight * toYIndex - 72,
		UnitPixel);

	return pBitmap;
}


Gdiplus::Bitmap* ImageGp::getFrameBitmap(int currentFrameX, int currentFrameY, float destX, float destY , float destWidth, float destHeight, float srcWidth, float srcHeight)
{
	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(destWidth, destHeight);
	Gdiplus::Graphics graphics(pBitmap);

	graphics.DrawImage(
		mCurBitmap,
		RectF(destX, destY, srcWidth, srcHeight),
		currentFrameX * mImageInfo->FrameWidth,
		currentFrameY * mImageInfo->FrameHeight,
		mImageInfo->FrameWidth,
		mImageInfo->FrameHeight,
		UnitPixel);

	return pBitmap;
}

Gdiplus::Bitmap* ImageGp::getFrameBitmapToIndex(int currentFrameX, int currentFrameY, int toXCount, int toYCount)
{
	float rWidth = mImageInfo->FrameWidth * (toXCount + 1);
	float rHeight = mImageInfo->FrameHeight * (toYCount + 1);

	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(rWidth, rHeight);
	Gdiplus::Graphics graphics(pBitmap);

	graphics.DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, rWidth, rHeight),
		currentFrameX * mImageInfo->FrameWidth,
		currentFrameY * mImageInfo->FrameHeight,
		rWidth,
		rHeight,
		UnitPixel);

	return pBitmap;
}

Gdiplus::Bitmap* ImageGp::getFrameBitmapToIndex(int currentFrameX, int currentFrameY, float width, float height, int toXIndex, int toYIndex)
{
	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(width, height);
	Gdiplus::Graphics graphics(pBitmap);

	graphics.DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, width, height),
		currentFrameX * mImageInfo->FrameWidth,
		currentFrameY * mImageInfo->FrameHeight,
		mImageInfo->FrameWidth * toXIndex,
		mImageInfo->FrameHeight * toYIndex,
		UnitPixel);

	return pBitmap;
}

Gdiplus::Bitmap* ImageGp::getFrameBitmapToIndexCenter(int currentFrameX, int currentFrameY, float width, float height, int toXIndex, int toYIndex)
{
	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(width, height);
	Gdiplus::Graphics graphics(pBitmap);

	graphics.DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, width, height),
		currentFrameX * mImageInfo->FrameWidth,
		currentFrameY * mImageInfo->FrameHeight,
		mImageInfo->FrameWidth * toXIndex,
		mImageInfo->FrameHeight * toYIndex,
		UnitPixel);

	return pBitmap;
}


Gdiplus::Bitmap* ImageGp::getPartBitmap(int x, int y, float width, float height)
{
	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(width, height);
	Gdiplus::Graphics graphics(pBitmap);

	graphics.DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, width, height),
		x,
		y,
		width,
		height,
		UnitPixel);

	return pBitmap;
}


Gdiplus::Bitmap* ImageGp::getPartBitmap(int x, int y, float destWidth, float destHeight, float srcWidth, float srcHeight)
{
	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(destWidth, destHeight);
	Gdiplus::Graphics graphics(pBitmap);

	graphics.DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, destWidth, destHeight),
		x,
		y,
		srcWidth,
		srcHeight,
		UnitPixel);

	return pBitmap;
}

