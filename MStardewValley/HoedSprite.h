#pragma once
#include "SingletonBase.h"
#include "GameNode.h"

class HoedSprite: public GameNode, public SingletonBase<HoedSprite>
{
public:
	HRESULT init(void);
	
	ImageGp * getNormalHoed(int x, int y);
	ImageGp * getWetHoed(int x, int y);
	void release();

private:
	ImageGp* mBaseSprite;
	ImageGp* mHoedNormal[4][4];
	ImageGp* mHoedWet[4][4];
};

