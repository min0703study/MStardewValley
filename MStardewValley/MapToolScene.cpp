#include "Stdafx.h"
#include "MapToolScene.h"

#define SAMPLE_SCROLL_BOX_WIDTH		(WINSIZE_X * 0.25f)
#define SAMPLE_SCROLL_BOX_HEIGHT	(WINSIZE_Y * 0.5f)

#define WORK_SCROLL_BOX_WIDTH		(WINSIZE_X * 0.75f)
#define WORK_SCROLL_BOX_HEIGHT		WINSIZE_R_Y

#define SELECT_CTRL_BOX_X		0
#define SELECT_CTRL_BOX_Y		(WINSIZE_Y * 0.5f) + 64

#define SELECT_CTRL_BOX_WIDTH		(WINSIZE_Y * 0.4f - 100.0f)
#define SELECT_CTRL_BOX_HEIGHT		(WINSIZE_Y * 0.4f - 100.0f)

#define SAVE_BTN_X		0
#define SAVE_BTN_Y		SELECT_CTRL_BOX_Y + SELECT_CTRL_BOX_HEIGHT

HRESULT MapToolScene::init(void)
{
	mTileSize = TILE_SIZE;

	mXWorkBoardCount = 30;
	mYWorkBoardCount = 30;

	mWorkBoardAllCount = mXWorkBoardCount * mYWorkBoardCount;

	mCurCtrl = MC_DRAW_ONE;
	mCurPaletteType = MS_MINE_1TO30;

	mCurPalette = MAPPALETTE->getBaseSprite(eMapSprite::MS_MINE_1TO30);
	MAPPALETTE->findTileNodeLIst(IMGCLASS->MapMines1To30, mCurTilePalette);

#if SAVE_MODE
	mTempPalette = MAPPALETTE->getBaseSprite(eMapSprite::MS_OUTDOOR_SPRING);
	mVSaveMode = new tagTile*[mTempPalette->getMaxFrameY()];
	mVSaveX = mTempPalette->getMaxFrameX() + 1;
	mVSaveY = mTempPalette->getMaxFrameY() + 1;
	for (int i = 0; i < mVSaveY; i++) {
		mVSaveMode[i] = new tagTile[mVSaveX];
		for (int x = 0;x < mVSaveX; x++) {
			mVSaveMode[i][x] = tagTile();
		}
	}
#endif

	mMapTileInfo.MapType = eMapType::MT_MINE;

	//타일 팔레트
	mTilePaletteScrollBox = new ScrollBox;
	mTilePaletteScrollBox->init("맵툴 팔레트 스크롤 박스", 0, 64, SAMPLE_SCROLL_BOX_WIDTH, SAMPLE_SCROLL_BOX_HEIGHT, mCurPalette, XS_LEFT, YS_TOP);
	mTilePaletteScrollBox->setContentClickUpEvent([this](GameUI* ui) {
		mCurSelectRectF =
			RectFMake(
				mCurSelectRectF.GetLeft(), mCurSelectRectF.GetTop(),
				mTileSize * (mSelectTileToXIndex - mSelectTileXIndex + 1), mTileSize * (mSelectTileToYIndex - mSelectTileYIndex + 1));

		((ScrollBox*)mSelectTileBox)->getContent()->coverBitmapCenter(MAPPALETTE->getBitmap(
			mCurPaletteType,
			mSelectTileXIndex,
			mSelectTileYIndex,
			mSelectTileToXIndex - mSelectTileXIndex,
			mSelectTileToYIndex - mSelectTileYIndex));
		mSelectTileBox->clipingContentArea();
	});
	mTilePaletteScrollBox->setContentClickDownEvent([this](GameUI* ui) {
		mCurCtrl = eMapToolCtrl::MC_DRAW_ONE;
		mWorkTileXIndex = mWorkTileYIndex = 0;
		mSelectTileToXIndex = 0;
		mSelectTileToYIndex = 0;
		mSelectTileXIndex = mTilePaletteScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;
		mSelectTileYIndex = mTilePaletteScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;

#if SAVE_MODE
		mVSaveMode[mSelectTileYIndex][mSelectTileXIndex].toString();
#endif
	});
	mTilePaletteScrollBox->setContentMouseOverEvent([this](GameUI* ui) {
		bIsShowingSelectRecF = true;
		int indexX = mTilePaletteScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;
		int indexY = mTilePaletteScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;

		int indexX2 = mTilePaletteScrollBox->getContentAreaRelXToX(_ptMouse.x) - mTilePaletteScrollBox->getContentAreaAbsXToX(_ptMouse.x);
		int indexY2 = mTilePaletteScrollBox->getContentAreaRelYToY(_ptMouse.y) - mTilePaletteScrollBox->getContentAreaAbsYToY(_ptMouse.y);

		mCurSelectRectF =
			RectFMake(
				mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + (indexX * mTileSize) - indexX2,
				mTilePaletteScrollBox->getContentAreaRectF().GetTop() + (indexY * mTileSize) - indexY2,
				mTileSize, mTileSize);
	});
	mTilePaletteScrollBox->setContentMouseOffEvent([this](GameUI* ui) {
		bIsShowingSelectRecF = false;
	});
	mTilePaletteScrollBox->setContentDragEvent([this](GameUI* ui) {
		mSelectTileToXIndex = mTilePaletteScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;
		mSelectTileToYIndex = mTilePaletteScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;

		mCurSelectRectF =
			RectFMake(
				mCurSelectRectF.GetLeft(), mCurSelectRectF.GetTop(),
				mTileSize * (mSelectTileToXIndex - mSelectTileXIndex + 1),
				mTileSize * (mSelectTileToYIndex - mSelectTileYIndex + 1));
	});

	//작업 영역
	ImageGp* tempWorkBoard = new ImageGp;
	tempWorkBoard->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(mTileSize * mXWorkBoardCount, mTileSize * mYWorkBoardCount));
	GDIPLUSMANAGER->drawGridLine(tempWorkBoard, mTileSize, mTileSize);
	mWorkBoardScrollBox = new ScrollBox;
	mWorkBoardScrollBox->init("작업 영역 스크롤 상자", SAMPLE_SCROLL_BOX_WIDTH, 0, WORK_SCROLL_BOX_WIDTH, WORK_SCROLL_BOX_HEIGHT, tempWorkBoard, XS_LEFT, YS_TOP);
	mWorkBoardScrollBox->setContentClickDownEvent([this](GameUI* ui) {
		switch (mCurCtrl) {
		case MC_ERASER: {
			int wIndexY = mWorkBoardScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;
			int wIndexX = mWorkBoardScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;
			int wIndex = wIndexX + wIndexY * mXWorkBoardCount;

			tagTile& wTile = mVCurWorkTile[wIndex];

			wTile.Terrain = TR_NULL;
			wTile.Object = OBJ_NULL;
			wTile.IsInit = false;
			wTile.IsCanMove = false;

			((ScrollBox*)ui)->getContent()->coverBitmap(
				(wIndexX * mTileSize),
				(wIndexY * mTileSize),
				GDIPLUSMANAGER->getBlankWorkBoard(TILE_SIZE, TILE_SIZE)
			);

			mWorkBoardScrollBox->clipingContentArea();
		}
						break;
		case MC_DRAW_ONE: {
			int wIndexY = mWorkBoardScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;
			int wIndexX = mWorkBoardScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;

			if (mWorkTileXIndex == x && mWorkTileYIndex == y) {
				//같은 타일 작업할때
			}
			else {
				int mCurWIndexY = wIndexY;
				for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++, mCurWIndexY++) {
					int mCurWIndexX = wIndexX;
					for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++, mCurWIndexX++) {
						int wIndex = mCurWIndexX + mCurWIndexY * mXWorkBoardCount;
						int pIndex = x + y * (mCurPalette->getMaxFrameX() + 1);

						tagTile& wTile = mVCurWorkTile[wIndex];
						tagTile& pTile = *mCurTilePalette[pIndex];

						if (pTile.Terrain != TR_NULL) {
							if (wTile.Object != OBJ_NULL) {
								if (!pTile.IsOverrayTerrain) {
									wTile.Object = OBJ_NULL;
								}
							}

							wTile.Terrain = pTile.Terrain;
							wTile.TerrainFrameX = pTile.TerrainFrameX;
							wTile.TerrainFrameY = pTile.TerrainFrameY;
							wTile.IsInit = pTile.IsInit;
						}
						else if (pTile.Object != OBJ_NULL) {
							if (pTile.IsOverrayTerrain) {
								if (wTile.Terrain == TR_NULL) {
									continue;
								}
							}

							wTile.Object = pTile.Object;
							wTile.ObjectFrameX = pTile.ObjectFrameX;
							wTile.ObjectFrameY = pTile.ObjectFrameY;
							wTile.IsInit = pTile.IsInit;
						}

						if (wTile.Terrain != TR_NULL) {
							((ScrollBox*)ui)->getContent()->coverBitmap(
								(mCurWIndexX * mTileSize),
								(mCurWIndexY * mTileSize),
								MAPPALETTE->getPalette(mCurPaletteType)[wTile.TerrainFrameY][wTile.TerrainFrameX].getBitmap()
							);
						}

						if (wTile.Object != OBJ_NULL) {
							((ScrollBox*)ui)->getContent()->overlayBitmap(
								(mCurWIndexX * mTileSize),
								(mCurWIndexY * mTileSize),
								MAPPALETTE->getPalette(mCurPaletteType)[wTile.ObjectFrameY][wTile.ObjectFrameX].getBitmap()
							);
						}

						wTile.toString();
					}
				}

				mWorkBoardScrollBox->clipingContentArea();
			}
		}
						  break;
		}
	});

	//버튼 - 그리기 도구
	mBtnEraser = new SButton;
	mBtnEraser->init("지우개 버튼", 400, 601, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnEraser), XS_LEFT, YS_TOP);
	mBtnEraser->setClickDownEvent([this](GameUI* ui) {
#if SAVE_MODE
		mVSRaveMode = new tagTile[mVSaveX * mVSaveY];
		int i = 0;
		for (int y = 0; y < mVSaveY; y++) {
			for (int x = 0; x < mVSaveX; x++) {
				mVSRaveMode[i++] = mVSaveMode[y][x];
			}
		}
		SaveFile<tagTile*>("Resources/Map/test.map", mVSRaveMode, sizeof(tagTile) * mVSaveX * mVSaveY);
#else
		saveMap();
#endif
	});

	mBtnSelect = new SButton;
	mBtnSelect->init("선택 버튼", 400, 674, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnSelect), XS_LEFT, YS_TOP);
	mBtnSelect->setClickDownEvent([this](GameUI* ui) {
#if SAVE_MODE
		mVSRaveMode = new tagTile[mVSaveX * mVSaveY];
		LoadFile<tagTile*>("Resources/Map/test.map", mVSRaveMode, sizeof(tagTile) *  mVSaveX * mVSaveY);

		int i = 0;
		for (int y = 0; y < mVSaveY; y++) {
			for (int x = 0; x < mVSaveX; x++) {
				mVSaveMode[y][x] = mVSRaveMode[i++];
			}
		}
#endif
	
	});

	//버튼 - 저장, 불러오기
	mBtnSave = new SButton;
	mBtnSave->init("저장 버튼", 20, 948 + 64, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnSave), XS_LEFT, YS_TOP);
	mBtnSave->setClickDownEvent([this](GameUI* ui) {
#if SAVE_MODE
	SaveFile<tagTile**>("Resources/Map/test.map", mVSaveMode, sizeof(tagTile) * mVSaveX * mVSaveY);
#else
		saveMap();
#endif
	});

	mBtnLoad = new SButton;
	mBtnLoad->init("불러오기 버튼", 200, 948 + 64, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnLoad), XS_LEFT, YS_TOP);
	mBtnLoad->setClickDownEvent([this](GameUI* ui) {
#if SAVE_MODE
		LoadFile<tagTile**>("Resources/Map/test.map", mVSaveMode, sizeof(tagTile) *  mVSaveX * mVSaveY);
#else
		loadMap();
#endif
	});

	mRBtnSelectMapType = new RadioButton;
	mRBtnSelectMapType->init(300, 0, 64, 64, new ImageGp*[3]{
		GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnSelectMine), 
		GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnSelectFarm),
		GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnSelectInterior) }, 3);
	mRBtnSelectMapType->setClickDownEvent([this](GameUI* ui) {
		mCurPaletteType = (eMapSprite)(((RadioButton*)ui)->changeSelectIndex());
		mCurPalette = MAPPALETTE->getBaseSprite(mCurPaletteType);
		mTilePaletteScrollBox->changeContent(mCurPalette);
	});
	
	mBtnBack = new SButton;
	mBtnBack->init("뒤로가기 버튼",0,0, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnBack), XS_LEFT, YS_TOP);

	ImageGp* tempSelectTile = new ImageGp;
	tempSelectTile->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(SELECT_CTRL_BOX_WIDTH, SELECT_CTRL_BOX_HEIGHT));

	mSelectTileBox = new ScrollBox;
	mSelectTileBox->init("현재 타일 스크롤 박스", SELECT_CTRL_BOX_X, SELECT_CTRL_BOX_Y, SELECT_CTRL_BOX_WIDTH, SELECT_CTRL_BOX_HEIGHT, tempSelectTile, XS_LEFT, YS_TOP);
	mSelectTileBox->scrollToCenter();

	mInputFileNameBox = new EditText;
	mInputFileNameBox->init("파일 이름 입력창", 0, 875.0f + 64, SELECT_CTRL_BOX_WIDTH, 50.0f, XS_LEFT, YS_TOP);

	for (int i = 0; i < mWorkBoardAllCount; i++) {
		mVCurWorkTile.push_back(tagTile(i));
	}

	UIMANAGER->addUi(mTilePaletteScrollBox);
	UIMANAGER->addUi(mWorkBoardScrollBox);
	UIMANAGER->addUi(mBtnEraser);
	UIMANAGER->addUi(mBtnSelect);
	UIMANAGER->addUi(mBtnSave);
	UIMANAGER->addUi(mBtnBack);
	UIMANAGER->addUi(mBtnLoad);
	UIMANAGER->addUi(mRBtnSelectMapType);
	UIMANAGER->addUi(mSelectTileBox);
	UIMANAGER->addUi(mInputFileNameBox);

	return S_OK;
}

