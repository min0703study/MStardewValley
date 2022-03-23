#include "Stdafx.h"
#include "MapToolScene.h"

#define SAMPLE_SCROLL_BOX_WIDTH		WINSIZE_X * 0.25f
#define SAMPLE_SCROLL_BOX_HEIGHT	WINSIZE_Y * 0.5f

#define WORK_SCROLL_BOX_WIDTH		WINSIZE_X * 0.75f
#define WORK_SCROLL_BOX_HEIGHT		WINSIZE_Y

HRESULT MapToolScene::init(void)
{
	mTileSize = 10;

	TILECLASS->findTileNodeLIst(IMGCLASS->MapMines1To30, mCurTagPalette);

	mSample = new GameUI;
	mSample->init("���� ���� ��ü", 0, 0, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapMines1To30));

	mSampleScrollBox = new ScrollBox;
	mSampleScrollBox->init("��ũ�� ���� ���� �ڽ�", 0, 0, SAMPLE_SCROLL_BOX_WIDTH, SAMPLE_SCROLL_BOX_HEIGHT, mSample);

	//�׸��� ����
	mBtnEraser = new SButton;
	mBtnEraser->init("���찳 ��ư", WINSIZE_X -100, 50, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapBtnEraser));

	mBtnSelect = new SButton;
	mBtnSelect->init("���� ��ư", WINSIZE_X - 200,50, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MapBtnSelect));

	//
	mWorkBoardScrollBox = new ScrollBox;
	mWorkBoardScrollBox->init("�۾� ���� ��ũ�� ����", SAMPLE_SCROLL_BOX_WIDTH, 0, WORK_SCROLL_BOX_WIDTH, WORK_SCROLL_BOX_HEIGHT, mSample);

	mWorkBoard = new GameUI;
	mWorkBoard->init("�۾� ���� ����", 0, 0, GDIPLUSMANAGER->findAndCloneImage(IMGCLASS->MenuBtn));


	return S_OK;
}

void MapToolScene::update(void)
{
	mSampleScrollBox->update();
	//mBtnEraser->update();
	//mBtnSelect->update();
	
	if (PtInRect(&mSampleScrollBox->getValueRECT(), _ptMouse)) {
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			float indexX = mSampleScrollBox->getValueRelX() + _ptMouse.x;
			float indexY = mSampleScrollBox->getValueRelY() + _ptMouse.y;

			MY_UTIL::log(DEBUG_ALL_TAG, "x : " + to_string(indexX) + " y : " + to_string(indexY));
		}
	}
}

void MapToolScene::release(void)
{
}

void MapToolScene::render(void)
{
	mSampleScrollBox->render();
	mBtnEraser->render();
	mBtnSelect->render();

	//mWorkBoardScrollBox->render();
}
