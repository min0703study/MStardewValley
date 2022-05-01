#pragma once
#include "GameScene.h"
#include "GameUI.h"

#define SAVE_MODE false
#define CHANGE_MODE false

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
	bool isTileSizeInitOver;
	bool isCheckOver;
	ImageGp* mTileSizeQuestion;
	bool IsAreadyWorkTileDrag(TINDEX tileIndex);
	EditText* mTileSizeInput;
	SButton* mTileSizeBtn;


	//타일 사이즈
	float mTileSize;

	bool bReqSceneChange;

	//BOARD COUNT
	int mXWorkBoardCount;
	int mYWorkBoardCount;
	int mAllWorkBoardCount;

	//cur map type
	string mCurPaletteKey;

	eMapToolCtrl mCurCtrl;
	int mObjectGroupIndex;
	
	// == UI
	ScrollBox* mTilePaletteScrollBox;
	ScrollBox* mWorkBoardScrollBox;
	ScrollBox* mSelectTileBox;

	UIComponent* mCurCtrlBox;

	EditText* mInputFileNameBox;

	SButton* mBtnCtrlList[eMapToolCtrl::MC_END];

	SButton* mBtnSave;
	SButton* mBtnLoad;
	SButton* mBtnBack;

	RadioButton* mRBtnSelectMapType;
	// UI ==
	ImageGp* mBaseSprite;
	ImageGp** mPalette;
	ImageGp* mBgImg;

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

	string mCurInputText;

	bool bChangeScene;
	string mChangeScene;

	void rebuild();
#if SAVE_MODE
	tagTileDef** mVSaveMode;
	SButton* mBtnSavePallete;
#endif
#if CHANGE_MODE
	tagTileOriginal** mVChangeList;
#endif
};

