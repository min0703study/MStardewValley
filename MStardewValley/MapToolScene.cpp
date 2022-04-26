#include "Stdafx.h"
#include "MapToolScene.h"

#define SAMPLE_SCROLL_BOX_WIDTH		(WINSIZE_X * 0.25f)
#define SAMPLE_SCROLL_BOX_HEIGHT	(WINSIZE_Y * 0.5f)

#define WORK_SCROLL_BOX_WIDTH		(WINSIZE_X * 0.75f)
#define WORK_SCROLL_BOX_HEIGHT		WINSIZE_R_Y

#define SELECT_TILE_BOX_X		0
#define SELECT_TILE_BOX_Y		(WINSIZE_Y * 0.5f) + 64

#define SELECT_TILE_BOX_WIDTH		(WINSIZE_Y * 0.4f - 100.0f)
#define SELECT_TILE_BOX_HEIGHT		(WINSIZE_Y * 0.4f - 100.0f)

#define CTRL_BTN_LIST_START_X		330.0f
#define CTRL_BTN_LIST_START_Y		720.0f

#define CTRL_BTN_WIDTH			70.0f
#define CTRL_BTN_HEIGHT			70.0f

#define SELECT_CTRL_BOX_X		330.0f
#define SELECT_CTRL_BOX_Y		605.0f

#define SELECT_CTRL_BOX_WIDTH	150.0f
#define SELECT_CTRL_BOX_HEIGHT	100.0f

#define SAVE_BTN_X		0
#define SAVE_BTN_Y		SELECT_TILE_BOX_Y + SELECT_CTRL_BOX_HEIGHT

