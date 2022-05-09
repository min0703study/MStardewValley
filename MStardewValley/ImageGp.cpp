#include "Stdafx.h"
#include "ImageGp.h"

int ImageGp::mCountIndex = 0;

HRESULT ImageGp::init(HDC memDc, string fileName, float width, float height, int maxFrameX, int maxFrameY)
{
	if (mImageInfo != NULL) this->release();

	mImage = new Gdiplus::Image(wstring(fileName.begin(), fileName.end()).c_str());

	if (mImage->GetLastStatus() != Gdiplus::Status::Ok)
	{
		release();
		return E_FAIL;
	}

	mIndex = 0;

	mImageInfo = new IMAGE_INFO;
	mImageInfo->LoadType = LOAD_FILE;
	mImageInfo->Type = IT_FRAME;

	mImageInfo->MaxFrameX = maxFrameX - 1;
	mImageInfo->MaxFrameY = maxFrameY - 1;
	
	mImageInfo->FrameWidth = width / static_cast<float> (maxFrameX);
	mImageInfo->FrameHeight = height / static_cast<float>(maxFrameY);

	mImageInfo->Width = width;
	mImageInfo->Height = height;

	mFileName = fileName;

	mOriginalBitmap = new Bitmap(wstring(fileName.begin(), fileName.end()).c_str());

	this->initBitmap(memDc, width, height);

	return S_OK;
}

HRESULT ImageGp::init(HDC memDc, Gdiplus::Bitmap* bitmap, float width, float height, int maxFrameX, int maxFrameY)
{
	mImage = bitmap;

	mImageInfo = new IMAGE_INFO;
	mImageInfo->LoadType = LOAD_FILE;
	mImageInfo->Type = IT_FRAME;

	mImageInfo->MaxFrameX = maxFrameX - 1;
	mImageInfo->MaxFrameY = maxFrameY - 1;

	mImageInfo->FrameWidth = width / static_cast<float> (maxFrameX);
	mImageInfo->FrameHeight = height / static_cast<float>(maxFrameY);

	mImageInfo->Width = width;
	mImageInfo->Height = height;

	mIndex = 0;

	mOriginalBitmap = bitmap;
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

HRESULT ImageGp::initCenter(HDC memDc, Gdiplus::Bitmap * bitmap, float width, float height, float xP, float yP)
{
	float centerX = width / 2.0f - bitmap->GetWidth() / 2.0f;
	float centerY = height / 2.0f - bitmap->GetHeight() / 2.0f;

	Bitmap* tempBitmap = GDIPLUSMANAGER->overlayBitmap(memDc, bitmap, centerX + xP, centerY + yP, width, height);
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
	mCurCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);

	mCountIndex = 0;

	mMemDc = memDc;

	mRenderType = RT_CACHED;
	
	bool haveAlpha = false;
	for (float y = 0; y < mImageInfo->Height; y++)
	{
		for (float x = 0; x < mImageInfo->Width; x++)
		{
			Color pxColor;
			mOriginalBitmap->GetPixel(x, y, &pxColor);
			if (pxColor.GetAlpha() != 0) {
				haveAlpha = true;
				break;
			}
			if (haveAlpha) break;
		}
	}
	mImageInfo->bHaveAlpha = haveAlpha;
	return S_OK;
}

void ImageGp::release()
{
	//SAFE_DELETE(_imageInfo);
	//SAFE_DELETE(_image);
}

// == size change
void ImageGp::setSizeRatio(float ratio)
{
	this->setSize(mImageInfo->Width * ratio, mImageInfo->Height * ratio);
}

void ImageGp::setWidth(float width)
{
	this->setSize(width, mImageInfo->Height);
}

void ImageGp::setHeight(float height)
{
	this->setSize(mImageInfo->Width, height);
}

