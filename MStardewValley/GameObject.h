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

	inline int getIndexX() { return static_cast<int>(getAbsX() / TILE_SIZE); };
	inline int getIndexY() { return static_cast<int>(getAbsY() / TILE_SIZE); };

	inline TINDEX getTIndex() { return TINDEX(getIndexX(), getIndexY()); };
	
	virtual void setAbsX(float centerX) {
		mCenterX = centerX;
		mRectF.X = centerX - getHalfWidth();
	};

	virtual void setAbsY(float centerY) {
		mCenterY = centerY;
		mRectF.Y = centerY - getHalfHeight();
	};

	virtual void setAbsXY(float centerX, float centerY) {
		mCenterX = centerX;
		mCenterY = centerY;

		mRECT = RectMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
		mRectF = RectFMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
	};

	virtual void setAbsXYToTile(int tileX, int tileY) {
		int absX = tileX * TILE_SIZE;
		int absY = tileY * TILE_SIZE;

		mRECT = RectMake(absX, absY, mWidth, mHeight);
		mRectF = RectFMake(absX, absY, mWidth, mHeight);

		mCenterX = mRectF.X + getHalfWidth();
		mCenterY = mRectF.Y + getHalfHeight();
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

	virtual void offsetX(float x) {
		mCenterX += x;
		mRectF.Offset(x, 0);
		mRECT = RectMakeCenter(mCenterX, mCenterY, mWidth, mHeight);
	};
	virtual void offsetY(float y) {
		mCenterY += y;
		mRectF.Offset(0, y);
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

