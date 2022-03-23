#pragma once
#include "SingletonBase.h"

class ImageClass: public SingletonBase<ImageClass>
{
public:
	const char* Cursor = "커서";
	const char* MenuBack = "메뉴 뒷 배경";
	const char* MenuBackCloud = "메뉴 뒷 배경 구름";
	const char* MenuBackLogo = "메뉴 로고";
	const char* MenuBtn = "메뉴 버튼";
	const char* MenuBtnMaptool = "메뉴 맵툴 버튼";
	const char* MenuBtnStart = "메뉴 시작 버튼";
	const char* MenuBtnExit = "메뉴 나가기 버튼";

	const char* UISetupBox = "게임 설정 상자";
	const char* UIScrollBtn = "게임 스크롤 바 버튼";
	const char* UIScrollBar = "게임 스크롤 바";

	const char* MapSpringSprite = "맵 봄 스프라이트";
	const char* MapSpringSpriteG = "맵 봄 스프라이트 png";
	const char* MapMines1To30 = "맵 광산 1층부터 30층까지";
	
	const char* MapBtnEraser = "맵 지우개 버튼";
	const char* MapBtnSelect = "맵 선택 버튼";


	HRESULT init(void);
	virtual void release(void);
};

