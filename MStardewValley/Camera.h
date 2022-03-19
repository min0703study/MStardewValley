#pragma once

#include "SingletonBase.h"
class Camera: public SingletonBase<Camera>
{
private:
	float mWidth;
	float mHeight;

	float mX;
	float mY;

	LPRECT mlpRc;
public:
	HRESULT init(float x, float y, float width, float height);
	void release(void);

	inline float getX() const { return mX; }
	inline float getY() const { return mY; }

	inline RECT getRc() const { return *mlpRc; }

	inline float getWidth() const { return mWidth; }
	inline float getHeight() const { return mHeight; }

	inline void offSetX(int x) { 
		mX += x; 
		mlpRc->left += x;
		mlpRc->right += x;
	};
	inline void offSetY(int y) { 
		mY += y; 
		mlpRc->top += y;
		mlpRc->bottom += y;
	};

	Camera() {};
	~Camera() {}
};