void ImageGp::setSize(float width, float height)
{
	Bitmap* tempBitmap = new Bitmap(width, height);
	Gdiplus::Graphics* tempGraphics = new Graphics(tempBitmap);
	tempGraphics->DrawImage(mCurBitmap, RectFMake(0.0f, 0.0f, width + 1.0f, height + 1.0f), 0.0f, 0.0f, mCurBitmap->GetWidth(), mCurBitmap->GetHeight(), UnitPixel);

	makeNewBitmap(tempBitmap, tempGraphics);
}
// size change ==

void ImageGp::rebuildChachedBitmap(void)
{
	delete mCurCacheBitmap;
	mCurCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);
}

void ImageGp::rebuildHBitmap(void)
{
	/*
	SelectObject(mHMemDc, &mHOldBitmap);
	DeleteObject(mHBitmap);
	DeleteDC(mHMemDc);
	*/

	Bitmap* pBitmap = getBitmapClone();
	pBitmap->GetHBITMAP(Color(255, 0, 255), &mHBitmap);

	mHOldBitmap = (HBITMAP)SelectObject(mHMemDc, mHBitmap);
}

// == rotate
void ImageGp::rotate(float angle)
{
	Bitmap* tempBitmap = new Bitmap(mImageInfo->Width * 2.0f, mImageInfo->Height * 2.0f);
	Gdiplus::Graphics* tempGraphics = new Graphics(tempBitmap);

	Gdiplus::Matrix matrix;
	matrix.RotateAt(angle, { mImageInfo->Width, mImageInfo->Height });
	tempGraphics->SetTransform(&matrix);
	tempGraphics->DrawImage(mCurBitmap, mImageInfo->Width / 2.0f, 0.0f, mImageInfo->Width, mImageInfo->Height);

	makeNewBitmap(tempBitmap, tempGraphics);
}
void ImageGp::rotateToXCenter(float angle, Bitmap* bitmap)
{
	Gdiplus::Graphics* tempGraphics = new Graphics(bitmap);

	Gdiplus::Matrix matrix;
	matrix.RotateAt(angle, { static_cast<float> (bitmap->GetWidth()) * 0.5f, static_cast<float> (bitmap->GetHeight()) * 0.5f});
	tempGraphics->SetTransform(&matrix);
	tempGraphics->DrawImage(mCurBitmap, (bitmap->GetWidth() * 0.5f) - (mImageInfo->Width * 0.5f), 0.0f, mImageInfo->Width, mImageInfo->Height);

	makeNewBitmap(bitmap, tempGraphics);
}

void ImageGp::rotate(float angle, eXStandard rotateX, eYStandard rotateY, float newWidthSize, float newHeightSize)
{
	Bitmap* tempBitmap = new Bitmap(newWidthSize, newHeightSize);
	Gdiplus::Graphics* tempGraphics = new Graphics(tempBitmap);

	PointF rotatePt;
	PointF drawPt;
	
	drawPt.X = tempBitmap->GetWidth() * 0.5f - mImageInfo->Width * 0.5f;
	drawPt.Y = (tempBitmap->GetHeight() * 0.5f) - mImageInfo->Height * 0.5f;

	switch (rotateX) {
	case XS_LEFT:
		rotatePt.X = (tempBitmap->GetWidth() * 0.5f) - mImageInfo->Width * 0.5f;
		break;
	case XS_CENTER:
		rotatePt.X = tempBitmap->GetWidth() * 0.5f;
		break;
	case XS_RIGHT:
		rotatePt.X = (tempBitmap->GetWidth() * 0.5f) + mImageInfo->Width * 0.5f;
		break;
	}

	switch (rotateY) {
	case YS_TOP:
		rotatePt.Y = (tempBitmap->GetHeight() * 0.5f) - mImageInfo->Height * 0.5f;
		break;
	case YS_CENTER:
		rotatePt.Y = tempBitmap->GetHeight() * 0.5f;
		break;
	case YS_BOTTOM:
		rotatePt.Y = (tempBitmap->GetHeight() * 0.5f) + mImageInfo->Height * 0.5f;
		break;
	}

	Gdiplus::Matrix matrix;
	matrix.RotateAt(angle, rotatePt);
	tempGraphics->SetTransform(&matrix);
	tempGraphics->DrawImage(mCurBitmap, drawPt.X, drawPt.Y, mImageInfo->Width, mImageInfo->Height);

	makeNewBitmap(tempBitmap, tempGraphics);
}

