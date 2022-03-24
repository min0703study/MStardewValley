#pragma once
#include "GameScene.h"
#include "GameUI.h"
class MapToolScene: public GameScene
{
public:
	enum eToolCtrl {
		TC_ERASER,
		TC_SELECT
	};

	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	float mTileSize;
	
	eToolCtrl mToolCtrl;

	ScrollBox* mTilePaletteScrollBox;
	ScrollBox* mWorkBoardScrollBox;
	
	GameUI* mTilePalette;
	GameUI* mWorkBoard;

	SButton* mBtnEraser;
	SButton* mBtnSelect;

	vector<RECT> mTilePaletteRECT;

	ImageGp* mines1To30Palette;

	vector<tagTile*> mCurTagPalette;
	vector<tagTile*> mCurTagWorkBoard;


	tagTile* mCurSelectTag;

	MapToolScene() {};
	~MapToolScene() {};
};

