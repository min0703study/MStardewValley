#include "Stdafx.h"
#include "MapToolScene.h"

#define SAMPLE_SCROLL_BOX_WIDTH		WINSIZE_X * 0.25f
#define SAMPLE_SCROLL_BOX_HEIGHT	WINSIZE_Y * 0.5f

#define WORK_SCROLL_BOX_WIDTH		WINSIZE_X * 0.75f
#define WORK_SCROLL_BOX_HEIGHT		WINSIZE_R_Y

HRESULT MapToolScene::init(void)
{
	mTileSize = 50.0f;

	mXWorkBoardCount = 50;
	mYWorkBoardCount = 50;

	TILECLASS->findTileNodeLIst(IMGCLASS->MapMines1To30, mCurTagPalette);

	mines1To30Palette = GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapMines1To30);

	float mines1To30PaletteW = mines1To30Palette->getMaxFrameX() * mTileSize;
	float mines1To30PaletteH = mines1To30Palette->getMaxFrameY() * mTileSize;

	//타일 팔레트
	mTilePalette = new GameUI;
	mTilePalette->init("샘플 파일 객체", 0, 0, mines1To30PaletteW, mines1To30PaletteH, mines1To30Palette);

	mTilePaletteScrollBox = new ScrollBox;
	mTilePaletteScrollBox->init("스크롤 샘플 파일 박스", 0, 0, SAMPLE_SCROLL_BOX_WIDTH, SAMPLE_SCROLL_BOX_HEIGHT, mTilePalette, XS_LEFT, YS_TOP);

	//그리기 도구
	mBtnEraser = new SButton;
	mBtnEraser->init("지우개 버튼", WINSIZE_X -100, 50, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapBtnEraser));

	mBtnSelect = new SButton;
	mBtnSelect->init("선택 버튼", WINSIZE_X - 200,50, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapBtnSelect));

	//작업 영역
	mWorkBoard = new GameUI;
	mWorkBoard->init("작업 영역 상자", 0, 0, mTileSize * mXWorkBoardCount, mTileSize * mYWorkBoardCount);
	GDIPLUSMANAGER->drawGridLine(mWorkBoard->getImgGp(), mTileSize, mTileSize);

	mWorkBoardScrollBox = new ScrollBox;
	mWorkBoardScrollBox->init("작업 영역 스크롤 상자", SAMPLE_SCROLL_BOX_WIDTH, 0, WORK_SCROLL_BOX_WIDTH, WORK_SCROLL_BOX_HEIGHT, mWorkBoard, XS_LEFT, YS_TOP);

	mCurTagImg = new ImageGp;
	mCurTagImg->init(getMemDc(), mTileSize, mTileSize);

	for (int x = 0; x < mXWorkBoardCount; x++)
	{
		for (int y = 0; y < mYWorkBoardCount; y++) {
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
	
	//맵 팔레트 충돌 검사
	if (PtInRect(&mTilePaletteScrollBox->getRECT(), _ptMouse)) {
		mTilePaletteScrollBox->mouseOverEvent();

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			mTilePaletteScrollBox->clickDownEvent();

			int indexX = mTilePaletteScrollBox->getValueRelXToX(_ptMouse.x) / mTileSize;
			int indexY = mTilePaletteScrollBox->getValueRelYToY(_ptMouse.y) / mTileSize;

			int t = indexX + (indexY * mines1To30Palette->getMaxFrameX());
			
			mCurSelectTag = mCurTagPalette[t];
			mCurSelectBitmap = mines1To30Palette->getFrameBitmap(mCurSelectTag->TerrainFrameX, mCurSelectTag->TerrainFrameY);
			mCurTagImg->addBitmap(
				0, 0,
				mCurSelectBitmap
			);

			mCurTagImg->rebuildChachedBitmap();
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
				int realPtY = mWorkBoardScrollBox->getValueRelYToY(_ptMouse.y);

				if (PtInRect(&(*iRect), { realPtX, realPtY })) {
					mWorkBoard->getImgGp()->addBitmap(
						(*iRect).left,
						(*iRect).top,
						mCurSelectBitmap
					);

					mWorkBoardScrollBox->clipingContentArea();
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

	GDIPLUSMANAGER->render(mCurTagImg, _ptMouse.x, _ptMouse.y);
}
