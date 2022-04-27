#include "Stdafx.h"
#include "GdiPlusManager.h"
#include "ImageGp.h"

HRESULT GdiPlusManager::init(HDC memDc)
{
	mFontFamily[0] = new FontFamily(GAME_FONT);
	mFontFamily[1] = new FontFamily(GAME_FONT_2);
	mFontFamily[2] = new FontFamily(GAME_FONT_3);

	centerFormat.SetAlignment(StringAlignmentCenter);

	mMemDc = memDc;

	return S_OK;
}

void GdiPlusManager::drawTextSimple(string message, float x, float y, float size, Color solid)
{
	wstring wMessage;
	wMessage.assign(message.begin(), message.end());

	this->drawTextSimple(wMessage, x, y, size, solid);
}
void GdiPlusManager::drawTextSimple(wstring message, float x, float y, float size, Color solid)
{
	Graphics gh(mMemDc);

	Font        font(mFontFamily[0], size, FontStyleRegular, UnitPixel);
	SolidBrush  solidBrush(solid);

	gh.DrawString(message.c_str(), -1, &font, PointF(x, y), &solidBrush);
}

void GdiPlusManager::drawText(string message, RectF rcF, float size, Color solid, Color outLine, eXStandard xStandard, FontStyle fontStyle, int fontIndex)
{
	wstring wMessage;
	wMessage.assign(message.begin(), message.end());
	
	this->drawText(wMessage, rcF, size, solid, outLine, xStandard, fontStyle, fontIndex);
}
void GdiPlusManager::drawText(wstring message, RectF rcF, float size, Color solid, Color outLine, eXStandard xStandard, FontStyle fontStyle, int fontIndex)
{
	Graphics gh(mMemDc);

	StringFormat sFormat;
	switch (xStandard) {
	case XS_CENTER:
		sFormat.SetAlignment(StringAlignmentCenter);
		break;
	case XS_LEFT:
		sFormat.SetAlignment(StringAlignmentNear);
		break;
	case XS_RIGHT:
		sFormat.SetAlignment(StringAlignmentFar);
		break;
	}

	GraphicsPath *pth = new GraphicsPath();
	pth->AddString(message.c_str(), -1, mFontFamily[fontIndex], fontStyle, size, rcF, &sFormat);

	SolidBrush solidBrush(solid);
	gh.FillPath(&solidBrush, pth);

	Pen outlinePen(outLine, 1);
	gh.DrawPath(&outlinePen, pth);

	pth->Reset();
	SAFE_DELETE(pth);
}

void GdiPlusManager::drawTextToBitmap(Bitmap* bitmap, std::wstring message, RectF rcF, float size, Color solid, Color outLine, eXStandard xStandard, FontStyle fontStyle, int fontIndex)
{
	Graphics gh(bitmap);

	StringFormat sFormat;

	switch (xStandard) {
	case XS_CENTER:
		sFormat.SetAlignment(StringAlignmentCenter);
		break;
	case XS_LEFT:
		sFormat.SetAlignment(StringAlignmentNear);
		break;
	case XS_RIGHT:
		sFormat.SetAlignment(StringAlignmentFar);
		break;

	}

	Font        font(mFontFamily[fontIndex], size, fontStyle, UnitPixel);
	SolidBrush  solidBrush(solid);

	gh.DrawString(message.c_str(), -1, &font, rcF, &sFormat, &solidBrush);

	/*
	GraphicsPath *pth = new GraphicsPath();
	pth->AddString(message.c_str(), -1, mFontFamily[fontIndex], fontStyle, size, rcF, &sFormat);

	SolidBrush solidBrush(solid);
	gh.FillPath(&solidBrush, pth);

	Pen outlinePen(outLine, 1);
	gh.DrawPath(&outlinePen, pth);

	pth->Reset();
	*/
}

void GdiPlusManager::drawTextToBitmap(Bitmap* bitmap, string message, RectF rcF, float size, Color solid, Color outLine, eXStandard xStandard, FontStyle fontStyle, int fontIndex)
{
	wstring wMessage;
	wMessage.assign(message.begin(), message.end());

	this->drawTextToBitmap(bitmap, wMessage, rcF, size, solid, outLine, xStandard, fontStyle, fontIndex);
}

void GdiPlusManager::drawTextToBitmap(Bitmap* bitmap, wstring message, float size, Color solid, Color outLine, eXStandard xStandard, FontStyle fontStyle, int fontIndex)
{
	this->drawTextToBitmap(bitmap, message, RectF(0,0, bitmap->GetWidth(), bitmap->GetHeight()), size, solid, outLine, xStandard, fontStyle, fontIndex);
}

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