void MapToolScene::update(void)
{
	UIMANAGER->update();
	mInputFileNameBox->update();

#if SAVE_MODE
	if (KEYMANAGER->isOnceKeyDown('1')) {
		mInputFileNameBox->changeEditMode(false);
		string curType = mInputFileNameBox->getInputText();
		
		for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++) {
			for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++) {
				if (curType == "tree") {
					mVSaveMode[y][x].Object = OBJ_TREE;
					mVSaveMode[y][x].IsOverrayTerrain = true;
				}
				else if (curType == "tree_attack") {
					mVSaveMode[y][x].Object = OBJ_TREE_ATTACK;
				}
				else if (curType == "door") {
					mVSaveMode[y][x].Object = OBJ_DOOR;
				}
				else if (curType == "building") {
					mVSaveMode[y][x].Object = OBJ_BUILDING;
				}
				else if (curType == "wall") {
					mVSaveMode[y][x].Object = OBJ_WALL;
				}
				else if (curType == "fence") {
					mVSaveMode[y][x].Object = OBJ_FENCE;
				}
				else if (curType == "obj") {
					mVSaveMode[y][x].Object = OBJ_OBJECT;
				}

				mVSaveMode[y][x].IsInit = true;

				mVSaveMode[y][x].ObjectFrameX = x;
				mVSaveMode[y][x].ObjectFrameY = y;
			}
		}
		mInputFileNameBox->changeEditMode(true);
	}

	if (KEYMANAGER->isOnceKeyDown('2')) {
		string a = mInputFileNameBox->getInputText();
		for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++) {
			for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++) {
				mVSaveMode[y][x].IsCanMove = a == "true";
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('3')) {
		string a = mInputFileNameBox->getInputText();
		for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++) {
			for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++) {
				mVSaveMode[y][x].IsOverrayTerrain = a == "true";
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('4')) {
		string a = mInputFileNameBox->getInputText();
		if (a == "normal") {
			for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++) {
				for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++) {
					mVSaveMode[y][x].Terrain = TR_NORMAL;
					mVSaveMode[y][x].TerrainFrameX = x;
					mVSaveMode[y][x].TerrainFrameY = y;
				}
			}
		}

		if (a == "grass") {
			for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++) {
				for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++) {
					mVSaveMode[y][x].Terrain = TR_GRASS;
					mVSaveMode[y][x].TerrainFrameX = x;
					mVSaveMode[y][x].TerrainFrameY = y;
				}
			}
		}

		if (a == "sand") {
			for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++) {
				for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++) {
					mVSaveMode[y][x].Terrain = TR_SAND;
					mVSaveMode[y][x].TerrainFrameX = x;
					mVSaveMode[y][x].TerrainFrameY = y;
				}
			}
		}

		if (a == "snow") {
			for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++) {
				for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++) {
					mVSaveMode[y][x].Terrain = TR_SNOW;
					mVSaveMode[y][x].TerrainFrameX = x;
					mVSaveMode[y][x].TerrainFrameY = y;
				}
			}
		}

		if (a == "water") {
			for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++) {
				for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++) {
					mVSaveMode[y][x].Terrain = TR_WATER;
					mVSaveMode[y][x].TerrainFrameX = x;
					mVSaveMode[y][x].TerrainFrameY = y;
				}
			}
		}

		if (a == "wood") {
			for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++) {
				for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++) {
					mVSaveMode[y][x].Terrain = TR_WOOD;
					mVSaveMode[y][x].TerrainFrameX = x;
					mVSaveMode[y][x].TerrainFrameY = y;
				}
			}
		}

		for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++) {
			for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++) {
				mVSaveMode[y][x].IsInit = true;
			}
		}

		for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++) {
			for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++) {
				mVSaveMode[y][x].Object= OBJ_NULL;
			}
		}
	}

