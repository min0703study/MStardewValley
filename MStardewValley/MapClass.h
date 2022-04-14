#pragma once
#include "SingletonBase.h"

class MapClass: public SingletonBase<MapClass>
{
public:
	const char* MINE_1 = "mine_1";
	const char* MINE_2 = "mine_2";
	const char*	FARM = "farm";
	const char*	Shop = "shop";
	const char*	HOME = "home";

	//ÆÈ·¹Æ®
	const char* MINE_P = "±¤»ê ÆÈ·¹Æ®";
	const char* OUTDOOR_P = "¿ÜºÎ ÆÈ·¹Æ®";
	const char* TOWN_INTERIOR_P = "¸¶À» ÆÈ·¹Æ®";

	HRESULT init(void);
	void release(void);
};

