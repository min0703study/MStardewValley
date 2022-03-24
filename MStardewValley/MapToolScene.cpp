#include "Stdafx.h"
#include "MapToolScene.h"

#define SAMPLE_SCROLL_BOX_WIDTH		WINSIZE_X * 0.25f
#define SAMPLE_SCROLL_BOX_HEIGHT	WINSIZE_Y * 0.5f

#define WORK_SCROLL_BOX_WIDTH		WINSIZE_X * 0.75f
#define WORK_SCROLL_BOX_HEIGHT		WINSIZE_R_Y

HRESULT MapToolScene::init(void)
{
	mTileSize = 50;

	TILECLASS->findTileNodeLIst(IMGCLASS->MapMines1To30, mCurTagPalette);

	mines1To30Palette = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapMines1To30);

	float mines1To30PaletteW = mines1To30Palette->getMaxFrameX() * mTileSize;
	float mines1To30PaletteH = mines1To30Palette->getMaxFrameY() * mTileSize;

	//Ÿ�� �ȷ�Ʈ
	mTilePalette = new GameUI;
	mTilePalette->init("���� ���� ��ü", 0, 0, mines1To30PaletteW, mines1To30PaletteH, mines1To30Palette);

	mTilePaletteScrollBox = new ScrollBox;
	mTilePaletteScrollBox->init("��ũ�� ���� ���� �ڽ�", 0, 0, SAMPLE_SCROLL_BOX_WIDTH, SAMPLE_SCROLL_BOX_HEIGHT, mTilePalette, XS_LEFT, YS_TOP);

	//�׸��� ����
	mBtnEraser = new SButton;
	mBtnEraser->init("���찳 ��ư", WINSIZE_X -100, 50, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapBtnEraser));

	mBtnSelect = new SButton;
	mBtnSelect->init("���� ��ư", WINSIZE_X - 200,50, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapBtnSelect));

	//�۾� ����
	mWorkBoard = new GameUI;
	mWorkBoard->init("�۾� ���� ����", 0, 0, mTileSize * 20, mTileSize * 70);
	mWorkBoard->getImgGp()->drawGridLine(50, 50);

	mWorkBoardScrollBox = new ScrollBox;
	mWorkBoardScrollBox->init("�۾� ���� ��ũ�� ����", SAMPLE_SCROLL_BOX_WIDTH, 0, WORK_SCROLL_BOX_WIDTH, WORK_SCROLL_BOX_HEIGHT, mWorkBoard, XS_LEFT, YS_TOP);

	for (int x = 0; x < 50; x++)
	{
		for (int y = 0; y < 50; y++) {
			mTilePaletteRECT.push_back(RectMake((x * mTileSize), (y * mTileSize), mTileSize, mTileSize));
		}
	}

	mCurSelectTag = nullptr;

	mToolCtrl = TC_SELECT;

	return S_OK;
}

void MapToolScene::update(void)
{
	//GameUi update
	mTilePaletteScrollBox->update();
	mWorkBoardScrollBox->update();
	mBtnEraser->update();
	mBtnSelect->update();
	
	//�� �ȷ�Ʈ �浹 �˻�
	if (PtInRect(&mTilePaletteScrollBox->getRECT(), _ptMouse)) {
		mTilePaletteScrollBox->mouseOverEvent();

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			mTilePaletteScrollBox->clickDownEvent();

			int indexX = mTilePaletteScrollBox->getValueRelXToX(_ptMouse.x) / mTileSize;
			int indexY = mTilePaletteScrollBox->getValueRelYToY(_ptMouse.y) / mTileSize;

			int t = indexX + (indexY * mines1To30Palette->getMaxFrameX());
			
			mCurSelectTag = mCurTagPalette[t];
		}
	} else {
		mTilePaletteScrollBox->mouseOffEvent();
	}

	if (PtInRect(&mWorkBoardScrollBox->getRECT(), _ptMouse)) {
		mWorkBoardScrollBox->mouseOverEvent();
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			mWorkBoardScrollBox->clickDownEvent();
			for (vector<RECT>::iterator iRect = mTilePaletteRECT.begin(); iRect != mTilePaletteRECT.end(); iRect++) {
				int realPtX = mWorkBoardScrollBox->getValueRelXToX(_ptMouse.x);
				int relPtY = mWorkBoardScrollBox->getValueRelYToY(_ptMouse.y);
				if (PtInRect(&(*iRect), { realPtX, relPtY })) {
					mWorkBoard->getImgGp()->addBitmap(
						(*iRect).left,
						(*iRect).top,
						mines1To30Palette->getFrameBitmap(mCurSelectTag->TerrainFrameX, mCurSelectTag->TerrainFrameY)
					);
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		mTilePaletteScrollBox->clickUpEvent();
		mWorkBoardScrollBox->clickUpEvent();
	}
}

void MapToolScene::release(void)
{
}

void MapToolScene::render(void)
{
	mBtnEraser->render();
	mBtnSelect->render();

	mTilePaletteScrollBox->render();
	mWorkBoardScrollBox->render();

	if (mines1To30Palette != nullptr) {
		if (mCurSelectTag != nullptr) {
			if (mCurSelectTag->Terrain != TR_NULL)
			{
				mines1To30Palette->frameRender(getMemDc(), _ptMouse.x, _ptMouse.y, mCurSelectTag->TerrainFrameX, mCurSelectTag->TerrainFrameY);
			}
			else {
				mines1To30Palette->frameRender(getMemDc(), _ptMouse.x, _ptMouse.y, mCurSelectTag->ObjectFrameX, mCurSelectTag->ObjectFrameY);
			}
		}
	}
}
