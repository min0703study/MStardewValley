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

HRESULT ImageGp::initBitmap(HDC memDc, float width, float height)
{
	if (mOriginalBitmap->GetWidth() != width || mOriginalBitmap->GetHeight() != height) {
		MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 리사이징 : " + mFileName + " " + to_string(mIndex));
		MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 원본 width : " + to_string(mOriginalBitmap->GetWidth()));
		MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 원본 height : " + to_string(mOriginalBitmap->GetHeight()));

		mCurBitmap = new Bitmap(width, height);

		mCurBitmapGraphics = new Graphics(mCurBitmap);
		mCurBitmapGraphics->DrawImage(mOriginalBitmap, 0.0f, 0.0f, width, height);

		MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 결과 width : " + to_string(mCurBitmap->GetWidth()));
		MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 결과 height : " + to_string(mCurBitmap->GetHeight()));
		MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 리사이징 종료 : " + mFileName + " " + to_string(mIndex));
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
	
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 리사이징 : " + mFileName + " " + to_string(mIndex));
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 원본 width : " + to_string(mCurBitmap->GetWidth()));
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 원본 height : " + to_string(mCurBitmap->GetHeight()));
	
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

	
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 결과 width : " + to_string(mCurBitmap->GetWidth()));
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 결과 height : " + to_string(mCurBitmap->GetHeight()));
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 리사이징 종료 : " + mFileName + " " + to_string(mIndex));
	
}

void ImageGp::flipX()
{
	mCurBitmap->RotateFlip(RotateNoneFlipX);
	mCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);
}

void ImageGp::setSizeRatio(float ratio)
{

	MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 리사이징 : " + mFileName + " " + to_string(mIndex));
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 원본 width : " + to_string(mCurBitmap->GetWidth()));
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 원본 height : " + to_string(mCurBitmap->GetHeight()));
	
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
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 결과 width : " + to_string(mCurBitmap->GetWidth()));
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 결과 height : " + to_string(mCurBitmap->GetHeight()));
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "== 리사이징 종료 : " + mFileName + " " + to_string(mIndex));

}

void ImageGp::changeColor()
{
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "컬러 변경 : " + mFileName + " " + to_string(mIndex));

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
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "컬러 변경 : " + mFileName + " " + to_string(mIndex));

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

void ImageGp::startClipping(float sourWidth, float sourHeight)
{
	mImageInfo->Type = IT_CLIPPING;
	//delete mCacheBitmap;
	mClippingBitmap = new Bitmap(sourWidth, sourHeight);
	mClippingBitmapGraphics = new Graphics(mClippingBitmap);
	mCacheBitmap = new CachedBitmap(mClippingBitmap, mGraphics);
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

void ImageGp::coverBitmap(float x, float y, Gdiplus::Bitmap* bitmap)
{
	//Pen      pen(Color(91, 43, 41), 0.5);
	//SolidBrush s(Color(255, 255, 255));

	//mCurBitmapGraphics->FillRectangle(&s, x, y, bitmap->GetWidth(), bitmap->GetHeight());
	mCurBitmapGraphics->DrawImage(bitmap, x, y, bitmap->GetWidth(), bitmap->GetHeight());
	//mCurBitmapGraphics->DrawRectangle(&pen, x, y, bitmap->GetWidth(), bitmap->GetHeight());
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

