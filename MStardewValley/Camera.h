#pragma once

#include "SingletonBase.h"

class Camera: public SingletonBase<Camera>
{
private:
	float mWidth;
	float mHeight;

	float mX;
	float mY;

	int mStartXIndex;
	int mStartYIndex;

	int mEndXIndex;
	int mEndYIndex;
public:
	HRESULT init(float x, float y, float width, float height);
	void release(void);

	inline float getX() const { return mX; }
	inline float getY() const { return mY; }

	inline float getWidth() const { return mWidth; }
	inline float getHeight() const { return mHeight; }

	inline float getStartTileXIndex() const { return mStartXIndex; }
	inline float getStartTileYIndex() const { return mStartYIndex; }

	inline float getEndTileXIndex() const { return mEndXIndex; }
	inline float getEndTileYIndex() const { return mEndYIndex; }

	inline void offsetX(int x) { 
		mX += x; 
		mStartXIndex = static_cast<int>(mX / TILE_SIZE);
		mEndXIndex = static_cast<int>((mX + mWidth) / TILE_SIZE);
	};

	inline void offsetY(int y) { 
		mY += y; 
		mStartYIndex = static_cast<int>(mY / TILE_SIZE);
		mEndYIndex = static_cast<int>((mY + mHeight) / TILE_SIZE);
	};
	
	inline void setX(float x) {
		mX = x;
		mStartXIndex = static_cast<int>(mX / TILE_SIZE);
		mEndXIndex = static_cast<int>((mX + mWidth) / TILE_SIZE);
	};
	
	inline void setY(float y) {
		mY = y;
		mStartYIndex = static_cast<int>(mY / TILE_SIZE);
		mEndYIndex = static_cast<int>((mY + mHeight) / TILE_SIZE);
	};

	inline void setToCenterX(float x) {
		mX = x - mWidth / 2.0f;
		mStartXIndex = static_cast<int>(mX / TILE_SIZE);
		mEndXIndex = static_cast<int>((mX + mWidth) / TILE_SIZE);
	};

	inline void setToCenterY(float y) {
		mY = y - mHeight / 2.0f;
		mStartYIndex = static_cast<int>(mY / TILE_SIZE);
		mEndYIndex = static_cast<int>((mY + mHeight) / TILE_SIZE);
	};

	Camera() {};
	~Camera() {}
};