HRESULT MapToolScene::init(void)
{
	mTileSize = TILE_SIZE;

	mXWorkBoardCount = 50;
	mYWorkBoardCount = 30;
	mAllWorkBoardCount = mXWorkBoardCount * mYWorkBoardCount;

	mAllWorkBoardCount = mXWorkBoardCount * mYWorkBoardCount;

	mCurCtrl = MC_DRAW;

	mSelectPYIndex = -1;
	mSelectPXIndex = -1;

	mCurPaletteKey = MAPCLASS->MINE_P;
	mMapTileInfo.MapType = eMapType::MT_MINE;

	mBaseSprite = MAPPALETTEMANAGER->findBaseSprite(mCurPaletteKey);
	mPalette = MAPPALETTEMANAGER->findPalette(mCurPaletteKey);
	mCurTilePalette = MAPPALETTEMANAGER->findTileNode(mCurPaletteKey);

	//작업 영역
	ImageGp* tempWorkBoard = new ImageGp;
	tempWorkBoard->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(mTileSize * mXWorkBoardCount, mTileSize * mYWorkBoardCount));
	
	GDIPLUSMANAGER->drawGridLine(tempWorkBoard, mTileSize, mTileSize);
	mWorkBoardScrollBox = new ScrollBox;
	mWorkBoardScrollBox->init("작업 영역 스크롤 상자", SAMPLE_SCROLL_BOX_WIDTH, 0, WORK_SCROLL_BOX_WIDTH, WORK_SCROLL_BOX_HEIGHT, tempWorkBoard);
	mWorkBoardScrollBox->setContentClickDownEvent([this](GameUI* ui) {
		mSelectWorkFrom = TINDEX(
			mWorkBoardScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize,
			mWorkBoardScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize,
			mXWorkBoardCount
		);
	});
	mWorkBoardScrollBox->setContentDragEvent([this](GameUI* ui) {
		ScrollBox* castUi = (ScrollBox*)ui;

		TINDEX tileIndex(
			mWorkBoardScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize,
			mWorkBoardScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize,
			mXWorkBoardCount
		);

		if (IsAreadyWorkTileDrag(tileIndex)) return;
		else mVDragWorkTileIndex.push_back(tileIndex);
		
		tagTile& wTile = mVCurWorkTile[tileIndex.ORDER];

		switch (mCurCtrl) {
		case MC_DRAW: {
			int mCurWIndexY = tileIndex.Y;
			for (int y = mSelectPYIndex; y <= mSelectPToYIndex; y++, mCurWIndexY++) {
				int mCurWIndexX = tileIndex.X;
				for (int x = mSelectPXIndex; x <= mSelectPToXIndex; x++, mCurWIndexX++) {
					int wIndex = mCurWIndexX + mCurWIndexY * mXWorkBoardCount;
					int pIndex = x + y * (mBaseSprite->getMaxFrameX() + 1);

					tagTile& wTile = mVCurWorkTile[wIndex];
					tagTileDef& pTile = *mCurTilePalette[pIndex];

					if (!pTile.IsInit) {
						LOG::e("초기화 되지 않은 타일 팔레트 입니다");
						LOG::e("x : " + to_string(x) + "y : " + to_string(y));
						break;
					}

					if (pTile.Terrain != TR_NULL) {
						wTile.Terrain = pTile.Terrain;
						wTile.TerrainFrameX = pTile.TerrainFrameX;
						wTile.TerrainFrameY = pTile.TerrainFrameY;
					}
					else if (pTile.Object != OBJ_NULL) {
						for (int i = 0; i < OBJ_C; i++) {
							if(wTile.ObjectFrameX[i] == pTile.ObjectFrameX && wTile.ObjectFrameY[i] == pTile.ObjectFrameY) {
								break;
							}

							if (wTile.Object[i] == OBJ_NULL) {
								wTile.Object[i] = pTile.Object;
								wTile.ObjectFrameX[i] = pTile.ObjectFrameX;
								wTile.ObjectFrameY[i] = pTile.ObjectFrameY;
								break;
							}
						}
					}

					if (wTile.Terrain != TR_NULL) {
						((ScrollBox*)ui)->getContent()->coverBitmap(
							(mCurWIndexX * mTileSize),
							(mCurWIndexY * mTileSize),
							mPalette[wTile.TerrainFrameY][wTile.TerrainFrameX].getBitmap()
						);
					}
					else {
						((ScrollBox*)ui)->getContent()->coverBitmap(
							(mCurWIndexX * mTileSize),
							(mCurWIndexY * mTileSize),
							GDIPLUSMANAGER->getBlankWorkBoard(mTileSize, mTileSize)
						);
					}

					RectF rcF = RectFMake((mCurWIndexX * mTileSize), (mCurWIndexY * mTileSize), mTileSize, mTileSize);
					castUi->getSubImgGp()->toTransparent(rcF);
					for (int i = 0; i < OBJ_C; i++) {
						if (wTile.Object[i] != OBJ_NULL) {
							((ScrollBox*)ui)->getContent()->overlayBitmap(
								(mCurWIndexX * mTileSize),
								(mCurWIndexY * mTileSize),
								mPalette[wTile.ObjectFrameY[i]][wTile.ObjectFrameX[i]].getBitmap()
							);
						}
					}

					GDIPLUSMANAGER->drawRectFToBitmap(castUi->getSubImgGp()->getBitmap(), rcF, wTile.IsCanMove ? CR_A_BLUE : CR_A_RED);
					GDIPLUSMANAGER->drawTextToBitmap(castUi->getSubImgGp()->getBitmap(), to_wstring(wTile.ObjectLevel[0]), rcF, 15.0f, CR_YELLOW);
				}
			}

#if DEBUG_MODE
			if (KEYMANAGER->isStayKeyDown('P')) {
				mVCurWorkTile[tileIndex.ORDER].toString();
			}
#endif
			mWorkBoardScrollBox->clipingContentArea();
		}
		case MC_COLLISION_TILE: {
			wTile.IsCanMove = false;
			RectF rcF = RectFMake((tileIndex.X * mTileSize), (tileIndex.Y * mTileSize), mTileSize, mTileSize);
			castUi->getSubImgGp()->toTransparent(rcF);
			GDIPLUSMANAGER->drawRectFToBitmap(castUi->getSubImgGp()->getBitmap(), rcF, CR_A_RED);
			GDIPLUSMANAGER->drawTextToBitmap(castUi->getSubImgGp()->getBitmap(), to_wstring(wTile.ObjectLevel[0]), rcF, 15.0f, CR_YELLOW);
			castUi->getSubImgGp()->rebuildChachedBitmap();
			break;
		}
		case MC_MOVABLE_TILE: {
			wTile.IsCanMove = true;
			RectF rcF = RectFMake((tileIndex.X * mTileSize), (tileIndex.Y * mTileSize), mTileSize, mTileSize);
			castUi->getSubImgGp()->toTransparent(rcF);
			GDIPLUSMANAGER->drawRectFToBitmap(castUi->getSubImgGp()->getBitmap(), rcF, CR_A_BLUE);
			GDIPLUSMANAGER->drawTextToBitmap(castUi->getSubImgGp()->getBitmap(), to_wstring(wTile.ObjectLevel[0]), rcF, 15.0f, CR_YELLOW);
			castUi->getSubImgGp()->rebuildChachedBitmap();
			break;
		}
		case MC_OBJECT_GROUP: {
			wTile.ObjectLevel[0] = mObjectGroupIndex;
			RectF rcF = RectFMake((tileIndex.X * mTileSize), (tileIndex.Y * mTileSize), mTileSize, mTileSize);
			castUi->getSubImgGp()->toTransparent(rcF);
			GDIPLUSMANAGER->drawRectFToBitmap(castUi->getSubImgGp()->getBitmap(), rcF, wTile.IsCanMove ? CR_A_BLUE : CR_A_RED);
			GDIPLUSMANAGER->drawTextToBitmap(castUi->getSubImgGp()->getBitmap(), to_wstring(wTile.ObjectLevel[0]), rcF, 15.0f, CR_YELLOW);
			castUi->getSubImgGp()->rebuildChachedBitmap();
			break;
		}
		case MC_ERASER: {
			wTile.clear();
			castUi->getSubImgGp()->toTransparent(RectFMake((tileIndex.X * mTileSize), (tileIndex.Y * mTileSize), mTileSize, mTileSize));

			castUi->getContent()->coverBitmap(
				(tileIndex.X * mTileSize),
				(tileIndex.Y * mTileSize),
				GDIPLUSMANAGER->getBlankWorkBoard(mTileSize, mTileSize)
			);

			castUi->clipingContentArea();
			break;
		}
		}
	});
	mWorkBoardScrollBox->setContentMouseOverEvent([this](GameUI* ui) {
		bShowingWboxRectF = true;
	});
	mWorkBoardScrollBox->setContentMouseOffEvent([this](GameUI* ui) {
		bShowingWboxRectF = false;
	});
	mWorkBoardScrollBox->setContentClickUpEvent([this](GameUI* ui) {
		mVDragWorkTileIndex.clear();
	});

	//타일 팔레트
	mTilePaletteScrollBox = new ScrollBox;
	mTilePaletteScrollBox->init("맵툴 팔레트 스크롤 박스", 0, 64, SAMPLE_SCROLL_BOX_WIDTH, SAMPLE_SCROLL_BOX_HEIGHT, mBaseSprite);
	mTilePaletteScrollBox->setContentClickUpEvent([this](GameUI* ui) {
		switch (mCurCtrl) {
			case MC_DRAW: {
				((ScrollBox*)mSelectTileBox)->getContent()->coverBitmapCenter(mBaseSprite->getFrameBitmapToIndex(
					mSelectPXIndex,
					mSelectPYIndex,
					mSelectPToXIndex - mSelectPXIndex,
					mSelectPToYIndex - mSelectPYIndex));
				mSelectTileBox->clipingContentArea();
				break;
			}
		}
	});
	mTilePaletteScrollBox->setContentClickDownEvent([this](GameUI* ui) {
		switch (mCurCtrl) {
		case MC_DRAW: {
			mSelectPXIndex = mTilePaletteScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;
			mSelectPYIndex = mTilePaletteScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;

			mSelectPToXIndex = 0;
			mSelectPToYIndex = 0;
#if DEBUG_MODE
#if SAVE_MODE
			if (KEYMANAGER->isStayKeyDown('P')) {
				int pIndex = mSelectPXIndex + mSelectPYIndex * (mBaseSprite->getMaxFrameX() + 1);
				mVSaveMode[mSelectPYIndex][mSelectPXIndex].toString();
			}
#else
			if (KEYMANAGER->isStayKeyDown('P')) {
				int pIndex = mSelectPXIndex + mSelectPYIndex * (mBaseSprite->getMaxFrameX() + 1);
				mCurTilePalette[pIndex]->toString();
			}
#endif
#endif
			break;
		}
		}
	});
	mTilePaletteScrollBox->setContentMouseOverEvent([this](GameUI* ui) {
		bShowingPBoxRecF = true;
		int indexX = mTilePaletteScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;
		int indexY = mTilePaletteScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;

		int indexX2 = mTilePaletteScrollBox->getContentAreaRelXToX(_ptMouse.x) - mTilePaletteScrollBox->getContentAreaAbsXToX(_ptMouse.x);
		int indexY2 = mTilePaletteScrollBox->getContentAreaRelYToY(_ptMouse.y) - mTilePaletteScrollBox->getContentAreaAbsYToY(_ptMouse.y);

		mPaletteSelectRectF =
			RectFMake(
				mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + (indexX * mTileSize) - indexX2,
				mTilePaletteScrollBox->getContentAreaRectF().GetTop() + (indexY * mTileSize) - indexY2,
				mTileSize, mTileSize);
	});
	mTilePaletteScrollBox->setContentMouseOffEvent([this](GameUI* ui) {
		bShowingPBoxRecF = false;
	});
	mTilePaletteScrollBox->setContentDragEvent([this](GameUI* ui) {
		switch (mCurCtrl) {
		case MC_DRAW:
			mSelectPToXIndex = mTilePaletteScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;
			mSelectPToYIndex = mTilePaletteScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;

			mPaletteSelectRectF =
				RectFMake(
					mPaletteSelectRectF.GetLeft(), mPaletteSelectRectF.GetTop(),
					(mSelectPToXIndex - mSelectPXIndex + 1) * mTileSize,
					(mSelectPToYIndex - mSelectPYIndex + 1) * mTileSize);
			break;
		case MC_ERASER:
			break;
		}

	});

	mBtnCtrlList[MC_ERASER] = new SButton;
	mBtnCtrlList[MC_ERASER]->init("지우개 버튼", CTRL_BTN_LIST_START_X, CTRL_BTN_LIST_START_Y, CTRL_BTN_WIDTH, CTRL_BTN_HEIGHT, GDIPLUSMANAGER->clone(IMGCLASS->MapBtnEraser));
	mBtnCtrlList[MC_ERASER]->setClickDownEvent([this](GameUI* ui) {
		mCurCtrl = MC_ERASER;
		mCurCtrlBox->getImgGp()->overlayBitmapCenter(ui->getImgGp()->getBitmapClone());
		mCurCtrlBox->getImgGp()->rebuildChachedBitmap();
	});

	mBtnCtrlList[MC_DRAW] = new SButton;
	mBtnCtrlList[MC_DRAW]->init("선택 버튼", CTRL_BTN_LIST_START_X + CTRL_BTN_WIDTH, CTRL_BTN_LIST_START_Y, CTRL_BTN_WIDTH, CTRL_BTN_HEIGHT, GDIPLUSMANAGER->clone(IMGCLASS->MapBtnSelect));
	mBtnCtrlList[MC_DRAW]->setClickDownEvent([this](GameUI* ui) {
		mCurCtrl = MC_DRAW;
		mCurCtrlBox->getImgGp()->overlayBitmapCenter(ui->getImgGp()->getBitmapClone());
		mCurCtrlBox->getImgGp()->rebuildChachedBitmap();
	});

	mBtnCtrlList[MC_COLLISION_TILE] = new SButton;
	mBtnCtrlList[MC_COLLISION_TILE]->init("충돌 타일 버튼", CTRL_BTN_LIST_START_X, CTRL_BTN_LIST_START_Y + CTRL_BTN_HEIGHT, CTRL_BTN_WIDTH, CTRL_BTN_HEIGHT, GDIPLUSMANAGER->clone(IMGCLASS->MapBtnCollision));
	mBtnCtrlList[MC_COLLISION_TILE]->setClickDownEvent([this](GameUI* ui) {
		mCurCtrl = MC_COLLISION_TILE;
		mCurCtrlBox->getImgGp()->overlayBitmapCenter(ui->getImgGp()->getBitmapClone());
		mCurCtrlBox->getImgGp()->rebuildChachedBitmap();
	});

	mBtnCtrlList[MC_MOVABLE_TILE] = new SButton;
	mBtnCtrlList[MC_MOVABLE_TILE]->init("이동 타일 버튼", CTRL_BTN_LIST_START_X + CTRL_BTN_WIDTH, CTRL_BTN_LIST_START_Y + CTRL_BTN_HEIGHT, CTRL_BTN_WIDTH, CTRL_BTN_HEIGHT, GDIPLUSMANAGER->clone(IMGCLASS->MapBtnMovable));
	mBtnCtrlList[MC_MOVABLE_TILE]->setClickDownEvent([this](GameUI* ui) {
		mCurCtrl = MC_MOVABLE_TILE;
		mCurCtrlBox->getImgGp()->overlayBitmapCenter(ui->getImgGp()->getBitmapClone());
		GDIPLUSMANAGER->drawTextToBitmap(mCurCtrlBox->getImgGp()->getBitmap(), to_wstring(mObjectGroupIndex), 12.0f, CR_WHITE);
		mCurCtrlBox->getImgGp()->overlayBitmapCenter(ui->getImgGp()->getBitmapClone());
		mCurCtrlBox->getImgGp()->rebuildChachedBitmap();
	});

	mBtnCtrlList[MC_OBJECT_GROUP] = new SButton;
	mBtnCtrlList[MC_OBJECT_GROUP]->init("오브젝트 묶기 타일 버튼", CTRL_BTN_LIST_START_X, CTRL_BTN_LIST_START_Y + (CTRL_BTN_HEIGHT * 2.0f), CTRL_BTN_WIDTH, CTRL_BTN_HEIGHT, GDIPLUSMANAGER->clone(IMGCLASS->MapBtnObjectGroup));
	mBtnCtrlList[MC_OBJECT_GROUP]->setClickDownEvent([this](GameUI* ui) {
		mCurCtrl = MC_OBJECT_GROUP;
		mCurCtrlBox->getImgGp()->overlayBitmapCenter(ui->getImgGp()->getBitmapClone());
		mCurCtrlBox->getImgGp()->rebuildChachedBitmap();
	});

	mBtnSave = new SButton;
	mBtnSave->init("저장 버튼", 20, 948 + 20, GDIPLUSMANAGER->clone(IMGCLASS->MapBtnSave));
	mBtnSave->setClickDownEvent([this](GameUI* ui) {
		saveMap();
	});

	mBtnLoad = new SButton;
	mBtnLoad->init("불러오기 버튼", 200, 948 + 20, GDIPLUSMANAGER->clone(IMGCLASS->MapBtnLoad));
	mBtnLoad->setClickDownEvent([this](GameUI* ui) {
		loadMap();
	});

	mRBtnSelectMapType = new RadioButton;
	mRBtnSelectMapType->init(300, 0, 64, 64, new ImageGp*[3]{
		GDIPLUSMANAGER->clone(IMGCLASS->MapBtnSelectMine),
		GDIPLUSMANAGER->clone(IMGCLASS->MapBtnSelectFarm),
		GDIPLUSMANAGER->clone(IMGCLASS->MapBtnSelectInterior) }, 3);
	mRBtnSelectMapType->setClickDownEvent([this](GameUI* ui) {
		int key = (((RadioButton*)ui)->changeSelectIndex());
		if (key == 0) {
			mCurPaletteKey = MAPCLASS->MINE_P;
		}
		else if (key == 1) {
			mCurPaletteKey = MAPCLASS->OUTDOOR_P;
		}
		else {
			mCurPaletteKey = MAPCLASS->TOWN_INTERIOR_P;
		}
		mBaseSprite = MAPPALETTEMANAGER->findBaseSprite(mCurPaletteKey);
		mPalette = MAPPALETTEMANAGER->findPalette(mCurPaletteKey);
		mCurTilePalette.clear();
		mCurTilePalette = MAPPALETTEMANAGER->findTileNode(mCurPaletteKey);
		mTilePaletteScrollBox->changeContent(mBaseSprite);
#if SAVE_MODE
		int i = 0;
		mVSaveMode = new tagTileDef*[mBaseSprite->getMaxFrameY() + 1];
		for (int i = 0; i < mBaseSprite->getMaxFrameY() + 1; i++) {
			mVSaveMode[i] = new tagTileDef[mBaseSprite->getMaxFrameX() + 1];
			for (int x = 0; x < mBaseSprite->getMaxFrameX() + 1; x++) {
				mVSaveMode[i][x] = tagTileDef();
			}
		}

		for (int y = 0; y < mBaseSprite->getMaxFrameY() + 1; y++) {
			for (int x = 0; x < mBaseSprite->getMaxFrameX() + 1; x++) {
				mVSaveMode[y][x] = (*mCurTilePalette[i++]);
			}
		}

		rebuild();
#endif
	});

	mBtnBack = new SButton;
	mBtnBack->init("뒤로가기 버튼", 0, 0, GDIPLUSMANAGER->clone(IMGCLASS->MapBtnBack));
	mBtnBack->setClickDownEvent([this](GameUI* ui) {});

	ImageGp* tempSelectTile = new ImageGp;
	tempSelectTile->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(SELECT_TILE_BOX_WIDTH, SELECT_TILE_BOX_HEIGHT));
	mSelectTileBox = new ScrollBox;
	mSelectTileBox->init("현재 타일 스크롤 박스", SELECT_TILE_BOX_X, SELECT_TILE_BOX_Y, SELECT_TILE_BOX_WIDTH, SELECT_TILE_BOX_HEIGHT, tempSelectTile);
	mSelectTileBox->scrollToCenter();

	mCurCtrlBox = new GameUI;
	mCurCtrlBox->init("현재 타일 스크롤 박스", SELECT_CTRL_BOX_X, SELECT_CTRL_BOX_Y, SELECT_CTRL_BOX_WIDTH, SELECT_CTRL_BOX_HEIGHT, GDIPLUSMANAGER->clone(IMGCLASS->UISetupBox));

	mInputFileNameBox = new EditText;
	mInputFileNameBox->init("파일 이름 입력창", 0, 875.0f + 64, SELECT_TILE_BOX_WIDTH, 50.0f);

