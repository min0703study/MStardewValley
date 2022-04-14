#include "Stdafx.h"
#include "MapPalette.h"

HRESULT MapPalette::init(void)
{
	LOG::d_blue("==============¸Ê ÆÈ·¹Æ® ÃÊ±âÈ­=====================");

	mBaseSpriteList[MS_MINE_1TO30] = GDIPLUSMANAGER->cloneImage(IMGCLASS->MapMines1To30);
	mBaseSpriteList[MS_OUTDOOR_SPRING] = GDIPLUSMANAGER->cloneImage(IMGCLASS->MapOutdoorSpring);
	mBaseSpriteList[MS_TOWN_INTERIOR] = GDIPLUSMANAGER->cloneImage(IMGCLASS->MapTownInterior);

	setTileInfo();

	for (int i = MS_MINE_1TO30; i < MS_END; i++) {
		int xCount = mBaseSpriteList[i]->getMaxFrameX() + 1;
		int yCount = mBaseSpriteList[i]->getMaxFrameY() + 1;

		mPallete[i] = new ImageGp*[yCount];

		for (int y = 0; y < yCount; y++) {
			mPallete[i][y] = new ImageGp[xCount];
		}

		for (int y = 0; y < yCount; y++) {
			for (int x = 0; x < xCount; x++) {
				mPallete[i][y][x].init(getMemDc(), mBaseSpriteList[i]->getFrameBitmap(x, y));
				mPallete[i][y][x].setSize(TILE_SIZE, TILE_SIZE);
			}
		}

		//»çÀÌÁî ¸ÂÃç¼­ ´Ù½Ã ¸¸µë
		Bitmap* rebuildBitmap = GDIPLUSMANAGER->getBlankBitmap(TILE_SIZE * xCount, TILE_SIZE * yCount);
		for (int x = 0; x < xCount; x++) {
			for (int y = 0; y < yCount; y++) {
				GDIPLUSMANAGER->combindBitmap(rebuildBitmap, mPallete[i][y][x].getBitmap(), x * TILE_SIZE, y * TILE_SIZE);
			}
		}

		mRebuildSpriteList[i] = new ImageGp;
		mRebuildSpriteList[i]->init(getMemDc(), rebuildBitmap, xCount * TILE_SIZE, yCount * TILE_SIZE, xCount, yCount);
	}


	return S_OK;
}

void MapPalette::setTileInfo(void)
{
	int index = 1;

	int xFrame = 0;
	int yFrame = 0;

	vector<tagTile*> vMines;
	//1
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));

	xFrame = 0;
	yFrame++;
	//2
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame)); //none
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));

	xFrame = 0;
	yFrame++;
	//3
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame)); //none
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));

	xFrame = 0;
	yFrame++;
	//4
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_OBJECT, xFrame++, yFrame));//
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_OBJECT, xFrame++, yFrame));//
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));

	xFrame = 0;
	yFrame++;
	//5
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));//
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));//
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //none
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //none

	xFrame = 0;
	yFrame++;
	//6
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));//
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));//
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //none

	xFrame = 0;
	yFrame++;
	//7
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));//
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));//
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));

	xFrame = 0;
	yFrame++;

	//8
	vMines.push_back(new tagTile(OBJ_MINE_DOOR, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_MINE_DOOR, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));

	xFrame = 0;
	yFrame++;
	//9
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //none
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //none
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));

	xFrame = 0;
	yFrame++;
	//10
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame)); //none
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));

	xFrame = 0;
	yFrame++;
	//11
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(TR_SAND, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));

	xFrame = 0;
	yFrame++;
	//12
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_TRAIN, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_TRAIN, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(TR_SAND, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_SAND, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));

	xFrame = 0;
	yFrame++;
	//13
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_TRAIN, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_TRAIN, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));

	xFrame = 0;
	yFrame++;
	//14
	vMines.push_back(new tagTile(OBJ_TRAIN, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_OBJECT, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));

	xFrame = 0;
	yFrame++;
	//15
	vMines.push_back(new tagTile(OBJ_TRAIN, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_OBJECT, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_OBJECT, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_OBJECT, xFrame++, yFrame, false, true));


	xFrame = 0;
	yFrame++;
	//16
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));//NONE
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //NONE



	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));//NONE
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //NONE

	xFrame = 0;
	yFrame++;
	//18
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame));//NONE
	vMines.push_back(new tagTile(TR_NORMAL, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame)); //NONE

	int spriteXCount = mBaseSpriteList[MS_MINE_1TO30]->getMaxFrameX() + 1;
	int spriteYCount = mBaseSpriteList[MS_MINE_1TO30]->getMaxFrameY() + 1;

	tagTile* mine = new tagTile[spriteXCount * spriteYCount];
	LoadFile<tagTile*>("Resources/Map/Palette/mine.map", mine, sizeof(tagTile) *  spriteXCount * spriteYCount);
	vector<tagTile*> vMine;
	for (int y = 0; y < spriteXCount * spriteYCount; y++) {
		vMine.push_back(new tagTile(mine[y]));
	}

	spriteXCount = mBaseSpriteList[MS_OUTDOOR_SPRING]->getMaxFrameX() + 1;
	spriteYCount = mBaseSpriteList[MS_OUTDOOR_SPRING]->getMaxFrameY() + 1;

	tagTile* outdoor = new tagTile[spriteXCount * spriteYCount];
	LoadFile<tagTile*>("Resources/Map/Palette/spring_outdoor.map", outdoor, sizeof(tagTile) *  spriteXCount * spriteYCount);
	vector<tagTile*> vOutdoor;
	for (int y = 0; y < spriteXCount * spriteYCount; y++) {
		vOutdoor.push_back(new tagTile(outdoor[y]));
	}


	spriteXCount = mBaseSpriteList[MS_TOWN_INTERIOR]->getMaxFrameX() + 1;
	spriteYCount = mBaseSpriteList[MS_TOWN_INTERIOR]->getMaxFrameY() + 1;

	tagTile* town = new tagTile[spriteXCount * spriteYCount];
	LoadFile<tagTile*>("Resources/Map/Palette/town_interior.map", town, sizeof(tagTile) *  spriteXCount * spriteYCount);
	vector<tagTile*> vTown;
	for (int y = 0; y < spriteXCount * spriteYCount; y++) {
		vTown.push_back(new tagTile(town[y]));
	}

	mVMapSprites.insert(make_pair(eMapSprite::MS_MINE_1TO30, vMine));
	mVMapSprites.insert(make_pair(eMapSprite::MS_OUTDOOR_SPRING, vOutdoor));
	mVMapSprites.insert(make_pair(eMapSprite::MS_TOWN_INTERIOR, vTown));
}

void MapPalette::release(void)
{
}

ImageGp* MapPalette::getBaseSprite(eMapSprite mapSprite)
{
	return mRebuildSpriteList[mapSprite];
}

ImageGp** MapPalette::getPalette(eMapSprite mapSprite)
{
	return mPallete[mapSprite];
}

HRESULT MapPalette::findTileNodeLIst(eMapSprite mapKey, OUT vector<tagTile*>& tagTiles)
{
	auto key = mVMapSprites.find(mapKey);

	if (key != mVMapSprites.end())
	{
		tagTiles = key->second;
		return S_OK;
	}

	return S_OK;
}

Bitmap* MapPalette::getBitmap(eMapSprite mapSprite, int startX, int startY, int xCount, int yCount)
{
	return mRebuildSpriteList[mapSprite]->getFrameBitmapToIndex(startX, startY, xCount, yCount);
}

