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
	HRESULT init();
	HRESULT init(HDC memDc);

	ImageGp * addFrameImage(string strKey, const string fileName, int width, int height, int maxFrameX, int maxFrameY);
	ImageGp * addImage(string strKey, const char * fileName, int width, int height);

	ImageGp * findImage(string strKey);
	ImageGp * findAndCloneImage(string strKey);

	void render(string strKey, HDC hdc, float x, float y);
	void render(string strKey, HDC hdc, float x, float y, float width, float height);
	void render(string strKey, HDC hdc, RectF rectF);
	void render(ImageGp * img, float x, float y);
	void render(string strKey, HDC hdc, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);

	void frameRender(string strKey, HDC hdc, float x, float y);
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	
	void drawText(HDC hdc, std::wstring message, float x, float y, int size, Color color);
	void release();
};

