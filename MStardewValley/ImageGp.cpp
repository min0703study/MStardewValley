#include "Stdafx.h"
#include "ImageGp.h"

HRESULT ImageGp::init(string fileName, float width, float height, int maxFrameX, int maxFrameY, HDC memDc)
{
	if (_imageInfo != NULL) this->release();

	_image = new Gdiplus::Image(wstring(fileName.begin(), fileName.end()).c_str());

	if (_image == nullptr)
	{
		release();
		return E_FAIL;
	}

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;

	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;

	_imageInfo->maxFrameX = maxFrameX - 1;
	_imageInfo->maxFrameY = maxFrameY - 1;
	
	_imageInfo->frameWidth = width / maxFrameX;
	_imageInfo->frameHeight = height / maxFrameY;

	_imageInfo->width = width;
	_imageInfo->height = height;

	mFileName = fileName;

	mGraphics = new Graphics(memDc);

	mBitmap = new Bitmap(wstring(fileName.begin(), fileName.end()).c_str());
	mCacheBitmap = new CachedBitmap(mBitmap, mGraphics);

	return S_OK;
}

HRESULT ImageGp::init(string fileName, float width, float height, HDC memDc)
{
	//if (_imageInfo != nullptr) this->release();

	_image = new Gdiplus::Image(wstring(fileName.begin(), fileName.end()).c_str());

	if (_image == nullptr)
	{
		release();
		return E_FAIL;
	}

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;

	_imageInfo->width = width;
	_imageInfo->height = height;

	mGraphics = new Graphics(memDc);

	mFileName = fileName;

	mBitmap = new Bitmap(wstring(fileName.begin(), fileName.end()).c_str());
	mCacheBitmap = new CachedBitmap(mBitmap, mGraphics);

	return S_OK;
}

void ImageGp::release()
{
	SAFE_DELETE(_imageInfo);
	SAFE_DELETE(_image);
}

void ImageGp::setWidth(float width)
{
	Bitmap pBitmap(width, _imageInfo->height);
	Gdiplus::Graphics graphics(&pBitmap);
	graphics.DrawImage(_image, 0.0f, 0.0f, width, _imageInfo->height);

	mBitmap = &pBitmap;
	mCacheBitmap = new CachedBitmap(&pBitmap, mGraphics);
}

void ImageGp::setHeight(float height)
{
	Bitmap pBitmap(_imageInfo->width, height);
	Gdiplus::Graphics graphics(&pBitmap);
	graphics.DrawImage(_image, 0.0f, 0.0f, _imageInfo->width, height);

	mBitmap = &pBitmap;
	mCacheBitmap = new CachedBitmap(&pBitmap, mGraphics);
}

void ImageGp::setSize(float width, float height)
{
	Bitmap* pBitmap = new Bitmap(width, height);
	Gdiplus::Graphics graphics(pBitmap);
	graphics.DrawImage(_image, 0.0f, 0.0f, width, height);

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
	mGraphics->DrawCachedBitmap(mCacheBitmap, rectF.GetLeft(), rectF.GetTop());
}