void ImageGp::rotateSample(float angle)
{
	Bitmap* tempBitmap = new Bitmap(mImageInfo->Width * 2.0f, mImageInfo->Height * 2.0f);
	Gdiplus::Graphics gp(tempBitmap);

	Gdiplus::Matrix matrix;
	matrix.RotateAt(angle, { mImageInfo->Width, mImageInfo->Height });
	gp.SetTransform(&matrix);

	gp.DrawImage(mCurBitmap, mImageInfo->Width, 0.0f, mImageInfo->Width, mImageInfo->Height);

	mCurBitmap = tempBitmap;
	mCurBitmapGraphics = new Gdiplus::Graphics(mCurBitmap);
	mCurCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);

	if (mImageInfo->Type == IT_FRAME) {
		mImageInfo->FrameWidth = tempBitmap->GetWidth() / static_cast<float> (mImageInfo->MaxFrameX + 1);
		mImageInfo->FrameHeight = tempBitmap->GetHeight() / static_cast<float> (mImageInfo->MaxFrameY + 1);
	}

	mImageInfo->Width = tempBitmap->GetWidth();
	mImageInfo->Height = tempBitmap->GetHeight();
}
void ImageGp::rotateToYCenter(float angle, Bitmap* bitmap)
{
	Gdiplus::Graphics gp(bitmap);

	Gdiplus::Matrix matrix;
	matrix.RotateAt(angle, { static_cast<float> (bitmap->GetWidth() * 0.5f), static_cast<float> (bitmap->GetHeight()) * 0.5f });
	gp.SetTransform(&matrix);

	gp.DrawImage(mCurBitmap, (bitmap->GetWidth() * 0.5f) - (mImageInfo->Width * 0.5f), (bitmap->GetHeight() * 0.5f) - (mImageInfo->Height * 0.5f), mImageInfo->Width, mImageInfo->Height);

	mCurBitmap = bitmap;
	mCurBitmapGraphics = new Gdiplus::Graphics(mCurBitmap);
	mCurCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);

	if (mImageInfo->Type == IT_FRAME) {
		mImageInfo->FrameWidth = bitmap->GetWidth() / static_cast<float> (mImageInfo->MaxFrameX + 1);
		mImageInfo->FrameHeight = bitmap->GetHeight() / static_cast<float> (mImageInfo->MaxFrameY + 1);
	}

	mImageInfo->Width = bitmap->GetWidth();
	mImageInfo->Height = bitmap->GetHeight();
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
	mCurCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);
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
// rotate ==

//flip
void ImageGp::flipX()
{
	mCurBitmap->RotateFlip(RotateNoneFlipX);
	rebuildChachedBitmap();
}
void ImageGp::flipY()
{
	mCurBitmap->RotateFlip(RotateNoneFlipY);
	rebuildChachedBitmap();
}
void ImageGp::flip90(int count)
{
	if (count == 1) {
		mCurBitmap->RotateFlip(Rotate90FlipNone);
	}
	else if (count == 2) {
		mCurBitmap->RotateFlip(Rotate180FlipNone);
	}
	else if (count == 3) {
		mCurBitmap->RotateFlip(Rotate270FlipNone);
	}

	rebuildChachedBitmap();
}

void ImageGp::move(float value)
{
	Bitmap* tempBitmap = new Bitmap(mImageInfo->Width, mImageInfo->Height);
	Gdiplus::Graphics* tempGraphics = new Graphics(tempBitmap);

	tempGraphics->DrawImage(
		mCurBitmap,
		RectFMake(0, 0, mImageInfo->Width, mImageInfo->Height),
		value, 0.0f,
		mImageInfo->Width, mImageInfo->Height,
		UnitPixel
	);

	makeNewBitmap(tempBitmap, tempGraphics);
}

