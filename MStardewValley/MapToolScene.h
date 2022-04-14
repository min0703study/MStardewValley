#pragma once
#include "GameScene.h"
#include "GameUI.h"

#define SAVE_MODE true

typedef struct tagTileIndex {
	int X;
	int Y;

	tagTileIndex(int x, int y) :X(x), Y(y) {};
} TINDEX;

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
	SButton* mBtnOneTile;
	SButton* mBtnSave;
	SButton* mBtnLoad;
	SButton* mBtnBack;

	RadioButton* mRBtnSelectMapType;
	// UI ==

	Bitmap* mSelectTileBitmap;

	ImageGp* mBaseSprite;
	ImageGp** mPalette;

	vector<tagTile*> mCurTilePalette;
	vector<tagTile> mVCurWorkTile;

#if SAVE_MODE
	tagTile** mVSaveMode;
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

	vector<TINDEX> mWorkTileIndexList;
	vector<TINDEX>::iterator miWorkTileIndexList;

	void saveMap();
	void loadMap();
	void updateMapStruct();

	float x, y;
};

