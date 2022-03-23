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

	float mTileSize;

	ScrollBox* mSampleScrollBox;
	ScrollBox* mWorkBoardScrollBox;
	
	GameUI* mSample;
	GameUI* mWorkBoard;

	SButton* mBtnEraser;
	SButton* mBtnSelect;

	vector<tagTile*> mCurTagPalette;

	MapToolScene() {};
	~MapToolScene() {};
};