// == color change
void ImageGp::changeColor()
{
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

	mCurBitmapGraphics->DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, mImageInfo->Width, mImageInfo->Height),
		0, 0,
		mCurBitmap->GetWidth(),
		mCurBitmap->GetHeight(),
		UnitPixel,
		&imageAttributes);	
}

void ImageGp::changeRedColor()
{
	ImageAttributes  imageAttributes;

	ColorMatrix colorMatrix = {
	   2.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	   0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	   0.2f, 0.2f, 0.2f, 0.0f, 1.0f };

	imageAttributes.SetColorMatrix(
		&colorMatrix,
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);

	mCurBitmapGraphics->DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, mImageInfo->Width, mImageInfo->Height),
		0, 0,
		mCurBitmap->GetWidth(),
		mCurBitmap->GetHeight(),
		UnitPixel,
		&imageAttributes);

	rebuildChachedBitmap();
}

void ImageGp::toOriginal()
{
	Gdiplus::Bitmap* tempBitmap = mOriginalBitmap->Clone(0, 0, mOriginalBitmap->GetWidth(), mOriginalBitmap->GetHeight(), mOriginalBitmap->GetPixelFormat());
	Gdiplus::Graphics* tempGraphics = new Graphics(mCurBitmap);

	makeNewBitmap(tempBitmap, tempGraphics);
}
// color change ==

// == alpha
void ImageGp::toAlpha(float alpha) {
	Gdiplus::Bitmap* tempBitmap = new Gdiplus::Bitmap(mImageInfo->Width, mImageInfo->Height);
	Gdiplus::Graphics* tempGraphics = new Graphics(tempBitmap);

	ImageAttributes  imageAttributes;
	const ColorMatrix colorMatrix = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
							   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
							   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
							   0.0f, 0.0f, 0.0f, alpha, 0.0f,
							   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	imageAttributes.SetColorMatrix(
		&colorMatrix,
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);

	tempGraphics->DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, mImageInfo->Width, mImageInfo->Height),
		0,
		0,
		mImageInfo->Width,
		mImageInfo->Height,
		UnitPixel, &imageAttributes);

	makeNewBitmap(tempBitmap, tempGraphics);
}
void ImageGp::toTransparent(RectF rcF) {
	for (float y = 0; y < rcF.Height; y++)
	{
		for (float x = 0; x < rcF.Width; x++)
		{
			mCurBitmap->SetPixel(x + rcF.X, y + rcF.Y, Color(0, 0, 0, 0));
		}
	}
}
void ImageGp::toTransparent() {
	for (float y = 0; y < mImageInfo->Height; y++)
	{
		for (float x = 0; x < mImageInfo->Width; x++)
		{
			mCurBitmap->SetPixel(x, y, Color(0, 0, 0, 0));
		}
	}
}
// alpha ==

