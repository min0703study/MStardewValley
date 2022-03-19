#pragma once
#include "GameScene.h"
#include "GameUI.h"
class MapToolScene: public GameScene
{
public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	ScrollBox* mSampleScrollBox;
	ScrollBox* mWorkScrollBox;
	
	GameUI* mSample;
	GameUI* mWork;

	MapToolScene() {};
	~MapToolScene() {};
};