#if SAVE_MODE
	mBtnSavePallete = new SButton;
	mBtnSavePallete->init("팔레트 저장 버튼", 400, 950, GDIPLUSMANAGER->clone(IMGCLASS->MapBtnNone));
	mBtnSavePallete->setClickDownEvent([this](GameUI* ui) {
		int saveX = mBaseSprite->getMaxFrameX() + 1;
		int saveY = mBaseSprite->getMaxFrameY() + 1;
		tagTileDef* mVSRaveMode = new tagTileDef[saveX * saveY];
		int i = 0;
		for (int y = 0; y < saveY; y++) {
			for (int x = 0; x < saveX; x++) {
				mVSRaveMode[i++] = mVSaveMode[y][x];
			}
		}

		SaveFile<tagTileDef*>("Resources/Map/temp_map.map", mVSRaveMode, sizeof(tagTileDef) * saveX * saveY);
	});
	UIMANAGER->addUi(mBtnSavePallete);
#endif

	UIMANAGER->addUi(mTilePaletteScrollBox);
	UIMANAGER->addUi(mWorkBoardScrollBox);
	UIMANAGER->addUi(mCurCtrlBox);
	UIMANAGER->addUiList((GameUI**)mBtnCtrlList, 5);
	UIMANAGER->addUi(mBtnSave);
	UIMANAGER->addUi(mBtnBack);
	UIMANAGER->addUi(mBtnLoad);
	UIMANAGER->addUi(mRBtnSelectMapType);
	UIMANAGER->addUi(mSelectTileBox);
	UIMANAGER->addUi(mInputFileNameBox);

	for (int i = 0; i < mAllWorkBoardCount; i++) {
		mVCurWorkTile.push_back(tagTile());
	}

	return S_OK;
}

