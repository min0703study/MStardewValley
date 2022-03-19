#include "Stdafx.h"
#include "MapToolScene.h"

#define SAMPLE_SCROLL_BOX_WIDTH		WINSIZE_X * 0.25f
#define SAMPLE_SCROLL_BOX_HEIGHT	WINSIZE_Y * 0.5f

#define WORK_SCROLL_BOX_WIDTH		WINSIZE_X * 0.75f
#define WORK_SCROLL_BOX_HEIGHT		WINSIZE_Y

HRESULT MapToolScene::init(void)
{
	mSample = new GameUI;
	mSample->init("»ùÇÃ ÆÄÀÏ °´Ã¼", IMGCLASS->MapSpringSpriteG, 0, 0, true);

	mSampleScrollBox = new ScrollBox;
	mSampleScrollBox->init("½ºÅ©·Ñ »ùÇÃ ÆÄÀÏ ¹Ú½º", IMGCLASS->UISetupBox, 0, 0, true, SAMPLE_SCROLL_BOX_WIDTH, SAMPLE_SCROLL_BOX_HEIGHT, mSample);

	mWork = new GameUI;
	mWork->init("»ùÇÃ ÆÄÀÏ °´Ã¼", IMGCLASS->MenuBtn, 0, 0, true);

	mWorkScrollBox = new ScrollBox;
	mWorkScrollBox->init("½ºÅ©·Ñ »ùÇÃ ÆÄÀÏ ¹Ú½º", IMGCLASS->UISetupBox, SAMPLE_SCROLL_BOX_WIDTH, 0, true, WORK_SCROLL_BOX_WIDTH, WORK_SCROLL_BOX_HEIGHT, mSample);

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
