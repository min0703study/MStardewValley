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
	vMines.push_back(new tagTile(TR_NORMAL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(TR_NORMAL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(TR_NORMAL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(TR_NORMAL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));

	xFrame = 0;
	yFrame++;
	//2
	vMines.push_back(new tagTile(TR_NORMAL,	 xFrame++	,yFrame )); //none
	vMines.push_back(new tagTile(TR_NORMAL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(TR_NORMAL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(TR_NORMAL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));

	xFrame = 0;
	yFrame++;
	//3
	vMines.push_back(new tagTile(TR_NORMAL,	 xFrame++	,yFrame )); //none
	vMines.push_back(new tagTile(TR_NORMAL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(TR_NORMAL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(TR_NORMAL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++	,yFrame ));

	xFrame = 0;
	yFrame++;
	//4
	vMines.push_back(new tagTile(OBJ_LIGHT,	 xFrame++ ,yFrame ));
	vMines.push_back(new tagTile(OBJ_NORMAL, xFrame++ ,yFrame ));//
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++ ,yFrame ));
	vMines.push_back(new tagTile(OBJ_NORMAL, xFrame++ ,yFrame ));//
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++ ,yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++ ,yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++ ,yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++ ,yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++ ,yFrame, false, true));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++ ,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++ ,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++ ,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++ ,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++ ,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++ ,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	 xFrame++ ,yFrame ));

	xFrame = 0;
	yFrame++;
	//5
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_LIGHT,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_LIGHT,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++	,yFrame ));//
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++	,yFrame ));//
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++	,yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++	,yFrame )); //none
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++	,yFrame )); //none

	xFrame = 0;
	yFrame++;
	//6
	vMines.push_back(new tagTile(OBJ_LIGHT,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_LIGHT,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_LIGHT,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));//
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));//
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame ));
	vMines.push_back(new tagTile(OBJ_WALL,	xFrame++, yFrame )); //none

	xFrame = 0;
	yFrame++;
	//7
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_LIGHT, xFrame++, yFrame));
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
	vMines.push_back(new tagTile(OBJ_DOOR, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_LIGHT, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_WALL, xFrame++, yFrame));
	vMines.push_back(new tagTile(OBJ_DOOR, xFrame++, yFrame, false, true));
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
	vMines.push_back(new tagTile(OBJ_DOOR, xFrame++, yFrame, false, true));
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
