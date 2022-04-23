#pragma once
#include "SingletonBase.h"

class SceneClass : public SingletonBase<SceneClass>
{
public:
	const char* LOAD = "load";
	const char* MINE = "mine";
	const char*	FARM = "farm";
};

