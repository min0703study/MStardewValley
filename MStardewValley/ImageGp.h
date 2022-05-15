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

	enum IMAGE_TYPE
	{
		IT_NORMAL = 0,     
		IT_FRAME,
		IT_CLIPPING,
		IT_ALPHA,
		IT_EMPTY,
	};

	enum eRanderType
	{
		RT_CACHED,
		RT_BITBLT,
	};

	typedef struct tagImage
	{
		int				MaxFrameX;
		int				MaxFrameY;
		float           FrameWidth;
		float           FrameHeight;
		float           Width;
		float           Height;
		BYTE			LoadType;   //이미지의 로드 타입
		IMAGE_TYPE		Type;
		bool			HaveAlpha;
		int				Alpha;
		BLENDFUNCTION	BlendFunc;

		tagImage()
		{
			MaxFrameX = 0;
			MaxFrameY = 0;
			FrameWidth = 0;
			FrameHeight = 0;
			LoadType = LOAD_RESOURCE;
			Type = IT_NORMAL;
		}

		tagImage(tagImage* copyInfo)
		{
			Width = copyInfo->Width;
			Height = copyInfo->Height;
			MaxFrameX = copyInfo->MaxFrameX;
			MaxFrameY = copyInfo->MaxFrameY;
			FrameWidth = copyInfo->FrameWidth;
			FrameHeight = copyInfo->FrameHeight;
			LoadType = copyInfo->LoadType;
			Type = copyInfo->Type;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;
private:
	LPIMAGE_INFO   mImageInfo;
	
	Gdiplus::Image* mImage;

	Gdiplus::Graphics* mCurBitmapGraphics;
	Gdiplus::Graphics* mGraphics;
	Gdiplus::Bitmap* mOriginalBitmap;
	Gdiplus::Bitmap* mCurBitmap;
	Gdiplus::CachedBitmap* mCurCacheBitmap;

	Gdiplus::Graphics* mClippingBitmapGraphics;
	Gdiplus::Bitmap* mClippingBitmap;

	HDC				mMemDc;

	HBITMAP			mHBitmap;
	HBITMAP			mHOldBitmap;
	HDC             mHMemDc;
	HDC             mHBlendMemDc;

	string mFileName;
	static int mCountIndex;
	int mIndex;

	eRanderType mRenderType;
public:
	//frame
	HRESULT init(HDC memDc, string fileName, float width, float height, int maxFrameX, int maxFrameY);
	HRESULT init(HDC memDc, Gdiplus::Bitmap * bitmap, float width, float height, int maxFrameX, int maxFrameY);

	//normal
	HRESULT init(HDC memDc, float width, float height);
	HRESULT init(HDC memDc, string fileName, float width, float height);
	
	//make
	HRESULT init(HDC memDc, Gdiplus::Bitmap* bitmap, float width, float height);
	HRESULT init(HDC memDc, Gdiplus::Bitmap * bitmap);

	//makeCenter
	HRESULT initCenter(HDC memDc, Gdiplus::Bitmap* bitmap, float width, float height);
	HRESULT initCenter(HDC memDc, Gdiplus::Bitmap * bitmap, float width, float height, float xP, float yP);

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

	// == getter
	inline float getWidth(void) const { return mImageInfo->Width; }
	inline float getHeight(void) const { return  mImageInfo->Height;}
	inline int getIndex(void) const { return mIndex; }

	inline Graphics* getGraphics() { return mGraphics; }

	inline float getFrameWidth(void) { return mImageInfo->FrameWidth; }
	inline float getFrameHeight(void) { return mImageInfo->FrameHeight; }

	inline int getMaxFrameX(void) { return mImageInfo->MaxFrameX; }
	inline int getMaxFrameY(void) { return mImageInfo->MaxFrameY; }
	inline string getFileName(void) const { return mFileName; }
	inline Gdiplus::Image* getImage(void) { return mImage; }

	inline Gdiplus::CachedBitmap* getCachedBitmap(void) { return mCurCacheBitmap; }

	inline Gdiplus::Bitmap* getBitmap(void) const { return mCurBitmap; }
	inline Bitmap* getOriginalBitmap(void) const { return mOriginalBitmap; }
	// == getter

	inline void setAlpha(int alpha) { 
		mImageInfo->Alpha = alpha; 
		mImageInfo->BlendFunc.SourceConstantAlpha = (BYTE)alpha;
	}
	inline void offsetAlpha(int alpha) {
		mImageInfo->Alpha += alpha;
		if (mImageInfo->Alpha >= 254) {
			mImageInfo->Alpha = 254;
		}

		if (mImageInfo->Alpha <= 0) {
			mImageInfo->Alpha = 0;
		}
		mImageInfo->BlendFunc.SourceConstantAlpha = (BYTE)mImageInfo->Alpha;
	}

	void setRenderBitBlt(void);
	void setRenderAlpha(void);

	void setWidth(float width);
	void setHeight(float height);
	void setSize(float width, float height);
	void setSizeRatio(float ratio);

	void flipX();
	void flipY();
	void flip90(int count);

	void move(float value);

	void changeColor();
	void changeRedColor();
	void toOriginal();

	void cutTransparentArea();
	void cutTransparentAreaVertical();

	void rotateToXCenter(float angle, Bitmap* bitmap);
	void rotateToYCenter(float angle, Bitmap * bitmap);
	void rotate(float angle);
	void rotate(float angle, eXStandard rotateX, eYStandard rotateY, float newWidthSize, float newHeightSize);

	void toAlpha(float alpha = 0.4f); //MAX 1.0f
	void toTransparent(RectF rcF);
	void toTransparent();

	void clipping(float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);
	void clipping(RectF rcF);
	void startClipping(float sourWidth, float sourHeight);

	void render(RectF rectF);
	void render(float x, float y, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP);
	void renderAlphaMode(float x, float y, eXStandard xStandard, eYStandard yStandard);

	void coverBitmap(float x, float y, Gdiplus::Bitmap * bitmap);
	void coverBitmapCenter(Gdiplus::Bitmap * bitmap);
	void overlayBitmap(float x, float y, Bitmap* bitmap);
	void overlayImageGp(const ImageGp * imageGp, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP, bool isOriginal = true);
	void overlayImageGp(const ImageGp * imageGp, float x, float y, bool isOriginal = true);

	// == cut Bitmap
	Gdiplus::Bitmap* getFrameBitmap(int currentFrameX, int currentFrameY);
	Gdiplus::Bitmap* getFrameBitmap(int currentFrameX, int currentFrameY, float width, float height);
	Gdiplus::Bitmap* getFrameBitmapToIndex(int currentFrameX, int currentFrameY, int toXIndex, int toYIndex);
	Gdiplus::Bitmap* getFrameBitmapToIndex(int currentFrameX, int currentFrameY, int toXIndex, int toYIndex, float width, float height);
	Gdiplus::Bitmap* getCutBitmap(int x, int y, float destWidth, float destHeight, float srcWidth, float srcHeight);
	// cut Bitmap ==

	void rebuildChachedBitmap(void);
	void rebuildHBitmap(void);
	void clear();

	//debug
	RectF getRectF(float x, float y, eXStandard xStandard = XS_LEFT, eYStandard yStandard = YS_TOP);

	ImageGp(): mImageInfo(nullptr), mImage(nullptr), mCurBitmapGraphics(nullptr), mGraphics(nullptr), mOriginalBitmap(nullptr), mCurBitmap(nullptr), mCurCacheBitmap(nullptr) {};
	~ImageGp() {};
private:
	void clone(int index, HDC hdc) {
		mIndex = index;

		mImageInfo = new IMAGE_INFO(mImageInfo);
		mImage = mImage->Clone();

		mOriginalBitmap = mOriginalBitmap->Clone(0.0f, 0.0f, mOriginalBitmap->GetWidth(), mOriginalBitmap->GetHeight(), mOriginalBitmap->GetPixelFormat());;
		mCurBitmap = mCurBitmap->Clone(0.0f, 0.0f, mCurBitmap->GetWidth(), mCurBitmap->GetHeight(), mCurBitmap->GetPixelFormat());
		mCurBitmapGraphics = new Graphics(mCurBitmap);

		mGraphics = new Graphics(hdc);

		mCurCacheBitmap = new CachedBitmap(mCurBitmap, mGraphics);
	}
	inline void setIndex(int index) { mIndex = index; }
	inline void makeNewBitmap(Bitmap* newBitmap, Graphics* newGrapics);
	inline Gdiplus::Bitmap* getBitmapClone(void) { return mCurBitmap->Clone(0.0f, 0.0f, mCurBitmap->GetWidth(), mCurBitmap->GetHeight(), mCurBitmap->GetPixelFormat()); }
};
