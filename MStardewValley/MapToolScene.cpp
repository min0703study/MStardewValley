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

	isDragging = false;

	mCurSelectTag = nullptr;
	mCurSelectBitmap = nullptr;

	mToolCtrl = TC_SELECT;

	TILECLASS->findTileNodeLIst(IMGCLASS->MapMines1To30, mCurTilePalette);

	mines1To30Palette = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapMines1To30);

	float mines1To30PaletteW = (mines1To30Palette->getMaxFrameX() + 1) * mTileSize;
	float mines1To30PaletteH = (mines1To30Palette->getMaxFrameY() + 1) * mTileSize;

	//타일 팔레트
	mTilePalette = new GameUI;
	mTilePalette->init("광산 타일 팔레트", 0, 0, mines1To30PaletteW, mines1To30PaletteH, mines1To30Palette);

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
	mBtnEraser->init("지우개 버튼", 400, SAVE_BTN_Y, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapBtnEraser), XS_LEFT, YS_TOP);

	mBtnSelect = new SButton;
	mBtnSelect->init("선택 버튼", WINSIZE_X - 200, 50, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapBtnSelect));

	//버튼 - 저장, 불러오기
	mBtnSave = new SButton;
	mBtnSave->init("저장 버튼", SAVE_BTN_X, SAVE_BTN_Y, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapBtnSave), XS_LEFT, YS_TOP);

	mBtnLoad = new SButton;
	mBtnLoad->init("불러오기 버튼", 180, SAVE_BTN_Y, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapBtnLoad), XS_LEFT, YS_TOP);
      

	mSelectTileBox = new GameUI;
	mSelectTileBox->init("선택 작업 창", SELECT_CTRL_BOX_X, SELECT_CTRL_BOX_Y, SELECT_CTRL_BOX_WIDTH, SELECT_CTRL_BOX_HEIGHT, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->UISetupBox), XS_LEFT, YS_TOP);

	for (int x = 0; x < mXWorkBoardCount; x++) {
		for (int y = 0; y < mYWorkBoardCount; y++) {
			mCurTileWork.push_back(tagTile());
		}
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

		if (PtInRect(&mTilePaletteScrollBox->getRECT(), _ptMouse)) {
			mToolCtrl = TC_SELECT;
			mTilePaletteScrollBox->clickDownEvent();
			if (mTilePaletteScrollBox->isCollisionContentBox(_ptfMouse)) {
				int indexX = mTilePaletteScrollBox->getValueRelXToX(_ptMouse.x) / mTileSize;
				int indexY = mTilePaletteScrollBox->getValueRelYToY(_ptMouse.y) / mTileSize;

				int t = indexX + (indexY * (mines1To30Palette->getMaxFrameX() + 1));

				mCurSelectTag = mCurTilePalette[t];

				if (mCurSelectTag->Terrain != TR_NULL) {
					mCurSelectBitmap = mines1To30Palette->getFrameBitmap(mCurSelectTag->TerrainFrameX, mCurSelectTag->TerrainFrameY);
				}
				else if(mCurSelectTag->Object != OBJ_NULL) {
					mCurSelectBitmap = mines1To30Palette->getFrameBitmap(mCurSelectTag->ObjectFrameX, mCurSelectTag->ObjectFrameY);
				}
				else if (mCurSelectTag->SubObject != OBJ_NULL) {
					mCurSelectBitmap = mines1To30Palette->getFrameBitmap(mCurSelectTag->SubObjectFrameX, mCurSelectTag->SubObjectFrameY);
				}

				mSelectTileBox->getImgGp()->overlayBitmapCenter(mCurSelectBitmap);
				mSelectTileBox->getImgGp()->rebuildChachedBitmap();

			}
		}

		if (PtInRect(&mWorkBoardScrollBox->getRECT(), _ptMouse)) {
			mWorkBoardScrollBox->clickDownEvent();
			if (!mWorkBoardScrollBox->isCollisionScrollBar(_ptfMouse)) {

				int indexX = mWorkBoardScrollBox->getValueRelXToX(_ptMouse.x) / mTileSize;
				int indexY = mWorkBoardScrollBox->getValueRelYToY(_ptMouse.y) / mTileSize;

				mVCurWorkIndex.push_back(indexX + (indexY * (mines1To30Palette->getMaxFrameX() + 1)));

				int index = indexX + (indexY * (mXWorkBoardCount));

				if (mToolCtrl == TC_ERASER) {
					mCurTileWork[index].Object = OBJ_NULL;
					mCurTileWork[index].SubObject = OBJ_NULL;
					mCurTileWork[index].Terrain = TR_NULL;

					mWorkBoard->getImgGp()->coverBitmap(
						(indexX * mTileSize),
						(indexY * mTileSize),
						mCurSelectBitmap
					);

					mWorkBoardScrollBox->clipingContentArea();
				}
				else {
					if (mCurSelectTag != nullptr && mCurSelectTag->Terrain != TR_NULL) { //바닥이 객체의 경우
						if (mCurTileWork[index].Object != OBJ_NULL) {
							mCurTileWork[index].Object = OBJ_NULL;
						}

						if (mCurTileWork[index].SubObject != OBJ_NULL) {
							mCurTileWork[index].SubObject = OBJ_NULL;
						}

						mCurTileWork[index].Terrain = mCurSelectTag->Terrain;
						mCurTileWork[index].TerrainFrameX = mCurSelectTag->TerrainFrameX;
						mCurTileWork[index].TerrainFrameY = mCurSelectTag->TerrainFrameY;

						mWorkBoard->getImgGp()->coverBitmap(
							(indexX * mTileSize),
							(indexY * mTileSize),
							mCurSelectBitmap
						);

						mCurTileWork[index].X = indexX;
						mCurTileWork[index].Y = indexY;
						mCurTileWork[index].IsInit = mCurSelectTag->IsInit;
						mWorkBoardScrollBox->clipingContentArea();
					}
					else if (mCurSelectTag != nullptr&&mCurSelectTag->Object != OBJ_NULL) { //오브젝트 객체의 경우
						if (mCurSelectTag->IsOverrayTerrain) {
							if (mCurTileWork[index].Terrain != TR_NULL) {
								mWorkBoard->getImgGp()->coverBitmap(
									(indexX * mTileSize),
									(indexY * mTileSize),
									mines1To30Palette->getFrameBitmap(mCurTileWork[index].TerrainFrameX, mCurTileWork[index].TerrainFrameY)
								);
							}
							mWorkBoard->getImgGp()->overlayBitmap(
								(indexX * mTileSize),
								(indexY * mTileSize),
								mCurSelectBitmap
							);
						}
						else {
							mCurTileWork[index].Terrain = TR_NULL;
							mWorkBoard->getImgGp()->coverBitmap(
								(indexX * mTileSize),
								(indexY * mTileSize),
								mCurSelectBitmap
							);
						}

						mCurTileWork[index].X = indexX;
						mCurTileWork[index].Y = indexY;
						mCurTileWork[index].IsInit = mCurSelectTag->IsInit;
						mCurTileWork[index].SubObject = OBJ_NULL;
						mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].Object = mCurSelectTag->Object;
						mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].ObjectFrameX = mCurSelectTag->ObjectFrameX;
						mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].ObjectFrameY = mCurSelectTag->ObjectFrameY;

						mWorkBoardScrollBox->clipingContentArea();
					}
					else if (mCurSelectTag != nullptr && mCurSelectTag->SubObject != TR_NULL) {
						if (mCurSelectTag->IsOverrayObject) {
							if (mCurTileWork[index].Object != OBJ_NULL) {
								mWorkBoard->getImgGp()->coverBitmap(
									(indexX * mTileSize),
									(indexY * mTileSize),
									mines1To30Palette->getFrameBitmap(mCurTileWork[index].ObjectFrameX, mCurTileWork[index].ObjectFrameY)
								);

								mWorkBoard->getImgGp()->overlayBitmap(
									(indexX * mTileSize),
									(indexY * mTileSize),
									mCurSelectBitmap
								);
							}
							else {
								mWorkBoard->getImgGp()->coverBitmap(
									(indexX * mTileSize),
									(indexY * mTileSize),
									mCurSelectBitmap
								);
							}
						}
						else {
							if (mCurTileWork[index].Terrain != TR_NULL || mCurTileWork[index].SubObject != OBJ_NULL) {
								mWorkBoard->getImgGp()->coverBitmap(
									(indexX * mTileSize),
									(indexY * mTileSize),
									mCurSelectBitmap
								);
							}
							else {
								mWorkBoard->getImgGp()->overlayBitmap(
									(indexX * mTileSize),
									(indexY * mTileSize),
									mCurSelectBitmap
								);
							}
						}

						mCurTileWork[index].Terrain = TR_NULL;
						mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].SubObject = mCurSelectTag->SubObject;
						mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].SubObjectFrameX = mCurSelectTag->SubObjectFrameX;
						mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].SubObjectFrameY = mCurSelectTag->SubObjectFrameY;
						mCurTileWork[index].IsInit = mCurSelectTag->IsInit;
						mCurTileWork[index].X = indexX;
						mCurTileWork[index].Y = indexY;
						mWorkBoardScrollBox->clipingContentArea();
					}
				}


				mCurTileWork[index].toString();
			}
		}
	}

	if (_ptMouse.x != x && _ptMouse.y != y) {
		x = _ptMouse.x;
		y = _ptMouse.y;

		if (PtInRect(&mTilePaletteScrollBox->getRECT(), _ptMouse)) {
			mTilePaletteScrollBox->mouseOverEvent();
			if (mTilePaletteScrollBox->isCollisionContentBox(_ptfMouse)) {
				int indexX = mTilePaletteScrollBox->getValueRelXToX(_ptMouse.x) / mTileSize;
				int indexY = mTilePaletteScrollBox->getValueRelYToY(_ptMouse.y) / mTileSize;

				int indexX2 = mTilePaletteScrollBox->getValueRelXToX(_ptMouse.x) - mTilePaletteScrollBox->getValueAbsXToX(_ptMouse.x);
				int indexY2 = mTilePaletteScrollBox->getValueRelYToY(_ptMouse.y) - mTilePaletteScrollBox->getValueAbsYToY(_ptMouse.y);

				mCurSelectRectF = 
					RectFMake(
						mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + (indexX * mTileSize) - indexX2, 
						mTilePaletteScrollBox->getContentAreaRectF().GetTop() + (indexY * mTileSize) - indexY2, 
						mTileSize, mTileSize);
			}
		} else {
			mTilePaletteScrollBox->mouseOffEvent();
		}

		if (PtInRect(&mWorkBoardScrollBox->getRECT(), _ptMouse)) {
			mWorkBoardScrollBox->mouseOverEvent();
			if (mCurSelectBitmap != nullptr) {
				if (isDragging) {
					int indexX = mWorkBoardScrollBox->getValueRelXToX(_ptMouse.x) / mTileSize;
					int indexY = mWorkBoardScrollBox->getValueRelYToY(_ptMouse.y) / mTileSize;

					int tempIndex = indexX + (indexY * (mines1To30Palette->getMaxFrameX() + 1));
					bool isNewTile = true;
					for (vector<int>::iterator mViCurWorkIndex = mVCurWorkIndex.begin(); mViCurWorkIndex != mVCurWorkIndex.end(); mViCurWorkIndex++) {
						if (tempIndex == *mViCurWorkIndex) {
							isNewTile = false;
						}
					}

					if (isNewTile) {
						mVCurWorkIndex.push_back(tempIndex);
						mWorkBoard->getImgGp()->overlayBitmap(
							(indexX * mTileSize),
							(indexY * mTileSize),
							mCurSelectBitmap
						);
						mWorkBoardScrollBox->clipingContentArea();
					}
				}
			}
			else {
				mWorkBoardScrollBox->mouseOffEvent();
			}
		}
	}

	//마우스 버튼 뗄 경우
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		isDragging = false;
		mTilePaletteScrollBox->clickUpEvent();
		mWorkBoardScrollBox->clickUpEvent();
		mVCurWorkIndex.clear();
	}
}

