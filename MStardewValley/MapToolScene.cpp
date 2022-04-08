#include "Stdafx.h"
#include "MapToolScene.h"

#define SAMPLE_SCROLL_BOX_WIDTH		(WINSIZE_X * 0.25f)
#define SAMPLE_SCROLL_BOX_HEIGHT	(WINSIZE_Y * 0.5f)

#define WORK_SCROLL_BOX_WIDTH		(WINSIZE_X * 0.75f)
#define WORK_SCROLL_BOX_HEIGHT		WINSIZE_R_Y

#define SELECT_CTRL_BOX_X		0
#define SELECT_CTRL_BOX_Y		(WINSIZE_Y * 0.5f)

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

	TILECLASS->findTileNodeLIst(IMGCLASS->MapMines1To30, mCurTilePalette);

	mines1To30Palette = MAPPALETTE->getBaseSprite();

	//맵 초기 생성
	mMapTileInfo.MapType = eMapType::MT_MINE;

	//타일 팔레트
	mTilePalette = new GameUI;
	mTilePalette->init("광산 타일 팔레트", 0, 0, mines1To30Palette);

	mTilePaletteScrollBox = new ScrollBox;
	mTilePaletteScrollBox->init("광산 타일 팔레트 스크롤 박스", 0, 0, SAMPLE_SCROLL_BOX_WIDTH, SAMPLE_SCROLL_BOX_HEIGHT, mTilePalette, XS_LEFT, YS_TOP);

	//작업 영역
	mWorkBoard = new GameUI;
	mWorkBoard->init("작업 영역 상자", 0, 0, mTileSize * mXWorkBoardCount, mTileSize * mYWorkBoardCount, XS_LEFT, YS_TOP);
	GDIPLUSMANAGER->drawGridLine(mWorkBoard->getImgGp(), mTileSize, mTileSize);

	mWorkBoardScrollBox = new ScrollBox;
	mWorkBoardScrollBox->init("작업 영역 스크롤 상자", SAMPLE_SCROLL_BOX_WIDTH, 0, WORK_SCROLL_BOX_WIDTH, WORK_SCROLL_BOX_HEIGHT, mWorkBoard, XS_LEFT, YS_TOP);

	//버튼 - 그리기 도구
	mBtnEraser = new SButton;
	mBtnEraser->init("지우개 버튼", 400, 537, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnEraser), XS_LEFT, YS_TOP);
	mBtnEraser->setClickDownEvent([this](GameUI* ui) {

		eraserTile();
	});

	mBtnSelect = new SButton;
	mBtnSelect->init("선택 버튼", 400, 610, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnSelect), XS_LEFT, YS_TOP);

	//버튼 - 저장, 불러오기
	mBtnSave = new SButton;
	mBtnSave->init("저장 버튼", 20, 948, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnSave), XS_LEFT, YS_TOP);

	mBtnLoad = new SButton;
	mBtnLoad->init("불러오기 버튼", 200, 948, GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnLoad), XS_LEFT, YS_TOP);

	mRBtnSelectMapType = new RadioButton;
	mRBtnSelectMapType->init(0, 0, 70, 70, new ImageGp*[2]{ GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnSelectMine) , GDIPLUSMANAGER->cloneImage(IMGCLASS->MapBtnSelectFarm) }, 2);

	mRBtnSelectMapType->setClickDownEvent([this](GameUI* ui) {
		((RadioButton*)ui)->changeSelectIndex(mCurPaletteType);
	});

	mSelectTile = new GameUI;
	ImageGp* img = new ImageGp;
	img->init(getMemDc(), GDIPLUSMANAGER->getBlankBitmap(SELECT_CTRL_BOX_WIDTH, SELECT_CTRL_BOX_HEIGHT));
	mSelectTile->init("현재 타일", 0.0f, 0.0f, img, XS_LEFT, YS_TOP);
      
	mSelectTileBox = new ScrollBox;
	mSelectTileBox->init("현재 타일 스크롤 박스", SELECT_CTRL_BOX_X, SELECT_CTRL_BOX_Y, SELECT_CTRL_BOX_WIDTH, SELECT_CTRL_BOX_HEIGHT, mSelectTile, XS_LEFT, YS_TOP);
	mSelectTileBox->scrollToCenter();

	mInputFileNameBox = new EditText;
	mInputFileNameBox->init("파일 이름 입력창", 0, 875.0f, SELECT_CTRL_BOX_WIDTH, 50.0f, XS_LEFT, YS_TOP);

	for (int i = 0; i < mWorkBoardAllCount; i++) {
		mVCurWorkTile.push_back(tagTile(i));
	}
	


	return S_OK;
}

