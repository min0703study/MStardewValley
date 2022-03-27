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

	MapToolScene() {};
	~MapToolScene() {};

private:
	//타일 사이즈
	float mTileSize;

	//BOARD COUNT
	int mXWorkBoardCount;
	int mYWorkBoardCount;

	bool isDragging;

	vector<int> mVCurWorkIndex;

	eToolCtrl mToolCtrl;

	ScrollBox* mTilePaletteScrollBox;
	ScrollBox* mWorkBoardScrollBox;

	GameUI* mTilePalette;
	GameUI* mWorkBoard;

	SButton* mBtnEraser;
	SButton* mBtnSelect;
	SButton* mBtnSave;
	SButton* mBtnLoad;

	GameUI* mSelectTileBox;

	ImageGp* mines1To30Palette;
	ImageGp* mCurTileImg;

	vector<tagTile*> mCurTilePalette;
	vector<tagTile> mCurTileWork;

	RectF mCurSelectRectF;

	tagTile* mCurSelectTag;
	Bitmap* mCurSelectBitmap;

	void saveMap();
	void loadMap();
	void eraserTile();
};

