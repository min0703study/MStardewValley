#pragma once
#include "SingletonBase.h"

class ItemClass : public SingletonBase<ItemClass>
{
public:
	const char* WEAPON = "Ä®";
	const char* PICK = "°î±ªÀÌ";
	const char*	HOE = "È£¹Ì";
	const char*	AXE = "µµ³¢";
	const char*	WATERING_CAN = "¹°»Ñ¸®°³";

	const char*	PARSNIP_SEED = "ÆÄ½º´Õ ¾¾¾Ñ";
	const char*	PARSNIP = "ÆÄ½º´Õ ¿­¸Å";
	const char*	POTATO_SEED = "°¨ÀÚ ¾¾¾Ñ";
	const char*	POTATO = "°¨ÀÚ ¿­¸Å";
	const char* CAULIFLOWER = "ÄÝ¸®ÇÃ¶ó¿ö ¿­¸Å";
	const char* CAULIFLOWER_SEED = "ÄÝ¸®ÇÃ¶ó¿ö ¾¾¾Ñ";
	const char* BEEN = "Äá ¿­¸Å";
	const char* BEEN_SEED = "Äá ¾¾¾Ñ";

	const char* STONE_NORMAL = "ÀÏ¹Ý µ¹";
};

