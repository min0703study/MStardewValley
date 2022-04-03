#pragma once
#include "GameNode.h"
#include "SingletonBase.h"

class MonsterSprite: public GameNode, public SingletonBase<MonsterSprite>
{
public:
	HRESULT init(void);
	void release(void);

	vector<ImageGp*> getVAni(eMonsterType type);
private:
	ImageGp* mBaseSprite;

	int mMonsterX[eMonsterType::MST_END];
	int mMonsterY[eMonsterType::MST_END];
	int mMonsterXCount[eMonsterType::MST_END];
	int mMonsterYCount[eMonsterType::MST_END];
	float mMonsterWidth[eMonsterType::MST_END];
	float mMonsterHeight[eMonsterType::MST_END];

	vector<ImageGp*> mVMonster[eMonsterType::MST_END];
};

