#pragma once
#include "SingletonBase.h"

class ItemClass : public SingletonBase<ItemClass>
{
public:
	//µµ±¸
	const char* PICK = "°î±ªÀÌ";
	const char*	HOE = "È£¹Ì";
	const char*	AXE = "µµ³¢";
	const char*	WATERING_CAN = "¹°»Ñ¸®°³";
	const char*	SICKLE = "³´";

	//¹«±â
	const char* WEAPON = "³ì½¼ °Ë";
	const char* WOODEN_BLADE = "¸ñµµ";
	const char* IRON_DIRCT = "Ã¶ ´õÅ©";
	const char* PIRATES_SWORD = "ÇØÀûÀÇ °Ë";
	const char* WOOD_MALLET = "³ª¹« ¸ÁÄ¡";
	const char* BONE_SWORD = "»ÀÀÇ °Ë";
	const char* INSECT_HEAD = "°ïÃæ ¸Ó¸®";

	//¾¾¾Ñ
	const char*	PARSNIP_SEED = "ÆÄ½º´Õ ¾¾¾Ñ";
	const char*	PARSNIP = "ÆÄ½º´Õ ¿­¸Å";
	const char*	POTATO_SEED = "°¨ÀÚ ¾¾¾Ñ";
	const char*	POTATO = "°¨ÀÚ ¿­¸Å";
	const char* CAULIFLOWER = "ÄÝ¸®ÇÃ¶ó¿ö ¿­¸Å";
	const char* CAULIFLOWER_SEED = "ÄÝ¸®ÇÃ¶ó¿ö ¾¾¾Ñ";
	const char* BEEN = "Äá ¿­¸Å";
	const char* BEEN_SEED = "Äá ¾¾¾Ñ";
	
	//ÀÚ¿ø
	const char* WOOD = "³ª¹« °¡Áö";
	const char* FIBER = "¼¶À¯";
	const char* STONE_NORMAL = "ÀÏ¹Ý µ¹";

	//±¤¼®
	const char* IRON = "Ã¶±¤¼®";
	const char* GOLD = "±Ý±¤¼®";
	const char* COPPER = "±¸¸®±¤¼®";
	const char* COAL = "¼®Åº";

	//ÁÖ±«
	const char* IRON_BAR = "Ã¶ ÁÖ±«";
	const char* GOLD_BAR = "±Ý ÁÖ±«";
	const char* COPPER_BAR = "±¸¸® ÁÖ±«";

	//
	const char* FURNACE = "¿ë±¤·Î";
};

