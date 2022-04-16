#pragma once
#include "GameNode.h"

class TileObject : public GameNode
{
public:
	void init(int indexX, int indexY, int xCount = 1, int yCount = 1, eXStandard xStandard = XS_CENTER, eYStandard eYStandard = YS_CENTER);

	virtual void update(void) {
		move();
		action();
	};
	virtual void render(void) {
		animation();
		render();
	};

	virtual void release(void);

	virtual void draw(void);
	virtual void animation(void);
	virtual void move(void);
	virtual void action(void);

	float getRelX() { return (mStartIndexX * TILE_SIZE) - CAMERA->getX(); };
	float getRelY() { return (mStartIndexY * TILE_SIZE) - CAMERA->getY(); };

	RectF getRelRectF() {
		RectF relRectF;
		mRectF.GetBounds(&relRectF);
		relRectF.Offset(-CAMERA->getX(), -CAMERA->getY());
		return relRectF;
	};

	TileObject() {};
	virtual ~TileObject() {};
private:
	string mId;

	RectF mRectF;
	
	int mIndexX;
	int mIndexY;

	int mStartIndexX;
	int mStartIndexY;

	int mEndIndexX;
	int mEndIndexY;
};


