#pragma once

#include "SingletonBase.h"

class Camera: public SingletonBase<Camera>
{
private:
	float mWidth;
	float mHeight;

	float mX;
	float mY;

public:
	HRESULT init(float x, float y, float width, float height);
	void release(void);

	inline float getX() const { return mX; }
	inline float getY() const { return mY; }

	inline float getWidth() const { return mWidth; }
	inline float getHeight() const { return mHeight; }

	inline void offsetX(int x) { 
		mX += x; 
	};
	inline void offsetY(int y) { 
		mY += y; 
	};

	inline void setX(float x) {
		mX = x;
	};
	inline void setY(float y) {
		mY = y;
	};

	inline void setToCenterX(float x) {
		mX = x - mWidth / 2.0f;
	};
	inline void setToCenterY(float y) {
		mY = y - mHeight / 2.0f;
	};

	Camera() {};
	~Camera() {}
};

