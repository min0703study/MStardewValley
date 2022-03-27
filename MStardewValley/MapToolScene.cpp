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
	mTileSize = 50.0f;

	mXWorkBoardCount = 30;
	mYWorkBoardCount = 30;

	isDragging = false;

	mCurSelectTag = nullptr;

	mToolCtrl = TC_SELECT;

	TILECLASS->findTileNodeLIst(IMGCLASS->MapMines1To30, mCurTilePalette);

	mines1To30Palette = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapMines1To30);

	float mines1To30PaletteW = (mines1To30Palette->getMaxFrameX() + 1) * mTileSize;
	float mines1To30PaletteH = (mines1To30Palette->getMaxFrameY() + 1) * mTileSize;

	//Ÿ�� �ȷ�Ʈ
	mTilePalette = new GameUI;
	mTilePalette->init("���� Ÿ�� �ȷ�Ʈ", 0, 0, mines1To30PaletteW, mines1To30PaletteH, mines1To30Palette);

	mTilePaletteScrollBox = new ScrollBox;
	mTilePaletteScrollBox->init("���� Ÿ�� �ȷ�Ʈ ��ũ�� �ڽ�", 0, 0, SAMPLE_SCROLL_BOX_WIDTH, SAMPLE_SCROLL_BOX_HEIGHT, mTilePalette, XS_LEFT, YS_TOP);

	//�۾� ����
	mWorkBoard = new GameUI;
	mWorkBoard->init("�۾� ���� ����", 0, 0, mTileSize * mXWorkBoardCount, mTileSize * mYWorkBoardCount, XS_LEFT, YS_TOP);
	GDIPLUSMANAGER->drawGridLine(mWorkBoard->getImgGp(), mTileSize, mTileSize);

	mWorkBoardScrollBox = new ScrollBox;
	mWorkBoardScrollBox->init("�۾� ���� ��ũ�� ����", SAMPLE_SCROLL_BOX_WIDTH, 0, WORK_SCROLL_BOX_WIDTH, WORK_SCROLL_BOX_HEIGHT, mWorkBoard, XS_LEFT, YS_TOP);

	//��ư - �׸��� ����
	mBtnEraser = new SButton;
	mBtnEraser->init("���찳 ��ư", 400, SAVE_BTN_Y, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapBtnEraser), XS_LEFT, YS_TOP);

	mBtnSelect = new SButton;
	mBtnSelect->init("���� ��ư", WINSIZE_X - 200, 50, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapBtnSelect));

	//��ư - ����, �ҷ�����
	mBtnSave = new SButton;
	mBtnSave->init("���� ��ư", SAVE_BTN_X, SAVE_BTN_Y, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapBtnSave), XS_LEFT, YS_TOP);

	mBtnLoad = new SButton;
	mBtnLoad->init("�ҷ����� ��ư", 180, SAVE_BTN_Y, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapBtnLoad), XS_LEFT, YS_TOP);
      

	mSelectTileBox = new GameUI;
	mSelectTileBox->init("���� �۾� â", SELECT_CTRL_BOX_X, SELECT_CTRL_BOX_Y, SELECT_CTRL_BOX_WIDTH, SELECT_CTRL_BOX_HEIGHT, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->UISetupBox), XS_LEFT, YS_TOP);



	mCurTileImg = new ImageGp;
	mCurTileImg->init(getMemDc(), mTileSize, mTileSize);

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

	if (PtInRect(&mBtnSave->getRECT(), _ptMouse)) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			mBtnSave->clickDownEvent();
			saveMap();
		}	
	}

	if (PtInRect(&mBtnLoad->getRECT(), _ptMouse)) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			mBtnSave->clickDownEvent();
			loadMap();
		}
	}

	if (PtInRect(&mBtnEraser->getRECT(), _ptMouse)) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			eraserTile();
		}
	}

	//�� �ȷ�Ʈ �浹 �˻�
	if (PtInRect(&mTilePaletteScrollBox->getRECT(), _ptMouse)) {
		mTilePaletteScrollBox->mouseOverEvent();
		int indexX = mTilePaletteScrollBox->getValueRelXToX(_ptMouse.x) / mTileSize;
		int indexY = mTilePaletteScrollBox->getValueRelYToY(_ptMouse.y) / mTileSize;


		if (mTilePaletteScrollBox->isCollisionContentBox(_ptfMouse)) {
			int indexX2 = mTilePaletteScrollBox->getValueRelXToX(_ptMouse.x) - mTilePaletteScrollBox->getValueAbsXToX(_ptMouse.x);
			int indexY2 = mTilePaletteScrollBox->getValueRelYToY(_ptMouse.y) - mTilePaletteScrollBox->getValueAbsYToY(_ptMouse.y);

			mCurSelectRectF = RectFMake(mTilePaletteScrollBox->getContentAreaRectF().GetLeft() + (indexX * mTileSize) - indexX2, mTilePaletteScrollBox->getContentAreaRectF().GetTop() + (indexY * mTileSize) - indexY2, mTileSize, mTileSize);
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			isDragging = true;
			mTilePaletteScrollBox->clickDownEvent();
			if (!mTilePaletteScrollBox->isCollisionScrollBar(_ptfMouse)) {
				int t = indexX + (indexY * (mines1To30Palette->getMaxFrameX() + 1));

				mCurSelectTag = mCurTilePalette[t];
				mCurSelectBitmap = mines1To30Palette->getFrameBitmap(mCurSelectTag->TerrainFrameX, mCurSelectTag->TerrainFrameY);
				mCurTileImg->overlayBitmap(
					0, 0,
					mCurSelectBitmap
				);

				mCurTileImg->rebuildChachedBitmap();
				mSelectTileBox->getImgGp()->overlayBitmapCenter(mCurSelectBitmap);
			}
		}
	} else {
		mTilePaletteScrollBox->mouseOffEvent();
	}

	//�۾� ���� �浹 �˻�
	if (PtInRect(&mWorkBoardScrollBox->getRECT(), _ptMouse)) {
		mWorkBoardScrollBox->mouseOverEvent();
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
		} else if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			mWorkBoardScrollBox->clickDownEvent();

			int indexX = mWorkBoardScrollBox->getValueRelXToX(_ptMouse.x) / mTileSize;
			int indexY = mWorkBoardScrollBox->getValueRelYToY(_ptMouse.y) / mTileSize;

			mVCurWorkIndex.push_back(indexX + (indexY * (mines1To30Palette->getMaxFrameX() + 1)));
			mWorkBoard->getImgGp()->overlayBitmap(
				(indexX * mTileSize),
				(indexY * mTileSize),
				mCurSelectBitmap
			);

			mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].IsInit = mCurSelectTag->IsInit;
			mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].Object = mCurSelectTag->Object;
			mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].ObjectFrameX = mCurSelectTag->ObjectFrameX;
			mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].ObjectFrameY = mCurSelectTag->ObjectFrameY;
			mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].Terrain = mCurSelectTag->Terrain;
			mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].TerrainFrameX = mCurSelectTag->TerrainFrameX;
			mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].TerrainFrameY = mCurSelectTag->TerrainFrameY;
			mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].X = mCurSelectTag->X;
			mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].Y = mCurSelectTag->Y;
			mCurTileWork[indexX + (indexY * (mXWorkBoardCount))].Index = mCurSelectTag->Index;

			isDragging = true;
			mWorkBoardScrollBox->clipingContentArea();
		}
	}

	//���콺 ��ư �� ���
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

				mCurSelectBitmap = mines1To30Palette->getFrameBitmap(mCurTileWork[t].TerrainFrameX, mCurTileWork[t].TerrainFrameY);
				mWorkBoard->getImgGp()->overlayBitmap(
					indexX, indexY,
					mCurSelectBitmap
				);

				mCurTileImg->rebuildChachedBitmap();
			}
		}
	}

	mWorkBoardScrollBox->clipingContentArea();
}

void MapToolScene::eraserTile()
{
	mCurSelectBitmap = GDIPLUSMANAGER->getBitmap(mTileSize, mTileSize);
	mCurTileImg->overlayBitmap(0,0,GDIPLUSMANAGER->getBitmap(mTileSize, mTileSize));
	mCurTileImg->rebuildChachedBitmap();
	mSelectTileBox->getImgGp()->overlayBitmapCenter(mCurSelectBitmap);
}
