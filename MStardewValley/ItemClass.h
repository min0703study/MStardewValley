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

	HRESULT init(void);
	virtual void release(void);
};

