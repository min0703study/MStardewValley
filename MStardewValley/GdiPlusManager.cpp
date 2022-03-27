#include "Stdafx.h"
#include "GdiPlusManager.h"
#include "ImageGp.h"

HRESULT GdiPlusManager::init()
{
	fontFamily = new FontFamily(GAME_FONT);
	centerFormat.SetAlignment(StringAlignmentCenter);

	return S_OK;
}

HRESULT GdiPlusManager::init(HDC memDc)
{
	fontFamily = new FontFamily(GAME_FONT);
	centerFormat.SetAlignment(StringAlignmentCenter);

	mMemDc = memDc;
	return S_OK;
}

ImageGp* GdiPlusManager::findImage(string strKey)
{
	auto key = _mImageList.find(strKey);
	if (key != _mImageList.end())
	{
		return key->second;
	}
	return nullptr;
}

ImageGp* GdiPlusManager::findAndCloneImage(string strKey)
{
	auto key = _mImageList.find(strKey);
	if (key != _mImageList.end())
	{
		return key->second->clone();
	}
	return nullptr;
}

ImageGp* GdiPlusManager::addFrameImage(string strKey, const string fileName, int width, int height, int maxFrameX, int maxFrameY)
{
	ImageGp* img = findImage(strKey);
	if (img) return img;

	img = new ImageGp();

	if (FAILED(img->init(mMemDc, fileName, width, height, maxFrameX, maxFrameY)))
	{
		MY_UTIL::log(DEBUG_IMG_GP_TAG, "프레임 이미지 생성 실패 : " + strKey + "\nㄴPATH: " + fileName);
		SAFE_DELETE(img);
		return NULL;
	}
	else {
		if (img->getImage()->GetWidth() != width || img->getImage()->GetHeight() != height) {
			MY_UTIL::log(DEBUG_IMG_GP_TAG, "프레임 이미지 리사이징 : " + strKey);
		}
		MY_UTIL::log(DEBUG_IMG_GP_TAG, "프레임 이미지 생성 성공 : " + strKey );
	}

	_mImageList.insert(make_pair(strKey, img));
}

ImageGp* GdiPlusManager::addImage(string strKey, const char * fileName, int width, int height)
{
	ImageGp* img = findImage(strKey);
	if (img) return img;

	img = new ImageGp();
	if (FAILED(img->init(mMemDc, fileName, width, height)))
	{
		MY_UTIL::log(DEBUG_IMG_GP_TAG, "이미지 생성 실패 : " + strKey + "\nㄴPATH: " + fileName);
		SAFE_DELETE(img);
		return NULL;
	}
	else {
		if (img->getImage()->GetWidth() != width || img->getImage()->GetHeight() != height) {
			MY_UTIL::log(DEBUG_IMG_GP_TAG, "이미지 리사이징 : " + strKey);
		}
		MY_UTIL::log(DEBUG_IMG_GP_TAG, "이미지 생성 성공 : " + strKey);
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

void GdiPlusManager::frameRender(string strKey, HDC hdc, float x, float y)
{
	ImageGp* img = findImage(strKey);
	if (!img) return;

	ImageAttributes imageAtt;

	imageAtt.SetColorKey(
		Color(255, 0, 255),
		Color(255, 0, 255),
		ColorAdjustTypeDefault
	);

	Gdiplus::RectF rcf = Gdiplus::RectF(x, y, img->getFrameWidth(), img->getFrameHeight());

	(*(img->getGraphics())).DrawImage(
		img->getImage(),
		rcf,
		0, 0, 
		img->getWidth(), 
		img->getHeight(),
		UnitPixel,
		&imageAtt);
}

void GdiPlusManager::render(string strKey, HDC hdc, float x, float y)
{
	ImageGp* img = findImage(strKey);
	if (!img) return;
	(*(img->getGraphics())).DrawCachedBitmap(img->getCachedBitmap(), x, y);
}

void GdiPlusManager::render(ImageGp* img, float x, float y)
{
	(*(img->getGraphics())).DrawCachedBitmap(img->getCachedBitmap(), x, y);
}

void GdiPlusManager::render(string strKey, HDC hdc, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight)
{
	ImageGp* img = findImage(strKey);
	if (!img) return;

	(*(img->getGraphics())).DrawCachedBitmap(img->getCachedBitmap(), destX, destY);

}

void GdiPlusManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	ImageGp* img = findImage(strKey);
	if (!img) return;

	
	if (offsetX < 0) offsetX = img->getWidth() + (offsetX % (int)img->getWidth());
	if (offsetY < 0) offsetY = img->getHeight() + (offsetY % (int)img->getHeight());


	RECT rcSour;
	int sourWidth;
	int sourHeight;

	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{

		rcSour.top = (y + offsetY) % (int)img->getHeight();
		rcSour.bottom = img->getHeight();
		sourHeight = rcSour.bottom - rcSour.top;


		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}


		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offsetX) % (int)img->getWidth();
			rcSour.right = img->getWidth();
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(strKey, hdc, (float)rcDest.left, (float)rcDest.top, (float)rcSour.left, (float)rcSour.top, sourWidth, sourHeight);
		}
	}
}

void GdiPlusManager::drawText(HDC hdc, std::wstring message, float x, float y, int size, Color color)
{
	Font        font(fontFamily, size, FontStyleRegular, UnitPixel);
	SolidBrush  solidBrush(color);
	//gh.DrawString(message.c_str(), -1, &font, PointF(x, y), &solidBrush);
}

void GdiPlusManager::drawRectF(HDC hdc, RectF rectF, Gdiplus::Color line, Gdiplus::Color solid)
{
	Gdiplus::Graphics gh(hdc);
	if (solid.GetAlpha() != 0) {
		SolidBrush s(solid);
		gh.FillRectangle(&s, rectF);
	}

	Pen pen(line);
	gh.DrawRectangle(&pen, rectF);
}

void GdiPlusManager::drawGridLine(ImageGp* imgGp, float gridXSize, float gridYSize)
{
	Gdiplus::Graphics graphics(imgGp->getBitmap());

	Pen      pen(Color(91, 43, 41), 1);
	SolidBrush s(Color(255, 255, 255));

	graphics.FillRectangle(&s, 0.0f, 0.0f, imgGp->getWidth(), imgGp->getHeight());

	for (float gridX = 0.0f; gridX < imgGp->getWidth(); gridX += gridXSize) {
		graphics.DrawLine(&pen, gridX, 0.0f, gridX, imgGp->getHeight());
	}
	for (float gridY = 0.0f; gridY < imgGp->getHeight(); gridY += gridYSize) {
		graphics.DrawLine(&pen, 0.0f, gridY, imgGp->getWidth(), gridY);
	}

	imgGp->rebuildChachedBitmap();
}

Bitmap* GdiPlusManager::getBitmap(float width, float height)
{
	Bitmap* pBitmap = new Bitmap(width, height);
	Gdiplus::Graphics graphics(pBitmap);

	Pen      pen(Color(91, 43, 41), 0.5);
	SolidBrush s(Color(255, 255, 255));

	graphics.FillRectangle(&s, 0.0f, 0.0f, width, height);
	graphics.DrawRectangle(&pen, 0.0f, 0.0f, width, height);
	return pBitmap;
}

void GdiPlusManager::release()
{
}
