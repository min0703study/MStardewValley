#pragma once
#include "SingletonBase.h"

class ImageClass: public SingletonBase<ImageClass>
{
public:
	const char* Cursor = "Ŀ��";
	const char* MenuBack = "�޴� �� ���";
	const char* MenuBackCloud = "�޴� �� ��� ����";
	const char* MenuBackLogo = "�޴� �ΰ�";
	const char* MenuBtn = "�޴� ��ư";
	const char* MenuBtnMaptool = "�޴� ���� ��ư";
	const char* MenuBtnStart = "�޴� ���� ��ư";
	const char* MenuBtnExit = "�޴� ������ ��ư";

	const char* UISetupBox = "���� ���� ����";

	const char* UIVScrollBtn = "���� ��ũ�� �� ��ư";
	const char* UIVScrollBar = "���� ��ũ�� ��";

	const char* UIHScrollBtn = "���� ��ũ�� �� ��ư";
	const char* UIHScrollBar = "���� ��ũ�� ��";

	const char* MapOutdoorSpring = "�� �� ��������Ʈ";
	const char* MapMines1To30 = "�� ���� 1������ 30������ ��������Ʈ";
	const char* MapTownInterior = "���� ���׸��� ��������Ʈ";
	
	const char* MapBtnEraser = "���� ���찳 ��ư";
	const char* MapBtnSelect = "���� ���� ��ư";
	const char* MapBtnNone = "���� �⺻ ��ư";
	const char* MapBtnSave = "���� ���� ��ư";
	const char* MapBtnBack = "���� �ڷΰ��� ��ư";
	const char* MapBtnLoad = "���� �ҷ����� ��ư";
	const char* MapBtnCollision = "���� �浹 ��ư";
	const char* MapBtnMovable = "���� ������ �� �ִ� ��ư";
	const char* MapBtnObjectGroup = "����  ������Ʈ ���� ��ư";
	const char* MapBtnSelectMine = "���� - ���� �ȷ�Ʈ ���� ��ư";
	const char* MapBtnSelectFarm = "���� - ���� �ȷ�Ʈ ���� ��ư";
	const char* MapBtnSelectInterior = "���� - ���׸��� �ȷ�Ʈ ���� ��ư";

	const char* PlayerSpriteMan= "���� ���� ��������Ʈ";
	const char* PlayerSpriteHair= "�Ӹ� ��������Ʈ";
	const char* PlayerSpriteCloth= "�� ��������Ʈ";

	const char* ToolSprite = "���� ��������Ʈ";
	const char* MineRockSprite = "���� ���� ��������Ʈ";
	const char* MinesItemSprite = "���� ������ ��������Ʈ";
	const char* MonsterSprite = "���� ��������Ʈ";
	const char* WeaponSprite = "���� ��������Ʈ";

	const char* Toolbar = "���� �ϴ� ����";
	const char* Clock = "���� �ð�";
	const char* EnergePGBarF = "������ ������ �� Front";
	const char* EnergePGBarB = "������ ������ �� Back";
	const char* InventoryBox = "�κ��丮 ����";
	const char* InventoryRadioBtn = "�κ��丮 ���� ��ư";
	const char* CraftRadioBtn = "���� ���� ��ư";
	const char* MoneyBoard = "�� �����";
	const char* CropsSeedSprite = "�۹� ���� ��������Ʈ";
	const char* CropsStageSprite = "�۹� ��ȭ ��������Ʈ";
	const char* HoedSprite = "������ �� �� ��������Ʈ";
	const char* ForageSprite = "forage ��������Ʈ";
	const char* WeedSprite = "���� ��������Ʈ";

	const char* ShopMenuItem = "���� �޴� ����Ʈ ������";

	const char* NpcSpritePierreP = "�ǿ��� �ʻ�ȭ ��������Ʈ";
	const char* NpcSpritePierreA = "�ǿ��� �׼� ��������Ʈ";


	const char* NpcSpriteMarlonP = "���� �ʻ�ȭ ��������Ʈ";
	const char* NpcSpriteMarlonA = "���� �׼� ��������Ʈ";

	const char* ItemInfoName = "������ �̸�";
	const char* ItemInfoContent = "������ ������";
	const char* ItemInfoEnd = "������ ��";

	const char* EventBox = "������ ��� ǥ��";

	const char* EffectSprite = "ȿ�� �ִϸ��̼� ��������Ʈ";
	const char* CraftablesSprite = "�������� ��������Ʈ";
	const char* WeaponIcon = "���� ������";

	const char* TileSize = "Ÿ�� ������";
	const char* FuranceOverEvent = "�뱤�� �۾� ���� �̺�Ʈ ��ǳ��";
	const char* QuestionBox = "���� ����";

	HRESULT init(void);
	virtual void release(void);
};