void MapToolScene::update(void)
{
	UIMANAGER->update();
	mInputFileNameBox->update();
	if (mCurCtrl == MC_OBJECT_GROUP) {
		if (mSelectWorkFrom.ORDER == -1) return;
		tagTile& wTile = mVCurWorkTile[mSelectWorkFrom.ORDER];
		int curKey = KEYMANAGER->getCurKeyDown();
		if (curKey == -1) return;

		if (curKey >= 48 && curKey <= 57) {
			mObjectGroupIndex = curKey - 48;
			GDIPLUSMANAGER->drawTextToBitmap(mCurCtrlBox->getImgGp()->getBitmap(), to_wstring(mObjectGroupIndex), 12.0f, CR_WHITE);
			mCurCtrlBox->getImgGp()->rebuildChachedBitmap();
		}
	}
#if SAVE_MODE
	if (KEYMANAGER->isOnceKeyDown('1')) {
		string curType = mInputFileNameBox->getInputText();
		for (int y = mSelectPYIndex; y <= mSelectPToYIndex; y++) {
			for (int x = mSelectPXIndex; x <= mSelectPToXIndex; x++) {
				OBJECT obj = mVSaveMode[y][x].getObjectByStr(curType);

				if (obj != OBJ_NULL) {
					mVSaveMode[y][x].IsInit = true;
					mVSaveMode[y][x].Object = obj;
					mVSaveMode[y][x].IsCanMove = false;
					mVSaveMode[y][x].ObjectFrameX = x;
					mVSaveMode[y][x].ObjectFrameY = y;

					mVSaveMode[y][x].Terrain = TR_NULL;

					Bitmap* tempbit = mBaseSprite->getFrameBitmapToIndex(x, y, 0, 0);
					Color tempColor;
					bool isOverrayTerrain = false;
					for (int i = 0; i < tempbit->GetHeight(); i++) {
						for (int j = 0; j < tempbit->GetWidth(); j++) {
							tempbit->GetPixel(i, j, &tempColor);
							BYTE a = tempColor.GetAlpha();
							if (a < (BYTE)150) {
								isOverrayTerrain = true;
								break;
							}
						};
						if (isOverrayTerrain) break;
					};

					mVSaveMode[y][x].IsOverrayTerrain = isOverrayTerrain;
					mVSaveMode[y][x].IsOverrayObject = false;

					LOG::d(curType + " 등록");
				}
				else {
					mVSaveMode[y][x].IsInit = false;
					LOG::e("입력값을 확인해주세요");
					return;
				}
			}
		}
		rebuild();
	}

	if (KEYMANAGER->isOnceKeyDown('4')) {
		string curType = mInputFileNameBox->getInputText();
		for (int y = mSelectPYIndex; y <= mSelectPToYIndex; y++) {
			for (int x = mSelectPXIndex; x <= mSelectPToXIndex; x++) {
				TERRAIN tr = mVSaveMode[y][x].getTerrainByStr(curType);
				if (tr != TR_NULL) {
					mVSaveMode[y][x].Terrain = tr;
					mVSaveMode[y][x].IsInit = true;
					mVSaveMode[y][x].IsOverrayTerrain = false;
					mVSaveMode[y][x].IsOverrayObject = false;
					mVSaveMode[y][x].TerrainFrameX = x;
					mVSaveMode[y][x].TerrainFrameY = y;
					mVSaveMode[y][x].Object = OBJ_NULL;
					mVSaveMode[y][x].ObjectFrameX = -1;
					mVSaveMode[y][x].ObjectFrameY = -1;
					LOG::d(curType + " 등록");
				}
				else {
					mVSaveMode[y][x].IsInit = false;
					LOG::e("입력값을 확인해주세요");
					return;
				}
			}
		}

		rebuild();
	}
#endif

#if SAVE_MODE
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) {
		mTilePaletteScrollBox->toggleShowingSubImg();
		mWorkBoardScrollBox->toggleShowingSubImg();
	}
