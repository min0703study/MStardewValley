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


	mBitmap = new Bitmap(wstring(fileName.begin(), fileName.end()).c_str());
	mBGraphics = new Graphics(mBitmap);

	mGraphics = new Graphics(memDc);
	mCacheBitmap = new CachedBitmap(mBitmap, mGraphics);

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

	mGraphics = new Graphics(memDc);

	mFileName = fileName;

	mIndex = 0;

	mBitmap = new Bitmap(wstring(fileName.begin(), fileName.end()).c_str());
	mCacheBitmap = new CachedBitmap(mBitmap, mGraphics);

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

	mGraphics = new Graphics(memDc);
	mBitmap = new Bitmap(width, height);
	mCacheBitmap = new CachedBitmap(mBitmap, mGraphics);

	return S_OK;
}

HRESULT ImageGp::init(HDC memDc, Gdiplus::Bitmap* bitmap, float width, float height)
{
	if (mImage->GetLastStatus() != Gdiplus::Status::Ok)
	{
		release();
		return E_FAIL;
	}

	mImage = bitmap;

	mImageInfo = new IMAGE_INFO;
	mImageInfo->LoadType = LOAD_FILE;

	mImageInfo->Width = width;
	mImageInfo->Height = height;

	mGraphics = new Gdiplus::Graphics(memDc);

	mIndex = 0;

	mBitmap = bitmap;
	mCacheBitmap = new Gdiplus::CachedBitmap(mBitmap, mGraphics);

	return S_OK;
}

void ImageGp::release()
{
	//SAFE_DELETE(_imageInfo);
	//SAFE_DELETE(_image);
}

void ImageGp::rebuildChachedBitmap(void)
{
	mCacheBitmap = new CachedBitmap(mBitmap, mGraphics);
}

void ImageGp::setWidth(float width)
{
	Bitmap pBitmap(width, mImageInfo->Height);
	Gdiplus::Graphics graphics(&pBitmap);
	graphics.DrawImage(mImage, 0.0f, 0.0f, width, mImageInfo->Height);

	mBitmap = &pBitmap;
	mCacheBitmap = new CachedBitmap(&pBitmap, mGraphics);

	if (mImageInfo->Type == IT_FRAME) {
		mImageInfo->FrameWidth = width / static_cast<float> (mImageInfo->MaxFrameX);
	}

	mImageInfo->Width = width;
}

void ImageGp::setHeight(float height)
{
	Bitmap pBitmap(mImageInfo->Width, height);
	Gdiplus::Graphics graphics(&pBitmap);
	graphics.DrawImage(mImage, 0.0f, 0.0f, mImageInfo->Width, height);

	mBitmap = &pBitmap;
	mCacheBitmap = new CachedBitmap(&pBitmap, mGraphics);

	if (mImageInfo->Type == IT_FRAME) {
		mImageInfo->FrameHeight = height / static_cast<float> (mImageInfo->MaxFrameY);
	}

	mImageInfo->Height = height;
}

void ImageGp::setSize(float width, float height)
{
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "리사이징 : " + mFileName + " " + to_string(mIndex));

	Bitmap* pBitmap = new Bitmap(width, height);
	Gdiplus::Graphics graphics(pBitmap);
	graphics.DrawImage(mImage, 0.0f, 0.0f, width, height);

	mBitmap = pBitmap;
	mCacheBitmap = new CachedBitmap(mBitmap, mGraphics);

	if (mImageInfo->Type == IT_FRAME) {
		mImageInfo->FrameWidth = width / static_cast<float> (mImageInfo->MaxFrameX);
		mImageInfo->FrameHeight = height / static_cast<float> (mImageInfo->MaxFrameY);
	}

	mImageInfo->Width = width;
	mImageInfo->Height = height;
}

