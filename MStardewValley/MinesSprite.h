#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class MinesSprite: public GameNode, public SingletonBase<MinesSprite>
{
public:
	HRESULT init(void);
	void release(void);

	vector<ImageGp*> getVAni(eRockType stoneType);
private:
	ImageGp* mBaseSprite;

	int mMineTypeIndexX[eRockType::RT_END];
	int mMineTypeIndexY[eRockType::RT_END];

	vector<ImageGp*> mVMines[eRockType::RT_END];
};

