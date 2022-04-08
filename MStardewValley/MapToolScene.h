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
	int mCurPaletteType;

	eMapToolCtrl mCurCtrl;
	
	// == UI
	ScrollBox* mTilePaletteScrollBox;
	ScrollBox* mWorkBoardScrollBox;
	ScrollBox* mSelectTileBox;

	EditText* mInputFileNameBox;

	GameUI* mSelectTile;
	GameUI* mTilePalette;
	GameUI* mWorkBoard;

	SButton* mBtnEraser;
	SButton* mBtnSelect;
	SButton* mBtnSave;
	SButton* mBtnLoad;

	RadioButton* mRBtnSelectMapType;
	// UI ==

	Bitmap* mSelectTileBitmap;

	ImageGp* mines1To30Palette;

	vector<tagTile*> mCurTilePalette;
	vector<tagTile> mVCurWorkTile;

	RectF mCurSelectRectF;

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

	float x;
	float y;
};

