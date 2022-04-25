#pragma once
#include "SingletonBase.h"

class MapClass: public SingletonBase<MapClass>
{
public:
	const char* MINE_1 = "mine_1";
	const char* MINE_2 = "mine_2";
	const char*	FARM = "farm";
	const char*	SHOP_SEED = "shop";
	const char*	HOME = "home";
	const char* TOWN = "town";
	const char* LOAD = "load_1";
	const char*	SHOP_WEAPON = "shop_weapon";

	//ÆÈ·¹Æ®
	const char* MINE_P = "±¤»ê ÆÈ·¹Æ®";
	const char* OUTDOOR_P = "¿ÜºÎ ÆÈ·¹Æ®";
	const char* TOWN_INTERIOR_P = "¸¶À» ÆÈ·¹Æ®";

	HRESULT init(void);
	void release(void);
};