#endif
}

void MapToolScene::render(void)
{
	UIMANAGER->render();
	if (bIsShowingSelectRecF) {
		GDIPLUSMANAGER->drawRectF(getMemDc(), mCurSelectRectF, Color(255, 0, 0));
	}

}

void MapToolScene::release(void)
{
}

void MapToolScene::saveMap()
{
	int realX = 0;
	int realY = 0;

	for (int x = 0; x < mXWorkBoardCount; x++) {
		if (!mVCurWorkTile[x].IsInit) {
			realX = x;
			break;
		}
	}

	for (int y = 0; y < mYWorkBoardCount; y += realX) {
		if (!mVCurWorkTile[y].IsInit) {
			realY = y;
			break;
		}
	}

	int realCount = realX * realY;

	tagTile* thearray = new tagTile[realCount];
	int allCount = mXWorkBoardCount * mYWorkBoardCount;
	int index = 0;
	for (int y = 0; y < mXWorkBoardCount* realY; y += mXWorkBoardCount) {
		for (int x = 0; x < realX; x++) {
			mVCurWorkTile[x + y].Index = index;
			thearray[index] = mVCurWorkTile[x + y];
			index += 1;
		}
	}

	mMapTileInfo.XCount = realX;
	mMapTileInfo.YCount = realY;
	mMapTileInfo.FileName = mInputFileNameBox->getInputText();

	MAPTILEMANAGER->addNewMap(thearray, mMapTileInfo);
}