ImageGp* GdiPlusManager::findOriginalImage(string strKey)
{
	auto key = _mImageList.find(strKey);
	if (key != _mImageList.end())
	{
		return key->second;
	}
	return nullptr;
}

ImageGp* GdiPlusManager::clone(string strKey)
{
	auto key = _mImageList.find(strKey);
	if (key != _mImageList.end())
	{
		return key->second->clone(mMemDc);
	}
	return nullptr;
}

void GdiPlusManager::setSizeRatio(string strKey, float ratio)
{
	ImageGp* img = findOriginalImage(strKey);
	if (!img) return;
	img->setSizeRatio(ratio);
}

Bitmap* GdiPlusManager::bitmapSizeChangeToHeight(Bitmap* bitmap, float height, string id)
{
	float rWidth = static_cast<float>(bitmap->GetWidth());
	float rHeight = static_cast<float>(bitmap->GetHeight());

	float mSizeChangeRatio = rWidth / rHeight;

	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(mSizeChangeRatio * height, height);
	Gdiplus::Graphics graphics(pBitmap);

	graphics.DrawImage(
		bitmap,
		RectF(0.0f, 0.0f, mSizeChangeRatio * height, height),
		0.0f,
		0.0f,
		bitmap->GetWidth(),
		bitmap->GetHeight(),
		UnitPixel);

	return pBitmap;
}

