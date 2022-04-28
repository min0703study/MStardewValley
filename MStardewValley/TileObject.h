#pragma once
#include "GameNode.h"

class TileObject : public GameNode
{
public:
	void init(int indexX, int indexY, int xCount = 1, int yCount = 1, eXStandard xStandard = XS_LEFT, eYStandard eYStandard = YS_TOP);

	virtual void update(void) {
		move();
		action();
	};
	
	virtual void render(void) {
		animation();
		draw();
	};

	virtual void release(void);

	virtual void draw(void);
	virtual void animation(void);
	virtual void move(void);
	virtual void action(void);

	RectF getRelRectF() {
		RectF relRectF;
		mRectF.GetBounds(&relRectF);
		relRectF.Offset(-CAMERA->getX(), -CAMERA->getY());
		return relRectF;
	};

	float getRelX() const { return mAbsX - CAMERA->getX(); };
	float getRelY() const { return mAbsY - CAMERA->getY(); };

	inline bool contains(TINDEX tIndex) {
		return tIndex.X >= mStartIndexX && tIndex.X <= mEndIndexX && tIndex.Y >= mStartIndexY && tIndex.Y <= mEndIndexY;
	}

	TileObject() {};
	virtual ~TileObject() {};
private:
	string mId;

	int mIndexX;
	int mIndexY;

	int mStartIndexX;
	int mStartIndexY;

	int mEndIndexX;
	int mEndIndexY;

	int mWidth;
	int mHeight;

	int mAbsX;
	int mAbsY;

	RectF mRectF;
};