#endif
}

void MapToolScene::render(void)
{
	UIMANAGER->render();

	if (bShowingPBoxRecF) {
		GDIPLUSMANAGER->drawRectF(getMemDc(), mPaletteSelectRectF, Color(255, 0, 0));
	}

	if (mCurCtrl == MC_OBJECT_GROUP) {
		GDIPLUSMANAGER->drawRectF(getMemDc(), mWorkboardSelectRectF, CR_YELLOW);
	}

}

void MapToolScene::saveMap()
{
	string fileName = mInputFileNameBox->getInputText();

	if (fileName.size() > 0) {
		int realX = mXWorkBoardCount - 1;
		int realY = mYWorkBoardCount - 1;

		for (int x = 0; x < mXWorkBoardCount; x++) {
			if (mVCurWorkTile[x].Terrain == TR_NULL && mVCurWorkTile[x].Object[0] == OBJ_NULL) {
				realX = x;
				break;
			}
		}

		for (int y = 0, index = 0; y < mAllWorkBoardCount; y += mXWorkBoardCount, index++) {
			if (mVCurWorkTile[y].Terrain == TR_NULL && mVCurWorkTile[y].Object[0] == OBJ_NULL) {
				realY = index;
				break;
			}
		}

		vector<tagTile> a;
		tagTile* saveMap = new tagTile[realX * realY];

		for (int y = 0, index = 0; y < realY; y++) {
			for (int x = 0; x < realX; x++, index++) {
				int indexY = y * mXWorkBoardCount;
				saveMap[index] = mVCurWorkTile[x + indexY];
				a.push_back(saveMap[index]);
			}
		}

		mMapTileInfo.XCount = realX;
		mMapTileInfo.YCount = realY;
		mMapTileInfo.FileName = fileName;
		mMapTileInfo.FilePath = MAP_FILE_PATH + fileName;

		MAPTILEMANAGER->makeMap(saveMap, mMapTileInfo);
	}

}

