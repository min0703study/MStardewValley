#pragma once
#include "GameScene.h"
#include "GameUI.h"

#define SAVE_MODE true
#define CHANGE_MODE false

typedef struct tagTileIndex {
	int X;
	int Y;
	int ORDER;
	tagTileIndex() :X(-1), Y(-1), ORDER(-1) {};
	tagTileIndex(int x, int y) :X(x), Y(y) {};
	tagTileIndex(int x, int y, int xSize) :X(x), Y(y) {
		ORDER = x + y * xSize;
	};
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
	bool IsAreadyWorkTileDrag(TINDEX tileIndex);
	//타일 사이즈
	float mTileSize;

	//BOARD COUNT
	int mXWorkBoardCount;
	int mYWorkBoardCount;
	int mWorkBoardAllCount;

	//cur map type
	string mCurPaletteKey;

	eMapToolCtrl mCurCtrl;
	
	// == UI
	ScrollBox* mTilePaletteScrollBox;
	ScrollBox* mWorkBoardScrollBox;
	ScrollBox* mSelectTileBox;
	GameUI* mCurCtrlBox;

	EditText* mInputFileNameBox;

	SButton* mBtnCtrlList[eMapToolCtrl::MC_END];
	SButton* mBtnSave;
	SButton* mBtnLoad;
	SButton* mBtnBack;

	RadioButton* mRBtnSelectMapType;
	// UI ==
	ImageGp* mBaseSprite;
	ImageGp** mPalette;

	vector<tagTileDef*> mCurTilePalette;
	vector<tagTile> mVCurWorkTile;

	RectF mPaletteSelectRectF;
	RectF mWorkboardSelectRectF;
	bool bShowingPBoxRecF;
	bool bShowingWboxRectF;

	MapTileInfo mMapTileInfo;

	int mSelectPXIndex;
	int mSelectPYIndex;

	int mSelectPToXIndex;
	int mSelectPToYIndex;

	vector<TINDEX> mVDragWorkTileIndex;
	vector<TINDEX>::iterator mViDragWorkTileIndex;

	TINDEX mSelectWorkFrom;
	TINDEX mSelectWorkTo;

	void saveMap();
	void loadMap();

	bool bChangeScene;
	string mChangeScene;
#if SAVE_MODE
	tagTileDef** mVSaveMode;
	SButton* mBtnSavePallete;
#endif
#if CHANGE_MODE
	tagTileOriginal** mVChangeList;
#endif
};