void ImageGp::changeColor()
{
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "컬러 변경 : " + mFileName + " " + to_string(mIndex));

	Bitmap* pBitmap = new Bitmap(mImageInfo->Width, mImageInfo->Height);

	ImageAttributes  imageAttributes;
	ColorMatrix colorMatrix = {
	   1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	   0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	   0.2f, 0.2f, 0.2f, 0.0f, 1.0f };
	
	Gdiplus::Graphics graphics(pBitmap);

	imageAttributes.SetColorMatrix(
		&colorMatrix,
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);
	
	Gdiplus::RectF rcf = Gdiplus::RectF(mImageInfo->X, mImageInfo->Y, mImageInfo->Width, mImageInfo->Height);

	graphics.DrawImage(
		mBitmap,
		rcf, 
		0, 0,
		pBitmap->GetWidth(),
		pBitmap->GetHeight(),
		UnitPixel,
		&imageAttributes);

	mBitmap = pBitmap;
	mCacheBitmap = new CachedBitmap(mBitmap, mGraphics);
	
}

void ImageGp::backOriginalColor()
{
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "컬러 변경 : " + mFileName + " " + to_string(mIndex));

	Bitmap* pBitmap = new Bitmap(mImageInfo->Width, mImageInfo->Height);

	ImageAttributes  imageAttributes;
	ColorMatrix colorMatrix = {
	   1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	   0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	Gdiplus::Graphics graphics(pBitmap);

	imageAttributes.SetColorMatrix(
		&colorMatrix,
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);

	Gdiplus::RectF rcf = Gdiplus::RectF(mImageInfo->X, mImageInfo->Y, mImageInfo->Width, mImageInfo->Height);

	graphics.DrawImage(
		mImage,
		rcf,
		0, 0,
		pBitmap->GetWidth(),
		pBitmap->GetHeight(),
		UnitPixel,
		&imageAttributes);

	mBitmap = pBitmap;
	mCacheBitmap = new CachedBitmap(mBitmap, mGraphics);

}

void ImageGp::clipping(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	mCBitmap = new Bitmap(sourWidth, sourHeight);
	Gdiplus::Graphics graphics(mCBitmap);
	graphics.DrawImage (
		mBitmap,
		destX, destY,
		sourX, sourY,
		sourWidth,
		sourHeight,
		UnitPixel);

	mCacheBitmap = new CachedBitmap(mCBitmap, mGraphics);
}

void ImageGp::render(HDC hdc, float x, float y)
{
	mGraphics->DrawCachedBitmap(mCacheBitmap, x, y);
}

void ImageGp::render(HDC hdc, float x, float y, float width, float height)
{
}

void ImageGp::render(HDC hdc, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	mGraphics->DrawCachedBitmap(mCacheBitmap, destX, destY);
	/*
	mGraphics->DrawImage (
		mBitmap,
		destX, destY,
		sourX, sourY,
		sourWidth,
		sourHeight,
		UnitPixel);
		*/
}

void ImageGp::render(HDC hdc, RectF rectF)
{
	mGraphics->DrawImage(mBitmap, rectF);
}

void ImageGp::frameRender(HDC hdc, float x, float y)
{
	mGraphics->DrawImage(
		mBitmap,
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
		mBitmap,
		x, y,
		mImageInfo->CurrentFrameX * mImageInfo->FrameWidth,
		mImageInfo->CurrentFrameY * mImageInfo->FrameHeight,
		mImageInfo->FrameWidth,
		mImageInfo->FrameHeight,
		UnitPixel);
}

void ImageGp::addBitmap(float x, float y, Gdiplus::Bitmap* bitmap)
{
	Gdiplus::Graphics graphics(mBitmap);
	graphics.DrawImage(bitmap, x, y, bitmap->GetWidth(), bitmap->GetHeight());
	mCacheBitmap = new CachedBitmap(mBitmap, mGraphics);
}

Gdiplus::Bitmap* ImageGp::getFrameBitmap(int currentFrameX, int currentFrameY) {

	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(mImageInfo->FrameWidth, mImageInfo->FrameHeight);
	Gdiplus::Graphics graphics(pBitmap);

	graphics.DrawImage(
		mBitmap,
		0.0f, 0.0f,
		currentFrameX * mImageInfo->FrameWidth,
		currentFrameY * mImageInfo->FrameHeight,
		mImageInfo->FrameWidth,
		mImageInfo->FrameHeight,
		UnitPixel);

	return pBitmap;
}

