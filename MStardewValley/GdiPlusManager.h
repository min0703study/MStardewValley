#pragma once
#include "SingletonBase.h"

class ImageGp;

class GdiPlusManager : public SingletonBase<GdiPlusManager>
{
private:
	typedef map<string, ImageGp*> mapImageList;
	typedef map<string, ImageGp*>::iterator mapImageIter;

	mapImageList _mImageList;

	FontFamily*  fontFamily;
	StringFormat centerFormat;

	HDC mMemDc;
public:
	HRESULT init(HDC memDc);

	ImageGp * addFrameImage(string strKey, const string fileName, int width, int height, int maxFrameX, int maxFrameY);
	ImageGp * addImage(string strKey, const char * fileName, int width, int height);


	ImageGp * findOriginalImage(string strKey);
	ImageGp * findAndCloneImage(string strKey);

	void renderOriginal(string strKey, HDC hdc, float x, float y);
	void render(HDC hdc, Bitmap * bitmap, float x, float y);
	void render(ImageGp * img, float x, float y);

	void frameRender(string strKey, HDC hdc, float x, float y);
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	
	void setSizeRatio(string strKey, float ratio);

	void drawText(HDC hdc, std::wstring message, float x, float y, int size, Color color);
	void drawRectF(HDC hdc, RectF rectF, Gdiplus::Color line = Color(0, 0, 0), Gdiplus::Color solid = Color(0, 255, 255, 255));
	void drawRectF(HDC hdc, float x, float y, float width, float height, Gdiplus::Color line = Color(0, 0, 0), Gdiplus::Color solid = Color(0, 255, 255, 255));
	Bitmap* getDrawElipseToBitmap(float x, float y, float width, float height, Gdiplus::Color solid);
	Bitmap * overlayBitmapCenter(HDC hdc, Gdiplus::Bitmap * bitmap, float width, float height);
	Bitmap * overlayBitmap(HDC hdc, Gdiplus::Bitmap * bitmap, float x, float y, float width, float height);

	void drawGridLine(ImageGp * imgGp, float gridXSize, float gridYSize);

	Bitmap * getBitmap(float width, float height);

	void release();
};