void ImageGp::cutTransparentArea()
{
	int topAlphaSize, leftAlphaSize, bottomAlphaSize, rightAlphaSize = -1;

	for (int y = 0; y < mImageInfo->Height; y++) {
		bool isOneLineAllAlpha = true;
		for (int x = 0; x < mCurBitmap->GetWidth(); x++) {
			Color color;
			mCurBitmap->GetPixel(x, y, &color);
			if (color.GetAlpha() != 0) {
				isOneLineAllAlpha = false;
				break;
			}
		}

		if (!isOneLineAllAlpha) {
			topAlphaSize = y;
			break;
		}
	}

	for (int y = (mImageInfo->Height - 1); y > 0; y--) {
		bool isOneLineAllAlpha = true;
		for (int x = 0; x < mCurBitmap->GetWidth(); x++) {
			Color color;
			mCurBitmap->GetPixel(x, y, &color);
			if (color.GetAlpha() != 0) {
				isOneLineAllAlpha = false;
				break;
			}
		}

		if (!isOneLineAllAlpha) {
			bottomAlphaSize = mCurBitmap->GetHeight() - y;
			break;
		}
	}

	for (int x = 0; x < mImageInfo->Width; x++) {
		bool isOneLineAllAlpha = true;
		for (int y = 0; y < mCurBitmap->GetHeight(); y++) {
			Color color;
			mCurBitmap->GetPixel(x, y, &color);
			if (color.GetAlpha() != 0) {
				isOneLineAllAlpha = false;
				break;
			}
		}
		if (!isOneLineAllAlpha) {
			leftAlphaSize = x;
			break;
		}
	}

	for (int x = mImageInfo->Width; x > 0; x--) {
		bool isOneLineAllAlpha = true;
		for (int y = 0; y < mCurBitmap->GetHeight(); y++) {
			Color color;
			mCurBitmap->GetPixel(x, y, &color);
			if (color.GetAlpha() != 0) {
				isOneLineAllAlpha = false;
				break;
			}
		}
		if (!isOneLineAllAlpha) {
			rightAlphaSize = mImageInfo->Width - x;
			break;
		}
	}

	int cutWidth = mImageInfo->Width - rightAlphaSize - leftAlphaSize;
	int cutHeight = mImageInfo->Height - bottomAlphaSize - topAlphaSize;

	Gdiplus::Bitmap* tempBitmap = new Gdiplus::Bitmap(cutWidth, cutHeight);
	Gdiplus::Graphics* tempGraphics = new Graphics(tempBitmap);

	tempGraphics->DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, cutWidth, cutHeight),
		leftAlphaSize,
		topAlphaSize,
		cutWidth,
		cutHeight,
		UnitPixel);

	makeNewBitmap(tempBitmap, tempGraphics);
}
void ImageGp::cutTransparentAreaVertical()
{
	int topAlphaSize, bottomAlphaSize = -1;

	for (int y = 0; y < mImageInfo->Height; y++) {
		bool isOneLineAllAlpha = true;
		for (int x = 0; x < mCurBitmap->GetWidth(); x++) {
			Color color;
			mCurBitmap->GetPixel(x, y, &color);
			if (color.GetAlpha() != 0) {
				isOneLineAllAlpha = false;
				break;
			}
		}

		if (!isOneLineAllAlpha) {
			topAlphaSize = y;
			break;
		}
	}

	for (int y = (mImageInfo->Height - 1); y > 0; y--) {
		bool isOneLineAllAlpha = true;
		for (int x = 0; x < mCurBitmap->GetWidth(); x++) {
			Color color;
			mCurBitmap->GetPixel(x, y, &color);
			if (color.GetAlpha() != 0) {
				isOneLineAllAlpha = false;
				break;
			}
		}

		if (!isOneLineAllAlpha) {
			bottomAlphaSize = mCurBitmap->GetHeight() - y;
			break;
		}
	}

	int cutHeight = mImageInfo->Height - bottomAlphaSize - topAlphaSize;

	Gdiplus::Bitmap* tempBitmap = new Gdiplus::Bitmap(mImageInfo->Width, cutHeight);
	Gdiplus::Graphics* tempGraphics = new Graphics(tempBitmap);

	tempGraphics->DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, mImageInfo->Width, cutHeight),
		0,
		topAlphaSize,
		mImageInfo->Width,
		cutHeight,
		UnitPixel);

	makeNewBitmap(tempBitmap, tempGraphics);
}
//
void ImageGp::clipping(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	mClippingBitmapGraphics->Clear(Color(0,0,0,0));
	mClippingBitmapGraphics->DrawImage(mCurBitmap,
		destX, destY,
		sourX, sourY,
		sourWidth,
		sourHeight,
		UnitPixel);

	mCurCacheBitmap = new CachedBitmap(mClippingBitmap, mGraphics);
}

void ImageGp::clipping(RectF rcF)
{
	mClippingBitmapGraphics->Clear(Color(0, 0, 0, 0));
	mClippingBitmapGraphics->DrawImage(mCurBitmap, rcF);

	mCurCacheBitmap = new CachedBitmap(mClippingBitmap, mGraphics);
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
	mClippingBitmap = new Bitmap(sourWidth, sourHeight);
	mClippingBitmapGraphics = new Graphics(mClippingBitmap);
	mCurCacheBitmap = new CachedBitmap(mClippingBitmap, mGraphics);
}

