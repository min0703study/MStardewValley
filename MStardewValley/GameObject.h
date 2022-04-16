#pragma once
#include "GameNode.h"

class GameObject: public GameNode
{
public:
	void Init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);

	virtual void update(void);
	virtual void render(void);
	virtual void release(void);

	virtual void draw(void);
	virtual void animation(void);
	virtual void move(void);
	virtual void action(void);

	float getWidth() { return mWidth; }
	float getHeight() { return mHeight; }

	float getHalfWidth() { return mWidth * 0.5f; }
	float getHalfHeight() { return mHeight * 0.5f; }

	inline float getAbsX() { return mCenterX; };
	inline float getAbsY() { return mCenterY; };

	float* getAbsPX() { return &mCenterX; };
	float* getAbsPY() { return &mCenterY; };
	
	void setAbsX(float centerX) {
		mCenterX = centerX;
		mRECT = RectMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
		mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
	};

	void setAbsY(float centerY) {
		mCenterY = centerY;
		mRECT = RectMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
		mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
	};

	void setAbsXY(float centerX, float centerY) {
		mCenterX = centerX;
		mCenterY = centerY;

		mRECT = RectMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
		mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
	};

	inline float getRelX() { return mCenterX - CAMERA->getX();};
	inline float getRelY() { return mCenterY - CAMERA->getY();};

	inline float getRelX(float x) { return x - CAMERA->getX(); };
	inline float getRelY(float y) { return y - CAMERA->getY(); };

	inline RECT getAbsRc() {
		return mRECT;
	};

	inline RectF getAbsRectF() {
		return mRectF;
	};

	inline RectF getRelRectF() {
		RectF tempRectF;
		mRectF.GetBounds(&tempRectF);
		tempRectF.Offset(-CAMERA->getX(), -CAMERA->getY());
		return tempRectF;
	};

	inline RECT getRc() {
		return {
			mRECT.left -	static_cast<int>(CAMERA->getX()),
			mRECT.top -		static_cast<int>(CAMERA->getY()),
			mRECT.right -	static_cast<int>(CAMERA->getX()),
			mRECT.bottom -	static_cast<int>(CAMERA->getY())
		};
	};

	void offsetX(float x) {
		mCenterX += x;
		mRECT = RectMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
		mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
	};

	void offsetY(float y) {
		mCenterY += y;
		mRECT = RectMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
		mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
	};

	GameObject() {};
	virtual ~GameObject() {};
protected:
	float mWidth;
	float mHeight;
private:
	string mId;

	RectF mRectF;
	RECT mRECT;

	float mCenterX;
	float mCenterY;
};