void MapToolScene::loadMap()
{
	mMapTileInfo = MAPTILEMANAGER->findInfo(mInputFileNameBox->getInputText());
	tagTile** mLoadMapTile = MAPTILEMANAGER->findTile(mInputFileNameBox->getInputText());

	for (int y = 0; y < mMapTileInfo.YCount; y++) {
		for (int x = 0; x < mMapTileInfo.XCount; x++) {
			int index = x + (y * mXWorkBoardCount);
			
			auto& curLoadT = mLoadMapTile[y][x];

			mVCurWorkTile[index] = curLoadT;
			if (curLoadT.Terrain != TR_NULL) {
				mWorkBoardScrollBox->getContent()->coverBitmap(
					(x * mTileSize),
					(y * mTileSize),
					MAPPALETTE->getPalette(mCurPaletteType)[curLoadT.TerrainFrameY][curLoadT.TerrainFrameX].getBitmap()
				);
			}

			if (curLoadT.Object != OBJ_NULL) {
				mWorkBoardScrollBox->getContent()->overlayBitmap(
					(x * mTileSize),
					(y * mTileSize),
					MAPPALETTE->getPalette(mCurPaletteType)[curLoadT.ObjectFrameY][curLoadT.ObjectFrameX].getBitmap()
				);
			}
		}
	}

	mWorkBoardScrollBox->clipingContentArea();
}

