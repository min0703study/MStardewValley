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

	mSelectTileYIndex = -1;
	mSelectTileXIndex = -1;

	mCurPaletteKey = MAPCLASS->MINE_P;
	mMapTileInfo.MapType = eMapType::MT_MINE;

	mBaseSprite = MAPPALETTEMANAGER->findBaseSprite(mCurPaletteKey);
	mPalette = MAPPALETTEMANAGER->findPalette(mCurPaletteKey);
	mCurTilePalette = MAPPALETTEMANAGER->findTileNode(mCurPaletteKey);

	//타일 팔레트
	mTilePaletteScrollBox = new ScrollBox;
	mTilePaletteScrollBox->init("맵툴 팔레트 스크롤 박스", 0, 64, SAMPLE_SCROLL_BOX_WIDTH, SAMPLE_SCROLL_BOX_HEIGHT, mBaseSprite, XS_LEFT, YS_TOP);
	mTilePaletteScrollBox->setContentClickUpEvent([this](GameUI* ui) {
		switch (mCurCtrl) {
		case MC_DRAW_ONE: case MC_DRAW_TILES: {
			mCurSelectRectF =
				RectFMake(
					mCurSelectRectF.GetLeft(), mCurSelectRectF.GetTop(),
					mTileSize * (mSelectTileToXIndex - mSelectTileXIndex + 1), mTileSize * (mSelectTileToYIndex - mSelectTileYIndex + 1));

			((ScrollBox*)mSelectTileBox)->getContent()->coverBitmapCenter(mBaseSprite->getFrameBitmapToIndex(
				mSelectTileXIndex,
				mSelectTileYIndex,
				mSelectTileToXIndex - mSelectTileXIndex,
				mSelectTileToYIndex - mSelectTileYIndex));

			mSelectTileBox->clipingContentArea();
			break;
		}}
	});
	mTilePaletteScrollBox->setContentClickDownEvent([this](GameUI* ui) {
#if DEBUG_MODE
		int tempX = mTilePaletteScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;
		int tempY = mTilePaletteScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;
		int wIndex = tempX + tempY * (mBaseSprite->getMaxFrameX() + 1);
		mCurTilePalette[wIndex]->toString();
#endif
		switch (mCurCtrl) {
		case MC_DRAW_ONE: case MC_DRAW_TILES: {
			mSelectTileXIndex = mTilePaletteScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;
			mSelectTileYIndex = mTilePaletteScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;
			mWorkTileXIndex = mWorkTileYIndex = 0;
			mSelectTileToXIndex = 0;
			mSelectTileToYIndex = 0;
			break;
		}}
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
		switch (mCurCtrl) {
		case MC_DRAW_TILES:
			break;
		case MC_DRAW_ONE:
			mSelectTileToXIndex = mTilePaletteScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;
			mSelectTileToYIndex = mTilePaletteScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;

			mCurSelectRectF =
				RectFMake(
					mCurSelectRectF.GetLeft(), mCurSelectRectF.GetTop(),
					mTileSize * (mSelectTileToXIndex - mSelectTileXIndex + 1),
					mTileSize * (mSelectTileToYIndex - mSelectTileYIndex + 1));
			break;
		}
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
			wTile.Object2 = OBJ_NULL;
			wTile.IsInit = false;
			wTile.IsCanMove = false;
			
			((ScrollBox*)ui)->getContent()->coverBitmap(
				(wIndexX * mTileSize),
				(wIndexY * mTileSize),
				GDIPLUSMANAGER->getBlankWorkBoard(TILE_SIZE, TILE_SIZE)
			);

			mWorkBoardScrollBox->clipingContentArea();
			break;
		}
		case MC_DRAW_ONE: {
			int wIndexY = mWorkBoardScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;
			int wIndexX = mWorkBoardScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;

			if (mWorkTileXIndex == x && mWorkTileYIndex == y) {
				//같은 타일 작업할때
			}
			else if (mSelectTileYIndex == -1 || mSelectTileXIndex == -1) {
				break;
			}
			else {
				int mCurWIndexY = wIndexY;
				for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++, mCurWIndexY++) {
					int mCurWIndexX = wIndexX;
					for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++, mCurWIndexX++) {
						int wIndex = mCurWIndexX + mCurWIndexY * mXWorkBoardCount;
						int pIndex = x + y * (mBaseSprite->getMaxFrameX() + 1);

						tagTile& wTile = mVCurWorkTile[wIndex];
						tagTile& pTile = *mCurTilePalette[pIndex];

						if (!pTile.IsInit) {
							LOG::e("초기화 되지 않은 타일 팔레트 입니다");
							LOG::e("x : " + to_string(x) + "y : " + to_string(y));
							break;
						}

						if (pTile.Terrain != TR_NULL) {
							if (wTile.Object != OBJ_NULL) {
								if (!wTile.IsOverrayTerrain) {
									wTile.Object = OBJ_NULL;
									wTile.Object2 = OBJ_NULL;
									wTile.IsCanMove = pTile.IsCanMove;
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
									//continue;
								}
							}

							wTile.Object = pTile.Object;
							wTile.ObjectFrameX = pTile.ObjectFrameX;
							wTile.ObjectFrameY = pTile.ObjectFrameY;
							wTile.IsOverrayTerrain = pTile.IsOverrayTerrain;
							wTile.IsInit = pTile.IsInit;
							wTile.IsCanMove = pTile.IsCanMove;
						} else if (pTile.Object2 != OBJ_NULL) {
							if (pTile.Object == OBJ_NULL) {
								//continue;
							}
							wTile.Object2 = pTile.Object2;
							wTile.Object2FrameX = pTile.Object2FrameX;
							wTile.Object2FrameY = pTile.Object2FrameY;
							wTile.IsOverrayTerrain = pTile.IsOverrayTerrain;
							wTile.IsInit = pTile.IsInit;
							wTile.IsCanMove = pTile.IsCanMove;
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

						if (wTile.Object != OBJ_NULL) {
							((ScrollBox*)ui)->getContent()->overlayBitmap(
								(mCurWIndexX * mTileSize),
								(mCurWIndexY * mTileSize),
								mPalette[wTile.ObjectFrameY][wTile.ObjectFrameX].getBitmap()
							);
						}

						if (wTile.Object2 != OBJ_NULL) {
							((ScrollBox*)ui)->getContent()->overlayBitmap(
								(mCurWIndexX * mTileSize),
								(mCurWIndexY * mTileSize),
								mPalette[wTile.Object2FrameY][wTile.Object2FrameX].getBitmap()
							);
						}
					}
				}

				mWorkBoardScrollBox->clipingContentArea();
			}
			break;
		}
		}
	});
	mWorkBoardScrollBox->setContentDragEvent([this](GameUI* ui) {
		switch (mCurCtrl) {
		case MC_DRAW_TILES: {
			int wIndexY = mWorkBoardScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;
			int wIndexX = mWorkBoardScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;

			bool isAreadyWorkTile = false;
			for (miWorkTileIndexList = mWorkTileIndexList.begin(); miWorkTileIndexList != mWorkTileIndexList.end(); miWorkTileIndexList++) {
				if (wIndexX == miWorkTileIndexList->X && wIndexY == miWorkTileIndexList->Y) {
					isAreadyWorkTile = true;
					break;
				}
			}

			if (isAreadyWorkTile) break;

			mWorkTileIndexList.push_back(TINDEX(wIndexX, wIndexY));

			int mCurWIndexY = wIndexY;
			for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++, mCurWIndexY++) {
				int mCurWIndexX = wIndexX;
				for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++, mCurWIndexX++) {
					int wIndex = mCurWIndexX + mCurWIndexY * mXWorkBoardCount;
					int pIndex = x + y * (mBaseSprite->getMaxFrameX() + 1);

					tagTile& wTile = mVCurWorkTile[wIndex];
					tagTile& pTile = *mCurTilePalette[pIndex];

					if (!pTile.IsInit) {
						LOG::e("초기화 되지 않은 타일 팔레트 입니다");
						LOG::e("x : " + to_string(x) + "y : " + to_string(y));
						break;
					}

					if (pTile.Terrain != TR_NULL) {
						if (wTile.Object != OBJ_NULL) {
							if (!wTile.IsOverrayTerrain) {
								wTile.Object = OBJ_NULL;
								wTile.IsCanMove = pTile.IsCanMove;
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
								//continue;
							}
						}

						wTile.Object = pTile.Object;
						wTile.ObjectFrameX = pTile.ObjectFrameX;
						wTile.ObjectFrameY = pTile.ObjectFrameY;
						wTile.IsOverrayTerrain = pTile.IsOverrayTerrain;
						wTile.IsInit = pTile.IsInit;
						wTile.IsCanMove = pTile.IsCanMove;
					}
					else if (pTile.Object2 != OBJ_NULL) {
						if (pTile.Object == OBJ_NULL) {
							//continue;
						}
						wTile.Object2 = pTile.Object2;
						wTile.Object2FrameX = pTile.Object2FrameX;
						wTile.Object2FrameY = pTile.Object2FrameY;
						wTile.IsOverrayTerrain = pTile.IsOverrayTerrain;
						wTile.IsInit = pTile.IsInit;
						wTile.IsCanMove = pTile.IsCanMove;
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

					if (wTile.Object != OBJ_NULL) {
						((ScrollBox*)ui)->getContent()->overlayBitmap(
							(mCurWIndexX * mTileSize),
							(mCurWIndexY * mTileSize),
							mPalette[wTile.ObjectFrameY][wTile.ObjectFrameX].getBitmap()
						);
					}


					if (wTile.Object2 != OBJ_NULL) {
						((ScrollBox*)ui)->getContent()->overlayBitmap(
							(mCurWIndexX * mTileSize),
							(mCurWIndexY * mTileSize),
							mPalette[wTile.Object2FrameY][wTile.Object2FrameX].getBitmap()
						);
					}
				}
			}

			mWorkBoardScrollBox->clipingContentArea();
		}
		case MC_COLLISION_TILE: {
			int wIndexY = mWorkBoardScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;
			int wIndexX = mWorkBoardScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;
			int wIndex = wIndexX + wIndexY * mXWorkBoardCount;

			bool isAreadyWorkTile = false;
			for (miWorkTileIndexList = mWorkTileIndexList.begin(); miWorkTileIndexList != mWorkTileIndexList.end(); miWorkTileIndexList++) {
				if (wIndexX == miWorkTileIndexList->X && wIndexY == miWorkTileIndexList->Y) {
					isAreadyWorkTile = true;
					break;
				}
			}

			if (isAreadyWorkTile) break;
			
			mWorkTileIndexList.push_back(TINDEX(wIndexX, wIndexY));

			tagTile& wTile = mVCurWorkTile[wIndex];

			wTile.IsCanMove = false;
			mWorkBoardScrollBox->clipingContentArea();
			break;
		}
		case MC_MOVABLE_TILE: {
			int wIndexY = mWorkBoardScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;
			int wIndexX = mWorkBoardScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;
			int wIndex = wIndexX + wIndexY * mXWorkBoardCount;

			bool isAreadyWorkTile = false;
			for (miWorkTileIndexList = mWorkTileIndexList.begin(); miWorkTileIndexList != mWorkTileIndexList.end(); miWorkTileIndexList++) {
				if (wIndexX == miWorkTileIndexList->X && wIndexY == miWorkTileIndexList->Y) {
					isAreadyWorkTile = true;
					break;
				}
			}

			if (isAreadyWorkTile) break;

			mWorkTileIndexList.push_back(TINDEX(wIndexX, wIndexY));

			tagTile& wTile = mVCurWorkTile[wIndex];

			wTile.IsCanMove = true;
			mWorkBoardScrollBox->clipingContentArea();
			break;
		}
		}
	});
	mWorkBoardScrollBox->setContentClickUpEvent([this](GameUI* ui) {
		switch (mCurCtrl) {
		case MC_DRAW_TILES: case MC_COLLISION_TILE: case MC_MOVABLE_TILE:
			mWorkTileIndexList.clear();
			break;
		}
	});

	//버튼 - 지우개 도구
	mBtnEraser = new SButton;
	mBtnEraser->init("지우개 버튼", 400, 601, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnEraser), XS_LEFT, YS_TOP);
	mBtnEraser->setClickDownEvent([this](GameUI* ui) {
		mCurCtrl = MC_ERASER;
		mSelectTileBox->getContent()->coverBitmapCenter(mBtnEraser->getImgGp()->getBitmapClone());
		mSelectTileBox->clipingContentArea();
	});

	//버튼 - 드래그 기능
	mBtnSelect = new SButton;
	mBtnSelect->init("여러개 선택 버튼", 400, 674, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnSelect), XS_LEFT, YS_TOP);
	mBtnSelect->setClickDownEvent([this](GameUI* ui) {
		mCurCtrl = MC_DRAW_TILES;
		mSelectTileBox->getContent()->coverBitmapCenter(ui->getImgGp()->getBitmapClone());
		mSelectTileBox->clipingContentArea();
	});

	//버튼 - 한개 타일 기능
	mBtnOneTile = new SButton;
	mBtnOneTile->init("하나 선택 버튼", 400, 740, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnSelect), XS_LEFT, YS_TOP);
	mBtnOneTile->setClickDownEvent([this](GameUI* ui) {
		mCurCtrl = MC_DRAW_ONE;
		mSelectTileBox->getContent()->coverBitmapCenter(ui->getImgGp()->getBitmapClone());
		mSelectTileBox->clipingContentArea();
	});

	mBtnCtrl[MC_COLLISION_TILE] = new SButton;
	mBtnCtrl[MC_COLLISION_TILE]->init("충돌 타일 버튼", 330, 674, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnCollision), XS_LEFT, YS_TOP);
	mBtnCtrl[MC_COLLISION_TILE]->setClickDownEvent(
		[this](GameUI* ui) {
		mCurCtrl = MC_COLLISION_TILE;
		mSelectTileBox->getContent()->coverBitmapCenter(ui->getImgGp()->getBitmapClone());
		mSelectTileBox->clipingContentArea();
	});

	mBtnCtrl[MC_MOVABLE_TILE] = new SButton;
	mBtnCtrl[MC_MOVABLE_TILE]->init("이동 타일 버튼", 330, 740, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnMovable), XS_LEFT, YS_TOP);
	mBtnCtrl[MC_MOVABLE_TILE]->setClickDownEvent(
		[this](GameUI* ui) {
		mCurCtrl = MC_MOVABLE_TILE;
		mSelectTileBox->getContent()->coverBitmapCenter(ui->getImgGp()->getBitmapClone());
		mSelectTileBox->clipingContentArea();
	});

	//버튼 - 저장, 불러오기
	mBtnSave = new SButton;
	mBtnSave->init("저장 버튼", 20, 948 + 40, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnSave), XS_LEFT, YS_TOP);
	mBtnSave->setClickDownEvent([this](GameUI* ui) {
		saveMap();
	});

	mBtnLoad = new SButton;
	mBtnLoad->init("불러오기 버튼", 200, 948 + 40, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnLoad), XS_LEFT, YS_TOP);
	mBtnLoad->setClickDownEvent([this](GameUI* ui) {
		loadMap();
	});

	mRBtnSelectMapType = new RadioButton;
	mRBtnSelectMapType->init(300, 0, 64, 64, new ImageGp*[3]{
		GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnSelectMine),
		GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnSelectFarm),
		GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnSelectInterior) }, 3);
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
		mVSaveMode = new tagTile*[mBaseSprite->getMaxFrameY() + 1];
		for (int i = 0; i < mBaseSprite->getMaxFrameY() + 1; i++) {
			mVSaveMode[i] = new tagTile[mBaseSprite->getMaxFrameX() + 1];
			for (int x = 0; x < mBaseSprite->getMaxFrameX() + 1; x++) {
				mVSaveMode[i][x] = tagTile();
			}
		}

		for (int y = 0; y < mBaseSprite->getMaxFrameY() + 1; y++) {
			for (int x = 0; x < mBaseSprite->getMaxFrameX() + 1; x++) {
				mVSaveMode[y][x] = (*mCurTilePalette[i++]);
			}
		}
