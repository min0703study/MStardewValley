#include "Stdafx.h"
#include "GdiPlusManager.h"
#include "ImageGp.h"

ImageGp* GdiPlusManager::addFrameImage(string strKey, const string fileName, float width, float height, int maxFrameX, int maxFrameY)
{
	ImageGp* img = findOriginalImage(strKey);
	if (img) return img;

	img = new ImageGp();
	LOG::d(LOG_IMG_GP_TAG, "== 프레임 이미지 생성 시작 : \t\t" + strKey + "\t\t ==");
	if (FAILED(img->init(mMemDc, fileName, width, height, maxFrameX, maxFrameY)))
	{
		LOG::e(LOG_IMG_GP_TAG, "ㄴ 실패 : " + strKey + " / PATH: " + fileName);
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));
	return img;
}

ImageGp* GdiPlusManager::addImage(string strKey, const char * fileName, float width, float height)
{
	ImageGp* img = findOriginalImage(strKey);
	if (img) return img;

	img = new ImageGp();
	LOG::d(LOG_IMG_GP_TAG, "== 이미지 생성 시작 : \t\t" + strKey + "\t\t ==");
	if (FAILED(img->init(mMemDc, fileName, width, height)))
	{
		LOG::e(LOG_IMG_GP_TAG, "ㄴ 실패 : " + strKey + " / PATH: " + fileName);
		SAFE_DELETE(img);
		return NULL;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

HRESULT GdiPlusManager::init(HDC memDc)
{
	fontFamily = new FontFamily(GAME_FONT);
	centerFormat.SetAlignment(StringAlignmentCenter);

	mMemDc = memDc;
	return S_OK;
}

ImageGp* GdiPlusManager::findOriginalImage(string strKey)
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

void GdiPlusManager::setSizeRatio(string strKey, float ratio)
{
	ImageGp* img = findOriginalImage(strKey);
	if (!img) return;
	img->setSizeRatio(ratio);
}

void GdiPlusManager::frameRender(string strKey, HDC hdc, float x, float y)
{
	ImageGp* img = findOriginalImage(strKey);
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

void GdiPlusManager::renderOriginal(string strKey, HDC hdc, float x, float y)
{
	ImageGp* img = findOriginalImage(strKey);
	if (!img) return;
	(*(img->getGraphics())).DrawCachedBitmap(img->getCachedBitmap(), x, y);
}

void GdiPlusManager::render(HDC hdc, Bitmap* bitmap, float x, float y)
{
	Graphics gh(hdc);
	gh.DrawImage(bitmap, x, y);
}


void GdiPlusManager::render(ImageGp* img, float x, float y)
{
	(*(img->getGraphics())).DrawCachedBitmap(img->getCachedBitmap(), x, y);
}

void GdiPlusManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	ImageGp* img = findOriginalImage(strKey);
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

			//render(strKey, hdc, (float)rcDest.left, (float)rcDest.top, (float)rcSour.left, (float)rcSour.top, sourWidth, sourHeight);
		}
	}
}

void GdiPlusManager::drawText(HDC hdc, std::wstring message, float x, float y, int size, Color color)
{
	Font        font(fontFamily, size, FontStyleRegular, UnitPixel);
	SolidBrush  solidBrush(color);
	Graphics gh(hdc);
	gh.DrawString(message.c_str(), -1, &font, PointF(x, y), &solidBrush);
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

void GdiPlusManager::drawRectFLine(HDC hdc, RectF rectF, Gdiplus::Color line, float border)
{
	Gdiplus::Graphics gh(hdc);
	Pen pen(line, border);
	gh.DrawRectangle(&pen, rectF);
}

void GdiPlusManager::drawRectF(HDC hdc, float x, float y, float width, float height, Gdiplus::Color line, Gdiplus::Color solid)
{
	Gdiplus::Graphics gh(hdc);
	RectF drawRectf = RectF(x, y, width, height);
	if (solid.GetAlpha() != 0) {
		SolidBrush s(solid);
		gh.FillRectangle(&s, drawRectf);
	}

	Pen pen(line);
	gh.DrawRectangle(&pen, drawRectf);
}

Bitmap* GdiPlusManager::getDrawElipseToBitmap(float x, float y, float width, float height, Gdiplus::Color solid)
{
	Bitmap* tempBitmap = new Bitmap(width, height);
	Gdiplus::Graphics gp(tempBitmap);

	SolidBrush s(solid);
	gp.FillEllipse(&s, x, y, width ,height);

	return tempBitmap;
}

Bitmap * GdiPlusManager::overlayBitmapCenter(HDC hdc, Gdiplus::Bitmap * bitmap, float width, float height)
{
	float centerX = width / 2.0f - bitmap->GetWidth() / 2.0f;
	float centerY = height / 2.0f - bitmap->GetHeight() / 2.0f;

	Bitmap* tempBitmap = new Bitmap(width, height);
	Gdiplus::Graphics gp(tempBitmap);
	gp.DrawImage(
		bitmap,
		centerX, centerY,
		0.0f,
		0.0f,
		bitmap->GetWidth(),
		bitmap->GetHeight(),
		UnitPixel);

	return tempBitmap;
}

Bitmap * GdiPlusManager::overlayBitmap(HDC hdc, Gdiplus::Bitmap * bitmap, float x, float y, float width, float height)
{
	Bitmap* tempBitmap = new Bitmap(width, height);
	Gdiplus::Graphics gp(tempBitmap);
	gp.DrawImage(
		bitmap,
		x, y,
		0.0f,
		0.0f,
		width,
		height,
		UnitPixel);

	return tempBitmap;
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