Bitmap* GdiPlusManager::bitmapSizeChangeToWidth(Bitmap* bitmap, float width, string id)
{
	float rWidth = static_cast<float>(bitmap->GetWidth());
	float rHeight = static_cast<float>(bitmap->GetHeight());

	float mSizeChangeRatio = rHeight / rWidth;

	Gdiplus::Bitmap* pBitmap = new Gdiplus::Bitmap(width, mSizeChangeRatio * width);
	Gdiplus::Graphics graphics(pBitmap);

	graphics.DrawImage(
		bitmap,
		RectF(0.0f, 0.0f, width, mSizeChangeRatio * width),
		0.0f,
		0.0f,
		bitmap->GetWidth(),
		bitmap->GetHeight(),
		UnitPixel);

	return pBitmap;
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

void GdiPlusManager::render(HDC hdc, Bitmap* bitmap, float x, float y, eXStandard xStandard, eYStandard yStandard)
{
	switch (xStandard) {
	case XS_LEFT:
		break;
	case XS_RIGHT:
		x = x - bitmap->GetWidth();
		break;
	case XS_CENTER:
		x = x - (bitmap->GetWidth() / 2.0f);
		break;
	}

	switch (yStandard) {
	case YS_TOP:
		break;
	case YS_BOTTOM:
		y = y - bitmap->GetHeight();
		break;
	case YS_CENTER:
		y = y - (bitmap->GetHeight() / 2.0f);
		break;
	}

	Graphics gh(hdc);
	gh.DrawImage(bitmap, x, y);
}

void GdiPlusManager::render(HDC hdc, CachedBitmap* bitmap, float leftX, float topY)
{
	Graphics gh(hdc);
	gh.DrawCachedBitmap(bitmap, leftX, topY);
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

void GdiPlusManager::drawRectF(RectF rectF, Gdiplus::Color line, Gdiplus::Color solid)
{
	Gdiplus::Graphics gh(mMemDc);

	if (solid.GetAlpha() != 0) {
		SolidBrush s(solid);
		gh.FillRectangle(&s, rectF);
	}

	Pen pen(line);
	gh.DrawRectangle(&pen, rectF);
}


void GdiPlusManager::drawPtf(HDC hdc, PointF ptF, Gdiplus::Color solid)
{
	Gdiplus::Graphics gh(hdc);

	SolidBrush s(solid);
	gh.FillRectangle(&s, RectFMakeCenter(ptF.X, ptF.Y, 5.0f, 5.0f));
}

void GdiPlusManager::drawRectFRelTile(HDC hdc, TINDEX tIndex, Gdiplus::Color solid, Gdiplus::Color line, float border)
{
	Gdiplus::Graphics gh(hdc);

	RectF rectF = RectFMake(tIndex.X * TILE_SIZE, tIndex.Y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	rectF.Offset(-CAMERA->getX(), -CAMERA->getY());

	if (solid.GetAlpha() != 0) {
		SolidBrush s(solid);
		gh.FillRectangle(&s, rectF);
	}

	Pen pen(line);
	gh.DrawRectangle(&pen, rectF);
}
void GdiPlusManager::drawTextRelTile(HDC hdc, wstring message, TINDEX tIndex, Gdiplus::Color solid)
{
	Graphics gh(hdc);

	Font        font(mFontFamily[0], 12.0f, FontStyleRegular, UnitPixel);
	SolidBrush  solidBrush(solid);
	
	RectF rectF = RectFMake(tIndex.X * TILE_SIZE, tIndex.Y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	rectF.Offset(-CAMERA->getX(), -CAMERA->getY());

	gh.DrawString(message.c_str(), -1, &font, rectF, &StringFormat(StringAlignmentCenter), &solidBrush);
}

void GdiPlusManager::drawRectFLine(HDC hdc, RectF rectF, Gdiplus::Color line, float border)
{
	Gdiplus::Graphics gh(hdc);
	Pen pen(line, border);
	gh.DrawRectangle(&pen, rectF);
}

void GdiPlusManager::drawRectFToBitmap(Bitmap* bitmap, float x, float y, float width, float height, Color solid, bool clearFlg)
{
	Gdiplus::Graphics gh(bitmap);
	SolidBrush s(solid);
	gh.FillRectangle(&s, RectFMake(x, y, width, height));
}


void GdiPlusManager::drawRectFToBitmap(Bitmap* bitmap, RectF rectF, Gdiplus::Color solid)
{
	Gdiplus::Graphics gh(bitmap);
	SolidBrush s(solid);
	gh.FillRectangle(&s, rectF);
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
	gp.FillEllipse(&s, x, y, width, height);

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

Bitmap * GdiPlusManager::combindBitmap(Bitmap * destBit, Bitmap* sourBit, float x, float y)
{
	Gdiplus::Graphics gp(destBit);
	gp.DrawImage(
		sourBit,
		x, y,
		0.0f,
		0.0f,
		static_cast<float>(sourBit->GetWidth()),
		static_cast<float>(sourBit->GetHeight()),
		UnitPixel);

	return destBit;
}

int GdiPlusManager::getAlphaHeightToTop(Bitmap * bitmap)
{
	int topAlpha = -1;
	bool curYAllAlpha = true;
	for (int y = 0; y < bitmap->GetHeight(); y++) {
		for (int x = 0; x < bitmap->GetWidth(); x++) {
			Color color;
			bitmap->GetPixel(x, y, &color);
			if (color.GetAlpha() != 0) {
				curYAllAlpha = false;
				break;
			}
		}

		if (!curYAllAlpha) {
			topAlpha = y;
			break;
		}
	}

	return topAlpha;
}

Gdiplus::CachedBitmap * GdiPlusManager::bitmapToCachedBitmap(HDC hdc, Gdiplus::Bitmap * bitmap)
{
	return new CachedBitmap(bitmap, &Graphics(hdc));
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

void GdiPlusManager::drawGridLineToBitmap(Bitmap* bitmap, float gridXWidth, float gridYWidth, Color line)
{
	Gdiplus::Graphics graphics(bitmap);
	Pen linePen(line);
	for (float gridX = 0.0f; gridX < bitmap->GetWidth(); gridX += gridXWidth) {
		graphics.DrawLine(&linePen, gridX, 0.0f, gridX, bitmap->GetHeight());
	}
	for (float gridY = 0.0f; gridY < bitmap->GetHeight(); gridY += gridYWidth) {
		graphics.DrawLine(&linePen, 0.0f, gridY, bitmap->GetWidth(), gridY);
	}
}


Bitmap* GdiPlusManager::getBlankWorkBoard(float width, float height)
{
	Bitmap* pBitmap = new Bitmap(width, height);
	Gdiplus::Graphics graphics(pBitmap);

	Pen      pen(Color(91, 43, 41), 0.5);
	SolidBrush s(Color(255, 255, 255));

	graphics.FillRectangle(&s, 0.0f, 0.0f, width, height);
	graphics.DrawRectangle(&pen, 0.0f, 0.0f, width, height);
	return pBitmap;
}

Bitmap* GdiPlusManager::getBlankBitmap(float width, float height)
{
	Bitmap* pBitmap = new Bitmap(width, height);
	Gdiplus::Graphics graphics(pBitmap);

	SolidBrush s(Color(0, 0, 0, 0));

	graphics.FillRectangle(&s, 0.0f, 0.0f, width, height);
	return pBitmap;
}

Bitmap* GdiPlusManager::getBlankBitmap(float width, float height, Color color)
{
	Bitmap* pBitmap = new Bitmap(width, height);
	Gdiplus::Graphics graphics(pBitmap);

	SolidBrush s(color);

	graphics.FillRectangle(&s, 0.0f, 0.0f, width, height);
	return pBitmap;
}


void GdiPlusManager::release()
{
}
