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

	const char* MapSpringSprite = "�� �� ��������Ʈ";
	const char* MapMines1To30 = "�� ���� 1������ 30������";
	
	const char* MapBtnEraser = "�� ���찳 ��ư";
	const char* MapBtnSelect = "�� ���� ��ư";
	const char* MapBtnNone = "�� �⺻ ��ư";
	const char* MapBtnSave = "�� ���� ��ư";
	const char* MapBtnLoad = "�� �ҷ����� ��ư";


	const char* PlayerSpriteMan= "���� ���� ��������Ʈ";
	const char* PlayerSpriteHair= "�Ӹ� ��������Ʈ";
	const char* PlayerSpriteCloth= "�� ��������Ʈ";

	const char* ToolSprite = "���� ��������Ʈ";
	const char* MineRockSprite = "���� ���� ��������Ʈ";
	const char* MonsterSprite = "���� ��������Ʈ";
	const char* WeaponSprite = "���� ��������Ʈ";

	const char* Toolbar = "���� �ϴ� ����";
	const char* Clock = "���� �ð�";
	const char* EnergeProgressBar = "���� ������ ���α׷��� ��";

	HRESULT init(void);
	virtual void release(void);
};