void MapToolScene::loadMap()
{
	mMapTileInfo = MAPTILEMANAGER->findInfo(mInputFileNameBox->getInputText());
#if CHANGE_MODE
	tagTile* original = new tagTile[mMapTileInfo.XCount * mMapTileInfo.YCount];
	LoadFile<tagTile*>(mMapTileInfo.FilePath.c_str(), original, sizeof(tagTile) *  mMapTileInfo.XCount * mMapTileInfo.YCount);
	tagTile** mLoadMapTile = new tagTile*[mMapTileInfo.YCount];
	int i = 0;
	for (int y = 0; y < mMapTileInfo.YCount; y++) {
		mLoadMapTile[y] = new tagTile[mMapTileInfo.XCount];
		for (int x = 0; x < mMapTileInfo.XCount; x++) {
			mLoadMapTile[y][x] = tagTile();
			mLoadMapTile[y][x].save(original[i++]);
		}
	}
# else
	tagTile** mLoadMapTile = MAPTILEMANAGER->findMapTile(mInputFileNameBox->getInputText());
#endif
	GDIPLUSMANAGER->drawGridLine(mWorkBoardScrollBox->getContent(), mTileSize, mTileSize);

	for (int y = 0; y < mMapTileInfo.YCount; y++) {
		for (int x = 0; x < mMapTileInfo.XCount; x++) {
			int index = x + (y * mXWorkBoardCount);

			RectF rcF = RectFMake(x * mTileSize, y * mTileSize, mTileSize, mTileSize);
			auto& curLoadT = mLoadMapTile[y][x];


			mVCurWorkTile[index] = curLoadT;
			if (curLoadT.Terrain != TR_NULL) {
				mWorkBoardScrollBox->getContent()->coverBitmap(
					(x * mTileSize),
					(y * mTileSize),
					mPalette[curLoadT.TerrainFrameY][curLoadT.TerrainFrameX].getBitmap()
				);
			}

			for (int i = 0; i < OBJ_C; i++) {
				if (curLoadT.Object[i] != OBJ_NULL) {
					mWorkBoardScrollBox->getContent()->overlayBitmap(
						(x * mTileSize),
						(y * mTileSize),
						mPalette[curLoadT.ObjectFrameY[i]][curLoadT.ObjectFrameX[i]].getBitmap()
					);
				}
			}

			GDIPLUSMANAGER->drawRectFToBitmap(mWorkBoardScrollBox->getSubImgGp()->getBitmap(), rcF, curLoadT.IsCanMove ? CR_A_BLUE : CR_A_RED);
			GDIPLUSMANAGER->drawTextToBitmap(mWorkBoardScrollBox->getSubImgGp()->getBitmap(), to_wstring(curLoadT.ObjectLevel[0]), rcF, 15.0f, CR_YELLOW);
		}
	}

	mWorkBoardScrollBox->clipingContentArea();
}