void ImageGp::setRenderBitBlt() {
	mRenderType = RT_BITBLT;

	Bitmap* pBitmap = getBitmapClone();
	mHBitmap = nullptr;

	pBitmap->GetHBITMAP(Color(255, 0, 255), &mHBitmap);

	mHMemDc = CreateCompatibleDC(mMemDc);
	mHOldBitmap = (HBITMAP)SelectObject(mHMemDc, mHBitmap);
}

void ImageGp::setRenderAlpha(void)
{
	mImageInfo->Type = IT_ALPHA;

	mImageInfo->BlendFunc.BlendFlags = 0;
	mImageInfo->BlendFunc.BlendOp = AC_SRC_OVER;
	mImageInfo->BlendFunc.AlphaFormat = 0;

	mHBlendMemDc = CreateCompatibleDC(mMemDc);
	mHOldBitmap = (HBITMAP)SelectObject(mHBlendMemDc, CreateCompatibleBitmap(mMemDc, mImageInfo->Width, mImageInfo->Height));
}

void ImageGp::render(float x, float y, eXStandard xStandard, eYStandard yStandard)
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
		y = y - (mImageInfo->Height * 0.5f);
		break;
	}

	if (mRenderType == RT_CACHED) {
		mGraphics->DrawCachedBitmap(mCurCacheBitmap, static_cast<int>(x), static_cast<int>(y));
	} else if(mRenderType == RT_BITBLT) {
		if (mImageInfo->Type == IT_ALPHA) {
			if (mImageInfo->bHaveAlpha) {
				BitBlt(mHBlendMemDc, 0, 0, static_cast<int>(mImageInfo->Width), static_cast<int>(mImageInfo->Height), mMemDc, static_cast<int>(x), static_cast<int>(y), SRCCOPY);
				GdiTransparentBlt
				(
					mHBlendMemDc,
					0,
					0,
					static_cast<int>(mImageInfo->Width),
					static_cast<int>(mImageInfo->Height),
					mHMemDc,
					0, 0,
					static_cast<int>(mImageInfo->Width),
					static_cast<int>(mImageInfo->Height),
					RGB(255, 0, 255)
				);
				AlphaBlend
				(
					mMemDc,
					static_cast<int>(x), static_cast<int>(y),
					static_cast<int>(mImageInfo->Width),
					static_cast<int>(mImageInfo->Height),
					mHBlendMemDc,
					0, 0,
					mImageInfo->Width,
					mImageInfo->Height,
					mImageInfo->BlendFunc
				);
			}
			else {
				AlphaBlend
				(
					mMemDc,
					static_cast<int>(x), static_cast<int>(y),
					static_cast<int>(mImageInfo->Width),
					static_cast<int>(mImageInfo->Height),
					mHMemDc,
					0, 0,
					mImageInfo->Width,
					mImageInfo->Height,
					mImageInfo->BlendFunc
				);
			}
		}
		else {
			if (mImageInfo->bHaveAlpha) {
				GdiTransparentBlt
				(
					mMemDc,
					static_cast<int>(x), static_cast<int>(y),
					static_cast<int>(mImageInfo->Width),
					static_cast<int>(mImageInfo->Height),
					mHMemDc,
					0, 0,
					static_cast<int>(mImageInfo->Width),
					static_cast<int>(mImageInfo->Height),
					RGB(255, 0, 255)
				);
			}
			else {
				BitBlt(mMemDc, static_cast<int>(x), static_cast<int>(y), static_cast<int>(mImageInfo->Width), static_cast<int>(mImageInfo->Height), mHMemDc, 0, 0, SRCCOPY);
			}
		}
	}
}