void MapToolScene::update(void)
{
	//GameUi update
	mTilePaletteScrollBox->update();
	mWorkBoardScrollBox->update();
	mBtnEraser->update();
	mBtnSelect->update();
	mBtnSave->update();
	mBtnLoad->update();
	mSelectTileBox->update();
	mInputFileNameBox->update();

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
		if (mTilePaletteScrollBox->isCollisionContentBox(_ptfMouse)) {
			mCurCtrl = eMapToolCtrl::MC_DRAW_ONE;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				mWorkTileXIndex = mWorkTileYIndex = 0;
				mSelectTileToXIndex = 0;
				mSelectTileToYIndex = 0;
				mSelectTileXIndex = mTilePaletteScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;
				mSelectTileYIndex = mTilePaletteScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;
			}
			else {
				mSelectTileToXIndex = mTilePaletteScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;
				mSelectTileToYIndex = mTilePaletteScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;
			}
		}

		if (mWorkBoardScrollBox->isCollisionContentBox(_ptfMouse)) {
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
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

					mWorkBoard->getImgGp()->coverBitmap(
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
								int pIndex = x + y * (mines1To30Palette->getMaxFrameX() + 1);

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
									mWorkBoard->getImgGp()->coverBitmap(
										(mCurWIndexX * mTileSize),
										(mCurWIndexY * mTileSize),
										MAPPALETTE->getPalette()[wTile.TerrainFrameY][wTile.TerrainFrameX].getBitmap()
									);
								}

								if (wTile.Object != OBJ_NULL) {
									mWorkBoard->getImgGp()->overlayBitmap(
										(mCurWIndexX * mTileSize),
										(mCurWIndexY * mTileSize),
										MAPPALETTE->getPalette()[wTile.ObjectFrameY][wTile.ObjectFrameX].getBitmap()
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
			}
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		if (mTilePaletteScrollBox->isCollisionContentBox(_ptfMouse)) {
			mSelectTile->getImgGp()->coverBitmapCenter(MAPPALETTE->getBitmap(
				mSelectTileXIndex, 
				mSelectTileYIndex, 
				mSelectTileToXIndex - mSelectTileXIndex, 
				mSelectTileToYIndex - mSelectTileYIndex));
			mSelectTileBox->clipingContentArea();
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		if (PtInRect(&mBtnSave->getRECT(), _ptMouse)) {
			mBtnSave->clickDownEvent();
			saveMap();
		}

		if (PtInRect(&mBtnLoad->getRECT(), _ptMouse)) {
			mBtnSave->clickDownEvent();
			loadMap();
		}

		if (PtInRect(&mBtnEraser->getRECT(), _ptMouse)) {
			eraserTile();
		}

		if (PtInRect(&mRBtnSelectMapType->getRECT(), _ptMouse)) {
			mRBtnSelectMapType->clickDownEvent();
		}
	}
	
	if (mTilePaletteScrollBox->isCollisionContentBox(_ptfMouse)) {
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
			mCurSelectRectF =
				RectFMake(
					mCurSelectRectF.GetLeft(), mCurSelectRectF.GetTop(),
					mTileSize * (mSelectTileToXIndex - mSelectTileXIndex + 1), mTileSize * (mSelectTileToYIndex - mSelectTileYIndex + 1));
		}
		else {
			int indexX = mTilePaletteScrollBox->getContentAreaRelXToX(_ptMouse.x) / mTileSize;
			int indexY = mTilePaletteScrollBox->getContentAreaRelYToY(_ptMouse.y) / mTileSize;

			int indexX2 = mTilePaletteScrollBox->getContentAreaRelXToX(_ptMouse.x) - mTilePaletteScrollBox->getContentAreaAbsXToX(_ptMouse.x);
			int indexY2 = mTilePaletteScrollBox->getContentAreaRelYToY(_ptMouse.y) - mTilePaletteScrollBox->getContentAreaAbsYToY(_ptMouse.y);

			mCurSelectRectF =
				RectFMake(
					mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + (indexX * mTileSize) - indexX2,
					mTilePaletteScrollBox->getContentAreaRectF().GetTop() + (indexY * mTileSize) - indexY2,
					mTileSize, mTileSize);
		}
	}

}


