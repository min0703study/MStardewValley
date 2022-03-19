#pragma once
#include "Stdafx.h"

class Animation;

class ImageBase
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
		DWORD         resID;      //리소스 아이디
		HDC            hMemDC;      //메모리 DC (Mem이라 적혀있으면 메모리 관련)
		HBITMAP         hBit;      //비트맵 가져올 것
		HBITMAP         hOBit;      //올드 비트맵
		float         x;
		float         y;
		int            width;      //이미지 가로
		int            height;      //이미지 세로
		int            currentFrameX;
		int            currentFrameY;
		int            maxFrameX;
		int            maxFrameY;
		int            frameWidth;
		int            frameHeight;
		BYTE         loadType;   //이미지의 로드 타입

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = y = 0;
			width = 0;
			height = 0;
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
	LPIMAGE_INFO   _imageInfo;         // 이미지 정보 (포인터 변수)
	CHAR*         _fileName;         //파일 이름
	BOOL         _isTrans;         //배경색 없앨건지
	COLORREF      _transColor;      //없앨거면 RGB 색상이 무엇인지 //RGB (각각 1바이트 0~255 농도 표현) // 더 쪼개고 싶다면 바이트로

	BLENDFUNCTION   _blendFunc;         //
	LPIMAGE_INFO   _blendImage;      //

public:

	//빈 비트맵 초기화
	HRESULT init(int width, int height); //초기화한다 무엇을? 가로 세로
	// 이미지 리소스 초기화
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	// 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	// 프레임 이미지 파일로 초기화
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//알파 블랜드 초기화
	HRESULT initForAlphaBlend(void);

	//투명 컬러키 세팅 (배경색 날릴건지, 어떤 색깔로 날릴 건지)
	void setTransColor(BOOL isTrans, COLORREF transColor);

	//해제
	void release(void);

	//렌더
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	// 클리핑
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//알파 렌더
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//프레임 렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//루프 렌더
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);
	
	void aniRender(HDC hdc, int destX, int destY, Animation * ani);

	//===============
	//# 인라인 함수 #
	//===============

	// DC 얻기
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	// 이미지 X 좌표
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	// 이미지 Y 좌표
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	// 이미지 센터 좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	// 이미지 가로, 세로 크기
	inline int getWidth(void) { 
		return _imageInfo->width; 
	}
	inline int getHeight(void) { 
		return _imageInfo->height; 
	}

	//바운딩 박스 (충돌용 렉트)
	inline RECT boundingBox(void)
	{
		RECT rc =
		{
		   (int)_imageInfo->x,
		   (int)_imageInfo->y,
		   (int)_imageInfo->x + _imageInfo->width,
		   (int)_imageInfo->y + _imageInfo->height,
		};
		return rc;
	}

	inline RECT boundingBoxWithFrame(void)
	{
		RECT rc =
		{
		   (int)_imageInfo->x,
		   (int)_imageInfo->y,
		   (int)_imageInfo->x + _imageInfo->frameWidth,
		   (int)_imageInfo->y + _imageInfo->frameHeight,
		};
		return rc;
	}

	//프레임 X
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline void offsetX(int frameX, bool isReverse)
	{
		_imageInfo->currentFrameX += frameX;
	}


	//프레임 Y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	// 이미지 1프레임 가로, 세로 크기
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	// 최대 프레임 x, y 갯수
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline void nextFrameAuto() {
		_imageInfo->currentFrameX = _imageInfo->currentFrameX++;
		if (_imageInfo->currentFrameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = 0;
		}
	}

	ImageBase();
	~ImageBase() {};
};