void MapToolScene::release(void)
{
}

void MapToolScene::render(void)
{
	mBtnEraser->render();
	mBtnSelect->render();
	mBtnLoad->render();

	mTilePaletteScrollBox->render();
	mWorkBoardScrollBox->render();

	mBtnSave->render();

	if (mTilePaletteScrollBox->isCollisionContentBox(_ptfMouse)) {
		GDIPLUSMANAGER->drawRectF(getMemDc(), mCurSelectRectF, Color(255, 0, 0));
	}

	mSelectTileBox->render();
}

void MapToolScene::saveMap()
{
	tagTile *thearray = &mCurTileWork[0];
	SaveFile<tagTile*>("Resources/Map/save_map.map", thearray, sizeof(tagTile) * mXWorkBoardCount * mYWorkBoardCount);
}

void MapToolScene::loadMap()
{
	tagTile *thearray = &mCurTileWork[0];
	LoadFile<tagTile*>("Resources/Map/save_map.map", thearray, sizeof(tagTile) * mXWorkBoardCount * mYWorkBoardCount);

	int indexX = 0;
	int indexY = 0;

	for (int y = 0; y < mYWorkBoardCount; y++) {
		for (int x = 0; x < mXWorkBoardCount; x++) {

			int t = x + (y * mXWorkBoardCount);
			if (mCurTileWork[t].IsInit) {
				indexX = x * mTileSize;
				indexY = y * mTileSize;

				if (mCurTileWork[t].Terrain != TR_NULL) {
					mCurSelectBitmap = mines1To30Palette->getFrameBitmap(mCurTileWork[t].TerrainFrameX, mCurTileWork[t].TerrainFrameY);
					mWorkBoard->getImgGp()->coverBitmap(
						indexX, indexY,
						mCurSelectBitmap
					);
				}

				if (mCurTileWork[t].Object != OBJ_NULL) {
					mCurSelectBitmap = mines1To30Palette->getFrameBitmap(mCurTileWork[t].ObjectFrameX, mCurTileWork[t].ObjectFrameY);
					mWorkBoard->getImgGp()->overlayBitmap(
						indexX, indexY,
						mCurSelectBitmap
					);
				}


				if (mCurTileWork[t].SubObject != OBJ_NULL) {
					mCurSelectBitmap = mines1To30Palette->getFrameBitmap(mCurTileWork[t].SubObjectFrameX, mCurTileWork[t].SubObjectFrameY);
					mWorkBoard->getImgGp()->overlayBitmap(
						indexX, indexY,
						mCurSelectBitmap
					);
				}
			}
		}
	}

	mWorkBoardScrollBox->clipingContentArea();
}

void MapToolScene::eraserTile()
{
	mCurSelectBitmap = GDIPLUSMANAGER->getBitmap(mTileSize, mTileSize);
	mSelectTileBox->getImgGp()->overlayBitmapCenter(mCurSelectBitmap);

	mToolCtrl = TC_ERASER;
}
