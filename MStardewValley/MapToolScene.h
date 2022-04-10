#pragma once
#include "GameScene.h"
#include "GameUI.h"

#define SAVE_MODE false

class MapToolScene: public GameNode
{
public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	MapToolScene() {};
	~MapToolScene() {};

private:
	//타일 사이즈
	float mTileSize;

	//BOARD COUNT
	int mXWorkBoardCount;
	int mYWorkBoardCount;
	int mWorkBoardAllCount;

	//cur map type
	eMapSprite mCurPaletteType;

	eMapToolCtrl mCurCtrl;
	
	// == UI
	ScrollBox* mTilePaletteScrollBox;
	ScrollBox* mWorkBoardScrollBox;
	ScrollBox* mSelectTileBox;

	EditText* mInputFileNameBox;

	SButton* mBtnEraser;
	SButton* mBtnSelect;
	SButton* mBtnSave;
	SButton* mBtnLoad;
	SButton* mBtnBack;

	RadioButton* mRBtnSelectMapType;
	// UI ==

	Bitmap* mSelectTileBitmap;

	ImageGp* mCurPalette;

	vector<tagTile*> mCurTilePalette;
	vector<tagTile> mVCurWorkTile;

#if SAVE_MODE
	ImageGp* mTempPalette;
	tagTile** mVSaveMode;
	tagTile* mVSRaveMode;
	int mVSaveX;
	int mVSaveY;
#endif
	RectF mCurSelectRectF;
	bool bIsShowingSelectRecF;

	MapTileInfo mMapTileInfo;

	int mSelectTileXIndex;
	int mSelectTileYIndex;

	int mSelectTileToXIndex;
	int mSelectTileToYIndex;

	int mWorkTileXIndex;
	int mWorkTileYIndex;

	void saveMap();
	void loadMap();
	void eraserTile();
	void updateMapStruct();

	float x, y;
};

