#include "Stdafx.h"
#include "ImageGp.h"

HRESULT ImageGp::init(string fileName, float width, float height, int maxFrameX, int maxFrameY, HDC memDc)
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

HRESULT ImageGp::init(string fileName, float width, float height, HDC memDc)
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

void ImageGp::release()
{
	//SAFE_DELETE(_imageInfo);
	//SAFE_DELETE(_image);
}

void ImageGp::setWidth(float width)
{
	Bitmap pBitmap(width, mImageInfo->Height);
	Gdiplus::Graphics graphics(&pBitmap);
	graphics.DrawImage(mImage, 0.0f, 0.0f, width, mImageInfo->Height);

	mBitmap = &pBitmap;
	mCacheBitmap = new CachedBitmap(&pBitmap, mGraphics);
}

void ImageGp::setHeight(float height)
{
	Bitmap pBitmap(mImageInfo->Width, height);
	Gdiplus::Graphics graphics(&pBitmap);
	graphics.DrawImage(mImage, 0.0f, 0.0f, mImageInfo->Width, height);

	mBitmap = &pBitmap;
	mCacheBitmap = new CachedBitmap(&pBitmap, mGraphics);
}

void ImageGp::setSize(float width, float height)
{
	MY_UTIL::log(DEBUG_IMG_GP_TAG, "리사이징 : " + mFileName + " " + to_string(mIndex));
	Bitmap* pBitmap = new Bitmap(width, height);
	Gdiplus::Graphics graphics(pBitmap);
	graphics.DrawImage(mImage, 0.0f, 0.0f, width, height);

	mBitmap = pBitmap;
	mCacheBitmap = new CachedBitmap(mBitmap, mGraphics);
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

void ImageGp::render(HDC hdc, float x, float y)
{
	mGraphics->DrawCachedBitmap(mCacheBitmap, x, y);
}

void ImageGp::render(HDC hdc, float x, float y, float width, float height)
{
}

void ImageGp::render(HDC hdc, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	mGraphics->DrawImage (
		mBitmap,
		destX, destY,
		sourX, sourY,
		sourWidth,
		sourHeight,
		UnitPixel);
}

void ImageGp::render(HDC hdc, RectF rectF)
{
	mGraphics->DrawImage(mBitmap, rectF);
}
