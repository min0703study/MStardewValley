#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class MinesSprite: public GameNode, public SingletonBase<MinesSprite>
{
public:
	HRESULT init(void);
	void release(void);

	vector<ImageGp*> getVAni(eMineStoneType stoneType);
private:
	ImageGp* mBaseSprite;

	int mMineTypeIndexX[eMineStoneType::MT_END];
	int mMineTypeIndexY[eMineStoneType::MT_END];

	vector<ImageGp*> mVMines[eMineStoneType::MT_END];
};

