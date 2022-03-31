#pragma once

#include "GameObject.h"
#include "SingletonBase.h"
#include "PlayerAnimation.h"

class Player: public GameObject, public SingletonBase<Player>
{
public:
	void Init(string id, float x, float y, float width, float height, eXStandard xStandard, eYStandard yStandard);
	
	void update(void) override;
	void render(void) override;
	void release(void) override;

	void draw(void) override;
	void animation(void)override;
	void move(void) override;
	void move(eGameDirection direction);
	void action(void) override;

	RectF getTempMoveBoxRectF(eGameDirection changeDirection);

	void changeActionStat(ePlayerStat changeStat);
	void changeDirection(eGameDirection changeDirection);
private:
	PlayerAnimation* ani;
	ePlayerStat mCurActionStat;
	eGameDirection mCurDirection;


};

