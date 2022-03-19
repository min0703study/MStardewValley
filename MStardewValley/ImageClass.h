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
	const char* UIScrollBtn = "���� ��ũ�� �� ��ư";
	const char* UIScrollBar = "���� ��ũ�� ��";

	const char* MapSpringSprite = "�� �� ��������Ʈ";
	const char* MapSpringSpriteG = "�� �� ��������Ʈ png";
	
	HRESULT init(void);
	virtual void release(void);
};

