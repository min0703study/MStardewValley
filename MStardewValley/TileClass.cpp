#include "Stdafx.h"
#include "TileClass.h"

HRESULT TileClass::init(void)
{
	//±¤»ê 1
	int index = 1;
	int xFrame = 0;
	int yFrame = 0;
	vector<tagTile*> vMines;
	//1
	vMines.push_back(new tagTile(TR_NORMAL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(TR_NORMAL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(TR_NORMAL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(TR_NORMAL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));

	xFrame = 0;
	yFrame++;
	//2
	vMines.push_back(new tagTile(TR_NORMAL,		index++,	xFrame++	,yFrame )); //none
	vMines.push_back(new tagTile(TR_NORMAL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(TR_NORMAL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(TR_NORMAL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));

	xFrame = 0;
	yFrame++;
	//3
	vMines.push_back(new tagTile(TR_NORMAL,		index++,	xFrame++	,yFrame )); //none
	vMines.push_back(new tagTile(TR_NORMAL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(TR_NORMAL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(TR_NORMAL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));

	xFrame = 0;
	yFrame++;
	//4
	vMines.push_back(new tagTile(OBJ_LIGHT,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_NORMAL,	index++,	xFrame++	,yFrame , false, true));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_NORMAL,	index++,	xFrame++	,yFrame , false, true));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame , true, false));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame , true, false));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame , true, false));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame , true, false));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame , true, false));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));

	xFrame = 0;
	yFrame++;
	//5
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_LIGHT,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_LIGHT,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_DOOR,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame )); //none
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame )); //none

	xFrame = 0;
	yFrame++;
	//6
	vMines.push_back(new tagTile(OBJ_LIGHT,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_LIGHT,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_LIGHT,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_DOOR,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,		index++,	xFrame++	,yFrame )); //none

	xFrame = 0;
	yFrame++;
	//7
	vMines.push_back(new tagTile(OBJ_DOOR, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_LIGHT, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_DOOR, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));

	xFrame = 0;
	yFrame++;

	//8
	vMines.push_back(new tagTile(OBJ_DOOR, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_LIGHT, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_DOOR, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));

	xFrame = 0;
	yFrame++;
	//9
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame)); //none
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame)); //none
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));

	xFrame = 0;
	yFrame++;
	//10
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame)); //none
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));

	xFrame = 0;
	yFrame++;
	//11
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(TR_SAND, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_DOOR, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));

	xFrame = 0;
	yFrame++;
	//12
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_TRAIN, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_TRAIN, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(TR_SAND, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_SAND, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));

	xFrame = 0;
	yFrame++;
	//13
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_TRAIN, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_TRAIN, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));

	xFrame = 0;
	yFrame++;
	//14
	vMines.push_back(new tagTile(OBJ_TRAIN, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_OBJECT, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));

	xFrame = 0;
	yFrame++;
	//15
	vMines.push_back(new tagTile(OBJ_TRAIN, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_OBJECT, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_OBJECT, index++, xFrame++, yFrame, true, false));
	vMines.push_back(new tagTile(OBJ_OBJECT, index++, xFrame++, yFrame, true, false));


	xFrame = 0;
	yFrame++;
	//16
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));//NONE
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame)); //NONE



	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));//NONE
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame)); //NONE

	xFrame = 0;
	yFrame++;
	//18
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_WATER, index++, xFrame++, yFrame));
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame));//NONE
	vMines.push_back(new tagTile(TR_NORMAL, index++, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame)); //NONE
	vMines.push_back(new tagTile(OBJ_WALL, index++, xFrame++, yFrame)); //NONE

	mVMapSprites.insert(make_pair(IMGCLASS->MapMines1To30, vMines));

	return S_OK;
}

void TileClass::release(void)
{
}

HRESULT TileClass::findTileNodeLIst(string strKey, OUT vector<tagTile*>& tagTiles)
{
	auto key = mVMapSprites.find(strKey);

	if (key != mVMapSprites.end())
	{
		tagTiles = key->second;
		return S_OK;
	}

	return E_FAIL;
}
