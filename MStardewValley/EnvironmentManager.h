#pragma once
#include "GameNode.h"
#include "MineRock.h"

class EnvironmentManager: public GameNode
{
public:
	typedef struct tagReqEnviroment{
		PointF Position;
		bool BIsRandomMake;
		int TypeId;
	};
public:
	HRESULT init();
	void render();
	void update();
	void release();

	vector<MineRock*> makeMineRock(eMineLevel level, vector<tagReqEnviroment> reqList);

	EnvironmentManager() {};
	~EnvironmentManager() {};
};