void MapToolScene::render(void)
{
	mBtnEraser->render();
	mBtnSelect->render();
	mBtnLoad->render();
	mTilePaletteScrollBox->render();
	mWorkBoardScrollBox->render();
	mInputFileNameBox->render();

	mBtnSave->render();

	if (mTilePaletteScrollBox->isCollisionContentBox(_ptfMouse)) {
		GDIPLUSMANAGER->drawRectF(getMemDc(), mCurSelectRectF, Color(255, 0, 0));
	}

	mRBtnSelectMapType->render();

	mSelectTileBox->render();
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
				mWorkBoard->getImgGp()->coverBitmap(
					(x * mTileSize),
					(y * mTileSize),
					MAPPALETTE->getPalette()[curLoadT.TerrainFrameY][curLoadT.TerrainFrameX].getBitmap()
				);
			}

			if (curLoadT.Object != OBJ_NULL) {
				mWorkBoard->getImgGp()->overlayBitmap(
					(x * mTileSize),
					(y * mTileSize),
					MAPPALETTE->getPalette()[curLoadT.ObjectFrameY][curLoadT.ObjectFrameX].getBitmap()
				);
			}
		}
	}

	mWorkBoardScrollBox->clipingContentArea();
}

void MapToolScene::eraserTile()
{
	mCurCtrl = MC_ERASER;
	mSelectTile->getImgGp()->coverBitmapCenter(mBtnEraser->getImgGp()->getBitmapClone());
	mSelectTileBox->clipingContentArea();
}

void MapToolScene::updateMapStruct() {
	for (vector<tagTile>::iterator iter = mVCurWorkTile.begin(); iter != mVCurWorkTile.end(); iter++) {
		if ((*iter).Terrain != TR_NULL) {
			int pIndex = (*iter).TerrainFrameX + (*iter).TerrainFrameY * (mines1To30Palette->getMaxFrameX() + 1);
			(*iter).Terrain = mCurTilePalette[pIndex]->Terrain;
			(*iter).TerrainFrameX = mCurTilePalette[pIndex]->TerrainFrameX;
			(*iter).TerrainFrameY = mCurTilePalette[pIndex]->TerrainFrameY;
			(*iter).IsCanMove = mCurTilePalette[pIndex]->IsCanMove;
		}

		if ((*iter).Object != TR_NULL) {
			int pIndex = (*iter).ObjectFrameX + (*iter).ObjectFrameY * (mines1To30Palette->getMaxFrameX() + 1);
			(*iter).Object = mCurTilePalette[pIndex]->Object;
			(*iter).ObjectFrameX = mCurTilePalette[pIndex]->ObjectFrameX;
			(*iter).ObjectFrameY = mCurTilePalette[pIndex]->ObjectFrameY;
			(*iter).IsCanMove = mCurTilePalette[pIndex]->IsCanMove;
			(*iter).IsOverrayObject = mCurTilePalette[pIndex]->IsOverrayObject;
			(*iter).IsOverrayTerrain = mCurTilePalette[pIndex]->IsOverrayTerrain;
		}
	}
}