void ImageGp::renderAlphaMode(float x, float y, eXStandard xStandard, eYStandard yStandard) {
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
		y = y - (mImageInfo->Height * 0.5f);
		break;
	}

	ImageAttributes  imageAttributes;
	const ColorMatrix colorMatrix = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
							   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
							   0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
							   0.0f, 0.0f, 0.0f, 0.3f, 0.0f,
							   0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	imageAttributes.SetColorMatrix(
		&colorMatrix,
		ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);

	mGraphics->DrawImage(
		mCurBitmap,
		RectF(x, y, mImageInfo->Width, mImageInfo->Height),
		0,
		0,
		mImageInfo->Width,
		mImageInfo->Height,
		UnitPixel, &imageAttributes);
}

void ImageGp::render(RectF rectF)
{
	if (mRenderType == RT_CACHED) {
		mGraphics->DrawImage(mCurBitmap, rectF);
	}
	else if (mRenderType == RT_BITBLT) {
		if (mImageInfo->Type == IT_ALPHA) {
			AlphaBlend
			(
				mMemDc,
				0,0,
				static_cast<int>(mImageInfo->Width),
				static_cast<int>(mImageInfo->Height),
				mHMemDc,
				0, 0,
				mImageInfo->Width,
				mImageInfo->Height,
				mImageInfo->BlendFunc
			);
		}
		else {
			if (!mImageInfo->bHaveAlpha) {
				BitBlt(mMemDc, static_cast<int>(rectF.X), static_cast<int>(rectF.Y), static_cast<int>(rectF.Width), static_cast<int>(rectF.Height), mHMemDc, 0, 0, SRCCOPY);
			}
			else {
				GdiTransparentBlt
				(
					mMemDc,
					0,
					0,
					static_cast<int>(mImageInfo->Width),
					static_cast<int>(mImageInfo->Height),
					mHMemDc,
					0, 0,
					static_cast<int>(mImageInfo->Width),
					static_cast<int>(mImageInfo->Height),
					RGB(255, 0, 255)
				);
			}
		}

	}
}

void ImageGp::loopRender(HDC hdc, float x, float y, int startIndex)
{
	int curIndex = 0;
	for (int i = 0; i < mVLoopCashBitmap.size(); i++) {
		curIndex = (i + startIndex) % (mImageInfo->LoopFrameX);
		mGraphics->DrawCachedBitmap(mVLoopCashBitmap[curIndex], i * mImageInfo->LoopWidth, y);
	}
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
	RectF rcF = RectFMake(x, y, bitmap->GetWidth(), bitmap->GetHeight());
	mCurBitmapGraphics->DrawImage(bitmap, 
		rcF,
		0.0f,0.0f,
		bitmap->GetWidth(), bitmap->GetHeight(),
		UnitPixel
	);
}