void MapToolScene::rebuild()
{
#if SAVE_MODE
	mTilePaletteScrollBox->getSubImgGp()->clear();
	for (int y = 0; y < mBaseSprite->getMaxFrameY() + 1; y++) {
		for (int x = 0; x < mBaseSprite->getMaxFrameX() + 1; x++) {
			Color msgColor;
			string msg;
			Color rectBg;
			RectF curRectF = RectFMake(x * mTileSize, y * mTileSize, mTileSize, mTileSize);

			if (!mVSaveMode[y][x].IsInit) {
				rectBg = CR_A_YELLOW;
				msgColor = CR_RED;
				msg = "!not init!";
			}
			else if (mVSaveMode[y][x].Terrain != TR_NULL && mVSaveMode[y][x].Object != OBJ_NULL) {
				rectBg = CR_A_YELLOW;
				msgColor = CR_RED;
				msg = "!error!";
			}
			else if (mVSaveMode[y][x].Terrain == TR_NULL && mVSaveMode[y][x].Object == OBJ_NULL) {
				rectBg = CR_A_YELLOW;
				msgColor = CR_RED;
				msg = "!error2!";
			}
			else {
				rectBg = mVSaveMode[y][x].IsCanMove ? CR_A_BLUE : CR_A_RED;
				if (mVSaveMode[y][x].Terrain != TR_NULL) {
					msgColor = CR_WHITE;
					msg = "Terrain";
				}

				if (mVSaveMode[y][x].Object != OBJ_NULL) {
					msgColor = CR_WHITE;
					msg = mVSaveMode[y][x].IsOverrayTerrain ? "OBJ - T" : "OBJ";
				}
			}

			GDIPLUSMANAGER->drawRectFToBitmap(
				mTilePaletteScrollBox->getSubImgGp()->getBitmap(),
				curRectF,
				rectBg);

			GDIPLUSMANAGER->drawTextToBitmap(
				mTilePaletteScrollBox->getSubImgGp()->getBitmap(),
				msg,
				curRectF,
				10.0f,
				msgColor);
		}
		mTilePaletteScrollBox->clipingContentArea();
	}
#endif
}

bool MapToolScene::IsAreadyWorkTileDrag(TINDEX tileIndex)
{
	for (mViDragWorkTileIndex = mVDragWorkTileIndex.begin(); mViDragWorkTileIndex != mVDragWorkTileIndex.end(); mViDragWorkTileIndex++) {
		if (tileIndex.X == mViDragWorkTileIndex->X && tileIndex.Y == mViDragWorkTileIndex->Y) {
			return true;
		}
	}

	return false;
}

void MapToolScene::release(void)
{
}
