#pragma once
#include "SingletonBase.h"

class ItemClass : public SingletonBase<ItemClass>
{
public:
	const char* WEAPON = "Ä®";
	const char* PICK = "°î±ªÀÌ";
	const char*	HOE = "È£¹Ì";
	const char*	AXE = "µµ³¢";
	const char*	WATERING_CAN = "¹°»Ñ¸®°Ô";

	const char*	PARSNIP_SEED = "ÆÄ½º´Õ ¾¾¾Ñ";
	const char*	PARSNIP = "ÆÄ½º´Õ";
	const char*	POTATO_SEED = "°¨ÀÚ ¾¾¾Ñ";
	const char*	PATATO = "°¨ÀÚ";
	const char* CAULIFLOWER = "ÄÝ¸®ÇÃ¶ó¿ö";
	const char* CAULIFLOWER_SEED = "ÄÝ¸®ÇÃ¶ó¿ö ¾¾¾Ñ";
	const char* BEEN = "Äá";
	const char* BEEN_SEED = "Äá ¾¾¾Ñ";


	HRESULT init(void);
	virtual void release(void);
};