void ImageGp::overlayBitmapCenter(Gdiplus::Bitmap* bitmap)
{
	float centerX = mCurBitmap->GetWidth() / 2.0f - bitmap->GetWidth() / 2.0f;
	float centerY = mCurBitmap->GetHeight() / 2.0f - bitmap->GetHeight() / 2.0f;
	
	mCurBitmapGraphics->DrawImage(bitmap, centerX, centerY, bitmap->GetWidth(), bitmap->GetHeight());

	//delete 삭제
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

void ImageGp::overlayImageGp(const ImageGp * imageGp, eXStandard xStandard, eYStandard yStandard, bool isOriginal)
{
	float leftX;
	float topY;

	switch (xStandard) {
	case XS_LEFT:
		leftX = 0;
		break;
	case XS_RIGHT:
		leftX = mImageInfo->Width - imageGp->getWidth();
		break;
	case XS_CENTER:
		leftX = (mImageInfo->Width * 0.5f) - (imageGp->getWidth() * 0.5f);
		break;
	}

	switch (yStandard) {
	case YS_TOP:
		topY = 0;
		break;
	case YS_BOTTOM:
		topY = mImageInfo->Height - imageGp->getHeight();
		break;
	case YS_CENTER:
		topY = (mImageInfo->Height * 0.5f) - (imageGp->getHeight() * 0.5f);
		break;
	}

	if (isOriginal) {
		mCurBitmapGraphics->DrawImage(
			imageGp->getOriginalBitmap(),
			RectFMake(leftX, topY, imageGp->getWidth(), imageGp->getHeight()),
			0.0f, 0.0f,
			imageGp->getOriginalBitmap()->GetWidth(), imageGp->getOriginalBitmap()->GetHeight(),
			UnitPixel
		);
	}
	else {
		mCurBitmapGraphics->DrawImage(
			imageGp->getBitmap(),
			RectFMake(leftX, topY, imageGp->getWidth(), imageGp->getHeight()),
			0.0f, 0.0f,
			imageGp->getBitmap()->GetWidth(), imageGp->getBitmap()->GetHeight(),
			UnitPixel
		);
	}


	rebuildChachedBitmap();
}
void ImageGp::overlayImageGp(const ImageGp * imageGp, float leftX, float topY, bool isOriginal)
{
	if (isOriginal) {
		mCurBitmapGraphics->DrawImage(
			imageGp->getOriginalBitmap(),
			RectFMake(leftX, topY, imageGp->getWidth(), imageGp->getHeight()),
			0.0f, 0.0f,
			imageGp->getOriginalBitmap()->GetWidth(), imageGp->getOriginalBitmap()->GetHeight(),
			UnitPixel
		);
	}
	else {
		mCurBitmapGraphics->DrawImage(
			imageGp->getBitmap(),
			RectFMake(leftX, topY, imageGp->getWidth(), imageGp->getHeight()),
			0.0f, 0.0f,
			imageGp->getBitmap()->GetWidth(), imageGp->getBitmap()->GetHeight(),
			UnitPixel
		);
	}

	rebuildChachedBitmap();
}

Gdiplus::Bitmap* ImageGp::getFrameBitmap(int currentFrameX, int currentFrameY)
{
	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(mImageInfo->FrameWidth, mImageInfo->FrameHeight);
	Gdiplus::Graphics graphics(pBitmap);

	graphics.DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, mImageInfo->FrameWidth, mImageInfo->FrameHeight),
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

Gdiplus::Bitmap* ImageGp::getFrameBitmapToIndex(int currentFrameX, int currentFrameY, int toXCount, int toYCount, float width, float height)
{
	float rWidth = mImageInfo->FrameWidth * (toXCount + 1);
	float rHeight = mImageInfo->FrameHeight * (toYCount + 1);

	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(width, height);
	Gdiplus::Graphics graphics(pBitmap);
	graphics.DrawImage(
		mCurBitmap,
		RectF(0.0f, 0.0f, width, height),
		currentFrameX * mImageInfo->FrameWidth,
		currentFrameY * mImageInfo->FrameHeight,
		rWidth,
		rHeight,
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

//debug
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

inline void ImageGp::makeNewBitmap(Bitmap * newBitmap, Graphics * newGrapics)
{
	//delete resource
	mCurBitmapGraphics->Clear(Color(0, 0, 0, 0));
	delete mCurBitmapGraphics;
	delete mCurBitmap;
	delete mCurCacheBitmap;

	//new mapping
	mCurBitmap = newBitmap;
	mCurBitmapGraphics = newGrapics;
	mCurCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);

	//info reset
	if (mImageInfo->Type == IT_FRAME) {
		mImageInfo->FrameWidth = mCurBitmap->GetWidth() / static_cast<float> (mImageInfo->MaxFrameX + 1);
		mImageInfo->FrameHeight = mCurBitmap->GetHeight() / static_cast<float> (mImageInfo->MaxFrameY + 1);
	}

	mImageInfo->Width = mCurBitmap->GetWidth();
	mImageInfo->Height = mCurBitmap->GetHeight();
}

void ImageGp::clear() {
	mGraphics->Clear(Color(0, 0, 0, 0));
	mCurBitmapGraphics->Clear(Color(0, 0, 0, 0));
}




