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

	enum IMAGE_TYPE // 어떤 방식으로 가져갈거야?
	{
		IT_NORMAL = 0,     
		IT_FRAME,
		IT_LOOP,
		IT_CLIPPING,
		IT_EMPTY,
	};

	typedef struct tagImage
	{
		float			X;
		float			Y;
		int				CurrentFrameX;
		int				CurrentFrameY;
		int				MaxFrameX;
		int				MaxFrameY;
		float           FrameWidth;
		float           FrameHeight;
		float           LoopWidth;
		int				LoopFrameX;
		float           Width;
		float           Height;
		BYTE			LoadType;   //이미지의 로드 타입
		IMAGE_TYPE		Type;

		tagImage()
		{
			X = Y = 0;
			CurrentFrameX = 0;
			CurrentFrameY = 0;
			MaxFrameX = 0;
			MaxFrameY = 0;
			FrameWidth = 0;
			FrameHeight = 0;
			LoadType = LOAD_RESOURCE;
			Type = IT_NORMAL;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO   mImageInfo;
	
	Gdiplus::Image* mImage;

	Gdiplus::Graphics* mGraphics;
	Gdiplus::Graphics* mCurBitmapGraphics;
	Gdiplus::Graphics* mClippingBitmapGraphics;

	Gdiplus::Bitmap* mOriginalBitmap;
	Gdiplus::Bitmap* mCurBitmap;
	Gdiplus::Bitmap* mClippingBitmap;
	Gdiplus::CachedBitmap* mCacheBitmap;

	vector<Gdiplus::CachedBitmap*> mVLoopCashBitmap;
	vector<Gdiplus::Bitmap*> mVLoopBitmap;

	string mFileName;
	int mIndex;
public:
	HRESULT init(HDC memDc, string fileName, float width, float height, int maxFrameX, int maxFrameY);
	HRESULT init(HDC memDc, string fileName, float width, float height);
	HRESULT init(HDC memDc, float width, float height);
	
	HRESULT init(HDC memDc, Gdiplus::Bitmap* bitmap, float width, float height);
	HRESULT initCenter(HDC memDc, Gdiplus::Bitmap* bitmap, float width, float height);
	HRESULT init(HDC memDc, Gdiplus::Bitmap * bitmap, float bitmapStartX, float bitmapStartY, float width, float height);

	HRESULT initBitmap(HDC memDc, float width, float height);

	void release();

	ImageGp* clone() { 
		setIndex(getIndex() + 1);
		ImageGp*  clone = new ImageGp(*this);
		return clone;
	};

	inline float getX(void) { return mImageInfo->X; }
	inline void setX(float x) { mImageInfo->X = x; }

	inline float getY(void) { return mImageInfo->Y; }
	inline void setY(float y) { mImageInfo->Y = y; }

	inline float getWidth(void) {
		return mImageInfo->Width;
	}
	inline float getHeight(void) {
		return  mImageInfo->Height;
	}

	inline int getIndex(void) {
		return mIndex;
	}
	inline void setIndex(int index) {
		mIndex = index;
	}

	inline Graphics* getGraphics() { return mGraphics; }

	inline int getFrameX(void) { return mImageInfo->CurrentFrameX; }
	inline void setFrameX(int frameX)
	{
		mImageInfo->CurrentFrameX = frameX;
		if (frameX > mImageInfo->MaxFrameX)
		{
			mImageInfo->CurrentFrameX = mImageInfo->MaxFrameX;
		}
	}

	inline int getFrameY(void) { return mImageInfo->CurrentFrameY; }
	inline void setFrameY(int frameY)
	{
		mImageInfo->CurrentFrameY = frameY;
		if (frameY > mImageInfo->MaxFrameY)
		{
			mImageInfo->CurrentFrameY = mImageInfo->MaxFrameY;
		}
	}

	inline float getFrameWidth(void) { return mImageInfo->FrameWidth; }
	inline float getFrameHeight(void) { return mImageInfo->FrameHeight; }

	inline int getMaxFrameX(void) { return mImageInfo->MaxFrameX; }
	inline int getMaxFrameY(void) { return mImageInfo->MaxFrameY; }

	inline string getFileName(void) { return mFileName; }

	inline Gdiplus::Image* getImage(void) { return mImage; }
	
	inline Gdiplus::CachedBitmap* getCachedBitmap(void) { return mCacheBitmap; }

	inline Gdiplus::Bitmap* getBitmap(void) { 
		return mCurBitmap;
	}

	inline Gdiplus::Bitmap* getOriginalBitmap(void) {
		return mOriginalBitmap;
	}

	void setWidth(float width);
	void setHeight(float height);
	void setSize(float width, float height);
	void flipX();

	void setSizeRatio(float ratio);

	void changeColor();

	void backOriginalColor();

	void clipping(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);
	void startLoopX(int frameCount);
	void startClipping(float sourWidth, float sourHeight);

	void render(HDC hdc, float x, float y);
	void render(HDC hdc, RectF rectF);
	void render(HDC hdc, float x, float y, eXStandard xStandard, eYStandard yStandard);
	void loopRender(HDC hdc, float x, float y, int count);

	void frameRender(HDC hdc, float x, float y);
	void frameRender(HDC hdc, float x, float y, int currentFrameX, int currentFrameY);

	void coverBitmap(float x, float y, Gdiplus::Bitmap * bitmap);

	void overlayBitmap(float x, float y, Bitmap* bitmap);
	void overlayBitmapCenter(Gdiplus::Bitmap * bitmap);
	void rebuildChachedBitmap(void);
	void changeOriginalToCurBitmap(void);

	void rotate(float angle);

	Gdiplus::Bitmap * getFrameBitmap(int currentFrameX, int currentFrameY);
	Gdiplus::Bitmap * getFrameBitmap(int currentFrameX, int currentFrameY, float width, float height);

	Gdiplus::Bitmap * getFrameBitmap(int currentFrameX, int currentFrameY, float destX, float destY, float destWidth, float destHeight, float srcWidth, float srcHeight);

	Gdiplus::Bitmap * getFrameBitmapToIndex(int currentFrameX, int currentFrameY, int toXIndex, int toYIndex);
	Gdiplus::Bitmap * getFrameBitmapToIndex(int currentFrameX, int currentFrameY, float width, float height, int toXIndex, int toYIndex);
	Gdiplus::Bitmap * getFrameBitmapToIndexCenter(int currentFrameX, int currentFrameY, float width, float height, int toXIndex, int toYIndex);
	Gdiplus::Bitmap * getPartBitmap(int x, int y, float width, float height);

	Gdiplus::Bitmap * getPartBitmap(int x, int y, float destWidth, float destHeight, float srcWidth, float srcHeight);

	RectF getRectF(float x, float y);

	ImageGp() {};
	~ImageGp() {};
};