#endif

	});

	mBtnBack = new SButton;
	mBtnBack->init("뒤로가기 버튼", 0, 0, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnBack), XS_LEFT, YS_TOP);

	ImageGp* tempSelectTile = new ImageGp;
	tempSelectTile->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(SELECT_CTRL_BOX_WIDTH, SELECT_CTRL_BOX_HEIGHT));
	mSelectTileBox = new ScrollBox;
	mSelectTileBox->init("현재 타일 스크롤 박스", SELECT_CTRL_BOX_X, SELECT_CTRL_BOX_Y, SELECT_CTRL_BOX_WIDTH, SELECT_CTRL_BOX_HEIGHT, tempSelectTile, XS_LEFT, YS_TOP);
	mSelectTileBox->scrollToCenter();

	mInputFileNameBox = new EditText;
	mInputFileNameBox->init("파일 이름 입력창", 0, 875.0f + 64, SELECT_CTRL_BOX_WIDTH, 50.0f, XS_LEFT, YS_TOP);

#if SAVE_MODE
	mBtnSavePallete = new SButton;
	mBtnSavePallete->init("팔레트 저장 버튼", 400, 950, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnNone), XS_LEFT, YS_TOP);
	mBtnSavePallete->setClickDownEvent([this](GameUI* ui) {
		int saveX = mBaseSprite->getMaxFrameX() + 1;
		int saveY = mBaseSprite->getMaxFrameY() + 1;
		tagTile* mVSRaveMode = new tagTile[saveX * saveY];
		int i = 0;
		for (int y = 0; y < saveY; y++) {
			for (int x = 0; x < saveX; x++) {
				mVSRaveMode[i++] = mVSaveMode[y][x];
			}
		}

		SaveFile<tagTile*>("Resources/Map/temp_map.map", mVSRaveMode, sizeof(tagTile) * saveX * saveY);
	});
	UIMANAGER->addUi(mBtnSavePallete);
