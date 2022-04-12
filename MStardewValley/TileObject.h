#pragma once
#include "GameNode.h"

class TileObject : public GameNode
{
public:
	void init(int indexX, int indexY, int toIndexX, int toIndexY);

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

	TileObject() {};
	virtual ~TileObject() {};
private:
	string mId;

	RectF mRectF;
	
	int mIndexX;
	int mIndexY;

	int mToIndexX;
	int mToIndexY;
};


