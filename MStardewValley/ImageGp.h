#pragma once

class ImageGp
{
public:
	enum IMAGE_LOAD_KIND // 어떤 방식으로 가져갈거야?
	{
		LOAD_RESOURCE = 0,      // 리소스로 가져올건지
		LOAD_FILE,            //파일로 가져올건지
		LOAD_EMPTY,            //빈 비트맵으로 가져올건지
		LOAD_END            // 안 가져올건지
	};

	typedef struct tagImage
	{
		float			x;
		float			y;
		int            currentFrameX;
		int            currentFrameY;
		int            maxFrameX;
		int            maxFrameY;
		int            frameWidth;
		int            frameHeight;
		float            width;
		float            height;
		BYTE         loadType;   //이미지의 로드 타입

		tagImage()
		{
			x = y = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO   _imageInfo;

	Gdiplus::Image* _image;
	Gdiplus::Graphics* mGraphics;

	Gdiplus::CachedBitmap* mCacheBitmap;
	Gdiplus::Bitmap* mBitmap;

	string mFileName;
public:
	HRESULT init(string fileName, float width, float height, int maxFrameX, int maxFrameY, HDC memDc);
	HRESULT init(string fileName, float width, float height, HDC memDc);

	void release();

	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	inline float getWidth(void) {
		return _imageInfo->width;
	}
	inline float getHeight(void) {
		return  _imageInfo->height;
	}

	inline Graphics* getGraphics() { return mGraphics; }

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline string getFileName(void) { return mFileName; }

	inline Gdiplus::Image* getImage(void) { return _image; }
	inline Gdiplus::CachedBitmap* getCachedBitmap(void) { return mCacheBitmap; }

	void setWidth(float width);
	void setHeight(float height);
	void setSize(float width, float height);

	void render(HDC hdc, float x, float y);
	void render(HDC hdc, float x, float y, float width, float height);
	void render(HDC hdc, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);
	void render(HDC hdc, RectF rectF);

	ImageGp() {};
	~ImageGp() {};
};
