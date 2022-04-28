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

	HDC            hMemDC;
	HDC				mMemDc;
	string mFileName;

	static int mCountIndex;
	int mIndex;
public:
	HRESULT init(HDC memDc, string fileName, float width, float height, int maxFrameX, int maxFrameY);
	HRESULT init(HDC memDc, Gdiplus::Bitmap * bitmap, float width, float height, int maxFrameX, int maxFrameY);
	HRESULT init(HDC memDc, string fileName, float width, float height);
	HRESULT init(HDC memDc, float width, float height);
	
	HRESULT init(HDC memDc, Gdiplus::Bitmap* bitmap, float width, float height);
	HRESULT init(HDC memDc, Gdiplus::Bitmap * bitmap);
	HRESULT initCenter(HDC memDc, Gdiplus::Bitmap* bitmap, float width, float height);
	HRESULT initCenter(HDC memDc, Gdiplus::Bitmap * bitmap, float width, float height, float xP, float yP);
	HRESULT init(HDC memDc, Gdiplus::Bitmap * bitmap, float bitmapStartX, float bitmapStartY, float width, float height);

	HRESULT initBitmap(HDC memDc, float width, float height);

	void release();

	ImageGp* clone(HDC hdc) {
		if (mIndex != 0) {
			LOG::e("원본만 복사 가능");
			return nullptr;
		} 

		mCountIndex += 1;
		ImageGp* clone = new ImageGp(*this);
		clone->clone(mCountIndex, hdc);
		return clone;
	};

	void clone(int index, HDC hdc) {
		mIndex = index;

		mImageInfo = LPIMAGE_INFO(mImageInfo);
		mImage = mImage->Clone();

		mOriginalBitmap = mOriginalBitmap->Clone(0.0f, 0.0f, mOriginalBitmap->GetWidth(), mOriginalBitmap->GetHeight(), mOriginalBitmap->GetPixelFormat());;
		mCurBitmap = mCurBitmap->Clone(0.0f, 0.0f, mCurBitmap->GetWidth(), mCurBitmap->GetHeight(), mCurBitmap->GetPixelFormat());
		mCurBitmapGraphics = new Graphics(mCurBitmap);
		
		mGraphics = new Graphics(hdc);

		mCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);
	}

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

	inline Gdiplus::Bitmap* getBitmapClone(void) {
		return mOriginalBitmap->Clone(0.0f, 0.0f, mCurBitmap->GetWidth(), mCurBitmap->GetHeight(), mCurBitmap->GetPixelFormat());
	}

	inline Gdiplus::Bitmap* getOriginalBitmap(void) {
		return mOriginalBitmap;
	}

	void setWidth(float width);
	void setHeight(float height);
	void setSize(float width, float height);
	void flipX();

	void flipY();

	void flip90(int count);

	void setSizeRatio(float ratio);

	void changeColor();

	void backOriginalColor();

	void clipping(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);
	void clipping(RectF rcF);
	void startLoopX(int frameCount);
	void startClipping(float sourWidth, float sourHeight);

	void render(HDC hdc, float x, float y);
	void render(RectF rectF);
	void render(HDC hdc, float x, float y, eXStandard xStandard, eYStandard yStandard);
	void render(float leftX, float topY);

	void renderMap(float leftX, float topY);

	void loopRender(HDC hdc, float x, float y, int count);

	void coverBitmap(float x, float y, float width, float height, Gdiplus::Bitmap * bitmap);

	void coverBitmap(float x, float y, Gdiplus::Bitmap * bitmap);

	void coverBitmapCenter(Gdiplus::Bitmap * bitmap);

	void coverBitmap(Gdiplus::Bitmap * bitmap);

	void overlayBitmap(float x, float y, Bitmap* bitmap);
	void overlayBitmapCenter(Gdiplus::Bitmap * bitmap);
	void overlayBitmapAdjustHeight(Gdiplus::Bitmap * bitmap);

	void rebuildChachedBitmap(void);
	void changeOriginalToCurBitmap(void);

	void toImageBase();

	void rotate(float angle);
	void rotateToXCenter(float angle, Bitmap* bitmap);
	void rotateSample(float angle);
	void rotateToYCenter(float angle, Bitmap * bitmap);
	void rotate(float angle, float x, float y);
	ImageGp* rotateAndClone(float angle);

	Gdiplus::Bitmap * getFrameBitmap(int currentFrameX, int currentFrameY);
	Gdiplus::Bitmap * getFrameBitmap(int currentFrameX, int currentFrameY, float width, float height);

	Gdiplus::Bitmap * getFrameBitmapRotate(int currentFrameX, int currentFrameY, float destWidth, float destHeight, float angle);

	Gdiplus::Bitmap * getFrameBitmapAbjustHeight(int currentFrameX, int currentFrameY, float destHeight);

	ImageGp * getFrameBitmapAbjustHeightAndClone(int currentFrameX, int currentFrameY, float destHeight);

	Gdiplus::Bitmap * getFrameBitmapAbjustHeightToIndex(int currentFrameX, int currentFrameY, float destHeight, int toXIndex, int toYIndex);

	Gdiplus::Bitmap * clippingAlpha(int currentFrameX, int currentFrameY, int toXIndex, int toYIndex);

	Gdiplus::Bitmap * getFrameBitmapTemp(int currentFrameX, int currentFrameY, float destHeight, int toXIndex, int toYIndex);

	Gdiplus::Bitmap * getFrameBitmap(int currentFrameX, int currentFrameY, float destX, float destY, float destWidth, float destHeight, float srcWidth, float srcHeight);

	Gdiplus::Bitmap * getFrameBitmapToIndex(int currentFrameX, int currentFrameY, int toXIndex, int toYIndex);
	Gdiplus::Bitmap * getFrameBitmapToIndex(int currentFrameX, int currentFrameY, int toXIndex, int toYIndex, float width, float height);

	Gdiplus::Bitmap * getFrameBitmapToIndexAlpha(int currentFrameX, int currentFrameY, int toXIndex, int toYIndex, float width, float height);

	Gdiplus::Bitmap * getFrameBitmapToIndexCenter(int currentFrameX, int currentFrameY, float width, float height, int toXIndex, int toYIndex);
	Gdiplus::Bitmap * getPartBitmap(int x, int y, float width, float height);

	Gdiplus::Bitmap * getPartBitmap(int x, int y, float destWidth, float destHeight, float srcWidth, float srcHeight);

	void clear();

	void toAlpha();

	void toTransparent(RectF rcF);

	void toTransparentAll();

	RectF getRectF(float x, float y, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP);

	ImageGp() {};
	~ImageGp() {};
};