#endif
	UIMANAGER->addUi(mTilePaletteScrollBox);
	UIMANAGER->addUi(mWorkBoardScrollBox);
	UIMANAGER->addUi(mBtnSelect);
	UIMANAGER->addUi(mBtnOneTile);
	UIMANAGER->addUi(mBtnSave);
	UIMANAGER->addUi(mBtnBack);
	UIMANAGER->addUi(mBtnCtrl[MC_COLLISION_TILE]);
	UIMANAGER->addUi(mBtnCtrl[MC_MOVABLE_TILE]);
	UIMANAGER->addUi(mBtnEraser);
	UIMANAGER->addUi(mBtnLoad);
	UIMANAGER->addUi(mRBtnSelectMapType);
	UIMANAGER->addUi(mSelectTileBox);
	UIMANAGER->addUi(mInputFileNameBox);

	for (int i = 0; i < mWorkBoardAllCount; i++) {
		mVCurWorkTile.push_back(tagTile(i));
	}

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
				if (curType == "obj") {
					mVSaveMode[y][x].Object = OBJ_OBJECT;
					mVSaveMode[y][x].IsCanMove = false;
				} else if (curType == "bed") {
					mVSaveMode[y][x].Object = OBJ_BED;
					mVSaveMode[y][x].IsCanMove = false;
				}
				else if (curType == "wall") {
					mVSaveMode[y][x].Object = OBJ_WALL;
					mVSaveMode[y][x].IsCanMove = false;
				}
				else if (curType == "fence") {
					mVSaveMode[y][x].Object = OBJ_FENCE;
					mVSaveMode[y][x].IsCanMove = false;
				}
				else if (curType == "mine_d") {
					mVSaveMode[y][x].Object = OBJ_MINE_DOOR;
					mVSaveMode[y][x].IsCanMove = false;
				}
				else if (curType == "mine_l") {
					mVSaveMode[y][x].Object = OBJ_MINE_LADDER;
					mVSaveMode[y][x].IsCanMove = false;
				}
				else if (curType == "tree") {
					mVSaveMode[y][x].Object = OBJ_TREE;
				}
				else if (curType == "tree_a") {
					mVSaveMode[y][x].Object = OBJ_TREE_ATTACK;
					mVSaveMode[y][x].IsCanMove = false;
				}
				else if (curType == "bush") {
					mVSaveMode[y][x].Object = OBJ_BUSH;
				}
				else if (curType == "flower") {
					mVSaveMode[y][x].Object = OBJ_FLOWER;
				}
				else if (curType == "building") {
					mVSaveMode[y][x].Object = OBJ_BUILDING;
					mVSaveMode[y][x].IsCanMove = false;
				}
				else if (curType == "building_d") {
					mVSaveMode[y][x].Object = OBJ_BUILDING_DOOR;
					mVSaveMode[y][x].IsCanMove = false;
				}
				else if (curType == "sale_stand") {
					mVSaveMode[y][x].Object = OBJ_SALE_STAND;
					mVSaveMode[y][x].IsCanMove = false;
				}
				else {
					LOG::e("입력값을 확인해주세요");
					break;
				}

				mVSaveMode[y][x].IsInit = true;
				mVSaveMode[y][x].ObjectFrameX = x;
				mVSaveMode[y][x].ObjectFrameY = y;

				mVSaveMode[y][x].Object2 = OBJ_NULL;
				mVSaveMode[y][x].Terrain = TR_NULL;
				mVSaveMode[y][x].IsOverrayObject = false;

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

			}
		}

		mInputFileNameBox->changeEditMode(true);
	}

	if (KEYMANAGER->isOnceKeyDown('2')) {
		string a = mInputFileNameBox->getInputText();
		for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++) {
			for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++) {
				mVSaveMode[y][x].IsCanMove = a == "t";
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
		mInputFileNameBox->changeEditMode(false);
		string curType = mInputFileNameBox->getInputText();
		for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++) {
			for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++) {
				if (curType == "normal") {
					mVSaveMode[y][x].Terrain = TR_NORMAL;
				}
				else if (curType == "grass") {
					mVSaveMode[y][x].Terrain = TR_GRASS;
				}
				else if (curType == "wood") {
					mVSaveMode[y][x].Terrain = TR_WOOD;
				}
				else if (curType == "sand") {
					mVSaveMode[y][x].Terrain = TR_SAND;
				}
				else if (curType == "snow") {
					mVSaveMode[y][x].Terrain = TR_SNOW;
				}
				else if (curType == "water") {
					mVSaveMode[y][x].Terrain = TR_WATER;
				}
				else if (curType == "crystal") {
					mVSaveMode[y][x].Terrain = TR_CRYSTAL;
				}
				else if (curType == "brick") {
					mVSaveMode[y][x].Terrain = TR_BRICK;
				}
				else if (curType == "stone") {
					mVSaveMode[y][x].Terrain = TR_STONE;
				}
				else {
					LOG::e("입력값을 확인해주세요");
					break;
				}

				mVSaveMode[y][x].IsInit = true;
				mVSaveMode[y][x].IsOverrayTerrain = false;
				mVSaveMode[y][x].Object = OBJ_NULL;
				mVSaveMode[y][x].Object2 = OBJ_NULL;
				mVSaveMode[y][x].IsOverrayObject = false;
				mVSaveMode[y][x].TerrainFrameX = x;
				mVSaveMode[y][x].TerrainFrameY = y;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('7')) {
		mInputFileNameBox->changeEditMode(false);
		string curType = mInputFileNameBox->getInputText();
		for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++) {
			for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++) {
				if (curType == "obj") {
					mVSaveMode[y][x].Object2 = OBJ_OBJECT;
					mVSaveMode[y][x].IsCanMove = false;
				}
				else if (curType == "window") {
					mVSaveMode[y][x].Object2 = OBJ_WINDOW;
					mVSaveMode[y][x].IsCanMove = false;
				}
				else if (curType == "wall") {
					mVSaveMode[y][x].Object2 = OBJ_WALL;
					mVSaveMode[y][x].IsCanMove = false;
				}
				else {
					LOG::e("입력값을 확인해주세요");
					break;
				}

				mVSaveMode[y][x].IsInit = true;
				mVSaveMode[y][x].Object2FrameX = x;
				mVSaveMode[y][x].Object2FrameY = y;
				mVSaveMode[y][x].Terrain = TR_NULL;
				mVSaveMode[y][x].Object = OBJ_NULL;
				mVSaveMode[y][x].IsOverrayTerrain = false;
				mVSaveMode[y][x].IsOverrayObject = true;

			}
		}

		mInputFileNameBox->changeEditMode(true);
	}

	if (KEYMANAGER->isOnceKeyDown('9')) {
		for (int y = mSelectTileYIndex; y <= mSelectTileToYIndex; y++) {
			for (int x = mSelectTileXIndex; x <= mSelectTileToXIndex; x++) {
				mVSaveMode[y][x].IsCanMove = true;
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

#if SAVE_MODE 
	if (KEYMANAGER->isToggleKey(VK_F1)) {
		for (int y = 0; y < mBaseSprite->getMaxFrameY() + 1; y++) {
			for (int x = 0; x < mBaseSprite->getMaxFrameX() + 1; x++) {
				int rX = mTilePaletteScrollBox->getContentAreaRelX() / TILE_SIZE;
				int rY = mTilePaletteScrollBox->getContentAreaRelY() / TILE_SIZE;
				int rDX = (mTilePaletteScrollBox->getContentAreaRelX() + mTilePaletteScrollBox->getContentAreaRectF().Width - 20) / TILE_SIZE;
				int rDY = (mTilePaletteScrollBox->getContentAreaRelY() + mTilePaletteScrollBox->getContentAreaRectF().Height) / TILE_SIZE;
				float ix = (x - rX) * TILE_SIZE;
				float iy = (y - rY) * TILE_SIZE;

				if (x >= rX && x <= rDX && y >= rY && y <= rDY) {
					if (!mVSaveMode[y][x].IsInit) {
						GDIPLUSMANAGER->drawRectF(getMemDc(), RectFMake(mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + ix, mTilePaletteScrollBox->getContentAreaRectF().GetTop() + iy, TILE_SIZE, TILE_SIZE), Color(0, 0, 0, 0), Color(100, 255, 255, 0));
						if (mVSaveMode[y][x].Object == OBJ_NULL && mVSaveMode[y][x].Terrain == TR_NULL && mVSaveMode[y][x].Object2 == OBJ_NULL) {
							GDIPLUSMANAGER->drawText(getMemDc(),
								L"not init",
								mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + ix,
								mTilePaletteScrollBox->getContentAreaRectF().GetTop() + iy,
								10,
								Color(255, 255, 255));
						}
						else {
							GDIPLUSMANAGER->drawText(getMemDc(),
								L"init error",
								mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + ix,
								mTilePaletteScrollBox->getContentAreaRectF().GetTop() + iy,
								10,
								Color(255, 255, 255));
						}
						continue;
					} else if (mVSaveMode[y][x].IsCanMove) {
						GDIPLUSMANAGER->drawRectF(getMemDc(), RectFMake(mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + ix, mTilePaletteScrollBox->getContentAreaRectF().GetTop() + iy, TILE_SIZE, TILE_SIZE), Color(0, 0, 0, 0), Color(100, 0, 0, 255));
					}
					else if(!mVSaveMode[y][x].IsCanMove) {
						GDIPLUSMANAGER->drawRectF(getMemDc(), RectFMake(mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + ix, mTilePaletteScrollBox->getContentAreaRectF().GetTop() + iy, TILE_SIZE, TILE_SIZE), Color(0, 0, 0, 0), Color(100, 255, 0, 0));
					}

					if (mVSaveMode[y][x].IsOverrayTerrain) {
						GDIPLUSMANAGER->drawText(getMemDc(),
							L"over T",
							mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + ix,
							mTilePaletteScrollBox->getContentAreaRectF().GetTop() + iy + 20,
							10,
							Color(255, 0, 0));
					}

					int s = 0;
					s += mVSaveMode[y][x].Terrain != TR_NULL;
					s += mVSaveMode[y][x].Object != OBJ_NULL;
					s += mVSaveMode[y][x].Object2 != OBJ_NULL;
					if (mVSaveMode[y][x].Terrain != TR_NULL && mVSaveMode[y][x].Object != OBJ_NULL) {
						GDIPLUSMANAGER->drawText(getMemDc(),
							L"error",
							mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + ix,
							mTilePaletteScrollBox->getContentAreaRectF().GetTop() + iy,
							10,
							Color(255, 0, 0));
					} else if (s > 1) {
						GDIPLUSMANAGER->drawText(getMemDc(),
							L"error",
							mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + ix,
							mTilePaletteScrollBox->getContentAreaRectF().GetTop() + iy,
							10,
							Color(255, 0, 0));
					} else {
						if (mVSaveMode[y][x].Terrain != TR_NULL) {
							if (mVSaveMode[y][x].Terrain == TR_NORMAL) {
								GDIPLUSMANAGER->drawText(getMemDc(),
									L"T : NORMAL",
									mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + ix,
									mTilePaletteScrollBox->getContentAreaRectF().GetTop() + iy,
									10,
									Color(100, 255, 0, 0));
							} else if (mVSaveMode[y][x].Terrain == TR_GRASS) {
								GDIPLUSMANAGER->drawText(getMemDc(),
									L"T : GRASS",
									mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + ix,
									mTilePaletteScrollBox->getContentAreaRectF().GetTop() + iy,
									10,
									Color(100, 255, 0, 0));
							}
							else {
								GDIPLUSMANAGER->drawText(getMemDc(),
									L"T : ELSE",
									mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + ix,
									mTilePaletteScrollBox->getContentAreaRectF().GetTop() + iy,
									10,
									Color(100, 255, 0, 0));
							}

						}

						if (mVSaveMode[y][x].Object != OBJ_NULL) {
							GDIPLUSMANAGER->drawText(getMemDc(),
								L"O",
								mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + ix,
								mTilePaletteScrollBox->getContentAreaRectF().GetTop() + iy,
								10,
								Color(0, 0, 255));
						}

						if (mVSaveMode[y][x].Object2 != SOBJ_NULL) {
							GDIPLUSMANAGER->drawText(getMemDc(),
								L"SO",
								mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + ix,
								mTilePaletteScrollBox->getContentAreaRectF().GetTop() + iy,
								10,
								Color(0, 255, 0));
						}
					}
				}
			}
		}

		for (int y = 0; y < mYWorkBoardCount + 1; y++) {
			for (int x = 0; x < mXWorkBoardCount + 1; x++) {
				int rX = mWorkBoardScrollBox->getContentAreaRelX() / TILE_SIZE;
				int rY = mWorkBoardScrollBox->getContentAreaRelY() / TILE_SIZE;
				int rDX = (mWorkBoardScrollBox->getContentAreaRelX() + mWorkBoardScrollBox->getContentAreaRectF().Width - 20) / TILE_SIZE;
				int rDY = (mWorkBoardScrollBox->getContentAreaRelY() + mWorkBoardScrollBox->getContentAreaRectF().Height) / TILE_SIZE;
				float ix = (x - rX) * TILE_SIZE;
				float iy = (y - rY) * TILE_SIZE;

				if (x >= rX && x <= rDX && y >= rY && y <= rDY) {
					int index = x + (y * mXWorkBoardCount);
					if (!mVCurWorkTile[index].IsCanMove) {
						GDIPLUSMANAGER->drawRectF(getMemDc(), RectFMake(mWorkBoardScrollBox->getContentAreaRectF().GetLeft() + ix, mWorkBoardScrollBox->getContentAreaRectF().GetTop() + iy, TILE_SIZE, TILE_SIZE), Color(0, 0, 0, 0), Color(100, 255, 0, 0));
					}
				}
			}
		}
	}
#endif

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

	MAPTILEMANAGER->makeMap(thearray, mMapTileInfo);
}

void MapToolScene::loadMap()
{
	mMapTileInfo = MAPTILEMANAGER->findInfo(mInputFileNameBox->getInputText());
#if CHANGE_MODE
	tagTileOriginal* original = new tagTileOriginal[mMapTileInfo.XCount * mMapTileInfo.YCount];
	LoadFile<tagTileOriginal*>(mMapTileInfo.FilePath.c_str(), original, sizeof(tagTileOriginal) *  mMapTileInfo.XCount * mMapTileInfo.YCount);
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

			auto& curLoadT = mLoadMapTile[y][x];

			mVCurWorkTile[index] = curLoadT;
			if (curLoadT.Terrain != TR_NULL) {
				mWorkBoardScrollBox->getContent()->coverBitmap(
					(x * mTileSize),
					(y * mTileSize),
					mPalette[curLoadT.TerrainFrameY][curLoadT.TerrainFrameX].getBitmap()
				);
			}

			if (curLoadT.Object != OBJ_NULL) {
				mWorkBoardScrollBox->getContent()->overlayBitmap(
					(x * mTileSize),
					(y * mTileSize),
					mPalette[curLoadT.ObjectFrameY][curLoadT.ObjectFrameX].getBitmap()
				);
			}

			if (curLoadT.Object2 != OBJ_NULL) {
				mWorkBoardScrollBox->getContent()->overlayBitmap(
					(x * mTileSize),
					(y * mTileSize),
					mPalette[curLoadT.Object2FrameY][curLoadT.Object2FrameX].getBitmap()
				);
			}
		}
	}
	mWorkBoardScrollBox->clipingContentArea();
}

void MapToolScene::release(void)
{
}