void MapToolScene::eraserTile()
{
	mCurCtrl = MC_ERASER;
	mSelectTileBox->getContent()->coverBitmapCenter(mBtnEraser->getImgGp()->getBitmapClone());
	mSelectTileBox->clipingContentArea();
}

void MapToolScene::updateMapStruct() {
	for (vector<tagTile>::iterator iter = mVCurWorkTile.begin(); iter != mVCurWorkTile.end(); iter++) {
		if ((*iter).Terrain != TR_NULL) {
			int pIndex = (*iter).TerrainFrameX + (*iter).TerrainFrameY * (mCurPalette->getMaxFrameX() + 1);
			(*iter).Terrain = mCurTilePalette[pIndex]->Terrain;
			(*iter).TerrainFrameX = mCurTilePalette[pIndex]->TerrainFrameX;
			(*iter).TerrainFrameY = mCurTilePalette[pIndex]->TerrainFrameY;
			(*iter).IsCanMove = mCurTilePalette[pIndex]->IsCanMove;
		}

		if ((*iter).Object != TR_NULL) {
			int pIndex = (*iter).ObjectFrameX + (*iter).ObjectFrameY * (mCurPalette->getMaxFrameX() + 1);
			(*iter).Object = mCurTilePalette[pIndex]->Object;
			(*iter).ObjectFrameX = mCurTilePalette[pIndex]->ObjectFrameX;
			(*iter).ObjectFrameY = mCurTilePalette[pIndex]->ObjectFrameY;
			(*iter).IsCanMove = mCurTilePalette[pIndex]->IsCanMove;
			(*iter).IsOverrayObject = mCurTilePalette[pIndex]->IsOverrayObject;
			(*iter).IsOverrayTerrain = mCurTilePalette[pIndex]->IsOverrayTerrain;
		}
	}
}
