#pragma once
#include "SingletonBase.h"

class ImageGp;

#define DEFULAT_COLOR	Color(0,0,0)
#define DEFULAT_FONT_SIZE	10.0f

class GdiPlusManager : public SingletonBase<GdiPlusManager>
{
private:
	typedef map<string, ImageGp*> mapImageList;
	typedef map<string, ImageGp*>::iterator mapImageIter;

	mapImageList _mImageList;

	FontFamily*  mFontFamily[3];
	StringFormat centerFormat;

	HDC mMemDc;

public:
	HRESULT init(HDC memDc);

	void drawTextSimple(string message, float x, float y, float size = DEFULAT_FONT_SIZE, Color solid = DEFULAT_COLOR);
	void drawTextSimple(wstring message, float x, float y, float size = DEFULAT_FONT_SIZE, Color solid = DEFULAT_COLOR);

	//draw text
	void drawText(string message, RectF rcF, float size = DEFULAT_FONT_SIZE, Color solid = DEFULAT_COLOR, Color outLine = Color(0,0,0,0), eXStandard xStandard = XS_LEFT,  FontStyle fontStyle = FontStyleRegular, int fontIndex = 0);
	void drawText(wstring message, RectF rcF, float size = DEFULAT_FONT_SIZE, Color solid = DEFULAT_COLOR, Color outLine = Color(0,0,0,0), eXStandard xStandard = XS_LEFT,  FontStyle fontStyle = FontStyleRegular, int fontIndex = 0);
	void drawTextToBitmap(Bitmap* bitmap, std::wstring message, RectF rcF, float size = DEFULAT_FONT_SIZE, Color solid = DEFULAT_COLOR, Color outLine = Color(0, 0, 0, 0), eXStandard xStandard = XS_LEFT, FontStyle fontStyle = FontStyleRegular, int fontIndex = 0);
	void drawTextToBitmap(Bitmap* bitmap, string message, RectF rcF, float size = DEFULAT_FONT_SIZE, Color solid = DEFULAT_COLOR, Color outLine = Color(0,0,0,0), eXStandard xStandard = XS_LEFT,  FontStyle fontStyle = FontStyleRegular, int fontIndex = 0);

	void drawTextToBitmap(Bitmap * bitmap, wstring message, float size, Color solid, Color outLine = Color(0, 0, 0, 0), eXStandard xStandard = XS_LEFT, FontStyle fontStyle = FontStyleRegular, int fontIndex = 0);

	//
	ImageGp * addFrameImage(string strKey, const string fileName, float width, float height, int maxFrameX, int maxFrameY);
	ImageGp * addImage(string strKey, const char * fileName, float width, float height);

	ImageGp * findOriginalImage(string strKey);
	ImageGp * clone(string strKey);

	void renderOriginal(string strKey, HDC hdc, float x, float y);
	void render(HDC hdc, Bitmap * bitmap, float x, float y, eXStandard xStandard = XS_CENTER, eYStandard yStandard = YS_CENTER);
	void render(HDC hdc, CachedBitmap * bitmap, float leftX, float topY);
	void render(ImageGp * img, float x, float y);


	void frameRender(string strKey, HDC hdc, float x, float y);
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	
	void setSizeRatio(string strKey, float ratio);
	void drawPtf(HDC hdc, PointF ptF, Gdiplus::Color solid = Color(0, 0, 0));

	void drawRectFRelTile(HDC hdc, TINDEX tIndex, Gdiplus::Color solid, Gdiplus::Color line = CR_NONE, float border = 1.0f);
	void drawTextRelTile(HDC hdc, wstring message, TINDEX tIndex, Gdiplus::Color solid = CR_BLUE);

	void drawRectFLine(HDC hdc, RectF rectF, Gdiplus::Color line, float border);
	void drawRectFToBitmap(Bitmap * bitmap, float x, float y, float width, float height, Color solid = Color(0, 255, 255, 255), bool clearFlg = false);
	void drawRectFToBitmap(Bitmap* bitmap, RectF rectF, Gdiplus::Color solid = Color(0, 255, 255, 255));
	void drawRectF(HDC hdc, float x, float y, float width, float height, Gdiplus::Color line = Color(0, 0, 0), Gdiplus::Color solid = Color(0, 255, 255, 255));
	void drawRectF(HDC hdc, RectF rectF, Gdiplus::Color line = Color(0, 0, 0), Gdiplus::Color solid = Color(0, 255, 255, 255));
	void drawRectF(RectF rectF, Gdiplus::Color outline = Color(0, 0, 0, 0), Gdiplus::Color solid = Color(100, 255, 255, 255));

	Bitmap* bitmapSizeChangeToHeight(Bitmap * bitmap, float height, string id = "");
	Bitmap * bitmapSizeChangeToWidth(Bitmap * bitmap, float width, string id = "");
	Bitmap* getDrawElipseToBitmap(float x, float y, float width, float height, Gdiplus::Color solid);
	Bitmap * overlayBitmapCenter(HDC hdc, Gdiplus::Bitmap * bitmap, float width, float height);
	Bitmap * overlayBitmap(HDC hdc, Gdiplus::Bitmap * bitmap, float x, float y, float width, float height);
	Bitmap * combindBitmap(Bitmap * destBit, Bitmap * sourBit, float x, float y);

	int getAlphaHeightToTop(Bitmap* bitmap);

	Gdiplus::CachedBitmap* bitmapToCachedBitmap(HDC hdc, Gdiplus::Bitmap * bitmap);

	void drawGridLine(ImageGp * imgGp, float gridXSize, float gridYSize);
	void drawGridLineToBitmap(Bitmap * bitmap, float gridXWidth, float gridYWidth, Color line);

	Bitmap * getBlankWorkBoard(float width, float height);

	Bitmap * getBlankBitmap(float width, float height);

	Bitmap * getBlankBitmap(float width, float height, Color color);

	void release();
};

