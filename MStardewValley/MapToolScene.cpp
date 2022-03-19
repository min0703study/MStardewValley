#include "Stdafx.h"
#include "MapToolScene.h"

#define SAMPLE_SCROLL_BOX_WIDTH		WINSIZE_X * 0.25f
#define SAMPLE_SCROLL_BOX_HEIGHT	WINSIZE_Y * 0.5f

#define WORK_SCROLL_BOX_WIDTH		WINSIZE_X * 0.75f
#define WORK_SCROLL_BOX_HEIGHT		WINSIZE_Y

HRESULT MapToolScene::init(void)
{
	mSample = new GameUI;
	mSample->init("基敲 颇老 按眉", IMGCLASS->MapSpringSpriteG, 0, 0, true);

	mSampleScrollBox = new ScrollBox;
	mSampleScrollBox->init("胶农费 基敲 颇老 冠胶", IMGCLASS->UISetupBox, 0, 0, true, SAMPLE_SCROLL_BOX_WIDTH, SAMPLE_SCROLL_BOX_HEIGHT, mSample);

	mWork = new GameUI;
	mWork->init("基敲 颇老 按眉", IMGCLASS->MenuBtn, 0, 0, true);

	mWorkScrollBox = new ScrollBox;
	mWorkScrollBox->init("胶农费 基敲 颇老 冠胶", IMGCLASS->UISetupBox, SAMPLE_SCROLL_BOX_WIDTH, 0, true, WORK_SCROLL_BOX_WIDTH, WORK_SCROLL_BOX_HEIGHT, mSample);

	return S_OK;
}

void MapToolScene::update(void)
{
	mSampleScrollBox->update();
	mWorkScrollBox->update();
}

void MapToolScene::release(void)
{
}

void MapToolScene::render(void)
{
	mSampleScrollBox->render();
	mWorkScrollBox->render();
}
