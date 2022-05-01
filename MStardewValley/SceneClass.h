#pragma once
#include "SingletonBase.h"

class SceneClass : public SingletonBase<SceneClass>
{
public:
	const char* LOAD = "load_1";
	const char* MINE = "mine";
	const char*	FARM = "farm";
	const char*	SHOP = "shop";
	const char*	HOME = "home";
	const char*	TOWN = "town";

	const char*	MAPTOOL = "maptool";
	const char*	START = "start";
};

